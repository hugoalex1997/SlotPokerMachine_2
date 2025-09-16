#pragma once

class AccountingImplementation {

	unsigned int credits {0};
	void setCredits(unsigned int credits_) { credits = credits_; }

public:
	// Implementation
	void AddMoney(unsigned int amount);
	bool StartPlay(unsigned int bet);

	//Getters and Setters
	unsigned int getCredits() const { return credits; }

};

class Accounting {

	AccountingImplementation impl;

public:
		
	static Accounting* Instance();

	void AddMoney(unsigned int amount) {impl.AddMoney(amount);}
	bool StartPlay(unsigned int bet) {return impl.StartPlay(bet);}
	unsigned int getCredits() const {return impl.getCredits();}


};