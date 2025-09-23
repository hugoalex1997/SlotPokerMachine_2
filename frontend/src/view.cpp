#include "view.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

#include "aliases.hpp"
#include "assetsmanager.hpp"
#include "defines.hpp"
#include "scene/scene.hpp"
#include "src/data_structures/sfml.hpp"

namespace frontend {

	GameView::GameView() {	//
		mAssetsmgr = std::make_unique<AssetsManager>();
		mWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOWSIZE_WIDHT, WINDOWSIZE_HEIGHT), "Game");
		mScene = std::make_unique<Scene>("main", true);
	}

	GameView::~GameView() = default;

	bool GameView::Initialize() {  //

		if (!mAssetsmgr->LoadAssets()) {
			LogError("Failed to load assets!");
			return false;
		}

		mScene->AttachAssetsManager(mAssetsmgr.get());

		if (!mScene->LoadScene()) {
			LogError("Failed to load scene!");
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
		LogInfo("Window Resized: y -{} x - {}", height, width);

		sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
		mWindow->setView(sf::View(visibleArea));
	}

	void GameView::keyboardButtonPressed(const sf::Event::KeyEvent& keyboard) {
		LogInfo("Key Pressed: {}", sdk::enums::ToString(keyboard.code));
	}

	void GameView::mouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) {
		LogInfo("Mouse Button Pressed: {}", sdk::enums::ToString(mouse.button));
	}
}  // namespace frontend