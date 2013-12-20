set(JSONCPP_SRC
  json_reader.cpp
  json_value.cpp
  json_writer.cpp
)

include_directories(

)

add_library(jsoncpp STATIC
  ${JSONCPP_SRC}
)

set_target_properties(jsoncpp
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

