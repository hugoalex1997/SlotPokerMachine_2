#include "scene.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <iostream>
#include "assetsmanager.hpp"
#include "sdk/filesystem.hpp"
#include "sdk/json.hpp"
#include "src/view.hpp"

namespace frontend {

	//================================ Entity =============================//

	Entity::Entity(sf::Drawable* drawable) : mDrawable(drawable) {};

	Entity::Entity(sf::Drawable* drawable, bool visible) : mDrawable(drawable), mVisible(visible) {}

	void Entity::Draw(sf::RenderWindow& window) const {
		if (!mVisible) {
			return;
		}

		window.draw(*mDrawable);
	}

	//================================ Container =============================//

	bool Container::AddObject(const std::string& name, const Entity& entity) {
		if (mObjects.find(name) != mObjects.end()) {
			std::cout << "Object with name " << name << " already exists in container!" << std::endl;
			return false;
		}

		mObjects[name] = std::make_shared<Entity>(entity);
		return true;
	}

	bool Container::AddObject(const std::string& name, const Container& container) {
		if (mObjects.find(name) != mObjects.end()) {
			std::cout << "Object with name " << name << " already exists in container!" << std::endl;
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

		const auto scene = sdk::json::ToJson(file);

		for (const auto& object : scene["objects"]) {
			const auto type_ = object["type"].get<std::string>();
			const auto type = GetObjectTypeFromString(type_);

			switch (type) {
				case ObjectType::Entity: {
					const auto name = object["name"].get<std::string>();
					const auto entity = createEntity(object);

					if (!entity) {
						std::cout << "Failed to create entity " << name << "!" << std::endl;
						continue;
					}

					if (!AddObject(name, *entity)) {
						std::cout << "Failed to add entity " << name << " to scene!" << std::endl;
					}

					std::cout << "Entity " << name << " added to scene!" << std::endl;
				} break;

				case ObjectType::Container: {
					const auto name = object["name"].get<std::string>();
					const auto container = createContainer(object);
					if (!AddObject(name, container)) {
						std::cout << "Failed to add container " << name << " to scene!" << std::endl;
					}

					std::cout << "Container " << name << " added to scene!" << std::endl;
				} break;

				default: {
					std::cout << "Unknown object type: " << type_ << std::endl;
					continue;
				}
			}
		}
		std::cout << "Scene " << mName << " loaded successfully!" << std::endl;
		return true;
	}

	std::optional<Entity> Scene::createEntity(const nlohmann::json& json) {
		DrawableProps props{};
		props.name = json["name"].get<std::string>();

		if (json.contains("x")) {
			props.x = json["x"].get<uint64_t>();
		}
		if (json.contains("y")) {
			props.y = json["y"].get<uint64_t>();
		}
		if (json.contains("width")) {
			props.width = json["width"].get<uint64_t>();
		}
		if (json.contains("height")) {
			props.height = json["height"].get<uint64_t>();
		}

		if (json.contains("texture")) {
			const auto texture = json["texture"].get<std::string>();
			props.texture = mAssetsManager->GetTexture(texture);
		}

		Shape shape{Shape::None};
		if (json.contains("shape")) {
			shape = GetShapeFromString(json["shape"].get<std::string>());
		}

		const auto drawable = createDrawable(props, shape);

		if (!drawable) {
			std::cout << "Failed to create drawable for entity: " << props.name << std::endl;
			return std::nullopt;
		}

		bool visible{false};
		if (json.contains("visibility")) {
			visible = json["visibility"].get<bool>();
		}
		return Entity{drawable, visible};
	}

	sf::Drawable* Scene::createDrawable(const DrawableProps& props, Shape shape) {
		sf::Drawable* drawable{nullptr};
		switch (shape) {
			case Shape::Rectangle: {
				drawable = new sf::RectangleShape(createRectangle(props));
				mEntities[props.name] = drawable;
			} break;

			default:
				std::cout << "Unknown shape type!" << std::endl;
		}
		return drawable;
	}

	sf::RectangleShape Scene::createRectangle(const DrawableProps& props) {
		sf::RectangleShape rectangle;
		rectangle.setTexture(props.texture);
		rectangle.setSize(sf::Vector2f(props.width, props.height));
		rectangle.setPosition(props.x, props.y);
		return rectangle;
	}

	Container Scene::createContainer(const nlohmann::json& json) {
		Container container{};

		if (!json.contains("objects")) {
			std::cout << "Container is empty!" << std::endl;
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
						std::cout << "Failed to create entity " << name << "!" << std::endl;
						continue;
					}

					if (!container.AddObject(name, *entity)) {
						std::cout << "Failed to add entity " << name << " to container!" << std::endl;
						continue;
					}
				} break;

				case ObjectType::Container: {
					const auto name = object["name"].get<std::string>();
					const auto innerContainer = createContainer(object);
					if (!container.AddObject(name, innerContainer)) {
						std::cout << "Failed to add container " << name << " to container!" << std::endl;
					}
				} break;

				default: {
					std::cout << "Unknown object type: " << type_ << std::endl;
					continue;
				}
			}
		}

		if (json.contains("visibility")) {
			const bool visible = json["visibility"].get<bool>();
			container.SetVisibility(visible);
		}
		return container;
	}

	bool Scene::AddObject(const std::string& name, const Entity& entity) {
		if (mObjects.find(name) != mObjects.end()) {
			std::cout << "Object with name " << name << " already exists in scene " << mName << "!" << std::endl;
			return false;
		}

		mObjects[name] = std::make_shared<Entity>(entity);
		return true;
	}

	bool Scene::AddObject(const std::string& name, const Container& container) {
		if (mObjects.find(name) != mObjects.end()) {
			std::cout << "Object with name " << name << " already exists in scene " << mName << "!" << std::endl;
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