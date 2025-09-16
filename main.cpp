#include "src/game.h"
// #include "rapidjson/writer.h"
// #include "rapidjson/document.h"
// #include "rapidjson/stringbuffer.h"

#include <SFML/Graphics.hpp>

int main() {
	Game game;
	game.Run();
	return 0;
}

/* TODO:
		Add Game Controller
		Analyse how to include only header file name, instead of path
		Add InputManager For Mouse and Keyboard
*/