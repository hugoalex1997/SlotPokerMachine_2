#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include "sdk/json.hpp"
#include "src/view.hpp"

namespace frontend {

	struct DrawableProps {
		std::string name{};
		std::string texture_name{};
		uint64_t x{};
		uint64_t y{};
		bool visible{};
	};

	SerializeAsJson(DrawableProps, name, texture_name, x, y, visible);

	enum class ObjectType : uint8_t {
		None,
		Entity,
		Container,
		__count__,
	};

	inline ObjectType GetObjectTypeFromString(const std::string& type) {
		if (type == "entity") {
			return ObjectType::Entity;
		} else if (type == "container") {
			return ObjectType::Container;
		}

		return ObjectType::None;
	}

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

	class Scene {
	public:
		explicit Scene(std::string name);

		Scene(std::string name, bool visible);

		void AttachAssetsManager(AssetsManager* assetsManager) { mAssetsManager = assetsManager; }

		[[nodiscard]] bool LoadScene();

		[[nodiscard]] std::string GetName() const { return mName; }

		[[nodiscard]] bool GetVisibility() const { return mVisible; }

		void SetVisibility(bool visible) { mVisible = visible; }

		[[nodiscard]] bool AddObject(const std::string& name, const Container& container);

		[[nodiscard]] bool AddObject(const std::string& name, const Entity& entity);

		void Draw(sf::RenderWindow& window) const;

		void Activate() { mVisible = true; }

		void Deactivate() { mVisible = false; }

	private:
		std::optional<Entity> createEntity(const DrawableProps& props);

		Container createContainer(const nlohmann::json& json);

		std::shared_ptr<sf::Sprite> createSprite(const DrawableProps& props);

	private:
		AssetsManager* mAssetsManager{nullptr};

		std::string mName{};
		bool mVisible{};
		std::map<std::string, std::shared_ptr<Object>> mObjects;
	};

};	// namespace frontend