#pragma once

#include <chrono>
#include <vector>

#include "accounting/accounting.hpp"
#include "fsm/finitestatemachine.hpp"

#define MAX_BET 100
#define MAX_LINES 5

namespace backend {
	class Game {
	public:
		Game() = default;

		~Game() = default;

		FiniteStateMachine* fsm = FiniteStateMachine::Instance();
		Accounting* accounting = Accounting::Instance();

		void Run();
		bool StartPlay();
		void PauseGame();
		void AddMoney(int amount);
		/**
		 * @brief Change Game Bet
		 *
		 * @param increment In case of this parameter be true the bet should increment
		 * by one, otherwise decrement by one.
		 */
		void ChangeBet(bool increment);
		/**
		 * @brief Change Game Bet Lines
		 *
		 * @param increment In case of this parameter be true the number of lines to
		 * bet should increment by one, otherwise decrement by one.
		 */
		void ChangeLines(bool increment);

		unsigned int getBet() const { return bet; }
		unsigned char getLines() const { return lines; }

		unsigned int getMaxBet() const { return maxBet; }
		unsigned char getMaxLines() const { return maxLines; }

	private:
		void Process(std::chrono::nanoseconds delta);
		void CreateFSM(std::vector<State> states, std::vector<Transition> transitions);

		void setBet(unsigned int bet_) { bet = bet_; }
		void setLines(unsigned int Lines_) { lines = Lines_; }
		unsigned int bet{1};
		unsigned char lines{1};

		unsigned int maxBet{MAX_BET};
		unsigned char maxLines{MAX_LINES};

	protected:
		bool running{true};
	};
}  // namespace backend