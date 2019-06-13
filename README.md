# Cpp-Evolution
Evolution Simulator made with C++, Sfml and Eigen. Uses Reinforcement learning to train Creatures to optain food.

## Program
Starting the Program opens a SFML Window which resembles a GameWorld in which freatures and food sources live. In the World, the creatures are governed by a neural network (NN), which is trained by an evolutionary process based on survival of the fittest and random mutations. 

The   Program can load existing Neural network structures from file, which where saved after a previous run of the Program or start with random initialisation of the NN.

In the beginning, creatures will behave randomly, after appro. 10 minutes of runtime the creates learned to collect food effectivley (i.e. with minimum time and without wasting of their stamina)

## Structure
The Project has two major classes; a Manager class and a Display class. The Display class `SMFL_Display` is responsible for the main loop at runtime, rendering all graphics and sounds and general SFML stuff. The manager class `Manager` manages all WorldObjects (Creatures, Food, ...) like spawning, killing, collision checks and so on. The methods get called by the display class in the main loop.

WorldObjects like creatures and food sources are seperate classes each, but all inherit from `WorldObject` class. 

Creatures contain a neural network, which is managed by the class `NeuralNetwork`. This class is responsible for input and output and learning.

In `main.cpp` is a very simple structure:

``` c++
// create the display class for window and main loop
SFML_Display Display(config::WINDOW_X, config::WINDOW_Y);

// create manager
Manager M;

// add food objects to the manager
M.addWorldObject<Food>(config::S_FOOD, M.food, Display.textureFood, Display.font);

// start the main loop, this will call all necessary manager funtions as well 
Display.StartMainLoop(M, P);
```

