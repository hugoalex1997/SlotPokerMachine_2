#pragma once

#include <chrono>
#include <thread>

namespace sdk {
	template <class ClockT, class DurationT>
	inline void SleepUntil(const std::chrono::time_point<ClockT, DurationT>& tp) {
		std::this_thread::sleep_until(tp - std::chrono::microseconds(10));
		while (tp >= ClockT::now()) std::this_thread::yield();	// NOLINT
	}

	template <class RepT, class PeriodT>
	inline void SleepFor(const std::chrono::duration<RepT, PeriodT>& duration) {
		std::this_thread::sleep_for(duration);
	}
}  // namespace sdk