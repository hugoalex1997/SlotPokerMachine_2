#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "fsm/finitestatemachine.h"
#include "accounting/accounting.h"
#include <vector>

#define MAX_BET 100
#define MAX_LINES 5
class Game {
    public:

    Game() {};

	FiniteStateMachine* fsm = FiniteStateMachine::Instance();
	Accounting* accounting = Accounting::Instance();

    void Run();
	bool StartPlay();
	void PauseGame();
	bool AddMoney(int amount);
	/**
	 * @brief Change Game Bet
	 * 
	 * @param increment In case of this parameter be true the bet should increment by one, otherwise decrement by one.
	 */
	void ChangeBet(bool increment);
	/**
	 * @brief Change Game Bet Lines
	 * 
	 * @param increment In case of this parameter be true the number of lines to bet should increment by one, otherwise decrement by one.
	 */
	void ChangeBetLines(bool increment);

	unsigned int getBet() const { return bet; }
	unsigned char getBetLines() const { return betLines; }

	unsigned int getMaxBet() const { return maxBet; }
	unsigned char getMaxBetLines() const { return maxBetLines; }
	
    private:
	void CreateFSM(std::vector<State> states,std::vector<Transition> transitions);

	void setBet(unsigned int bet_) { bet = bet_; }
	void setBetLines(unsigned int betLines_) { betLines = betLines_; }
	unsigned int bet {1};
	unsigned char betLines {1};

	unsigned int maxBet {MAX_BET};
	unsigned char maxBetLines {MAX_LINES};
	
};


#endif //_GAME_H