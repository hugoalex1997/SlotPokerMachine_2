find_package(SFML REQUIRED COMPONENTS graphics window system)

include_directories(frontend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE
                    ${CMAKE_SOURCE_DIR})

set(SOURCE_FILES main.cpp view.cpp)

add_executable(frontend ${SOURCE_FILES})

target_link_libraries(frontend PRIVATE backend sfml-graphics sfml-window
                                       sfml-system)
