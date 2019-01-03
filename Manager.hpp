// stores and opens sprites and creatures


class Manager
{
	private:
		
		// creatures (polymorphism with worldObject? -> store all objects in one array)
		std::vector<Creature> creatures;
		// std::vector<sf::Sprite> creatureSprites;
		
		// food 
		std::vector<Food> food;
		// std::vector<sf::Sprite> foodSprites;
		
		// vars
		unsigned int m_creature_count;
		unsigned int m_food_count;

	
	public:

		// add food objects
		void addFood(unsigned int count, sf::Texture& texture){
			for (int i = 0; i < count; i++)
			{
				food.push_back( Food(texture, random(0,config::WINDOW_X), random(0,config::WINDOW_Y)) );
			}
			m_food_count = count;
		}

		// add creatures and array of corresponding creatureSprites
		void addCreatures(unsigned int count, sf::Texture& texture)
		{
			for (int i = 0; i < count; i++)
			{
				creatures.push_back(
					Creature(texture, random(0,config::WINDOW_X), random(0,config::WINDOW_Y))
					);
			}
			m_creature_count = count;
		}

		void updateAll(){
			// updates all creatures
			for(int i = 0; i<m_creature_count; i++){
				creatures[i].update();
			}

		}


		// // simple accesors
		
		const int getObjectCount() const
		{
			return m_creature_count;
		}
		const int getFoodCount() const
		{
			return m_food_count;
		}
		
		const sf::Sprite &getCreatureSprite(unsigned int pos) const
		{
			if (pos < m_creature_count)
			{
				return creatures[pos].getSprite();
			}
			else
			{
				throw std::invalid_argument("Error: Index out of Bounds!");
			}
		}
		const sf::Sprite &getFoodSprite(unsigned int pos) const
		{
			if (pos < m_food_count)
			{
				return food[pos].getSprite();
			}
			else
			{
				throw std::invalid_argument("Error: Index out of Bounds!");
			}
		}
		const std::vector<Creature> &getCreatures() const { return creatures; }
};