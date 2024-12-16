
if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
else()
  set(PLATFORM_LINK websockets)
endif()

set(COCOS_NETWORK_SRC

    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp

)

if(OHOS)
  add_library(network STATIC ${COCOS_NETWORK_SRC})
  include_directories(${COCOS2DX_ROOT_PATH}/external/websockets/include/ohos)
  target_link_libraries(network
    ext_websockets
    ext_ssl
    ext_crypto
  )
  set_target_properties(network
      PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  )
endif()

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
