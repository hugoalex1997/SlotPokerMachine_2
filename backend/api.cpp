#include "api.hpp"
#include <iostream>
#include "game.hpp"

namespace backend {

	//================================ Getters ================================//

	uint64_t API::GetCurrentCredits() const { return mGame->GetCurrentCredits(); }

	uint64_t API::GetCurrentBet() const { return mGame->GetCurrentBet(); }

	uint8_t API::GetCurrentBetLevel() const { return mGame->GetCurrentBetLevel(); }

	uint8_t API::GetCurrentLines() const { return mGame->GetCurrentLines(); }

	//=========================================================================//

	API::API() { mGame = std::make_unique<Game>(); }

	API::~API() = default;

	void API::Shutdown() { std::cout << "Destroying backend!!" << std::endl; }

	bool API::Initialize() {
		std::cout << "Initializing backend!!" << std::endl;
		return mGame->Initialize();
	}

	bool API::AddMoney(const uint64_t amount) {
		std::cout << "Adding money: " << amount << std::endl;
		return mGame->AddMoney(amount);
	}

	bool API::StartPlay() {
		std::cout << "Starting play!!" << std::endl;
		return mGame->StartPlay();
	}

	void API::EndPlay() {
		std::cout << "Ending play!!" << std::endl;
		return mGame->EndPlay();
	}

	bool API::UpdateBetLevel(const uint8_t level) {
		std::cout << "Updating bet level to " << static_cast<int>(level) << std::endl;
		return mGame->UpdateBetLevel(level);
	}

	bool API::UpdateLines(const uint8_t lines) {
		std::cout << "Updating lines to " << static_cast<int>(lines) << std::endl;
		return mGame->UpdateLines(lines);
	}

}  // namespace backend