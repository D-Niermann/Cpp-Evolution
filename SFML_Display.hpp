

class SFML_Display
{
  protected:
	// window size
	unsigned int wSize_x, wSize_y;
	sf::RenderWindow m_window;

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

  public:
	//constructor
	SFML_Display(unsigned int wSize_x, unsigned int wSize_y) : wSize_x(wSize_x),
															   wSize_y(wSize_y),
															   m_window({wSize_x, wSize_y}, "MainWindow")
	{
		loadTextures();
		m_window.setFramerateLimit(60);
		m_window.setVerticalSyncEnabled(true);
	}

	//deconstructor
	~SFML_Display() {}

	void StartMainLoop(Manager &M)
	{

		// main loop
		while (m_window.isOpen())
		{
			// poll events from sfml
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
			}

			// update all instances in the game world
			M.updateAll();

			// clear the window from prev frame
			m_window.clear(sf::Color(50, 200, 50));

			// iterate all sprites and draw them
			for (int i = 0; i < M.getFoodCount(); i++)
			{
				m_window.draw(M.getFoodSprite(i));
			}
			for (int i = 0; i < M.getObjectCount(); i++)
			{
				m_window.draw(M.getCreatureSprite(i));
			}

			// display all stuff
			m_window.display();
		}
	}
};