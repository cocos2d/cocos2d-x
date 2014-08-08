set(COCOS_STORAGE_SRC 
    local-storage/LocalStorage.cpp
)

add_library(sqlite3 STATIC
  ${COCOS_STORAGE_SRC}
)

set_target_properties(sqlite3
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
