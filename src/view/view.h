#pragma once
#ifndef _VIEW_H
#define _VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameView {
    
public:
    GameView();
    void Update();
    void Close();
    bool isOpen();
    void Clear();
private:
    
    sf::RenderWindow* CreateWindow();
    

    sf::RenderWindow* window{nullptr};
};




#endif //_VIEW_H