
if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
else()
  set(PLATFORM_LINK websockets)
endif()

if(ANDROID)
  set(COCOS_NETWORK_SPECIFIC_SRC
    network/CCDownloader-android.cpp
  )
endif()

set(COCOS_NETWORK_SRC

    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp
    network/CCDownloader.cpp
    network/CCDownloader-curl.cpp
    ${COCOS_NETWORK_SPECIFIC_SRC}
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
