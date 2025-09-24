cmake_minimum_required(VERSION 3.15)
project(SPokerM)

# Defina o padrão de compilação
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Add subprojects
add_subdirectory(sdk)
add_subdirectory(backend)
add_subdirectory(frontend)

include(ConfigureFiles)