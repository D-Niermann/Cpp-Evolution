#pragma once

class Creature : public WorldObject
{
  protected:
	NN_Input input_container;
	// layers
	Eigen::Vector2f l_input;
	Eigen::Vector3f l_output;
	Eigen::VectorXf l_hidden;
	// weights
	Eigen::MatrixXf weights1;
	Eigen::MatrixXf weights2;
	// bias
	Eigen::Vector2f b_input;
	Eigen::Vector3f b_output;
	Eigen::VectorXf b_hidden;
	
	
	

	position v_e;

	const int n_hidden_units = 3;
	const int n_input_units = 2;
	const int n_output_units = 3;

	const float max_move_speed = 2;
	const float max_rot_speed = 2;

	const float w_init_multiplier = 0.07;

	void propagate()
	{
		// convert input into eigen vector
		l_input[0] = input_container.dist;
		l_input[1] = input_container.angle;

		// hidden units
		l_hidden =  (weights1 * l_input) + b_hidden;
		l_output =  (weights2 * l_hidden)+ b_output;
	}	

  public:
	sf::Vertex vertices[2] ;
	

	// Constructor
	Creature(sf::Texture &texture, float x, float y, sf::Font& font) : WorldObject(texture, x, y, font)
	{
		using namespace Eigen;
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);

		respawn();

		
	}

	void respawn() override
	{
		WorldObject::respawn();
		/*
		Eigen
		*/
		// random init of weights
		weights1 = weights1.Random(n_hidden_units, n_input_units)*w_init_multiplier;
		weights2 = weights2.Random(n_output_units, n_hidden_units)*w_init_multiplier;
		// random init of bias
		b_input = b_input.Random(n_input_units)*w_init_multiplier;
		b_hidden = b_hidden.Random(n_hidden_units)*w_init_multiplier;
		b_output = b_output.Random(n_output_units)*w_init_multiplier;
		// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
		// zero init of visible layers
		l_input = l_input.Zero(n_input_units);
		l_output = l_output.Zero(n_output_units);
		/* Network:
				o
		dis	o	o	o = forw speed and dir [-1,1]
				o	o = unused
		ang	o	o	o = rot. speed and dir [-1,1]
				o
		*/
	}

	void update() override
	{
		// calc output of NN
		propagate();

		// forward vector
		v_e.x = std::cos(rot*3.1415/180);
		v_e.y = std::sin(rot*3.1415/180);

		// transform
		pos.x += v_e.x * clamp(l_output[0],-max_move_speed,max_move_speed);
		pos.y += v_e.y * clamp(l_output[0],-max_move_speed,max_move_speed);
		rot += clamp(l_output[2],-max_rot_speed,max_rot_speed);
		

		vertices[0] = sf::Vertex(sf::Vector2f(  pos.x,  pos.y), sf::Color::Red);
		vertices[1] = sf::Vertex(sf::Vector2f(  pos.x+v_e.x*10, pos.y+v_e.y*10), sf::Color::Red);

		// base class update call
		WorldObject::update();

		// set text1
		m_text.setString("input:\n"+roundToString(l_input[0],4)+"\n"+roundToString(l_input[1],4));
		m_text.setPosition(pos.x+20, pos.y+20);
		// set text2 
		m_text2.setString("output:\n"+roundToString(l_output[0],4)+"\n"+roundToString(l_output[2],4));
		m_text2.setPosition(pos.x+20, pos.y-20);


	}
		
	void eat()
	{
		// gets called externally when collision with food is detected
		health = S_HEALTH;
	}

	~Creature()
	{
		// print("Deleted Creature");
	}

	void giveInput(const NN_Input& I){
		this->input_container = I;
	}


	
};