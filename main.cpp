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
	manager class does not really push back, count vars need to be added correctly, also needs remove (delete) methods
	manager class only one array for all sprites ? or one methods that just returns all sprites correctly
		- would remove all dublicate accessor functions
	manager class one array for food and creatures ? vector<base class> polymorphism?
		- or just give the save array to the functions and tell a telplate which class to store in it 
*/

int main()
{
	// create the display class for window and main loop
	SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);
	
	// create manager
	Manager M;
	M.addFood(20, Display.textureFood);
	M.addCreatures(3, Display.textureCreature);


	Display.StartMainLoop(M);
}