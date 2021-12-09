#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "accounting/accounting.h"


struct MockAccounting : public AccountingImplementation {
    MockAccounting() {};
};

TEST(Accounting,AddCredits) {
   	auto accounting = new MockAccounting();
    ASSERT_EQ(accounting->getCredits(),0);
	accounting->AddMoney(10);
	ASSERT_EQ(accounting->getCredits(),10);
}


