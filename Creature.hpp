
class Creature : public WorldObject
{
  protected:
	
	float m_DecayRate;
	

	void calcHealth()
	{
		float h;
		h = this->health-m_DecayRate;
		health = h;
	}

	void respawn(){
		WorldObject::respawn();

	}


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
	
		// transform
		pos.x += 1;
		pos.y += 1;
		rot += 1;

		// collision checks
		// calcFoodDistances(); // do this in manager and make a getter for the distance array
		collisionFood();

		// performs boundary checks and sets the sprites values to the this Object values
		transformSprite();
	}


	void collisionFood(){

	}


	~Creature()
	{
		// print("Deleted Creature");
	}

	float getHealth(){ return health; }
};