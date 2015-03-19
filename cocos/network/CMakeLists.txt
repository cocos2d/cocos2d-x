
cocos_target_sources(${COCOS2D_TARGET} GROUP "network" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "network/HttpClient.cpp"
    "network/SocketIO.cpp"
    "network/WebSocket.cpp"
    )

cocos_use_package(${COCOS2D_TARGET} WEBSOCKETS REQUIRED)
cocos_use_package(${COCOS2D_TARGET} CURL REQUIRED)
# CURL depends CRYPTO and SSL.
# SSL Must BEFORE CRYPTO.
cocos_use_package(${COCOS2D_TARGET} OpenSSL REQUIRED)
cocos_use_package(${COCOS2D_TARGET} CRYPTO REQUIRED)

