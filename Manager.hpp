
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

		}

		void CollisionCheck()
		{
			// go through all creatures and food and if distance is below threshold destroy food and call creature[i].eat()
		}
};