#pragma once

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
  sf::RenderWindow *CreateWindow();

  sf::RenderWindow *window{nullptr};
};
