#include <iostream>

#include "game.h"
#include "fsm/finitestatemachine.h"
//#include "accounting/accounting.h"


Game* Game::Instance() {
    static Game instance;
    return &instance;
} 

Game::Game() {

}

Game::~Game() {

}

void Game::Run() {
    std::cout << " Game is Starting" << std::endl;
    
}