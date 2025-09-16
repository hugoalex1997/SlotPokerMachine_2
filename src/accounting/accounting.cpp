#include "accounting.h"

Accounting* Accounting::Instance() {
	static Accounting instance;
	return &instance;
}

void AccountingImplementation::AddMoney(unsigned int amount) { setCredits(getCredits() + amount); }

bool AccountingImplementation::StartPlay(unsigned int bet) {
	if (bet <= getCredits()) {
		this->setCredits(this->getCredits() - bet);
		return true;
	}
	return false;
}