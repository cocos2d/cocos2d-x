set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

set(FLATBUFFERS_SRC
./flatc.cpp
./idl_gen_cpp.cpp
./idl_gen_fbs.cpp
./idl_gen_general.cpp
./idl_gen_go.cpp
./idl_gen_text.cpp
./idl_parser.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(flatbuffers STATIC
  ${FLATBUFFERS_SRC}
)

set_target_properties(flatbuffers
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
