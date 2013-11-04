set(NETWORK_SRC
  HttpClient.cpp
  SocketIO.cpp
)

add_library(network STATIC
  ${NETWORK_SRC}
)

target_link_libraries(network
  curl
)
