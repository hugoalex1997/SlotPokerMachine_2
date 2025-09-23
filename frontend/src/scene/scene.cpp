

#include "scene.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "objects.hpp"
#include "sdk/enums.hpp"
#include "sdk/filesystem.hpp"
#include "sdk/json.hpp"
#include "src/aliases.hpp"
#include "src/assetsmanager.hpp"
#include "src/view.hpp"

namespace frontend {

	namespace {
		ObjectType GetObjectTypeFromString(const std::string& type) {
			if (type == "entity") {
				return ObjectType::Entity;
			} else if (type == "container") {
				return ObjectType::Container;
			}

			return ObjectType::None;
		}

		template <class PropsT>
		[[nodiscard]] inline auto* GetPropsAs(const std::shared_ptr<IProps> props) {
			return dynamic_cast<PropsT*>(props.get());
		}
	}  // namespace

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
			const auto type = object["type"].get<ObjectType>();

			switch (type) {
				case ObjectType::Entity: {
					const auto props = object.get<EntityProps>();
					const auto entity = createEntity(props);

					if (!entity) {
						LogError("Failed to create entity {}", props.name);
						continue;
					}

					if (!AddObject(props.name, *entity)) {
						LogError("Failed to add entity {} to scene!", props.name);
						continue;
					}

					LogInfo("Entity {} added to scene!", props.name);
				} break;

				case ObjectType::Container: {
					const auto props = object.get<ContainerProps>();
					const auto container = createContainer(props);

					if (!AddObject(props.name, container)) {
						LogError("Failed to add container {} to scene!", props.name);
						continue;
					}

					LogInfo("Container {} added to scene!", props.name);
				} break;

				default: {
					LogError("Unknown object type: {}", sdk::enums::ToString(type));
					continue;
				}
			}
		}
		LogInfo("Scene {} loaded successfully!", mName);
		return true;
	}

	std::optional<Entity> Scene::createEntity(const EntityProps& props) {
		auto sprite = std::make_shared<sf::Sprite>();

		const auto* texture = mAssetsManager->GetTexture(props.texture_name);

		if (!texture) {
			LogError("Failed to get texture for sprite: {}", props.name);
			return std::nullopt;
		}

		sprite->setTexture(*texture);
		sprite->setPosition(props.x, props.y);

		return Entity{sprite, props.visible};
	}

	Container Scene::createContainer(const ContainerProps& props) {
		Container container{};

		if (props.objects.empty()) {
			LogWarn("Container is empty!");
			return container;
		}

		for (const auto& object : props.objects) {
			const auto type = object->GetType();

			switch (type) {
				case ObjectType::Entity: {
					const auto props = GetPropsAs<EntityProps>(object);
					const auto entity = createEntity(*props);

					if (!entity) {
						LogError("Failed to create entity {}", props->name);
						continue;
					}

					if (!container.AddObject(props->name, *entity)) {
						LogError("Failed to add entity {} to container!", props->name);
						continue;
					}
				} break;

				case ObjectType::Container: {
					const auto props = GetPropsAs<ContainerProps>(object);
					const auto innerContainer = createContainer(*props);

					if (!container.AddObject(props->name, innerContainer)) {
						LogError("Failed to add container {} to container!", props->name);
					}
				} break;

				default: {
					LogError("Unknown object type: {}", sdk::enums::ToString(type));
					continue;
				}
			}
		}

		container.SetVisibility(props.visible);
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