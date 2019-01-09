
class Manager
{
	protected:

		Creature* best_creature;

	public:
		// plant  creatures
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


		void updateAll()
		{
			// updates all creatures
			for(int i = 0; i<creatures.size(); i++){
				creatures[i].update();
			}
			// updates all food
			for(int i = 0; i<food.size(); i++){
				food[i].update();
			}

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
						food[j].respawn();
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
				else{
					// no plant visible
					// set creature vertex 
					creatures[i].vertices[0] = sf::Vertex(sf::Vector2f(  creatures[i].getPos().x,  creatures[i].getPos().y), sf::Color(255,0,0,0));
					creatures[i].vertices[1] = sf::Vertex(sf::Vector2f(  creatures[i].getPos().x,  creatures[i].getPos().y), sf::Color(255,0,0));

					creature_input.angle = -180;
					creature_input.dist = 99999;
					creatures[i].giveInput(creature_input);
				}

				if (creatures[i].getScore()>best_score){
					best_creature = &creatures[i];
				}
			}
		}

		Creature* getBestCreature(){
			return best_creature;
		}

};