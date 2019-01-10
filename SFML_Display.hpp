

class SFML_Display
{
  protected:
	// window size
	unsigned int wSize_x, wSize_y;
	sf::RenderWindow m_window;
	int frame;
	bool GamePaused;
	// plotter
	sf::Sprite spritePlotPoint;


  public:
	sf::Texture textureCreature;
	sf::Texture textureFood;
	sf::Texture texturePlotPoint;
	sf::Font font;


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
		//load plotpoint textures
		if (!texturePlotPoint.loadFromFile("Images/circle3.png"))
		{
			throw("Error");
		}
		spritePlotPoint.setTexture(texturePlotPoint);
		spritePlotPoint.setColor(sf::Color(10,30,230));
		spritePlotPoint.setScale(0.1,0.1);
	}
	
	void printLog(Manager& M){
		print("--- GAME INFO: ---");
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
		
		// load font
		if (!font.loadFromFile("Fonts/arial.ttf")){}

		// window settings
		m_window.setFramerateLimit(config::FRAMERATE);
		m_window.setVerticalSyncEnabled(config::VSYNC);
		frame = 0;
		GamePaused = false;
	}

	//deconstructor
	~SFML_Display() {}

	void StartMainLoop(Manager &M, Plotter &P)
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
				// window close event
				if (event.type == sf::Event::Closed)
					m_window.close();

				// key press events
				if (event.type == sf::Event::KeyPressed){
					// P key pressed 
					if (event.key.code == sf::Keyboard::P){
						GamePaused = !GamePaused;
						if(GamePaused){
							std::cout << "Game Paused!" << std::endl;
						}
						else{
							std::cout << "Game Continued!" << std::endl;
						}
					}
				}

			}

			// update all instances in the game world
			if (!GamePaused)
			{
				// update all creatures and food
				M.updateAll();
				
				// check reproduction and print log
				if (frame % 60 == 0){
					M.reproduceCreatures(textureCreature, font);
					// M.reproduceFood(textureFood, font);
					// print log
					printLog(M);

					// update plots
					P.addNewPoint(M.getAvHealth());
					P.update();
				}
					

			}

			//Draw stuff
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
			
				/*
				DEBUG DRAW
				*/
				// draw debug lines
				m_window.draw(M.creatures[i].vertices, 2, sf::Lines);
				// debug text
				for (int t = 0; t<2; t++){
					m_window.draw(M.creatures[i].getText(t));
					m_window.draw(P.verticesXAxis, 2, sf::Lines);
					m_window.draw(P.verticesYAxis, 2, sf::Lines);
				}
			}

			position pos;
			for (int i = 0; i<P.getSize(); i++){
				// draw a sprite on each position
				pos = P.getData(i);
				spritePlotPoint.setPosition(pos.x, pos.y);
				m_window.draw(spritePlotPoint);
			}

			// display all stuff
			m_window.display();
		}
	}
};