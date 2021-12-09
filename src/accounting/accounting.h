#ifndef _Accounting_H
#define _Accounting_H


class AccountingImplementation {

	unsigned int credits {0};
	void setCredits(unsigned int credits_) { credits = credits_; }

public:

	void AddMoney(unsigned int amount);
	unsigned int getCredits() const { return credits; }
	
};

class Accounting {

	AccountingImplementation impl;

public:
		
	static Accounting* Instance();

	void AddMoney(unsigned int amount) {impl.AddMoney(amount);}
	unsigned int getCredits() const {return impl.getCredits();}


};

#endif //_Accounting_H