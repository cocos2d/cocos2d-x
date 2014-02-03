set(TINYXML2_SRC
  tinyxml2.cpp
)

add_library(tinyxml2 STATIC
  ${TINYXML2_SRC}
)

set_target_properties(tinyxml2
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

