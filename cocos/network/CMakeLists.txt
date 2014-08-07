if(WIN32)
  set(PLATFORM_SRC
    WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
  )
elseif(NOT APPLE)
  set(PLATFORM_SRC
    WebSocket.cpp
  )

  set(PLATFORM_LINK
    websockets
    ssl
    crypto
  )
endif()

set(COCOS_NETWORK_SRC
  HttpClient.cpp
  SocketIO.cpp
  ${PLATFORM_SRC}
)

add_library(network STATIC
	${COCOS_NETWORK_SRC}
)

IF (WIN32 AND NOT MINGW)
  set(COCOS_NETWORK_LINK
    libcurl_imp
    ${PLATFORM_LINK}
  )
ELSE()
  set(COCOS_NETWORK_LINK
    curl
    ${PLATFORM_LINK}
  )
ENDIF()

target_link_libraries(network
  ${COCOS_NETWORK_LINK}
)

set_target_properties(network
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
