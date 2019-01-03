

class WorldObject
{
  protected:
	position pos;
	int lifetime;
	float health;
	// rotation
	float rot;
	// references to sfml stuff
	sf::Sprite m_sprite;
	

  public:
	// Constructor
	WorldObject(sf::Texture& texture, float x, float y) : m_sprite(texture), pos(x, y) 
	{
		m_sprite.setPosition(x,y);
		m_sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
	}

	virtual void update()
	{
		lifetime += 1;
	}

	void boundaryCheck(){
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
	}

	void moveSprite(){
		boundaryCheck();
		m_sprite.setPosition(pos.x,pos.y);
		m_sprite.setRotation(rot);
	}


	const position& getPos() const
	{
		return pos;
	}

	const sf::Sprite& getSprite() const
	{
		return m_sprite;
	}
	// // Copy constructor
	// Creature(const Creature& other): m_window(other.m_window), m_sprite(other.m_sprite), pos(other.pos){

	// }

	// // Deconstructor
	// ~Creature()
	// {

	// }
};
