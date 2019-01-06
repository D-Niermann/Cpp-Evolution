

class SFML_Display
{
  protected:
	// window size
	unsigned int wSize_x, wSize_y;
	sf::RenderWindow m_window;
	int frame;

  public:
	sf::Texture textureCreature;
	sf::Texture textureFood;

	void loadTextures()
	{
		// load creature texture
		if (!textureCreature.loadFromFile("Images/circle3.png"))
		{
			throw("Error");
		}
		//load plant textures
		if (!textureFood.loadFromFile("Images/tree_01.png"))
		{
			throw("Error");
		}
	}
	
	void printLog(Manager& M){
		print("--- GAME INFO: ---")
		// print("Frame:" + std::to_string(frame));
		print("Active Creatures:" + std::to_string(M.creatures.size()));
		print("Active Plants:" + std::to_string(M.food.size()));
		print("\n");
	}

  public:
	//constructor
	SFML_Display(unsigned int wSize_x, unsigned int wSize_y) : wSize_x(wSize_x),
															   wSize_y(wSize_y),
															   m_window({wSize_x, wSize_y}, "MainWindow")
	{
		loadTextures();
		m_window.setFramerateLimit(config::FRAMERATE);
		m_window.setVerticalSyncEnabled(config::VSYNC);
		frame = 0;
	}

	//deconstructor
	~SFML_Display() {}

	void StartMainLoop(Manager &M)
	{

		// main loop
		while (m_window.isOpen())
		{
			// count frames
			frame += 1;

			// poll events from sfml
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
			}

			// print log
			if (frame % 60 == 0){
				// printLog(M);
			}

			// update all instances in the game world
			M.updateAll();

			// clear the window from prev frame
			m_window.clear(sf::Color(50, 200, 50));

			// iterate all sprites and draw them
			for (int i = 0; i < M.food.size(); i++)
			{
				m_window.draw(M.food[i].getSprite());
			}
			for (int i = 0; i < M.creatures.size(); i++)
			{
				m_window.draw(M.creatures[i].getSprite());
				// draw debug lines
				//m_window.draw(M.creatures[i].vertices, 2, sf::Lines);
			}

			// display all stuff
			m_window.display();
		}
	}
};