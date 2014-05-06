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
IF ( WIN32 )
target_link_libraries(network
  libcurl_imp
  ${PLATFORM_LINK}
)
ELSE()
  curl
  ${PLATFORM_LINK}
)
ENDIF()
