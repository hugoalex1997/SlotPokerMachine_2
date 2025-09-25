find_package(SFML REQUIRED COMPONENTS graphics window system)

find_package(nlohmann_json REQUIRED)

include_directories(frontend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp src/view.cpp src/assetsmanager.cpp src/scene/scene.cpp src/scene/objects.cpp)

add_executable(frontend ${SOURCE_FILES})

# internal libraries
target_link_libraries(frontend PRIVATE backend sdk)

# external libraries
target_link_libraries(frontend PRIVATE sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
