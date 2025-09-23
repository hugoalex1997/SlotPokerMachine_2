
#include <SFML/Graphics.hpp>
#include <iostream>
#include "backend/api.hpp"
#include "src/view.hpp"

#include "aliases.h"
#include "sdk/sleep.hpp"

int main() {
	backend::API api;
	frontend::GameView view{};
	if (!view.Initialize()) {
		std::cerr << "Failed to initialize frontend!" << std::endl;
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

// TODO(hg):
//  - Add layer level to scene.
//  - Add a proper logger.