#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include "Dependencies/eigen/Eigen/Dense"
#include <SFML/Graphics.hpp>
#include "SFML/Window/Keyboard.hpp"


#include "utils.hpp"
#include "NeuralNetwork.hpp"
#include "WorldObject.hpp"
#include "Creature.hpp"
#include "Food.hpp"
#include "Manager.hpp"
#include "Plotter.hpp"
#include "SFML_Display.hpp"



int main()
{
	// create the display class for window and main loop
	SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);
	
	// create manager
	Manager M;

	// create plotters
	Plotter P(config::WINDOW_X - 300, config::WINDOW_Y - 40);

	// add WorldObjects
	M.addWorldObject<Creature>(config::S_CREATURES, M.creatures, Display.textureCreature, Display.font);
	M.addWorldObject<Food>(config::S_FOOD, M.food, Display.textureFood, Display.font);


	Display.StartMainLoop(M, P);
}