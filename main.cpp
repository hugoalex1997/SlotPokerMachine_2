#include "src/game.h"
#include <iostream>
// #include "rapidjson/writer.h"
// #include "rapidjson/document.h"
// #include "rapidjson/stringbuffer.h"

int main(int argc, char** argv)
{
    Game::Instance()->Run();

    return 0;
}


/* TODO: 
	Add Game Controller
	Add Game View 
    Include Rapidjson for JSON Parse
	Analyse how to include only header file name, instead of path
	
*/