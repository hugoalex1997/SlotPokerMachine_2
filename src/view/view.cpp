#include "view.h"

#include <iostream>



GameView::GameView() {
    window = this->CreateWindow();
}

sf::RenderWindow* GameView::CreateWindow() {
    auto* _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
    return _window;
}

void GameView::Update() {
    window->display();
}

void GameView::Close() {
    window->close();
}

bool GameView::isOpen() {
    return window->isOpen();
}

void GameView::Clear() {
    window->clear();
}
