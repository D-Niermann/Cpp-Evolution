struct CollectionVars
{
	float av_score_creatures;
};

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
	// window specific
	static const unsigned int FRAMERATE = 60;
	static const bool VSYNC = true;
	static const unsigned int WINDOW_X = 1200;
	static const unsigned int WINDOW_Y = 800;
	static const unsigned int TEXTSIZE = 12;

	static constexpr float foodSpriteScale = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static constexpr float hunterSpriteScale = 0.7;
	static const int worldMargin = 20;

	// world object specific
	static constexpr float creatureDecayRate = 0.001;
	static constexpr float hunterDecayRate = 0.001;
	static constexpr float creatureFoodReach = 30;
	static const int REPRO_TIME_CREATURES = 12*60; // needs to be mutlitudes of 60! 1*60 is 1 sec
	static const int REPRO_TIME_HUNTERS = 3*60; // needs to be mutlitudes of 60! 1*60 is 1 sec
	static const int REPRO_TIME_FOOD = 1*60; // needs to be mutlitudes of 60! 1*60 is 1 sec

	static const unsigned int S_CREATURES = 7;
	static const unsigned int MIN_CREATURES = 4;
	static const unsigned int MAX_CREATURES = 10;
	static const unsigned int S_FOOD = 4;
	static const unsigned int MAX_FOOD = 20;
	static const unsigned int S_HUNTERS = 2;

	static constexpr float MUTATION_FACTOR = 0.4;

	// loading and saving
	static const bool INIT_LOAD = false;
	static const std::string SAVE_PATH;
	static const std::string LOAD_ID_CREATURES;
	static const std::string LOAD_ID_HUNTERS;
	static const bool DO_SAVE = true;
	static const bool DO_PRINTLOG = true;
};
// initialisations for config
const std::string config::SAVE_PATH ="C:/Users/dniermann/Documents/GitHub/Cpp-Evolution/build/Saves/";
const std::string config::LOAD_ID_CREATURES = "10415"; 
const std::string config::LOAD_ID_HUNTERS = "10415"; 


/* 

FUNCTIONS

*/

float random(float low, float high)
{
	if (high==low){
		print("WARNING: RandomFunction high == low!");
		return low;
	}
	if (high > RAND_MAX || low > RAND_MAX){
		print("WARNING: RandomFunction boundarys to high !");
		std::cout << high << "," << low<< std::endl;
		return low;
	}
	float r;
	r = low + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(high-low)));
	return r; 
}
int randomInt(float low, float high)
{
	return (int)random(low, high); 
}


position randomPositionInWindow()
{
	position p;
	float x = random(0+config::worldMargin, config::WINDOW_X-config::worldMargin);
	float y = random(0+config::worldMargin, config::WINDOW_Y-config::worldMargin);
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
	return std::atan2(v1.x*v2.y-v1.y*v2.x,v1.x*v2.x+v1.y*v2.y)*180/3.1415;
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

Eigen::VectorXf clamp(Eigen::VectorXf v, float min, float max){
	for(int i = 0; i<v.size(); i++){
		v[i] = clamp(v[i], min, max);
	}
	return v;
}

// stupid implementation per ...
// void clamp(Eigen::VectorXf& M, float min, float max)
// {
// 	for(int i= 0; i < M.rows(); i++){
// 		for (int j = 0; j< M.cols(); j++){
// 			if (M(i,j) > max){
// 				M(i,j) = max;
// 			}
// 			else if (M(i,j) < min){
// 				M(i,j) = min;
// 			}
			
// 		}
// 	}
// }
/*
// implementation through ...
void clamp(Eigen::MatrixXf& M, float min, float max)
{
	for(int i= 0; i < M.rows(); i++){
		for (int j = 0; j< M.cols(); j++){
			if (M(i,j) > max){
				M(i,j) = max;
			}
			else if (M(i,j) < min){
				M(i,j) = min;
			}
			
		}
	}
}
// implementation though iterator
void clamp(Eigen::MatrixXf& M, float min, float max)
{
	for(int i= 0; i < M.rows(); i++){
		for (int j = 0; j< M.cols(); j++){
			if (M(i,j) > max){
				M(i,j) = max;
			}
			else if (M(i,j) < min){
				M(i,j) = min;
			}
			
		}
	}
}
*/