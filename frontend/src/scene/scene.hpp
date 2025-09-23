#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <nlohmann/json_fwd.hpp>

#include <memory>
#include <string>

#include "src/scene/objects.hpp"
#include "src/view.hpp"

namespace frontend {

	class Object;
	class Entity;
	class EntityProps;
	class Container;
	class ContainerProps;

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
		std::optional<Entity> createEntity(const EntityProps& props);

		Container createContainer(const ContainerProps& json);

	private:
		AssetsManager* mAssetsManager{nullptr};

		std::string mName{};
		bool mVisible{};
		std::map<std::string, std::shared_ptr<Object>> mObjects;
	};

};	// namespace frontend