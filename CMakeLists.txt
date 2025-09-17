cmake_minimum_required(VERSION 3.15)
project(SPokerM)

# Defina o padrão de compilação
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


# Add subprojects
add_subdirectory(backend)
add_subdirectory(frontend)