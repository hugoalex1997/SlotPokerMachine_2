#include "view.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include "assetsmanager.hpp"
#include "defines.hpp"
#include "scene.hpp"

namespace frontend {

	GameView::GameView() {	//
		mAssetsmgr = std::make_unique<AssetsManager>();
		mWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOWSIZE_WIDHT, WINDOWSIZE_HEIGHT), "Game");
		mScene = std::make_unique<Scene>("main", true);
	}

	GameView::~GameView() = default;

	bool GameView::Initialize() {  //
		if (!mAssetsmgr->LoadAssets()) {
			std::cout << "Failed to load assets!" << std::endl;
			return false;
		}

		mScene->AttachAssetsManager(mAssetsmgr.get());

		if (!mScene->LoadScene()) {
			std::cout << "Failed to load scene!" << std::endl;
			return false;
		}

		return true;
	}

	void GameView::Close() {  //
		mWindow->close();
	}

	void GameView::clear() {  //
		mWindow->clear();
	}

	void GameView::Process(const std::chrono::nanoseconds delta) {
		sf::Event event;
		while (mWindow->pollEvent(event)) {
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

			draw();
		}
	}

	void GameView::draw() {
		mWindow->clear(sf::Color::Black);

		mScene->Draw(*mWindow);

		mWindow->display();
	}

	void GameView::resize(const unsigned int width, const unsigned int height) {
		std::cout << "Window Resized: y - " << width << "x - " << height << std::endl;

		sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
		mWindow->setView(sf::View(visibleArea));
	}

	void GameView::keyboardButtonPressed(const sf::Event::KeyEvent& keyboard) {
		std::cout << "Key Pressed: " << keyboard.code << std::endl;
	}

	void GameView::mouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) {
		std::cout << "Mouse Button Pressed: " << mouse.button << std::endl;
	}
}  // namespace frontend