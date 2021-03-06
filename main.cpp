#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <memory>
#include <random>
#include "Dependencies/eigen/Eigen/Dense"
#include <SFML/Graphics.hpp>
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Window/ContextSettings.hpp>
#include <typeinfo>

#include "config.hpp"
#include "utils.hpp"
#include "NeuralNetwork.hpp"
#include "WorldObject.hpp"
#include "Creature.hpp"
#include "Hunter.hpp"
#include "Food.hpp"
#include "Manager.hpp"
#include "Plotter.hpp"
#include "SFML_Display.hpp"



int main()
{
	// config::load("C:/Users/dniermann/Documents/GitHub/Cpp-Evolution/config.txt");
	// sf::ContextSettings(0,0,4);

	// srand(223132);

	// create the display class for window and main loop
	SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);
	
	// create manager
	Manager M;

	// create plotters
	Plotter P(config::WINDOW_X - 300, config::WINDOW_Y - 40);

	
	
	// add WorldObjects
	
		// creatures, either init them randomly or load them from file
		if (!config::INIT_LOAD){
			print("Random init of creatures!");
			M.addWorldObject<Creature>(config::S_CREATURES, M.creatures, Display.textureCreature, Display.font);
		}
		else{ 
			print("Loading from file! " + config::LOAD_ID_CREATURES);
			M.addWorldObject<Creature>(config::S_CREATURES, M.creatures, Display.textureCreature, Display.font, config::LOAD_ID_CREATURES);
		}


		// food
		M.addWorldObject<Food>(config::S_FOOD, M.food, Display.textureFood, Display.font);



	Display.StartMainLoop(M, P);
	
}