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

