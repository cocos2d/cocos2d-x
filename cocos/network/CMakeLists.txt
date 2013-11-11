set(NETWORK_SRC
  HttpClient.cpp
  SocketIO.cpp
)

add_library(network STATIC
  ${NETWORK_SRC}
)

target_link_libraries(network
  curl
  ldap
  lber
  idn
  rtmp
)

set_target_properties(network
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

