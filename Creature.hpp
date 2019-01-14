#pragma once

class Creature : public WorldObject
{
  protected:

	const int n_hidden_units = 3;
	const int n_input_units = 2;
	const int n_output_units = 3;

	const float max_move_speed = 2;
	const float max_rot_speed = 2;

	int food_eaten = 0;


	// input container contains all possible input vars from creature
	NN_Input input_container;
	
	// stores all parameters and methods of the neural network
	NeuralNetwork NN;	

	// this is just a 2d position vector
	position v_e;



  public:
	sf::Vertex vertices[2] ;
	

	// Constructor
	Creature(sf::Texture &texture, float x, float y, sf::Font& font) : 
		WorldObject(texture, x, y, font), 
		NN(n_input_units, n_hidden_units, n_output_units)
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
		NN(n_input_units, n_hidden_units, n_output_units, C->getNN())
	{
		// set srpite scale
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		// set decay rate slightly random
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);
		// inits the rest (set position to the parent creature)
		respawn(position(x,y));
		// mutate 
		NN.mutate();
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
		// calc output of NN
		NN.propagate(input_container);

		// forward vector
		v_e.x = std::cos(rot*3.1415/180);
		v_e.y = std::sin(rot*3.1415/180);

		// transform
		pos.x += v_e.x * clamp(NN.getOutput()[0],-max_move_speed,max_move_speed);
		pos.y += v_e.y * clamp(NN.getOutput()[0],-max_move_speed,max_move_speed);
		rot += clamp(NN.getOutput()[2],-max_rot_speed,max_rot_speed);
		


		// base class update call
		WorldObject::update();

		// set text1
		m_text.setString("ID: "+ std::to_string(ID));
		m_text.setPosition(pos.x+20, pos.y+10);
		// set text2 
		m_text2.setString("Score: "+roundToString(getScore(),4));
		m_text2.setPosition(pos.x+20, pos.y);


	}

	
	void eat()
	{
		// gets called externally when collision with food is detected
		health = S_HEALTH;
		food_eaten += 1;
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

	const float& getScore() override {
		score = health * food_eaten;
		return score;
	}

	
};