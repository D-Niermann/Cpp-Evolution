
using namespace Eigen;

class NeuralNetwork
{
	private:
		// mutate factor in percent of the mutated value
		static constexpr float P = 5;

		const static int n_layers = 3;

		int n_input, n_hidden, n_output;

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

		static constexpr float w_init_multiplier = 0.1;

	public:
		NeuralNetwork(int n_input, int n_hidden, int n_output) : n_input(n_input), n_hidden(n_hidden), n_output(n_output)
		{
			// random init of weights
			weights1 = weights1.Random(n_hidden, n_input)*w_init_multiplier;
			weights2 = weights2.Random(n_output, n_hidden)*w_init_multiplier;
			// random init of bias
			b_hidden = b_hidden.Random(n_hidden)*w_init_multiplier;
			b_output = b_output.Random(n_output)*w_init_multiplier;
			b_input = b_input.Random(n_input)*w_init_multiplier;
			b_output(0) = 0.5;
			// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
			// zero init of visible layers
			l_input = l_input.Zero(n_input);
			l_hidden = l_hidden.Zero(n_hidden);
			l_output = l_output.Zero(n_output);
		}

		// init Neural network with existing other NN
		NeuralNetwork(int n_input, int n_hidden, int n_output, const NeuralNetwork& other) : n_input(n_input), n_hidden(n_hidden), n_output(n_output)
		{
			
			// random init of weights
			weights1 = other.weights1;
			weights2 = other.weights2;
			// random init of bias
			b_hidden = other.b_hidden;
			b_output = other.b_output;
			b_input = other.b_input;
			// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
			// zero init of visible layers
			l_input = other.l_input;
			l_output = other.l_output;
			
		}
		// init Neural network with existing other NN
		NeuralNetwork(int n_input, int n_hidden, int n_output, const std::string& load_id) : n_input(n_input), n_hidden(n_hidden), n_output(n_output)
		{
			std::string load_string = config::SAVE_PATH + load_id + "_";
			// loading of weights
			weights1 = readMatrix(load_string+"weights1.txt");
			weights2 = readMatrix(load_string+"weights2.txt");
			// loading  of bias
			b_hidden = readMatrix(load_string+"b_hidden.txt");
			b_output = readMatrix(load_string+"b_output.txt");
			b_input = readMatrix(load_string+"b_input.txt");
			// weights1.block(1,0,n_hidden_units-1,1) = MatrixXf().Zero(n_hidden_units-1,1);
			// zero init of visible layers
			l_input = l_input.Zero();
			l_output = l_output.Zero();
			
		}

		void propagate(NN_Input& input_container)
		{
			// convert input into eigen vector
			l_input[0] = std::sqrt(input_container.dist);
			l_input[1] = input_container.angle;

			// hidden units
			l_hidden =  (weights1 * l_input) + b_hidden;
			// clamp(l_hidden, -1, 1);
			l_output =  (weights2 * l_hidden)+ b_output;
		}

		void mutateW()
		{
			int x,y;
			int which_w = (int)random(0,2); // by casting to int the max bound needs to be one int higher
			if (which_w == 0)
			{
				x = (int)random(0,weights1.rows());
				y = (int)random(0,weights1.cols());
				weights1(x,y) += random(-weights1(x,y)*P,weights1(x,y)*P);
			}
			else if (which_w == 1)
			{
				x = (int)random(0,weights2.rows());
				y = (int)random(0,weights2.cols());
				weights2(x,y) += random(-weights2(x,y)*P,weights2(x,y)*P);
			}
		}

		void mutateB()
		{
			int which_b = (int)random(0, n_layers);
			unsigned int x;
			print("Mutate Bias " + std::to_string(which_b));

			if (which_b == 0)
			{
				x = (int) random(0, n_input-1);
				b_input(x) += random(-b_input(x)*P, b_input(x)*P);
			}
			else if (which_b == 1)
			{
				x = (int) random(0, n_hidden-1);
				b_hidden(x) += random(-b_hidden(x)*P, b_hidden(x)*P);
			}
			else if (which_b == 2)
			{
				x = (int) random(0, n_output-1);
				print("Mutate pos:");
				print(n_output);
				b_output(x) += random(-b_output(x)*P, b_output(x)*P);
			}
		
		}
		

		const Vector3f& getOutput() const{
			return l_output;
		}

		sf::Color calcColor(const float& f){
			float r = 255 - weights2.row(0).mean()*100;
			float g = 255 - weights2.row(1).mean()*100;
			float b = 255 - weights2.row(2).mean()*100;
			float a = f*255;
			return sf::Color(r,g,b,a);
		}

		int save(int ID, const std::string& path)
		{
			using namespace std;
			// make folder with ID name
			// could use boost here to actually create a folder
			// save all weights and biases to this folder
			string fileName;
			string folderName = path + std::to_string(ID);
			ofstream myfile;

			fileName = folderName + "_weights1" + ".txt";
			myfile.open(fileName);
			myfile << weights1;
			myfile.close();

			fileName = folderName + "_weights2" + ".txt";
			myfile.open(fileName);
			myfile << weights2;
			myfile.close();

			fileName = folderName + "_b_hidden" + ".txt";
			myfile.open(fileName);
			myfile << b_hidden;
			myfile.close();

			fileName = folderName + "_b_output" + ".txt";
			myfile.open(fileName);
			myfile << b_output;
			myfile.close();

			
			fileName = folderName + "_b_input" + ".txt";
			myfile.open(fileName);
			myfile << b_input;
			myfile.close();

			
			return 1;

		}


		#define MAXBUFSIZE  ((int) 1e3)

		MatrixXf readMatrix(const std::string& filename)
		{
			using namespace std;
			int cols = 0, rows = 0;
			float buff[MAXBUFSIZE];

			// Read numbers from file into buffer.
			ifstream infile;
			infile.open(filename);
			while (! infile.eof())
			{
				string line;
				getline(infile, line);

				int temp_cols = 0;
				stringstream stream(line);
				while(! stream.eof())
					stream >> buff[cols*rows+temp_cols++];

				if (temp_cols == 0)
					continue;

				if (cols == 0)
					cols = temp_cols;

				rows++;
			}

			infile.close();


			// Populate matrix with numbers.
			MatrixXf result(rows,cols);
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					result(i,j) = buff[ cols*i+j ];

			return result;
		};

};
