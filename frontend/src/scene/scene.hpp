#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <vector>
#include "src/view.hpp"

namespace frontend {

	enum class Shape : uint8_t {
		None,
		Rectangle,
		Circle,
		Sprite,
		__count__,
	};

	inline Shape GetShapeFromString(const std::string& shape) {
		if (shape == "rectangle") {
			return Shape::Rectangle;
		} else if (shape == "circle") {
			return Shape::Circle;
		} else if (shape == "sprite") {
			return Shape::Sprite;
		}

		return Shape::None;
	}

	struct DrawableProps {
		std::string name{};
		sf::Texture* texture{};
		uint64_t x{};
		uint64_t y{};
	};

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
		explicit Entity(sf::Drawable* drawable);

		Entity(sf::Drawable* drawable, bool visible);

		[[nodiscard]] ObjectType GetType() override { return ObjectType::Entity; }

		[[nodiscard]] bool GetVisibility() override { return mVisible; }

		void Draw(sf::RenderWindow& window) const override;

	private:
		bool mVisible{};
		sf::Drawable* mDrawable;
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
		std::optional<Entity> createEntity(const nlohmann::json& json);

		Container createContainer(const nlohmann::json& json);

		sf::Sprite* createSprite(const DrawableProps& props);

	private:
		AssetsManager* mAssetsManager{nullptr};

		std::string mName{};
		bool mVisible{};
		std::map<std::string, std::shared_ptr<Object>> mObjects;
		std::map<std::string, sf::Drawable*> mEntities{};
	};
};	// namespace frontend