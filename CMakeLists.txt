cmake_minimum_required(VERSION 3.10)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

# set the project name
project(GAME)

# Include cmake util functions
include(${CMAKE_SOURCE_DIR}/utils/cmake/utils.cmake)

# Downloads SFML library
downloadSFML()

set(SFML_DIR "external/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)


file(GLOB_RECURSE SOURCES
        src/*.cpp
        #external/rapidjson/*.h
        )

include_directories(src)

# add the executable
add_executable(GAME main.cpp ${SOURCES})

target_link_libraries(GAME sfml-graphics sfml-audio sfml-system sfml-window)