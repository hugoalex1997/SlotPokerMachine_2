#include "assetsmanager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <iostream>
#include "sdk/filesystem.hpp"
#include "sdk/json.hpp"

namespace frontend {

	std::optional<sf::Texture> AssetsManager::loadTexture(const std::string& name, const std::filesystem::path& path) {
		sf::Texture texture;

		if (!texture.loadFromFile(path)) {
			std::cout << "Failed to load texture: " << path << std::endl;
			return std::nullopt;
		}
		return texture;
	}

	bool AssetsManager::LoadAssets() {
		const auto file = sdk::fs::GetAssetsJsonFile();

		const auto assets = sdk::json::ToJson(file);

		const auto assetsPath = sdk::fs::GetAssetsFolder();

		for (const auto& asset : assets["assets"]) {
			const auto name = asset["name"].get<std::string>();
			const auto path = asset["path"].get<std::string>();

			auto texture = loadTexture(name, assetsPath / path);

			if (!texture) {
				std::cout << "Failed to load texture: " << path << std::endl;
				return false;
			}
			mTextures[name] = std::move(*texture);
		}

		std::cout << "All assets loaded successfully!" << std::endl;
		return true;
	}

	sf::Texture* AssetsManager::GetTexture(const std::string& name) {
		auto it = mTextures.find(name);
		if (it != mTextures.end()) {
			return &it->second;
		}
		std::cout << "Texture " << name << " not found!" << std::endl;
		return nullptr;	 // not found
	}

}  // namespace frontend
