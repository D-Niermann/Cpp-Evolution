// stores and opens sprites and creatures


class Manager
{
	private:
		// for polymorph array
		// creatures (polymorphism with worldObject -> store all objects in one array)
		// WorldObject* p = NULL;
		// std::vector<WorldObject*> Objects;
	public:
		
		// plant  creatures
		std::vector<Creature> creatures;
		
		// food 
		std::vector<Food> food;
		
		// vars

	
		// add class to given array
		template < class T >
		void addWorldObject(unsigned int count, std::vector<T>& saveVector, sf::Texture& texture)
		{
			// redefine variable for shorter code line
			int m = config::worldMargin;
			// add all class instances of type T to the save vector
			for (int i = 0; i < count; i++)
			{
				saveVector.push_back( T(texture, random(0+m,config::WINDOW_X-m), random(0+m,config::WINDOW_Y-m)) );
			}
		}




		void updateAll()
		{
			// updates all creatures
			for(int i = 0; i<creatures.size(); i++){
				creatures[i].update();
				print(creatures[i].getPos().x);
			}

		}


	
		// const void printObjects(){
		// 	for (int i = 0; i<m_creature_count; i++)
		// 	{
		// 		std::cout << Objects[i]->getSprite() <<std::endl;
		// 	}
		// }
};