set(XXHASH
  xxhash.c
)

add_library(xxhash STATIC
  ${XXHASH}
)

set_target_properties(xxhash
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

