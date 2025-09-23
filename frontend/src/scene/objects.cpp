#include "objects.hpp"

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
};	// namespace frontend