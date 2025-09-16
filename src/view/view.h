#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <memory>

class GameView {
public:
	GameView();

	void Process(std::chrono::nanoseconds delta);

	void Close();

	[[nodiscard]] bool IsOpen() const { return window->isOpen(); };

private:
	void draw();

	void clear();

	void resize(unsigned int width, unsigned int height);

	void keyboardButtonPressed(const sf::Event::KeyEvent& key);

	void mouseButtonPressed(const sf::Event::MouseButtonEvent& mouse);

private:
	std::unique_ptr<sf::RenderWindow> window{nullptr};
};
