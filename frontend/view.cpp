#include "view.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

namespace frontend {

	GameView::GameView() {	//
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game");
	}

	void GameView::Close() {  //
		window->close();
	}

	void GameView::clear() {  //
		window->clear();
	}

	void GameView::Process(const std::chrono::nanoseconds delta) {
		sf::Event event;
		while (window->pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: {
					Close();
				} break;

				case sf::Event::Resized: {
					resize(event.size.width, event.size.height);
				} break;

				case sf::Event::KeyPressed: {
					keyboardButtonPressed(event.key);
				} break;

				case sf::Event::MouseButtonPressed: {
					mouseButtonPressed(event.mouseButton);
				} break;

				default:
					break;
			}

			window->clear(sf::Color::Black);

			draw();

			window->display();
		}
	}

	void GameView::draw() {
		window->clear(sf::Color::Black);

		// TODO(hg): implement draw logic

		window->display();
	}

	void GameView::resize(const unsigned int width, const unsigned int height) {
		std::cout << "Window Resized: y - " << width << "x - " << height << std::endl;

		sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
		window->setView(sf::View(visibleArea));
	}

	void GameView::keyboardButtonPressed(const sf::Event::KeyEvent& keyboard) {
		std::cout << "Key Pressed: " << keyboard.code << std::endl;
	}

	void GameView::mouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) {
		std::cout << "Mouse Button Pressed: " << mouse.button << std::endl;
	}
}  // namespace frontend