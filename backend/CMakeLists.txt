set(SOURCE_FILES api.cpp src/game.cpp src/accounting.cpp)

add_library(backend ${SOURCE_FILES})

include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# internal libraries
target_link_libraries(backend PRIVATE sdk)
