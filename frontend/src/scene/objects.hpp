#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <nlohmann/json_fwd.hpp>

#include <map>
#include <memory>
#include <string>

#include "sdk/enums.hpp"
#include "sdk/json.hpp"

namespace frontend {

	enum class ObjectType : uint8_t {
		None,
		Entity,
		Container,
		__count__,
	};

	struct IProps {
		virtual ObjectType GetType() = 0;
	};

	SerializeAsJsonEmpty(IProps);

	struct EntityProps : public IProps {
		[[nodiscard]] ObjectType GetType() override { return ObjectType::Entity; }

		std::string name{};
		std::string texture_name{};
		uint64_t x{};
		uint64_t y{};
		bool visible{};
	};

	struct ContainerProps : public IProps {
		[[nodiscard]] ObjectType GetType() override { return ObjectType::Container; }

		std::string name{};
		std::vector<std::shared_ptr<IProps>> objects{};
		bool visible{};
	};

	struct Object {
		[[nodiscard]] virtual ObjectType GetType() = 0;

		[[nodiscard]] virtual bool GetVisibility() = 0;

		virtual void Draw(sf::RenderWindow& window) const = 0;
	};

	class Entity : public Object {
	public:
		explicit Entity(std::shared_ptr<sf::Drawable> drawable);

		Entity(std::shared_ptr<sf::Drawable> drawable, bool visible);

		[[nodiscard]] ObjectType GetType() override { return ObjectType::Entity; }

		[[nodiscard]] bool GetVisibility() override { return mVisible; }

		void Draw(sf::RenderWindow& window) const override;

	private:
		bool mVisible{};
		std::shared_ptr<sf::Drawable> mDrawable;
	};

	class Container : public Object {
	public:
		Container() = default;

		explicit Container(bool visible) : mVisible(visible) {}

		[[nodiscard]] ObjectType GetType() override { return ObjectType::Container; }

		[[nodiscard]] bool GetVisibility() override { return mVisible; }

		void SetVisibility(bool visible) { mVisible = visible; }

		[[nodiscard]] bool AddObject(const std::string& name, const Container& container);

		[[nodiscard]] bool AddObject(const std::string& name, const Entity& entity);

		void Draw(sf::RenderWindow& window) const override;

	private:
		bool mVisible{};
		std::map<std::string, std::shared_ptr<Object>> mObjects;
	};
}  // namespace frontend

//================================ NLOHMANN JSON SERIALIZERS =============================//

NLOHMANN_JSON_NAMESPACE_BEGIN

using EntityProps = frontend::EntityProps;
template <>
struct adl_serializer<EntityProps> {
	static void to_json(json& j, const EntityProps& props) {
		j["name"] = props.name;
		j["texture_name"] = props.texture_name;
		j["x"] = props.x;
		j["y"] = props.y;
		j["visible"] = props.visible;
		j["type"] = "entity";
	}

	static void from_json(const json& j, EntityProps& props) {
		props.name = j.at("name").get<std::string>();
		props.texture_name = j.at("texture_name").get<std::string>();
		props.x = j.at("x").get<uint64_t>();
		props.y = j.at("y").get<uint64_t>();
		props.visible = j.at("visible").get<bool>();
	}
};

using ContainerProps = frontend::ContainerProps;
using ObjectType = frontend::ObjectType;
template <>
struct adl_serializer<ContainerProps> {
	static void to_json(json& j, const ContainerProps& props) {
		j["name"] = props.name;
		j["visible"] = props.visible;
		j["type"] = "container";

		for (const auto& child : props.objects) {
			if (child->GetType() == ObjectType::Entity) {
				j["objects"].push_back(*std::dynamic_pointer_cast<EntityProps>(child));
			} else if (child->GetType() == ObjectType::Container) {
				j["objects"].push_back(*std::dynamic_pointer_cast<ContainerProps>(child));
			}
		}
	}

	static void from_json(const json& j, ContainerProps& props) {
		props.name = j.at("name").get<std::string>();
		props.visible = j.at("visible").get<bool>();

		if (!j.contains("objects")) {
			return;
		}

		for (const auto& child : j.at("objects")) {
			const auto type = child.at("type").get<std::string>();

			if (type == "entity") {
				props.objects.push_back(std::make_shared<EntityProps>(child.get<EntityProps>()));
			} else if (type == "container") {
				props.objects.push_back(std::make_shared<ContainerProps>(child.get<ContainerProps>()));
			} else {
				assert(false && "Unknown object type in container");
			}
		}
	}
};

NLOHMANN_JSON_NAMESPACE_END

//================================ ENUMS AS JSON =============================//

// clang-format off
EnumBegin(frontend::ObjectType)
	EnumCustomEntry(None, "none")
	EnumCustomEntry(Entity, "entity")
	EnumCustomEntry(Container, "container")
	EnumCustomEntry(__count__, "__count__")
EnumEnd()

EnumAsJson(frontend, ObjectType)

	// clang-format on

	//============================================================================//
