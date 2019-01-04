
class Creature : public WorldObject
{
  protected:
	

	void calcHealth()
	{
		float h;
		h = this->health-config::creatureDecayRate;
		if (h < 0){
			h = 0;
		}
		health = h;
	}


  public:
	// Constructor
	Creature(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y)
	{
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
	}

	void update()
	{
		// base class update call
		WorldObject::update();
	
		// transform
		pos.x += 1;
		pos.y += 1;
		rot += 1;

		// performs boundary checks and sets the sprites values to the this Object values
		transformSprite();
	}

	~Creature()
	{
		print("Deleted Creature");
	}
};