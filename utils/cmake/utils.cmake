# Download SFML if doesn't exist
function(downloadSFML)
    if (NOT EXISTS "${CMAKE_SOURCE_DIR}/external/SFML-2.5.1")
        file(DOWNLOAD "https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz" ${CMAKE_SOURCE_DIR}/sfml.tar.gz
                SHOW_PROGRESS
                TIMEOUT 60  # seconds
                TLS_VERIFY ON
                )

        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/external)

        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xzvf ${CMAKE_SOURCE_DIR}/sfml.tar.gz
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external)

        file(REMOVE ${CMAKE_SOURCE_DIR}/sfml.tar.gz)
    endif ()
endfunction()