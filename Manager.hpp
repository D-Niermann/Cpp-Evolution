
class Manager
{
	protected:

	public:
		// plant  creatures
		std::vector<Creature> creatures;
		// food 
		std::vector<Food> food;
	
		// add class to given array
		template < class T >
		void addWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.emplace_back( T(texture, random(0+m,config::WINDOW_X-m), random(0+m,config::WINDOW_Y-m)) );
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
			NN_Input creature_input;
			position diff_vector;
			float angle;
			// go through all creatures and food and if distance is below threshold destroy food and call creature[i].eat()
			for(int i = 0; i<creatures.size(); i++){
				for (int j = 0; j<food.size(); j++){
					// calc distance
					square_dist_i = pow(creatures[i].getPos().x - food[j].getPos().x, 2) + pow(creatures[i].getPos().y - food[j].getPos().y, 2);
					// calc diff vector between creature and food and the angle of it
					diff_vector.x = creatures[i].getPos().x - food[j].getPos().x;
					diff_vector.y = creatures[i].getPos().y - food[j].getPos().y;
					angle = vec_angle(diff_vector.x, diff_vector.y);
				
					if (sqrt(square_dist_i) < config::creatureFoodReach)
					{
						creatures[i].eat();
						food[j].respawn();
					}

					// give input to creature i
					creature_input.angle = std::abs(angle - creatures[i].getRot()-180);
					creature_input.dist = std::sqrt(square_dist_i);
					creatures[i].giveInput(creature_input);

				}
			}
		}


};