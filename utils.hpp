# define print(x) std::cout << x << std::endl;
# include <iostream>

struct position
{
	float x, y;
	
	position() : 
	 x(0), y(0) {}

	position(float x, float y): 
	 x(x), y(y) {}

	void display(){
		std::cout << x << "," << y << std::endl;
	}

	position& operator = (const position& pos){
		this->x = pos.x;
		this->y = pos.y;
		return *this;
	}
};




struct config
{
	static const unsigned int WINDOW_X = 1000;
	static const unsigned int WINDOW_Y = 500;

	static constexpr float foodSpriteScale = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static const int worldMargin = 20;

	static constexpr float creatureDecayRate = 0.01;

	static const unsigned int MAX_CREATURES = 10;
	static const unsigned int MAX_FOOD = 30;
};


float random(float low, float high)
{
	float r;
	r = low + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(high-low)));
	return r; 
}


position randomPositionInWindow()
{
	position p;
	float x = 0 + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(config::WINDOW_X-0)));
	float y = 0 + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(config::WINDOW_Y-0)));
	p.x = x;
	p.y = y;
	return p; 
}