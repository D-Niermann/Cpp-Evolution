


class Hunter : public Creature
{
	private:
		static constexpr float max_move_speed = 2;
		static constexpr float max_rot_speed = 2;
		static constexpr float eps = 0.0001;

		
	public:
		// Constructor
		Hunter(sf::Texture &texture, float x, float y, sf::Font& font) : 
			WorldObject(texture,x, y, font),
			Creature(texture, x, y, font)
		{
			
			// set srpite scale
			m_sprite.setScale(config::hunterSpriteScale, config::hunterSpriteScale);
			// set decay rate slightly random
			m_DecayRate = config::hunterDecayRate + random(-config::hunterDecayRate*0.1, config::hunterDecayRate*0.1);
			// inits the rest 
			respawn(position(x,y));
		}

		// consttructor for inheritance of parent parameters
		Hunter(sf::Texture &texture, float x, float y, sf::Font& font, Hunter* C) : 
			WorldObject(texture,x, y, font),
			Creature(texture, x, y, font , C)
		{
			// set srpite scale
			m_sprite.setScale(config::hunterSpriteScale, config::hunterSpriteScale);
			// set decay rate slightly random
			m_DecayRate = config::hunterDecayRate + random(-config::hunterDecayRate*0.1, config::hunterDecayRate*0.1);
			// inits the rest (set position to the parent hunter)
			respawn(position(x,y));
			// take over the food_eaten score, bec otherwise it will get culled instantly 
			// food_eaten = C->food_eaten;
			// rot = C->rot + 90;
			// // mutate 
			// NN.mutateW();
			// NN.mutateB();
		}
		
		// consttructor for loading of parameters from file
		Hunter(sf::Texture &texture, float x, float y, sf::Font& font, const std::string load_id) : 
			WorldObject(texture,x, y, font),
			Creature(texture, x, y, font, load_id)
		{
			// set srpite scale
			m_sprite.setScale(config::hunterSpriteScale, config::hunterSpriteScale);
			// set decay rate slightly random
			m_DecayRate = config::hunterDecayRate + random(-config::hunterDecayRate*0.1, config::hunterDecayRate*0.1);
			// inits the rest (set position to the parent hunter)
			respawn(position(x,y));
			// // mutate 
			// for (int i = 0; i<3; i++){
			// 	NN.mutateW();
			// 	NN.mutateB();
			// }
		}
};