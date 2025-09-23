#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using JSON = nlohmann::json;
#define SerializeAsJson(...) NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(__VA_ARGS__)
#define SerializeAsJsonWithDefault(...) NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(__VA_ARGS__)

namespace sdk::json {

	template <class ObjT>
	inline std::string Stringify(ObjT&& object, bool pretty = true) {
		const JSON obj(std::forward<ObjT>(object));
		return obj.dump(pretty ? 2 : -1);  // JSON string
	}

	inline std::optional<JSON> FromFile(const std::filesystem::path& filepath) {
		JSON json;
		{
			std::ifstream file(filepath);
			if (!file.is_open()) {
				std::cout << "Failed to open " << filepath << " as json" << std::endl;
				return std::nullopt;
			}
			file >> json;
		}

		return json;
	}

	template <class ObjT>
	inline std::optional<ObjT> FromFileTo(const std::string_view path) {
		try {
			const auto* cpath = path.data();
			std::ifstream file(cpath);
			auto parsed = JSON::parse(file);
			return parsed.get<ObjT>();
		} catch (const std::exception& e) {
			std::cout << "Failed to parse JSON file: " << e.what() << std::endl;
		}
		return std::nullopt;
	}
}  // namespace sdk::json
