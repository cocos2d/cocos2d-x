
if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
elseif(ANDROID)
  set(PLATFORM_LINK websockets)
else()
  set(PLATFORM_LINK websockets)
endif()

if(ANDROID)
   set(COCOS_NETWORK_PLATFORM_SRC
        network/CCDownloader-android.cpp
        )
endif()

set(COCOS_NETWORK_SRC
    ${COCOS_NETWORK_PLATFORM_SRC}
    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp
    network/CCDownloader.cpp
    network/CCDownloader-curl.cpp
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
