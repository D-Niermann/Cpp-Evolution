
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
			
			if (frame%5 == 0)
				CollisionCheckAndCreatureInput();

		}

		void CollisionCheckAndCreatureInput()
		{
			float square_dist_i;
			float best_score = 0;
			NN_Input creature_input;
			position diff_vector;
			float angle;
			
			// go through all creatures and food and if distance is below threshold destroy food and call creature[i].eat()
			for(int i = 0; i<creatures.size(); i++){
				// creature loop	
				float closest_distance = 10000;
				int save_j = -1;

				// update collection vars
				av_score += creatures[i].getScore();
				
				for (int j = 0; j<food.size(); j++){
					// food loop
					// calc distance to food j
					square_dist_i = pow(creatures[i].getPos().x - food[j].getPos().x, 2) + pow(creatures[i].getPos().y - food[j].getPos().y, 2);
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = creatures[i].getPos().x - food[j].getPos().x;
					diff_vector.y = creatures[i].getPos().y - food[j].getPos().y;
					angle = angle_in_deg(diff_vector,-creatures[i].getV_e());
					// collision check to food j
					if (std::sqrt(square_dist_i) < config::creatureFoodReach)
					{
						creatures[i].eat();
						food[j].respawn(randomPositionInWindow());
					}

					// check if closest food is food j
					if (std::abs(angle)< 90 && std::sqrt(square_dist_i)<closest_distance){
						closest_distance = std::sqrt(square_dist_i);
						save_j = j;
					}


				}

				// give input to creature i from closest food source save_j
				if (save_j!=-1){
					// calc distance to food j
					square_dist_i = pow(creatures[i].getPos().x - food[save_j].getPos().x, 2) + pow(creatures[i].getPos().y - food[save_j].getPos().y, 2);
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = creatures[i].getPos().x - food[save_j].getPos().x;
					diff_vector.y = creatures[i].getPos().y - food[save_j].getPos().y;
					angle = vec_angle_in_deg(diff_vector.x, diff_vector.y);

					// set creature vertex 
					creatures[i].vertices[0] = sf::Vertex(sf::Vector2f(  creatures[i].getPos().x,  creatures[i].getPos().y), sf::Color(255,0,0,0));
					creatures[i].vertices[1] = sf::Vertex(sf::Vector2f(  food[save_j].getPos().x, food[save_j].getPos().y), sf::Color(255,0,0));

					creature_input.angle = angle_in_deg(diff_vector,-creatures[i].getV_e());
					creature_input.dist = std::sqrt(square_dist_i);
					creatures[i].giveInput(creature_input);
				}
				else
				{
					// no plant visible
					// set creature vertex 
					creatures[i].vertices[0] = sf::Vertex(sf::Vector2f(  creatures[i].getPos().x,  creatures[i].getPos().y), sf::Color(255,0,0,0));
					creatures[i].vertices[1] = sf::Vertex(sf::Vector2f(  creatures[i].getPos().x,  creatures[i].getPos().y), sf::Color(255,0,0));

					creature_input.angle = 0;
					creature_input.dist = 100000;
					creatures[i].giveInput(creature_input);
				}

				if (creatures[i].getScore()>best_score){
					best_creature = &creatures[i];
					best_score = creatures[i].getScore();
				}

			av_score = av_score/creatures.size();
				
				
			}
		}
		
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
		
		void reproduceCreatures(sf::Texture& texture, sf::Font& font)
		{
			for(int i = 0; i<creatures.size(); i++)
			{
				if (creatures[i].getLifetime()%config::REPRO_TIME==0 && creatures[i].getLifetime()>0)
				{
					reproduceWorldObject<Creature>(1,creatures, texture, font, &creatures[i]);
				}
			}
			if (creatures.size() > config::MAX_CREATURES)
				cull(creatures);
		}

		void reproduceFood(sf::Texture& texture, sf::Font& font){
			float x,y;
			for(int i = 0; i<food.size(); i++){
				int rng = (int)random(-20,20);
				if (food[i].getLifetime()%60+rng==0 && food[i].getLifetime()>0){
					addWorldObject<Food>(1,food,texture, font);
				}
			}
		}

		const Creature* getBestCreature(){
			return best_creature;
		}

		const float& getAvHealth(){
			return av_score;
		}
		
		~Manager()
		{
			
			if ((*best_creature).getNN().save(best_creature->getID(),config::SAVE_PATH))
			 print("Saved best Neural Network!");
		}

};