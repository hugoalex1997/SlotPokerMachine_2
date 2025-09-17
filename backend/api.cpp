#include "api.hpp"
#include "game.hpp"

namespace backend {
	API::API() {
		Game game{};
		game.Run();
	}
}  // namespace backend