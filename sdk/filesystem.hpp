#pragma once
#include <filesystem>

namespace sdk::fs {

	inline std::filesystem::path GetRootFolder() {
		auto buildFolder = std::filesystem::read_symlink("/proc/self/exe").parent_path().parent_path().parent_path();
		return buildFolder.parent_path();
	}

	inline std::filesystem::path GetLogsPath() {  //
		return GetRootFolder() / "logs";
	}

	inline std::filesystem::path GetMainLogPath() {	 //
		return GetRootFolder() / "logs" / "main.log";
	}

	inline std::filesystem::path GetAssetsFolder() {  //
		return GetRootFolder() / "frontend" / "assets";
	}

	inline std::filesystem::path GetAssetsJsonFile() {	//
		return GetAssetsFolder() / "assets.json";
	}

	inline std::filesystem::path GetSceneJsonFile() {  //
		return GetRootFolder() / "frontend" / "src" / "scene" / "scene.json";
	}
}  // namespace sdk::fs