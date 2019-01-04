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
	Manager class does not really push back, count vars need to be added correctly, also needs remove (delete) methods

	Manager
		- or just give the save array to the functions and tell a telplate which class to store in it 
*/

int main()
{
	// create the display class for window and main loop
	SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);
	
	// create manager
	Manager M;
	M.addWorldObject<Creature>(2, M.creatures, Display.textureCreature);
	M.addWorldObject<Food>(2, M.food, Display.textureFood);


	Display.StartMainLoop(M);
}