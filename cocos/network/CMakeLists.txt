if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
endif()

set(COCOS_NETWORK_SRC
    HttpClient.cpp
    SocketIO.cpp
    WebSocket.cpp
)

add_library(network STATIC
    ${COCOS_NETWORK_SRC}
)

if(MSVC)
  set(COCOS_NETWORK_LINK 
    libcurl_imp 
    ${PLATFORM_LINK}
  )
else()
  set(COCOS_NETWORK_LINK 
    curl
    ${PLATFORM_LINK} 
  )
endif()

target_link_libraries(network
  ${COCOS_NETWORK_LINK}
)

set_target_properties(network
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
