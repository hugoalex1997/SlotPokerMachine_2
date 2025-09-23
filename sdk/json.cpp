#include "json.hpp"

namespace sdk::json {
	std::optional<JSON> FromFile(const std::filesystem::path& filepath) {
		JSON json;
		{
			std::ifstream file(filepath);
			if (!file.is_open()) {
				MainLogError("Failed to open {} as json", filepath.string());
				return std::nullopt;
			}
			file >> json;
		}

		return json;
	}
}  // namespace sdk::json