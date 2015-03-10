
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
# There's no findCrypto.cmake yet, so find_package can't work.
# If there's no prebuilt crypto, use find_library instead.
# There's no prebuilt crypto for linux.
if(NOT BUILD_USE_PREBUILT_LIBS OR
        COCOS_TARGET_SYSTEM_LINUX)
    find_library(CRYPTO_LIBRARY crypto)
    if(NOT CRYPTO_LIBRARY)
        message(FATAL_ERROR "Can't find library 'crypto' on target system.")
    endif()
    # Define target 'CRYPTO::CRYPTO' for cocos_use_package usage.
    set(_target "CRYPTO")
    add_library(${_target}::${_target} UNKNOWN IMPORTED)
    set_target_properties(${_target}::${_target} PROPERTIES
        IMPORTED_LOCATION ${CRYPTO_LIBRARY}
    )
    mark_as_advanced(CRYPTO_LIBRARY)
endif()
cocos_use_package(${COCOS2D_TARGET} CRYPTO REQUIRED)

