#include "view.h"

#include <iostream>



GameView::GameView() {
    window = this->CreateWindow();
}

sf::RenderWindow* GameView::CreateWindow() {
    auto* _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
    return _window;
}

sf::RenderWindow* GameView::GetWindow() {
    return window;
}

void update() {
    std::cout << "Game View Update" << std::endl;
}