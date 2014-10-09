if(WINDOWS AND NOT BUILD_STATIC)
  ADD_DEFINITIONS (-D_USREXDLL)
endif()

if(WINDOWS)

#  set(PLATFORM_EXTENSIONS_SRC
#    ../extensions/proj.win32/Win32InputBox.cpp
#  )
  
elseif(MACOSX)

else()
#  set(PLATFORM_EXTENSIONS_SRC
#    ../../extensions/GUI/CCEditBox/CCEditBoxImplNone.cpp)
endif()

include_directories(
  ../../extensions
)

set(COCOS_EXTENSIONS_SRC

  ../extensions/assets-manager/AssetsManager.cpp
  ../extensions/assets-manager/AssetsManagerEx.cpp
  ../extensions/assets-manager/CCEventAssetsManagerEx.cpp
  ../extensions/assets-manager/CCEventListenerAssetsManagerEx.cpp
  ../extensions/assets-manager/Downloader.cpp
  ../extensions/assets-manager/Manifest.cpp
  ../extensions/GUI/CCControlExtension/CCControl.cpp
  ../extensions/GUI/CCControlExtension/CCControlButton.cpp
  ../extensions/GUI/CCControlExtension/CCControlColourPicker.cpp
  ../extensions/GUI/CCControlExtension/CCControlHuePicker.cpp
  ../extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp
  ../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp
  ../extensions/GUI/CCControlExtension/CCControlSlider.cpp
  ../extensions/GUI/CCControlExtension/CCControlStepper.cpp
  ../extensions/GUI/CCControlExtension/CCControlSwitch.cpp
  ../extensions/GUI/CCControlExtension/CCControlUtils.cpp
  ../extensions/GUI/CCControlExtension/CCInvocation.cpp
  ../extensions/GUI/CCScrollView/CCScrollView.cpp
  ../extensions/GUI/CCScrollView/CCTableView.cpp
  ../extensions/GUI/CCScrollView/CCTableViewCell.cpp
  ../extensions/physics-nodes/CCPhysicsDebugNode.cpp
  ../extensions/physics-nodes/CCPhysicsSprite.cpp
  ${PLATFORM_EXTENSIONS_SRC}
)
