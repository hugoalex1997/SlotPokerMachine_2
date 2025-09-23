#pragma once

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

#include "logger.hpp"

using JSON = nlohmann::json;
#define SerializeAsJson(...) NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(__VA_ARGS__)
#define SerializeAsJsonWithDefault(...) NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(__VA_ARGS__)
#define SerializeAsJsonEmpty(type)                                                                                    \
	inline void to_json(nlohmann::json& nlohmann_json_j, const type&) { nlohmann_json_j = nlohmann::json::object(); } \
	inline void from_json(const nlohmann::json&, type&) {}

namespace sdk::json {

	std::optional<JSON> FromFile(const std::filesystem::path& filepath);

	template <class ObjT>
	inline std::optional<ObjT> FromFileTo(const std::string_view path) {
		try {
			const auto* cpath = path.data();
			std::ifstream file(cpath);
			auto parsed = JSON::parse(file);
			return parsed.get<ObjT>();
		} catch (const std::exception& e) {
			MainLogError("Failed to parse JSON file: {}", e.what());
		}
		return std::nullopt;
	}

	template <class ObjT>
	inline std::string Stringify(ObjT&& object, bool pretty = true) {
		const JSON obj(std::forward<ObjT>(object));
		return obj.dump(pretty ? 2 : -1);  // JSON string
	}
}  // namespace sdk::json
