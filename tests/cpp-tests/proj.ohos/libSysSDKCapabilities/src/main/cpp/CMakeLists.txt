cmake_minimum_required(VERSION 3.4.1)
project(nativerender)
set(COCOS_SYS_CAPABILITIES_HEADER
    napi/sdk_plugin_manager.h
    napi/helper/NapiValueConverter.h
    napi/helper/Js_Cocos2dxHelper.h
    napi/helper/NapiHelper.h
    CCSDKApplication.h
    napi/modules/LoginSDKNapi.h
    napi/modules/PaySDKNapi.h
)
set(COCOS_SYS_CAPABILITIES_SRC
    napi/sdk_plugin_manager.cpp
    napi/helper/NapiValueConverter.cpp
    napi/helper/Js_Cocos2dxHelper.cpp
    napi/helper/NapiHelper.cpp
    CCSDKApplication.cpp
    napi/modules/LoginSDKNapi.cpp
    napi/modules/PaySDKNapi.cpp
)

find_library(hilog-lib hilog_ndk.z)
find_library(libnapi-lib ace_napi.z)
find_library(libuv-lib uv)

add_library(syssdkcapabilities SHARED ${COCOS_SYS_CAPABILITIES_HEADER} ${COCOS_SYS_CAPABILITIES_SRC})
target_link_libraries(syssdkcapabilities ${hilog-lib} ${libnapi-lib} ${libuv-lib})