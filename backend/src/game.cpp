#include "game.hpp"
#include <iostream>
#include "aliases.hpp"

namespace backend {

	bool Game::Initialize() {
		mAccounting = std::make_unique<Accounting>();
		mState = GameState::Idle;

		mRunning = true;
		return true;
	}

	bool Game::StartPlay() {
		if (mState != GameState::Idle) {
			LogError("Cannot start play because game is not in idle state.");
			return false;
		}

		const auto bet = GetCurrentBet();
		if (!mAccounting->StartPlay(bet)) {
			LogError("Cannot start play, insufficient credits.");
			return false;
		}

		mState = GameState::Playing;
		return true;
	}

	void Game::EndPlay() {
		const uint64_t winnings = 100;	// TODO: calculate wins
		mAccounting->AddMoney(winnings);
		mState = GameState::Idle;
	}

	bool Game::AddMoney(const uint64_t amount) {  //
		mAccounting->AddMoney(amount);
		return true;
	}

	bool Game::UpdateBetLevel(const uint8_t level) {
		if (level > kMaxBetLevel) {
			LogError("Bet value exceeds maximum allowed bet.");
			return false;
		}

		mBetLevel = level;
		return true;
	}

	bool Game::UpdateLines(const uint8_t lines) {
		if (lines > kMaxLines) {
			LogError("Lines value exceeds maximum allowed lines.");
			return false;
		}

		mLines = lines;
		return true;
	}
}  // namespace backend