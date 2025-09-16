cmake_minimum_required(VERSION 3.15)
project(SPokerM)
set(BINARY ${CMAKE_PROJECT_NAME})


# Defina o padrão de compilação
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


# All warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
elseif(MSVC)
  add_compile_options(/Wall /permissive- /W4)
endif()


# Conan packages
find_package(SFML REQUIRED COMPONENTS graphics window system)
find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES main.cpp src/game.cpp src/fsm/finitestatemachine.cpp
                 src/accounting/accounting.cpp src/view/view.cpp)

add_executable(${BINARY} ${SOURCE_FILES})

target_link_libraries(${BINARY} PRIVATE sfml-graphics sfml-window sfml-system)
