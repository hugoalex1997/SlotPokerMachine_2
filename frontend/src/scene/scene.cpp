#include "scene.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include "sdk/filesystem.hpp"
#include "sdk/json.hpp"
#include "src/assetsmanager.hpp"
#include "src/view.hpp"

#include "src/aliases.hpp"

namespace frontend {

	//================================ Entity =============================//

	Entity::Entity(std::shared_ptr<sf::Drawable> drawable) : mDrawable(drawable) {};

	Entity::Entity(std::shared_ptr<sf::Drawable> drawable, bool visible) : mDrawable(drawable), mVisible(visible) {}

	void Entity::Draw(sf::RenderWindow& window) const {
		if (!mVisible) {
			return;
		}

		window.draw(*mDrawable);
	}

	//================================ Container =============================//

	bool Container::AddObject(const std::string& name, const Entity& entity) {
		if (mObjects.find(name) != mObjects.end()) {
			LogError("Object with name {} already exists in container!", name);
			return false;
		}

		mObjects[name] = std::make_shared<Entity>(entity);
		return true;
	}

	bool Container::AddObject(const std::string& name, const Container& container) {
		if (mObjects.find(name) != mObjects.end()) {
			LogError("Object with name {} already exists in container!", name);
			return false;
		}

		mObjects[name] = std::make_shared<Container>(container);
		return true;
	}

	void Container::Draw(sf::RenderWindow& window) const {
		if (!mVisible) {
			return;
		}

		for (const auto& [_, object] : mObjects) {
			if (!object->GetVisibility()) {
				continue;
			}

			object->Draw(window);
		}
	}

	//================================ Scene =============================//

	Scene::Scene(std::string name) : mName(std::move(name)) {};

	Scene::Scene(std::string name, bool visible) : mName(std::move(name)), mVisible(visible) {};

	bool Scene::LoadScene() {
		const auto file = sdk::fs::GetSceneJsonFile();

		const auto scene = sdk::json::FromFile(file);

		if (!scene) {
			LogError("Failed to load scene file: {}", file.string());
			return false;
		}

		const auto sceneJson = *scene;

		for (const auto& object : sceneJson["objects"]) {
			const auto type_ = object["type"].get<std::string>();
			const auto type = GetObjectTypeFromString(type_);

			switch (type) {
				case ObjectType::Entity: {
					const auto name = object["name"].get<std::string>();
					const auto entity = createEntity(object);

					if (!entity) {
						LogError("Failed to create entity {}", name);
						continue;
					}

					if (!AddObject(name, *entity)) {
						LogError("Failed to add entity {} to scene!", name);
					}

					LogInfo("Entity {} added to scene!", name);
				} break;

				case ObjectType::Container: {
					const auto name = object["name"].get<std::string>();
					const auto container = createContainer(object);
					if (!AddObject(name, container)) {
						LogError("Failed to add container {} to scene!", name);
					}

					LogInfo("Container {} added to scene!", name);
				} break;

				default: {
					LogError("Unknown object type: {}", type_);
					continue;
				}
			}
		}
		LogInfo("Scene {} loaded successfully!", mName);
		return true;
	}

	std::optional<Entity> Scene::createEntity(const DrawableProps& props) {
		const auto drawable = createSprite(props);
		if (!drawable) {
			LogError("Failed to create drawable for entity: {}", props.name);
			return std::nullopt;
		}

		return Entity{drawable, props.visible};
	}

	std::shared_ptr<sf::Sprite> Scene::createSprite(const DrawableProps& props) {
		auto sprite = std::make_shared<sf::Sprite>();

		const auto* texture = mAssetsManager->GetTexture(props.texture_name);

		if (!texture) {
			LogError("Failed to get texture for sprite: {}", props.name);
			return nullptr;
		}

		sprite->setTexture(*texture);
		sprite->setPosition(props.x, props.y);
		return sprite;
	}

	Container Scene::createContainer(const nlohmann::json& json) {
		Container container{};

		if (!json.contains("objects")) {
			LogWarn("Container is empty!");
			return container;
		}

		for (const auto& object : json["objects"]) {
			const auto type_ = object["type"].get<std::string>();
			const auto type = GetObjectTypeFromString(type_);

			switch (type) {
				case ObjectType::Entity: {
					const auto name = object["name"].get<std::string>();
					const auto entity = createEntity(object);

					if (!entity) {
						LogError("Failed to create entity {}", name);
						continue;
					}

					if (!container.AddObject(name, *entity)) {
						LogError("Failed to add entity {} to container!", name);
						continue;
					}
				} break;

				case ObjectType::Container: {
					const auto name = object["name"].get<std::string>();
					const auto innerContainer = createContainer(object);
					if (!container.AddObject(name, innerContainer)) {
						LogError("Failed to add container {} to container!", name);
					}
				} break;

				default: {
					LogError("Unknown object type: {}", type_);
					continue;
				}
			}
		}

		if (json.contains("visible")) {
			const bool visible = json["visible"].get<bool>();
			container.SetVisibility(visible);
		}
		return container;
	}

	bool Scene::AddObject(const std::string& name, const Entity& entity) {
		if (mObjects.find(name) != mObjects.end()) {
			LogError("Object with name {} already exists in scene {}!", name, mName);
			return false;
		}

		mObjects[name] = std::make_shared<Entity>(entity);
		return true;
	}

	bool Scene::AddObject(const std::string& name, const Container& container) {
		if (mObjects.find(name) != mObjects.end()) {
			LogError("Object with name {} already exists in scene {}!", name, mName);
			return false;
		}

		mObjects[name] = std::make_shared<Container>(container);
		return true;
	}

	void Scene::Draw(sf::RenderWindow& window) const {
		for (const auto& [_, object] : mObjects) {
			if (!object->GetVisibility()) {
				continue;
			}

			object->Draw(window);
		}
	}

}  // namespace frontend