#pragma once

#include <chrono>
#include <memory>

#include "accounting.hpp"
#include "sdk/enums.hpp"

namespace backend {

	class Accounting;

	enum class GameState : uint8_t {
		None,
		Idle,
		Playing,
		__count__,
	};

	class Game {
	public:
		Game() = default;

		~Game() = default;

		[[nodiscard]] const uint64_t GetCurrentCredits() const { return mAccounting->GetCredits(); }

		[[nodiscard]] uint64_t GetCurrentBet() const { return mBetLevel * mLines; };

		[[nodiscard]] uint8_t GetCurrentBetLevel() const { return mBetLevel; };

		[[nodiscard]] uint8_t GetCurrentLines() const { return mLines; };

		[[nodiscard]] bool Initialize();

		[[nodiscard]] bool StartPlay();

		void EndPlay();

		[[nodiscard]] bool AddMoney(uint64_t amount);

		[[nodiscard]] bool UpdateBetLevel(uint8_t level);

		[[nodiscard]] bool UpdateLines(uint8_t lines);

	private:
		void process(std::chrono::nanoseconds delta);

	private:
		static constexpr const uint8_t kMaxBetLevel{100};
		static constexpr const uint8_t kMaxLines{5};

		bool mRunning{false};

		std::unique_ptr<Accounting> mAccounting{};

		GameState mState{GameState::None};
		uint8_t mBetLevel{1};
		uint8_t mLines{1};
	};
}  // namespace backend

//================================ ENUMS AS JSON =============================//

// clang-format off
EnumBegin(backend::GameState)
	EnumCustomEntry(None, "none")
	EnumCustomEntry(Idle, "idle")
	EnumCustomEntry(Playing, "playing")
	EnumCustomEntry(__count__, "__count__")
EnumEnd()

EnumAsJson(backend, GameState)
	// clang-format on

	//============================================================================//
