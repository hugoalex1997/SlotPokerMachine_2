set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        #external/rapidjson/*.h
        )

set(SOURCES ${TEST_SOURCES})
set(SFML_DIR "external/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock sfml-graphics sfml-audio sfml-system sfml-window)

