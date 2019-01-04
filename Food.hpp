
class Food : public WorldObject
{
  private:
	/* data */
  public:
	Food(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y) 
	{
		m_sprite.setScale(config::foodSpriteScale, config::foodSpriteScale);
		m_sprite.setRotation(random(0,360));
	}

	void update(){
		WorldObject::update();
	}

	void respawn(){}
	
};