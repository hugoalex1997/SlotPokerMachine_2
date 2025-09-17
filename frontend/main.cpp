
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sdk/sleep.hpp>
#include "../backend/api.hpp"
#include "view.hpp"

int main() {
	std::cout << "Initializing Frontend" << std::endl;

	backend::API api;
	frontend::GameView view{};

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
		sdk::SleepUntil(next);
		next += tick;
	}
	std::cout << "Closing Frontend" << std::endl;

	return 0;
}