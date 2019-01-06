
class Creature : public WorldObject
{
  protected:
	NN_Input input_container;
	Eigen::Vector2f l_input;
	Eigen::Vector3f l_output;
	Eigen::VectorXf l_hidden;
	Eigen::MatrixXf weights1;
	Eigen::MatrixXf weights2;
	
	

	position v_e;

	const int n_hidden_units = 3;
	const int n_input_units = 2;
	const int n_output_units = 3;

	void propagate()
	{
		// convert input into eigen vector
		l_input[0] = input_container.dist;
		l_input[1] = input_container.angle;

		// hidden units
		l_hidden =  weights1 * l_input;
		l_output = weights2 * l_hidden;
	}	

  public:
	sf::Vertex vertices[2] ;
	
	// Constructor
	Creature(sf::Texture &texture, float x, float y) : WorldObject(texture, x, y)
	{
		using namespace Eigen;
		m_sprite.setScale(config::creatureSpriteScale, config::creatureSpriteScale);
		m_DecayRate = config::creatureDecayRate + random(-config::creatureDecayRate*0.1, config::creatureDecayRate*0.1);

		// eigen
		
		// random init of weights
		weights1 = weights1.Random(n_hidden_units, n_input_units)*0.1;
		weights2 = weights2.Random(n_output_units, n_hidden_units)*0.1;
		weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);

	/*
			o
	dis	o	o	o = forw speed and dir [-1,1]
			o	
	ang	o	o	o = rot. speed and dir [-1,1]
			o
	
	*/

		// zero init of visible layers
		l_input = l_input.Zero(n_input_units);
		l_output = l_output.Zero(n_output_units);
	}

	void respawn()
	{
		WorldObject::respawn();
		weights1 = weights1.Random(n_hidden_units, n_input_units)*0.1;
		weights2 = weights2.Random(n_output_units, n_hidden_units)*0.1;
	}

	void update()
	{
		// calc output of NN
		propagate();

		// forward vector
		v_e.x = std::cos(rot*3.1415/180);
		v_e.y = std::sin(rot*3.1415/180);

		// transform
		pos.x += v_e.x * clamp(l_output[0],-1,1);
		pos.y += v_e.y * clamp(l_output[0],-1,1);
		rot += clamp(l_output[2],-1,1);
		

		vertices[0]=sf::Vertex(sf::Vector2f(  pos.x,  pos.y), sf::Color::Red);
		vertices[1]=sf::Vertex(sf::Vector2f(  pos.x+v_e.x*10, pos.y+v_e.y*10), sf::Color::Red);

		// base class update call
		WorldObject::update();
		
	

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