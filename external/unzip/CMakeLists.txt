set(UNZIP_SRC
  ioapi.cpp
  unzip.cpp
)

add_library(unzip STATIC
  ${UNZIP_SRC}
)

set_target_properties(unzip
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

