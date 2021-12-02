#include <iostream>

#include "game.h"
#include "finitestatemachine.h"



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