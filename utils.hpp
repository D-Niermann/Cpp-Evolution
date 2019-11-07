struct CollectionVars
{
	float av_score_creatures;
};

std::string roundToString(float n, int n_digits)
{
	return std::to_string(n).substr(0,n_digits);
}


std::string vectorToString(std::vector<float> v){
	std::string s;
	for (int i = 0; i<v.size(); i++){
		s = s + roundToString(v[i],5) + ", ";
	}
	return s;
}


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

float mean(std::vector<float> vec){
	float buff = 0;
	for(int i = 0; i<vec.size();i++){
		buff += vec[i];
	}
	return buff/vec.size();
}


class NN_Input
{
	private: 
		// distance to the nearest food source
		float dist;
		// angle to the neares food source
		float angle;
		// average distance to others of same species
		float av_same_dist;
		// min distance along same_dist vector
		float min_same_dist;

	public:
		// number of input vars
		static const int size = 4; // number of free input params in this class.

		NN_Input(){
			dist = 0;
			angle = 0;
			av_same_dist = 0;
			min_same_dist = 0;
		}
		

		float getMinSameDist(){
			return min_same_dist;
		}

		float getAvSameDist(){
			return av_same_dist;
		}

		float getDistance(){
			return dist;
		}

		float getAngle(){
			return angle;
		}
		
		void setValues(float angle, float dist, float av_same_dist, float min_same_dist){
			/*
			Set all values that the NN input object needs.
			Angle to food >> Distance to food >> average distance to same species >> min distance to same species
			*/
			this-> angle = angle;
			this-> dist = dist;
			this-> av_same_dist = av_same_dist;
			this-> min_same_dist = min_same_dist;
		}



		
};


template <typename T>
void print(T t, std::string message = ""){
	std::cout << message << " " << t << std::endl;
}



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