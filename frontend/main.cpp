
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sdk/sleep.hpp>
#include "../backend/api.hpp"
#include "src/view.hpp"

#include <nlohmann/json.hpp>

int main() {
	std::cout << "Initializing Frontend" << std::endl;

	backend::API api;
	frontend::GameView view{};
	if (!view.Initialize()) {
		std::cout << "Failed to initialize frontend!" << std::endl;
		return -1;
	}

	using clock = std::chrono::steady_clock;

	constexpr std::chrono::milliseconds tick{
		16,	 // ~60 FPS
	};

	auto prev = clock::now();
	auto next = prev + tick;

	while (view.IsOpen()) {
		const auto now = clock::now();
		const auto delta = now - prev;

		{  // process backend logic
			view.Process(delta);
		}

		prev = now;
		sdk::sleep::SleepUntil(next);
		next += tick;
	}
	std::cout << "Closing Frontend" << std::endl;

	return 0;
}

//TODO(hg):
// - Add layer level to scene.
// - Add a proper logger.