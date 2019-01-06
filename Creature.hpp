
class Creature : public WorldObject
{
  protected:



  public:
	// Constructor
	Creature(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y)
	{
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);
	}


	void update()
	{
		// base class update call
		WorldObject::update();
		// WARNING: this also already transforms the sprite, thus position changes are only effective next frame
	
		// transform
		pos.x += 1;
		pos.y += 1;
		rot += 1;

	}
		
	void eat()
	{
		// gets called externally when collision with food is detected
		health = S_HEALTH;
	}

	~Creature()
	{
		// print("Deleted Creature");
	}


	float getHealth(){ return health; }
};