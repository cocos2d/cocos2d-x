
if(WINDOWS)
  set(PLATFORM_LINK websockets)
elseif(LINUX)
  set(PLATFORM_LINK websockets ssl crypto)
elseif(ANDROID)
  set(PLATFORM_LINK websockets)
elseif(EMSCRIPTEN)
else()
  set(PLATFORM_LINK websockets)
endif()

if(ANDROID)
  set(COCOS_NETWORK_SRC
    network/HttpClient-android.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp
    network/CCDownloader.cpp
    network/CCDownloader-android.cpp
  )
elseif(EMSCRIPTEN)
  set(COCOS_NETWORK_SRC
    network/HttpClient-emcc.cpp
    network/WebSocket-emcc.cpp
  )
else()
  set(COCOS_NETWORK_SRC
    network/HttpClient.cpp
    network/SocketIO.cpp
    network/WebSocket.cpp
    network/CCDownloader.cpp
    network/CCDownloader-curl.cpp
  )
endif()

if(MSVC)
  set(COCOS_NETWORK_LINK 
    libcurl_imp 
    ${PLATFORM_LINK}
  )
elseif(ANDROID)
  set(COCOS_NETWORK_LINK
    ${PLATFORM_LINK} 
  )
elseif(EMSCRIPTEN)
  set(COCOS_NETWORK_LINK 
  )
else()
  set(COCOS_NETWORK_LINK 
    curl
    ${PLATFORM_LINK} 
  )
endif()
