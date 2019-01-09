
class Food : public WorldObject
{
  protected:

  public:
	Food(sf::Texture &texture, float x, float y, sf::Font& font) : WorldObject(texture, x, y, font) 
	{
		m_sprite.setScale(config::foodSpriteScale, config::foodSpriteScale);
		m_sprite.setRotation(random(0,360));
	}



};