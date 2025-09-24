set(_IN_FILES "${CMAKE_CURRENT_LIST_DIR}/config_files")

configure_file("${_IN_FILES}/variables.in.json" "${PROJECT_SOURCE_DIR}/.variables.json")

unset(_IN_FILES)