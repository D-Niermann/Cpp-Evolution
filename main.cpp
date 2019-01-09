#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include "Dependencies/eigen/Eigen/Dense"


#include "utils.hpp"
#include "WorldObject.hpp"
#include "Creature.hpp"
#include "Food.hpp"
#include "Manager.hpp"
#include "SFML_Display.hpp"

/*
TODO:
	Manager, Display and WorldObject instances should have references to each other (maybe)
	input actually smalles distance and angle to create
	enable real push back dynamical array for reproduction
*/

int main()
{
	// create the display class for window and main loop
	SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);
	
	// create manager
	Manager M;

	// add WorldObjects
	M.addWorldObject<Creature>(config::MAX_CREATURES, M.creatures, Display.textureCreature, Display.font);
	M.addWorldObject<Food>(config::MAX_FOOD, M.food, Display.textureFood, Display.font);


	Display.StartMainLoop(M);
}