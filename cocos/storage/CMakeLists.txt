
SET(STORAGE_SOURCES
  local-storage/LocalStorage.cpp
  )

add_library(storage STATIC
  ${STORAGE_SOURCES}
)

target_link_libraries(storage
    sqlite3
)

set_target_properties(storage
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
