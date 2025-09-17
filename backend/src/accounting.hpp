#pragma once

#include <cstdint>

namespace backend {
	class Accounting {
	public:
		[[nodiscard]] uint64_t GetCredits() const { return mCredits; }

		void AddMoney(uint64_t amount);

		[[nodiscard]] bool StartPlay(uint64_t bet);

	private:
		uint64_t mCredits{};
	};

}  // namespace backend