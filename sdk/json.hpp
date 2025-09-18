#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace sdk::json {

	static nlohmann::json ToJson(const std::filesystem::path& filepath) {
		nlohmann::json json;
		{
			std::ifstream file(filepath);
			if (!file.is_open()) {
				std::cout << "Failed to open " << filepath << " as json" << std::endl;
				return {};
			}
			file >> json;
		}

		return json;
	}
}  // namespace sdk::json