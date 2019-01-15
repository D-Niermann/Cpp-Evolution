

class WorldObject
{
  protected:
  	// start values 
  	static constexpr float S_HEALTH = 1;
	static const int S_LIFETIME = 0;
	static constexpr float S_ROTATION = 0;

	//constants
	float m_DecayRate = 0;
	int ID = (int)random(0,981239);
	
	// runtime values
	position pos;
	int lifetime;
	float health;
	float score;
	// rotation
	float rot;
	// references to sfml stuff
	sf::Sprite m_sprite;
	sf::Text m_text;
	sf::Text m_text2;
	

	virtual void calcHealth(){ 
		float h;
		h = this->health-m_DecayRate;
		health = h;
	}

	virtual void calcScore(){
		score = health;
	}

  public:
	// Constructor
	WorldObject(sf::Texture& texture, float x, float y, sf::Font& font) : m_sprite(texture)
	{
		respawn(position(x,y));

		m_sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);

		init_text(m_text, font);
		init_text(m_text2, font);
	}

	void init_text(sf::Text& t, sf::Font& font)
	{
		t.setFont(font);
		t.setStyle(sf::Text::Bold);
		t.setFillColor(sf::Color::Black);
		t.setCharacterSize(config::TEXTSIZE);
	}
	virtual void update()
	{
		lifetime += 1;
		calcHealth();
		calcScore();
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
		if (rot < 0){
			rot = 360 + rot;
		}
		if (rot > 360){
			rot = 0;
		}
	}

	void transformSprite(){
		boundaryCheck();
		m_sprite.setPosition(pos.x,pos.y);
		m_sprite.setRotation(rot);
		m_sprite.setColor(CalcColor());
	}


	void respawnCheck(){
		if (health <= 0)
		{
			respawn(randomPositionInWindow());
		}
	}

	virtual void respawn(position p)
	{
		rot = WorldObject::S_ROTATION;
		lifetime = WorldObject::S_LIFETIME;
		health = WorldObject::S_HEALTH;
		pos = p;
		transformSprite();
	}

	virtual sf::Color CalcColor(){
		float r = 255;
		float g = 255;
		float b = 255;
		float a = health*255;
		return sf::Color(r,g,b,a);
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

	const sf::Text& getText(unsigned int i) const 
	{
		if (i==0){
			return m_text;
		}
		else{
			return m_text2;
		}
	}

	const float& getHealth() const
	{ 
		return health;
	}

	const virtual float& getScore() const {
		return score;
	}

	virtual int getLifetime() const{
		return lifetime;
	}

	const int getID() const {
		return ID;
	}
	// // Copy constructor
	// WorldObject(const WorldObject& other): m_window(other.m_window), m_sprite(other.m_sprite), pos(other.pos){
	bool operator<(WorldObject const &rhs) const
	{ return score < rhs.score; }
	bool operator>(WorldObject const &rhs) const
	{ return score > rhs.score; }
};
