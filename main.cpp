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
    Add Unit Tests to FSM
    Finish trigger transition logic
    Include Rapidjson for JSON Parse
*/