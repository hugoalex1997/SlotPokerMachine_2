set(SOURCE_FILES api.cpp game.cpp accounting/accounting.cpp
                 fsm/finitestatemachine.cpp)

add_library(backend STATIC ${SOURCE_FILES})

include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE
                    ${CMAKE_SOURCE_DIR})

target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
