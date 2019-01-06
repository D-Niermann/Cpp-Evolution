

class WorldObject
{
  protected:
  	// start values 
  	static constexpr float S_HEALTH = 1;
	static const int S_LIFETIME = 0;
	static constexpr float S_ROTATION = 0;

	//constants
	float m_DecayRate;
	
	// runtime values
	position pos;
	int lifetime;
	float health;
	// rotation
	float rot;
	// references to sfml stuff
	sf::Sprite m_sprite;
	

	virtual void calcHealth(){ 
		float h;
		h = this->health-m_DecayRate;
		health = h;
	}

  public:
	// Constructor
	WorldObject(sf::Texture& texture, float x, float y) : m_sprite(texture), pos(x, y) 
	{
		rot = S_ROTATION;
		health = S_HEALTH;
		lifetime = S_LIFETIME;

		m_DecayRate = 0;

		m_sprite.setPosition(x,y);
		m_sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
	}

	virtual void update()
	{
		lifetime += 1;
		calcHealth();
		respawnCheck();
		transformSprite();
	}

	void boundaryCheck(){
		// limit position
		if (pos.x > config::WINDOW_X-config::worldMargin)
		{
			pos.x = config::WINDOW_X-config::worldMargin;
		}
		else if (pos.x < config::worldMargin)
		{
			pos.x = config::worldMargin;
		}
		if (pos.y > config::WINDOW_Y-config::worldMargin)
		{
			pos.y = config::WINDOW_Y-config::worldMargin;
		}
		else if (pos.y < config::worldMargin)
		{
			pos.y = config::worldMargin;
		}
		// limit rotation
		if (rot > 360 || rot < 0){
			rot = 0;
		}
	}

	void transformSprite(){
		boundaryCheck();
		m_sprite.setPosition(pos.x,pos.y);
		m_sprite.setRotation(rot);
		m_sprite.setColor(sf::Color(255,255,255,health*255));
	}


	void respawnCheck(){
		if (health <= 0)
		{
			respawn();
		}
	}

	virtual void respawn()
	{
		health = WorldObject::S_HEALTH;
		pos = randomPositionInWindow();
		rot = 0;
		transformSprite();
	}

	const position& getPos() const
	{
		return pos;
	}

	const float& getRot()
	{
		if (rot<0 || rot>360){
			rot = 0;
		}
		return rot;
	}

	const sf::Sprite& getSprite() const
	{
		return m_sprite;
	}

	const float& getHealth()
	{ 
		return health;
	}
	// // Copy constructor
	// WorldObject(const WorldObject& other): m_window(other.m_window), m_sprite(other.m_sprite), pos(other.pos){

};
