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

struct NN_Input
{
	// distance to the nearest food source
	float dist;
	// angle to the neares food source
	float angle;

	// number of input vars
	static const int mysize = 2;

	NN_Input(){
		dist = 0;
		angle = 0;
	}

	const int& size(){
		return this->mysize;
	}

	void display(){
		std::cout << "Distance: " << dist << "," << "Angle: " << angle << std::endl;
	}
};



struct config
{
	static const unsigned int FRAMERATE = 60;
	static const bool VSYNC = true;
	static const unsigned int WINDOW_X = 1000;
	static const unsigned int WINDOW_Y = 500;

	static constexpr float foodSpriteScale = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static const int worldMargin = 20;

	static constexpr float creatureDecayRate = 0.001;
	static constexpr float creatureFoodReach = 20;

	static const unsigned int MAX_CREATURES = 100;
	static const unsigned int MAX_FOOD = 1;
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

float vec_angle(float x, float y)
{
	// SP betwenn input vector and x axis
	float SP = x;
	// length of input vector
	float len = sqrt(pow(x,2)+pow(y,2));
	// SP definition
	float angle = acos(SP/len);
	return angle*180/3.1415;
}

float clamp(float x, float min, float max)
{
	if (x > max){
		x = max;
	}
	else if (x<min){
		x = min;
	}
	return x;
}