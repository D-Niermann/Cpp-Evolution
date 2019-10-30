#pragma once
class Creature : public WorldObject
{
  protected:

	static const int n_hidden_units = 3;
	static const int n_output_units = 3;

	static constexpr float max_move_speed = 2;
	static constexpr float max_rot_speed = 2;
	static constexpr float eps = 0.0001;

	int food_eaten = 0;
	


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
		// decr health if boost (NN output[1]) is higher than 1, but save health if boost is lower 1
		float h;
		h = this -> health  - m_DecayRate*clamp(NN.getOutput()[1],0.5,2);
		health = h;
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
		rot = C->rot + 90;
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

			// calc output of NN
			NN.propagate(input_container);

			updateV_e();

			// transform
			pos.x += v_e.x * clamp(NN.getOutput()[0],-max_move_speed,max_move_speed) * clamp(NN.getOutput()[1],0.5,2);  // move based on NN output [0] and boost NN output [1]
			pos.y += v_e.y * clamp(NN.getOutput()[0],-max_move_speed,max_move_speed) * clamp(NN.getOutput()[1],0.5,2); // move based on NN output [0] and boost NN output [1]
			rot += clamp(NN.getOutput()[2],-max_rot_speed,max_rot_speed);


			// base class update call
			WorldObject::update();

			// set text1
			m_text.setString("Out: "+ roundToString(NN.getHidden()[0],4) + ", " + roundToString(NN.getHidden()[1],4) + ", " +roundToString(NN.getHidden()[2],4));
			m_text.setPosition(pos.x+20, pos.y+10);
			m_text.setFillColor(sf::Color(0,0,0,health*255));
			// set text2 
			// set text2 
				// set text2 
			// set text2 

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

	void giveInput(const NN_Input& I){
		this->input_container = I;
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
	
};