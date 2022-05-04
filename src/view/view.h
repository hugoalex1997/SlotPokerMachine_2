#pragma once
#ifndef _VIEW_H
#define _VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameView {
    
public:
    GameView();
    sf::RenderWindow* GetWindow();
private:
    
    sf::RenderWindow* CreateWindow();
    void update();

    sf::RenderWindow* window{nullptr};
};




#endif //_VIEW_H