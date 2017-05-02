set(PROTOBUF_SRC
./src/google/protobuf/stubs/once.cc
./src/google/protobuf/stubs/common.cc
./src/google/protobuf/stubs/stringprintf.cc
./src/google/protobuf/generated_message_util.cc
./src/google/protobuf/message_lite.cc
./src/google/protobuf/extension_set.cc
./src/google/protobuf/wire_format_lite.cc
./src/google/protobuf/repeated_field.cc
./src/google/protobuf/io/zero_copy_stream_impl.cc
./src/google/protobuf/io/zero_copy_stream_impl_lite.cc
./src/google/protobuf/io/zero_copy_stream.cc
./src/google/protobuf/io/coded_stream.cc
./src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf
)

add_library(protobuf STATIC
  ${PROTOBUF_SRC}
)

set_target_properties(protobuf
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
