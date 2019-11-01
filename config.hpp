#include <string>


struct config
{
	// window specific
	static const unsigned int FRAMERATE = 60;
	static const bool VSYNC = false;
	static const unsigned int WINDOW_X = 1200;
	static const unsigned int WINDOW_Y = 800;
	static const unsigned int TEXTSIZE = 12;

	static constexpr float foodSpriteScale     = 0.3;
	static constexpr float creatureSpriteScale = 1.0;
	static constexpr float hunterSpridteScale   = 0.7;
	static const int worldMargin               = 20;

	// world object specific
	static constexpr float creatureDecayRate = 0.001;
	static constexpr float hunterDecayRate   = 0.001;
	static constexpr float creatureFoodReach = 30;
	static const int REPRO_TIME_CREATURES    = 10;  // in seconds
	static const int REPRO_TIME_HUNTERS      = 3;   // in seconds
	static const int REPRO_TIME_FOOD         = 1;   // in seconds

	static const unsigned int S_CREATURES   = 10;
	static const unsigned int MIN_CREATURES = 0;
	static const unsigned int MAX_CREATURES = 15;
	static const unsigned int S_FOOD        = 4;
	static const unsigned int MAX_FOOD      = 20;
	static const unsigned int S_HUNTERS     = 0;

	static constexpr float MUTATION_FACTOR = 1;

	// loading and saving
	static const bool INIT_LOAD   = true;
	static const bool DO_SAVE     = true;
	static const bool DO_PRINTLOG = true;
	static const std::string SAVE_PATH;
	static const std::string LOAD_ID_CREATURES;
	static const std::string LOAD_ID_HUNTERS;
};
// initialisations for config
const std::string config::SAVE_PATH ="C:/Users/Dario/Documents/GitHub/Evolution-Cpp/build/Saves/";
const std::string config::LOAD_ID_CREATURES = "23071"; 
const std::string config::LOAD_ID_HUNTERS = "23071"; 
