#pragma once

#include <fmt/format.h>

#include <cassert>
#include <optional>
#include <vector>

#include "json.hpp"

namespace sdk::enums {

	template <class EnumT, class CastT>
	using CanCastEnumT = std::enable_if_t<std::is_enum_v<EnumT> && sizeof(EnumT) <= sizeof(CastT), CastT>;

	template <class EnumT>
	using UnderT = std::underlying_type_t<EnumT>;

	template <class EnumT>
	constexpr CanCastEnumT<EnumT, UnderT<EnumT>> CastEnum(EnumT val) {
		return static_cast<UnderT<EnumT>>(val);
	}

	template <class IntegT, class EnumT>
	constexpr CanCastEnumT<EnumT, IntegT> CastEnum(EnumT val) {
		return static_cast<IntegT>(val);
	}

	using NameChangerT = std::string (*)(const std::string_view);

	template <class EnumT>
	struct EnumLookup {
		EnumT value;
		const char* name;
	};

	template <class>
	struct NamedEnum;

	template <class EnumT>
	constexpr std::string_view ToString(const EnumT value) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == value) {
				return entry.name;
			}
		}
		assert(!"invalid value");
		return "";
	}

	template <class EnumT>
	inline auto ToString(const EnumT value, const NameChangerT transform) -> std::string {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == value) {
				return transform ? transform(entry.name) : entry.name;
			}
		}
		assert(!"invalid value");
		return "";
	}

	template <class EnumT>
	inline auto ToStringCopy(const EnumT value) -> std::string {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == value) {
				return entry.name;
			}
		}
		assert(!"invalid value");
		return {};
	}

	template <class EnumT>
	constexpr std::string_view ToString(const int value) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == static_cast<EnumT>(value)) {
				return entry.name;
			}
		}
		assert(!"invalid value");
		return "";
	}

	template <class EnumT>
	inline auto ToString(const int value, NameChangerT transform) -> std::string {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == static_cast<EnumT>(value)) {
				return transform ? transform(entry.name) : entry.name;
			}
		}
		assert(!"invalid value");
		return "";
	}

	template <class EnumT>
	inline auto ToStringCopy(const int value) -> std::string {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == static_cast<EnumT>(value)) {
				return entry.name;
			}
		}
		assert(!"invalid value");
		return {};
	}

	template <class EnumT>
	constexpr EnumT FromString(const std::string_view name) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.name == name) {
				return entry.value;
			}
		}
		assert(!"invalid value name");
		return {};
	}

	template <class EnumT>
	constexpr bool HasName(const EnumT value) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.value == value) {
				return true;
			}
		}
		return false;
	}

	template <class EnumT, class ValueT>
	constexpr bool HasName(const ValueT value) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (CastEnum(entry.value) == value) {
				return true;
			}
		}
		return false;
	}

	template <class EnumT>
	constexpr bool HasValue(const std::string_view name) {
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			if (entry.name == name) {
				return true;
			}
		}
		return false;
	}

	template <class EnumT, class ValueT>
	constexpr EnumT GetValue(const ValueT value) {
		if (HasName<EnumT, ValueT>(value)) {
			return static_cast<EnumT>(value);
		}
		return EnumT{};
	}

	template <class EnumT>
	inline std::vector<std::string_view> GetNames() {
		std::vector<std::string_view> names;
		for (const auto& entry : NamedEnum<EnumT>::LookupTable) {
			names.emplace_back(entry.name);
		}
		return names;
	}

	template <class OutEnumT, class InEnumT>
	constexpr std::optional<OutEnumT> ConvertTo(const InEnumT in) {
		using namespace sdk::enums;

		if (!HasName(in)) {
			return std::nullopt;
		}

		const auto out = ToString(in);

		if (!HasValue<OutEnumT>(out)) {
			return std::nullopt;
		}

		return FromString<OutEnumT>(out);
	}

	inline constexpr const auto EnumBindTag{"__bind_enum__"};

}  // namespace sdk::enums

#define EnumBegin(enum_name)          \
	namespace sdk::enums {            \
		template <>                   \
		struct NamedEnum<enum_name> { \
			using EnumT = enum_name;  \
			static inline constexpr const EnumLookup<enum_name> LookupTable[] {
// clang-format off
#define EnumEnd() \
			};       \
		};           \
	}
// clang-format on

#define EnumAsJsonBegin(enum_name)    \
	namespace sdk::enums {            \
		template <>                   \
		struct NamedEnum<enum_name> { \
			using EnumT = enum_name;  \
			static inline constexpr const EnumLookup<enum_name> LookupTable[] {
// clang-format off
#define EnumAsJsonEnd(enum_name)                                                            \
			};                                                                                 \
		};                                                                                     \
	}                                                                                          \
	inline void to_json(nlohmann::json& nlohmann_json_j, const enum_name& nlohmann_json_t) {   \
		nlohmann_json_j = sdk::enums::ToString(nlohmann_json_t);                      \
	}                                                                                          \
	inline void from_json(const nlohmann::json& nlohmann_json_j, enum_name& nlohmann_json_t) { \
		const auto name = nlohmann_json_j.get<std::string>();                                  \
		nlohmann_json_t = sdk::enums::FromString<enum_name>(name);                    \
	}
// clang-format on

#define EnumEntry(value) {EnumT::value, #value},
#define EnumCustomEntry(value, name) {EnumT::value, name},

#define EnumAsJson(namespace_, enum_name)                                                          \
	namespace namespace_ {                                                                         \
		inline void to_json(nlohmann::json& nlohmann_json_j, const enum_name& nlohmann_json_t) {   \
			nlohmann_json_j = sdk::enums::ToString(nlohmann_json_t);                               \
		}                                                                                          \
		inline void from_json(const nlohmann::json& nlohmann_json_j, enum_name& nlohmann_json_t) { \
			const auto name = nlohmann_json_j.get<std::string>();                                  \
			nlohmann_json_t = sdk::enums::FromString<enum_name>(name);                             \
		}                                                                                          \
	}
