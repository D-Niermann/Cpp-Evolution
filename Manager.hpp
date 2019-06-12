
class Manager
{
	protected:

		Creature* best_creature;
		float av_score;

	public:
		// creatures
		std::vector<Creature> creatures;
		// food 
		std::vector<Food> food;
		// hunters
		std::vector<Hunter> hunters;
	
	



		// add class to given array
		template < class T >
		void addWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture, sf::Font& font)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.emplace_back( T(texture, random(0+m,config::WINDOW_X-m), random(0+m,config::WINDOW_Y-m), font) );
			}
		}
		// overload with load id that tells what file to load the NN from
		template < class T >
		void addWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture, sf::Font& font, const std::string& load_id)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.emplace_back( T(texture, random(0+m,config::WINDOW_X-m), random(0+m,config::WINDOW_Y-m), font, load_id) );
			}
		}



		template < class T >
		void reproduceWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture, sf::Font& font, T* parent)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.emplace_back( T(texture, parent->getPos().x, parent->getPos().y, font, parent) );
			}
		}


		void updateAll(const int& frame)
		{
			// updates all creatures
			for(int i = 0; i<creatures.size(); i++){
				creatures[i].update();
			}
			// updates all food
			for(int i = 0; i<food.size(); i++){
				food[i].update();
			}
			// updates all hunters
			for(int i = 0; i<hunters.size(); i++){
				hunters[i].update();
			}
			
			if (frame%5 == 0)
				CollisionCheckAndInput(creatures, food);
				CollisionCheckAndInput(hunters, creatures);

		}

		// calc the distance and collision between v1 to v2, give NN inputs to v1 where v2 is the food source 
		template <typename T1, typename T2>
		void CollisionCheckAndInput(std::vector<T1>& v1, std::vector<T2>& v2)
		{
			float dist_i;
			float best_score = 0;
			
			NN_Input creature_input;
			position diff_vector;

			float angle;
			av_score = 0;
			
			// go through all creatures and food and if distance is below threshold destroy food and call creature[i].eat()
			for(int i = 0; i<v1.size(); i++)
			{
				
				// creature loop	
				float closest_distance = 10000;
				int save_j = -1;

				// update collection vars
				av_score += v1[i].getScore();
				
				for (int j = 0; j<v2.size(); j++)
				{
					// food loop
					
					// calc distance to food j
					dist_i = sqrt(pow(v1[i].getPos().x - v2[j].getPos().x, 2) + pow(v1[i].getPos().y - v2[j].getPos().y, 2));
					
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = v1[i].getPos().x - v2[j].getPos().x;
					diff_vector.y = v1[i].getPos().y - v2[j].getPos().y;
					angle = angle_in_deg(diff_vector,-v1[i].getV_e());

					// collision check to food j
					if (dist_i < config::creatureFoodReach)
					{
						v1[i].eat();
						v2.erase(v2.begin()+j);
					}


					// check if seen food is food j
					if (std::abs(angle)< 90 && dist_i<closest_distance){
						closest_distance = dist_i;
						save_j = j;
					}


				} // all food looped through and closest seeable food found

				// give input to creature i from closest see-able food source save_j
				if (save_j!=-1)
				{
					// calc distance to food j
					// dist_i = pow(creatures[i].getPos().x - food[save_j].getPos().x, 2) + pow(creatures[i].getPos().y - food[save_j].getPos().y, 2);
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = v1[i].getPos().x - v2[save_j].getPos().x;
					diff_vector.y = v1[i].getPos().y - v2[save_j].getPos().y;
					angle = vec_angle_in_deg(diff_vector.x, diff_vector.y);

					// set creature vertex 
					v1[i].vertices[0] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0,0));
					v1[i].vertices[1] = sf::Vertex(sf::Vector2f(  v2[save_j].getPos().x, v2[save_j].getPos().y), sf::Color(255,0,0));

					// give input
					creature_input.angle = angle_in_deg(diff_vector,-v1[i].getV_e());
					creature_input.dist = dist_i;
					v1[i].giveInput(creature_input);

				}
				else
				{
					// no plant visible
					// set creature vertex 
					v1[i].vertices[0] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0,0));
					v1[i].vertices[1] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0));

					creature_input.angle = 0;
					creature_input.dist = 100000;
					v1[i].giveInput(creature_input);
				}

				if (v1[i].getScore()>best_score)
				{
					best_creature = &v1[i];
					best_score = v1[i].getScore();
				}
	
			}
			av_score = av_score/creatures.size();
		}
		
		// depricated, culls all creatures in v that are below an score threshold so that the MAX_creatures count is reached again
		template <typename T>
		void cull(std::vector<T>& v)
		{
			// get all scores
			std::vector<float> scores;
			float threshold;
			unsigned int cull_count;

			for (const T& item : v){
				scores.push_back(item.getScore());
			
			}
			// sort the vector
			std::sort(scores.begin(),scores.end());
		
			// calc the threshold value
			cull_count = v.size() - config::MAX_CREATURES;
			threshold = scores[cull_count];	
			print(threshold,"Culling below");

			// if score below threshold erase the creatue
			for (int i = 0; i < v.size(); i++){
				if (v[i].getScore() <= threshold){
					v.erase(v.begin()+i);
				}
			}
		}

		// cleans all corpses (deletes them), if creature count is less than Min creatures , respawn them instead
		template <typename T>
		void cleanDeads(std::vector<T>& container){
			int min_worldObj;
			std::string type_name = typeid(container[0]).name();

			if (type_name.find("Creature")!=std::string::npos){
				min_worldObj = config::MIN_CREATURES;	
			}
			else if (type_name.find("Hunter")!=std::string::npos){
				min_worldObj = config::S_HUNTERS;
			}

			for (int i = 0; i<container.size(); i++){
				if (!container[i].isAlive())
				{
					if (min_worldObj < container.size()){
						container.erase(container.begin()+i);
					}
					else{
						container[i].respawn(randomPositionInWindow());
					}
				}
			}
		}
		
		void reproduceCreatures(sf::Texture& texture, sf::Font& font)
		{
			if (creatures.size()<config::MIN_CREATURES){
				addWorldObject<Creature>(2, creatures, texture, font);
			}
			for(int i = 0; i<creatures.size(); i++)
			{
				if (creatures[i].getLifetime()%config::REPRO_TIME_CREATURES==0 && creatures[i].getLifetime()>0 && creatures[i].getHealth()>0.85)
				{
					reproduceWorldObject<Creature>(1,creatures, texture, font, &creatures[i]);
				}
			}
			// if (creatures.size() > config::MAX_CREATURES)
			// 	cull(creatures);
			cleanDeads(creatures);
		}

		void reproduceHunters(sf::Texture& texture, sf::Font& font)
		{
			for(int i = 0; i<hunters.size(); i++)
			{
				if (hunters[i].getLifetime()%config::REPRO_TIME_HUNTERS==0 && hunters[i].getLifetime()>0 && hunters[i].getHealth()>0.85)
				{
					reproduceWorldObject<Hunter>(1,hunters, texture, font, &hunters[i]);
				}
			}
			// if (hunters.size() > config::MAX_CREATURES)
			// 	cull(hunters);
			cleanDeads(hunters);
		}

		void reproduceFood(sf::Texture& texture, sf::Font& font){
			float x,y;
			if (food.size()<config::S_FOOD){
				addWorldObject<Food>(2, food, texture, font);
			}
			for(int i = 0; i<food.size(); i++){
				if (food[i].getLifetime()%config::REPRO_TIME_FOOD==0 && food[i].getLifetime()>0 && food.size()<config::MAX_FOOD && randomInt(0,3)==0){
					reproduceWorldObject<Food>(1,food,texture, font, &food[i]);
				}
			}
		}

		const Creature* getBestCreature(){
			return best_creature;
		}

		const float& getAvHealth(){
			::print(av_score);
			return av_score;
		}
		
		~Manager()
		{
			if (config::DO_SAVE)
				if (
					(*best_creature).getNN().save(best_creature->getID(),config::SAVE_PATH)
					)
					print("Saved best Neural Network!");

				// save best hunter
		}

};