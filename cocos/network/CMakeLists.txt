if(WIN32)
  set(PLATFORM_SRC
    network/WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
  )
elseif(NOT APPLE)
  set(PLATFORM_SRC
    network/WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
    ssl
    crypto
  )
endif()

set(COCOS_NETWORK_SRC
  network/HttpClient.cpp
  network/SocketIO.cpp
  ${PLATFORM_SRC}
)

set(COCOS_NETWORK_LINK
  curl
  ${PLATFORM_LINK}
)
