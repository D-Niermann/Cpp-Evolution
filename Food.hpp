
class Food : public WorldObject
{
  protected:

  public:
	Food(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y) 
	{
		m_sprite.setScale(config::foodSpriteScale, config::foodSpriteScale);
		m_sprite.setRotation(random(0,360));
	}


	void respawn(){}

};