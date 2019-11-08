
class Manager
{
	protected:

		// Creature* best_creature;
		int best_creature_id;
		float av_score;
	public:
		// creatures
		std::vector<Creature> creatures;
		// food 
		std::vector<Food> food;
		// hunters
		std::vector<Hunter> hunters;

	
		// init of variables
		Manager(){
			best_creature_id = 0;
			av_score = 0;
		}

		// add class to given array
		template < class T >
		void addWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture, sf::Font& font)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.emplace_back( T(texture, randomPositionInWindow().x, randomPositionInWindow().y, font) );
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
				saveVector.emplace_back( T(texture, randomPositionInWindow().x, randomPositionInWindow().y, font, load_id) );
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


		void updateAll(const int& frame, sf::Texture& foodText, sf::Texture& creatureText, sf::Texture& hunterText, sf::Font& font)
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


			
			if (frame%5 == 0){
				CollisionCheckAndInput(creatures, food);
				CollisionCheckAndInput(hunters, creatures);
			}

			if(frame % 60 == 0 && frame>0){
				//// reproduce worldObjects
				reproduceCreatures(creatureText, font);
				// M.reproduceHunters(hunterText, font);
				reproduceFood(foodText, font);
			}

			//update distance matrices
			updateCCDistances();

		}


		void updateCCDistances(){
			/*
			Update creature creature distance values
			*/
			for(int i = 0; i < creatures.size(); i++){
				std::vector<float> vec;
				for(int j = 0; j < creatures.size(); j++){
					if (i!=j){
						// size - 1 eintreage
						vec.push_back(Distance(creatures[i].getPos(), creatures[j].getPos()));
					}
				}
				creatures[i].setCCDistances(vec);
			}


		}

		float Distance(position p1, position p2){
			
			return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		}

		// calc the distance and collision between v1 to v2, give NN inputs to v1 where v2 is the food source 
		template <typename T1, typename T2>
		void CollisionCheckAndInput(std::vector<T1>& v1, std::vector<T2>& v2)
		{
			float dist_i;
			float best_score = 0;
			// best_creature_id = 0;
			
			NN_Input creature_input;
			position diff_vector;

			float angle, view_angle;
			// av_score = 0;
			
			// go through all creatures and food and if distance is below threshold destroy food and call creature[i].eat()
			for(int i = 0; i<v1.size(); i++)
			{
				
				// creature loop	
				float closest_distance = 10000;
				int save_j = -1;

				// update collection vars
				av_score += v1[i].getScore();
				
						// food loop
						for (int j = 0; j<v2.size(); j++)
						{
							
							// calc distance to food j
							dist_i = Distance(v1[i].getPos(), v2[j].getPos());
							
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


						} // all food looped through and closest see-able food found

				// if food found
				if (save_j!=-1)
				{
					// calc distance to food j
					// dist_i = pow(creatures[i].getPos().x - food[save_j].getPos().x, 2) + pow(creatures[i].getPos().y - food[save_j].getPos().y, 2);
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = v1[i].getPos().x - v2[save_j].getPos().x;
					diff_vector.y = v1[i].getPos().y - v2[save_j].getPos().y;
					angle = vec_angle_in_deg(diff_vector.x, diff_vector.y);
					view_angle = angle_in_deg(diff_vector,-v1[i].getV_e());

					// set creature vertex 
					v1[i].vertices[0] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0,0));
					v1[i].vertices[1] = sf::Vertex(sf::Vector2f(  v2[save_j].getPos().x, v2[save_j].getPos().y), sf::Color(255,0,0));

				}
				// if food not found
				else
				{
					// no plant visible
					// set creature vertex 
					v1[i].vertices[0] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0,0));
					v1[i].vertices[1] = sf::Vertex(sf::Vector2f(  v1[i].getPos().x,  v1[i].getPos().y), sf::Color(255,0,0));
					
					closest_distance = 100000;
					view_angle = 0;
					v1[i].giveInput(creature_input);
				}


				// give input to creature i
				creature_input.setValues(
					view_angle,
					closest_distance,
					v1[i].getAverageCCDist(),
					v1[i].getMinCCDist());
				v1[i].giveInput(creature_input);
				
				
				if (v1[i].getScore()>best_score)
				{
					best_creature_id = v1[i].getID();
					best_score = v1[i].getScore();
				}
				
	
			}
			if (creatures.size() > 0){
				av_score = av_score/creatures.size();
			}
		}

		
		void reproduceCreatures(sf::Texture& texture, sf::Font& font)
		{

			// if less then MIN_CREATURES creatures are living, spawn in new random ones
			if (creatures.size()<config::MIN_CREATURES){
				addWorldObject<Creature>(1, creatures, texture, font);
			}


			// if less then MAX_Creatures are living, allow reproduction (check every creature and reproduce them if allowed)
			if (creatures.size()<config::MAX_CREATURES){
				
				for(int i = 0; i<creatures.size(); i++)
				{
				
					if (
					creatures[i].isAlive() && 
					creatures[i].getLifetime()%(config::REPRO_TIME_CREATURES*60)==0 && 
					creatures[i].getLifetime()>0 && 
					creatures[i].getHealth() > 0.75)
					{
						reproduceWorldObject<Creature>(1,creatures, texture, font, &creatures[i]);
					}
				}
			}

		
			// delete corpses
			for (int i = 0; i<creatures.size(); i++){
				if (!creatures[i].isAlive())
				{
					
					creatures.erase(creatures.begin()+i);
					
				}
			}		
		}

		void reproduceHunters(sf::Texture& texture, sf::Font& font)
		{
			// if less then MIN_Hunters creatures are living, spawn in new random ones
			if (hunters.size()<config::MIN_HUNTERS){
				addWorldObject<Hunter>(1, hunters, texture, font);
			}

			
			// if less then MAX_Creatures are living, allow reproduction (check every creature and reproduce them if allowed)
			if (creatures.size()<config::MAX_CREATURES){
				for(int i = 0; i<hunters.size(); i++)
				{
					if (
					hunters[i].isAlive() && 
					hunters[i].getLifetime()%(config::REPRO_TIME_HUNTERS*60)==0 && 
					hunters[i].getLifetime()>0 && 
					hunters[i].getHealth()>0.85)
					{
						reproduceWorldObject<Hunter>(1,hunters, texture, font, &hunters[i]);
					}
				}
			}
			// delete corpses
			for (int i = 0; i<hunters.size(); i++){
				if (!hunters[i].isAlive())
				{
					
					hunters.erase(hunters.begin()+i);
					
				}
			}	
		}

		void reproduceFood(sf::Texture& texture, sf::Font& font){
			float x,y;
			if (food.size()<config::S_FOOD){
				addWorldObject<Food>(2, food, texture, font);
			}
			
			for(int i = 0; i<food.size(); i++){
				if (food[i].getLifetime()%(config::REPRO_TIME_FOOD*60)==0 && food[i].getLifetime()>0 && food.size()<config::MAX_FOOD && randomInt(0,3)==0){
					reproduceWorldObject<Food>(1,food,texture, font, &food[i]);
				}
				if (!food[i].isAlive())
				{
					food.erase(food.begin()+i);	
				}
			}
		
		}

		int getBestCreatureID(){
			return best_creature_id;
		}

		float getAvHealth(){
			return av_score;
		}

		
		int findCreature(int ID){
			for(int i = 0; i < creatures.size(); i++){
				if (creatures[i].getID() == ID){
					return i;
				}
			}
			return -1;
		}

		~Manager()
		{
			int best_i = findCreature(best_creature_id);

			if (config::DO_SAVE and best_i != -1){
				if (creatures[best_i].getNN().save(creatures[best_i].getID(), config::SAVE_PATH)){
					print("Saved best Neural Network!");
				}
			}
			else{
				print("Warning: Could not save best creature!");
				print(best_i,"best_i : ");
			}
				// save best hunter
		}

};