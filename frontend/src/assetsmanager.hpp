#include <sys/types.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <nlohmann/json.hpp>

#include <map>
#include <optional>
#include <string>

namespace frontend {

	class AssetsManager {
		using Textures = std::map<std::string, sf::Texture>;

	public:
		bool LoadAssets();

		sf::Texture* GetTexture(const std::string& name);

	private:
		std::optional<sf::Texture> loadTexture(const std::string& name, const std::filesystem::path& path);

	private:
		Textures mTextures{};
	};
}  // namespace frontend