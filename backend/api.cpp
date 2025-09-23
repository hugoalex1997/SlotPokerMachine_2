#include "api.hpp"

#include <iostream>

#include "aliases.hpp"
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

	void API::Shutdown() {	//
		LogInfo("Destroying backend!!");
	}

	bool API::Initialize() {
		LogInfo("Initializing backend!!");
		return mGame->Initialize();
	}

	bool API::AddMoney(const uint64_t amount) {
		LogInfo("Adding money: {}", amount);
		return mGame->AddMoney(amount);
	}

	bool API::StartPlay() {
		LogInfo("Starting play!!");
		return mGame->StartPlay();
	}

	void API::EndPlay() {
		LogInfo("Ending play!!");
		return mGame->EndPlay();
	}

	bool API::UpdateBetLevel(const uint8_t level) {
		LogInfo("Updating bet level to {}", level);
		return mGame->UpdateBetLevel(level);
	}

	bool API::UpdateLines(const uint8_t lines) {
		LogInfo("Updating lines to {}", lines);
		return mGame->UpdateLines(lines);
	}

}  // namespace backend