#include "assetsmanager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <iostream>
#include "aliases.hpp"
#include "sdk/filesystem.hpp"
#include "sdk/json.hpp"

namespace frontend {

	std::optional<sf::Texture> AssetsManager::loadTexture(const std::string& name, const std::filesystem::path& path) {
		sf::Texture texture;

		if (!texture.loadFromFile(path)) {
			LogError("Failed to load texture: {}", path.string());
			return std::nullopt;
		}
		return texture;
	}

	bool AssetsManager::LoadAssets() {
		const auto file = sdk::fs::GetAssetsJsonFile();

		const auto assets = sdk::json::FromFile(file);
		if (!assets) {
			LogError("Failed to load assets file: {}", file.string());
			return false;
		}

		const auto assetsJson = *assets;

		const auto assetsPath = sdk::fs::GetAssetsFolder();

		for (const auto& asset : assetsJson["assets"]) {
			const auto name = asset["name"].get<std::string>();
			const auto path = asset["path"].get<std::string>();

			auto texture = loadTexture(name, assetsPath / path);

			if (!texture) {
				LogError("Failed to load texture: {}", path);
				return false;
			}
			mTextures[name] = std::move(*texture);
		}

		LogInfo("All assets loaded successfully!");
		return true;
	}

	sf::Texture* AssetsManager::GetTexture(const std::string& name) {
		auto it = mTextures.find(name);
		if (it != mTextures.end()) {
			return &it->second;
		}
		LogError("Texture {} not found!", name);
		return nullptr;	 // not found
	}

}  // namespace frontend
