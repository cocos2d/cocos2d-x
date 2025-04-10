if(WIN32)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/win32/CCStdC.cpp
  platform/win32/CCFileUtilsWin32.cpp
  platform/win32/CCCommon.cpp
  platform/win32/CCApplication.cpp
  platform/win32/CCDevice.cpp
)

elseif(APPLE)


elseif(OHOS)
  set(COCOS_PLATFORM_SPECIFIC_SRC
    platform/ohos/CCDevice.cpp
    platform/ohos/CCGLView.cpp
    platform/ohos/CCApplication.cpp
    platform/ohos/CCCommon.cpp
    platform/ohos/CCFileUtils-ohos.cpp
    platform/ohos/CCTextBitmap.cpp
    platform/ohos/napi/modules/RawFileUtils.cpp
    platform/ohos/napi/modules/TouchesNapi.cpp
    platform/ohos/napi/modules/InputNapi.cpp
    platform/ohos/napi/modules/MouseNapi.cpp
    platform/ohos/napi/modules/WebViewNapi.cpp
    platform/ohos/napi/modules/VideoPlayerNapi.cpp
    platform/ohos/napi/helper/NapiValueConverter.cpp
    platform/ohos/napi/helper/Js_Cocos2dxHelper.cpp
    platform/ohos/napi/helper/NapiHelper.cpp
    platform/ohos/napi/render/egl_core.cpp
    platform/ohos/napi/render/plugin_render.cpp
    platform/ohos/napi/plugin_manager.cpp
    platform/ohos/napi/WorkerMessageQueue.cpp
  )
else()

set(COCOS_PLATFORM_SPECIFIC_SRC
  platform/linux/CCStdC.cpp
  platform/linux/CCFileUtilsLinux.cpp
  platform/linux/CCCommon.cpp
  platform/linux/CCApplication.cpp
  platform/linux/CCDevice.cpp
)

endif()

include_directories(
  ../external/ConvertUTF
)
if(OHOS)
  set(COCOS_PLATFORM_SRC
    platform/CCSAXParser.cpp
    platform/CCThread.cpp
    platform/CCGLViewProtocol.cpp
    platform/CCFileUtils.cpp
    platform/CCImage.cpp
    ../external/edtaa3func/edtaa3func.cpp
    ../external/ConvertUTF/ConvertUTFWrapper.cpp
    ../external/ConvertUTF/ConvertUTF.c
    ${COCOS_PLATFORM_SPECIFIC_SRC}
  )
else()
  set(COCOS_PLATFORM_SRC
    platform/CCSAXParser.cpp
    platform/CCThread.cpp
    platform/CCGLViewProtocol.cpp
    platform/CCFileUtils.cpp
    platform/CCImage.cpp
    platform/desktop/CCGLView.cpp
    ../external/edtaa3func/edtaa3func.cpp
    ../external/ConvertUTF/ConvertUTFWrapper.cpp
    ../external/ConvertUTF/ConvertUTF.c
    ${COCOS_PLATFORM_SPECIFIC_SRC}
  )
endif()
