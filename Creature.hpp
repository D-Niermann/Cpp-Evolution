
class Creature : public WorldObject
{
  protected:
	// sf::RenderWindow &m_window;

	float calcHealth()
	{
		return 0;
	}


  public:
	// Constructor
	Creature(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y)
	{
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
	}

	void update()
	{
		// transform object
		pos.x += 1;
		pos.y += 1;
		rot += 1;

		// performs boundary checks and sets the sprites values to the this Object values
		moveSprite();
	}
};