#pragma once
#include <cstdint>
#include <memory>
namespace backend {

	class Game;

	class API {
	public:
		API();

		~API();

		//================================ Getters ================================//

		[[nodiscard]] uint64_t GetCurrentCredits() const;

		[[nodiscard]] uint64_t GetCurrentBet() const;

		[[nodiscard]] uint8_t GetCurrentBetLevel() const;

		[[nodiscard]] uint8_t GetCurrentLines() const;

		//=========================================================================//

		void Shutdown();

		[[nodiscard]] bool Initialize();

		[[nodiscard]] bool AddMoney(uint64_t amount);

		[[nodiscard]] bool StartPlay();

		void EndPlay();

		[[nodiscard]] bool UpdateBetLevel(uint8_t level);

		[[nodiscard]] bool UpdateLines(uint8_t lines);

	private:
		std::unique_ptr<Game> mGame{};
	};
}  // namespace backend