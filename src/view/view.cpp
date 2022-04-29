#include "view.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

GameView::GameView() {
    std::cout << "default constructor" << std::endl;
}

void GameView::init() {

    std::cout << "init" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    //TODO: study multithreading to implement on view and main
    while() {

    }
}