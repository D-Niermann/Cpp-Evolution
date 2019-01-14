
using namespace Eigen;

class NeuralNetwork
{
	private:
		// mutate factor in percent of the mutated value
		const float P = 0.1;

		// layers
		Vector2f l_input;
		Vector3f l_output;
		VectorXf l_hidden;
		// weights
		MatrixXf weights1;
		MatrixXf weights2;
		// bias
		Vector2f b_input;
		Vector3f b_output;
		VectorXf b_hidden;
		/* Network:
				o
		dis	o	o	o = forw speed and dir [-1,1]
				o	o = unused
		ang	o	o	o = rot. speed and dir [-1,1]
				o
		*/

		const float w_init_multiplier = 0.1;

	public:
		NeuralNetwork(int n_input, int n_hidden, int n_output)
		{
			// random init of weights
			weights1 = weights1.Random(n_hidden, n_input)*w_init_multiplier;
			weights2 = weights2.Random(n_output, n_hidden)*w_init_multiplier;
			// random init of bias
			b_hidden = b_hidden.Random(n_hidden)*w_init_multiplier;
			b_output = b_output.Random(n_output)*w_init_multiplier;
			b_output(0) = 0.5;
			// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
			// zero init of visible layers
			l_input = l_input.Zero(n_input);
			l_output = l_output.Zero(n_output);
		}

		// init Neural network with existing other NN
		NeuralNetwork(int n_input, int n_hidden, int n_output, const NeuralNetwork& other)
		{
			
			// random init of weights
			weights1 = other.weights1;
			weights2 = other.weights2;
			// random init of bias
			b_hidden = other.b_hidden;
			b_output = other.b_output;
			b_output(0) = 0.5;
			b_output(1) = 0;
			// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
			// zero init of visible layers
			l_input = other.l_input;
			l_output = other.l_output;
			
		}


		void propagate(NN_Input& input_container)
		{
			// convert input into eigen vector
			l_input[0] = input_container.dist;
			l_input[1] = input_container.angle;

			// hidden units
			l_hidden =  (weights1 * l_input) + b_hidden;
			l_output =  (weights2 * l_hidden)+ b_output;
		}

		void mutate()
		{
			int x = (int)random(0,1);
			int y = (int)random(0,1);
			int which_w = (int)random(0,2); // by casting to int the max bound needs to be one int higher
			if (which_w == 0)
				weights1(x,y) += random(-weights1(x,y)*P,weights1(x,y)*P);
			else	
				weights2(x,y) += random(-weights2(x,y)*P,weights2(x,y)*P);
		}

		const Vector3f& getOutput() const{
			return l_output;
		}

		sf::Color calcColor(const float& f){
			float r = weights2.row(0).mean()*100;
			float g = weights2.row(1).mean()*100;
			float b = weights2.row(2).mean()*100;
			float a = f*255;
			return sf::Color(r,g,b,a);
		}

		void save(int ID, const std::string& path)
		{
			// make folder with ID name
			// save all weights and biases to this folder

		}

};