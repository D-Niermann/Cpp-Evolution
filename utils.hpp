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
	
	position operator - (){
		position v;
		v.x = - this->x;
		v.y = - this->y;
		return v;
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
template <typename T>
void print(T t, std::string message = ""){
	std::cout << message << " " << t << std::endl;
}

struct config
{
	static const unsigned int FRAMERATE = 60;
	static const bool VSYNC = true;
	static const unsigned int WINDOW_X = 1000;
	static const unsigned int WINDOW_Y = 500;
	static const unsigned int TEXTSIZE = 12;

	static constexpr float foodSpriteScale = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static const int worldMargin = 20;

	static constexpr float creatureDecayRate = 0.001;
	static constexpr float creatureFoodReach = 30;

	static const unsigned int MAX_CREATURES = 10;
	static const unsigned int MAX_FOOD = 10;
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

std::string roundToString(float n, int n_digits)
{
	return std::to_string(n).substr(0,n_digits);
}

float vec_angle_in_deg(float x, float y)
{
	
	float angle = atan2f(x,y)-3.1415/2;
	if (angle<0){
		angle = angle+2*3.1415;
	}
	return angle*180/3.1415;
}

float angle_in_deg(position v1, position v2)
{
	return std::atan2f(v1.x*v2.y-v1.y*v2.x,v1.x*v2.x+v1.y*v2.y)*180/3.1415;
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