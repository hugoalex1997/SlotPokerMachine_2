#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <memory>

namespace frontend {

	class Scene;
	class AssetsManager;

	class GameView {
	public:
		GameView();

		~GameView();

		[[nodiscard]] bool Initialize();

		void Process(std::chrono::nanoseconds delta);

		void Close();

		[[nodiscard]] bool IsOpen() const { return mWindow->isOpen(); };

	private:
		void createGameContainer();

		void createSettingsContainer();

		void draw();

		void clear();

		void resize(unsigned int width, unsigned int height);

		void keyboardButtonPressed(const sf::Event::KeyEvent& key);

		void mouseButtonPressed(const sf::Event::MouseButtonEvent& mouse);

	private:
		std::unique_ptr<AssetsManager> mAssetsmgr{nullptr};
		std::unique_ptr<sf::RenderWindow> mWindow{nullptr};
		std::unique_ptr<Scene> mScene{nullptr};
	};
}  // namespace frontend
