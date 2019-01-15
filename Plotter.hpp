

class Plotter
{
	protected:
		position origin;
		const float xScale = 1;
		const float yScale = 10;
		const float xEnd = config::WINDOW_X-20;
		const float x_spacing = 2;
		std::vector<position> m_data;


	public:
		// line for x axis
		sf::Vertex verticesXAxis[2];
		sf::Vertex verticesYAxis[2];


		Plotter(int x, int y)
		{
			origin.x = x;
			origin.y = y;

			verticesXAxis[0] = sf::Vertex(sf::Vector2f( origin.x, origin.y) , sf::Color(0,0,0));
			verticesXAxis[1] = sf::Vertex(sf::Vector2f( xEnd, origin.y) , sf::Color(0,0,0));

			verticesYAxis[0] = sf::Vertex(sf::Vector2f( origin.x, origin.y) , sf::Color(0,0,0));
			verticesYAxis[1] = sf::Vertex(sf::Vector2f( origin.x, origin.y-100) , sf::Color(0,0,0));
		};

		void update()
		{
			/*
			shove all points to the left
			delete points that are out of bounds (left from origin.x)
			*/
			for ( int i = 0; i < m_data.size(); i++ ){
				m_data[i].x -= x_spacing;
				if (m_data[i].x < origin.x){
					m_data.erase(m_data.begin() + i);
				}
			}
		}

		void addNewPoint(const position& p)
		{
			m_data.emplace_back(position(origin.x + p.x, origin.y - p.y*yScale));
		}
		void addNewPoint(float y)
		{
			m_data.emplace_back(position(xEnd, origin.y - y * yScale));
		}

		std::vector<position>& getData(){
			return m_data;
		}
		position& getData(unsigned int i){
			return m_data[i];
		}

		int getSize(){
			return m_data.size();
		}
};

