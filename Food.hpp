
class Food : public WorldObject
{
  protected:

  public:
	Food(sf::Texture &texture, float x, float y, sf::Font& font) : WorldObject(texture, x, y, font) 
	{
		float rng = random(-0.1,0.1);
		m_sprite.setScale(config::foodSpriteScale+rng, config::foodSpriteScale+rng);
		m_sprite.setRotation(random(0,360));
	}



};