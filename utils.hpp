#define print(x) std::cout << x << std::endl;

float random(float low, float high){
	float r;
	r = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
	return r; 
}


struct position
{
	float x, y;

	position(float x, float y): x(x), y(y) {}
};


struct config{
	static const unsigned int WINDOW_X = 1000;
	static const unsigned int WINDOW_Y = 500;

	static constexpr float foodSpriteScale = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static const int worldMargin = 20;
};