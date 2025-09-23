find_package(nlohmann_json REQUIRED)

find_package(spdlog REQUIRED)

set(SOURCE_FILES json.cpp logger.cpp)

add_library(sdk ${SOURCE_FILES})

include_directories(sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# external libraries
target_link_libraries(sdk PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog)
