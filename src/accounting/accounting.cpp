#include "accounting.h"


Accounting* Accounting::Instance() {
    static Accounting instance;
    return &instance;
}

void AccountingImplementation::AddMoney(unsigned int amount) {
	setCredits(getCredits() + amount);
}