#include "accounting.hpp"

namespace backend {

	void Accounting::AddMoney(uint64_t amount) {  //
		mCredits += amount;
	}

	bool Accounting::StartPlay(uint64_t bet) {
		if (bet > mCredits) {
			return false;
		}

		mCredits -= bet;
		return true;
	}
}  // namespace backend