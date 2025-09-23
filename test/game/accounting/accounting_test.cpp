#include "accounting/accounting.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct MockAccounting : public AccountingImplementation {
	MockAccounting() {};
};

TEST(Accounting, AddCredits) {
	unsigned int bet = 5;
	auto accounting = new MockAccounting();
	ASSERT_EQ(accounting->getCredits(), 0);
	ASSERT_EQ(accounting->StartPlay(bet), false);
	accounting->AddMoney(10);
	ASSERT_EQ(accounting->getCredits(), 10);
	ASSERT_EQ(accounting->StartPlay(bet), true);
	ASSERT_EQ(accounting->getCredits(), 10 - bet);
}
