#pragma once
class Creature : public WorldObject
{
  private:
	std::vector<float> CCDistances;
  protected:
	static const int n_hidden_units = 5;
	static const int n_output_units = 3;

	static constexpr float max_move_speed = 2;
	static constexpr float max_rot_speed = 2;
	static constexpr float eps = 0.0001;

	int food_eaten = 0;

	// values that get assigned by the NN outputs
	float cur_speed = 0;
	float cur_rotation = 0;
	float cur_boost = 0;
	
	//
	int time_last_reproduction = 0;

	// input container contains all possible input vars from creature
	NN_Input input_container;
	
	// stores all parameters and methods of the neural network
	NeuralNetwork NN;	

	// this is just a 2d position vector
	position v_e;

	void calcScore() override{
		score = food_eaten/((lifetime+eps)/600);
	}

	void calcHealth() override{ 
		health = health  - m_DecayRate*cur_boost;
	}

	void updateV_e()
	{
		// forward vector
		v_e.x = std::cos(rot*3.1415/180);
		v_e.y = std::sin(rot*3.1415/180);
	}

  public:
	sf::Vertex vertices[2] ;

	// Constructor
	Creature(sf::Texture &texture, float x, float y, sf::Font& font) : 
		WorldObject(texture, x, y, font), 
		NN(NN_Input::size, n_hidden_units, n_output_units)
	{

		// set srpite scale
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		// set decay rate slightly random
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);
		// inits the rest 
		respawn(position(x,y));
	}
	// consttructor for inheritance of parent parameters
	Creature(sf::Texture &texture, float x, float y, sf::Font& font, Creature* C) : 
		WorldObject(texture, x, y, font), 
		// init the neural network with existing one
		NN(NN_Input::size, n_hidden_units, n_output_units, C->getNN())
	{
		// set srpite scale
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		// set decay rate slightly random
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);
		// inits the rest (set position to the parent creature)
		respawn(position(x,y));
		// take over the food_eaten score, bec otherwise it will get culled instantly 
		// food_eaten = C->food_eaten;
		rot = C->rot + randomInt(-90,90);
		// mutate 
		NN.mutateW();
		NN.mutateB();
	}
	// consttructor for loading of parameters from file
	Creature(sf::Texture &texture, float x, float y, sf::Font& font, const std::string load_id) : 
		WorldObject(texture, x, y, font), 
		// init the neural network with existing one
		NN(NN_Input::size, n_hidden_units, n_output_units, load_id)
	{
		// set srpite scale
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		// set decay rate slightly random
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);
		// inits the rest (set position to the parent creature)
		respawn(position(x,y));
		// mutate 
		for (int i = 0; i<3; i++){
			NN.mutateW();
			NN.mutateB();
		}
	}

	void respawn(position p) override
	{
		// call parent respawn
		WorldObject::respawn(p);

		// do creature specific:
		food_eaten = 0;
	}



	void update() override
	{
		if (is_alive){

			// base class update call
			WorldObject::update();
			time_last_reproduction += 1;

			// calc output of NN
			NN.propagate(input_container);
			cur_speed = (NN.getOutput()[0] - 0.5)*max_move_speed;
			cur_boost = NN.getOutput()[1] * 2;
			cur_rotation = (NN.getOutput()[2] -0.5) * max_rot_speed;
			

			// transform
			updateV_e();
			pos.x += v_e.x * cur_speed * cur_boost;  // move based on NN output [0] and boost NN output [1]
			pos.y += v_e.y * cur_speed * cur_boost; // move based on NN output [0] and boost NN output [1]
			rot += cur_rotation;


			// set text1
			m_text.setString("ID: " + roundToString(getID(),5) + "\n" + "Input: "+NN.getInputString()+"Output: "+ NN.getOutputString());

			m_text.setPosition(pos.x+20, pos.y+10);
			m_text.setFillColor(sf::Color(0,0,0,health*255));
		

		}
	}



	void eat()
	{
		// gets called externally when collision with food is detected
		if (is_alive){
			health += 0.4;
			food_eaten += 1;
		}
	}

	~Creature()
	{
		// print("Deleted Creature");
	}

	void giveInput(const NN_Input& InputContainer){
		// reference to input container should this not be a copy? maybe the = already copies it into own member var
		this->input_container = InputContainer;
	}

	position& getV_e(){
		return v_e;
	}

	sf::Color CalcColor() override
	{
		return NN.calcColor(health);
	}

	NeuralNetwork getNN(){
		return NN;
	}

	const float& getScore() const override{
		return score;
	}

	const NN_Input& getInput() const {
		return input_container;
	}

	void setCCDistances(std::vector<float> v){
		this->CCDistances = v;
	}

	float getAverageCCDist(){
		return mean(CCDistances);
	}

	float getMinCCDist(){
		return *std::min_element(CCDistances.begin(), CCDistances.end());
	}
	
	int getLastReproTime(){
		return time_last_reproduction;
	}
	
	void resetLastReproTime(){
		time_last_reproduction = 0;
	}

};