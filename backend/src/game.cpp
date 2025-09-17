#include "game.hpp"
#include <iostream>

namespace backend {

	bool Game::Initialize() {
		std::cout << "Starting backend loading" << std::endl;

		mAccounting = std::make_unique<Accounting>();
		mState = GameState::Idle;

		mRunning = true;
		return true;
	}

	bool Game::StartPlay() {
		if (mState != GameState::Idle) {
			std::cout << "Cannot start play, game not in idle state." << std::endl;
			return false;
		}

		const auto bet = GetCurrentBet();
		if (!mAccounting->StartPlay(bet)) {
			std::cout << "Cannot start play, insufficient credits." << std::endl;
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
			std::cout << "Bet value exceeds maximum allowed bet." << std::endl;
			return false;
		}

		mBetLevel = level;
		return true;
	}

	bool Game::UpdateLines(const uint8_t lines) {
		if (lines > kMaxLines) {
			std::cout << "Lines value exceeds maximum allowed lines." << std::endl;
			return false;
		}

		mLines = lines;
		return true;
	}
}  // namespace backend