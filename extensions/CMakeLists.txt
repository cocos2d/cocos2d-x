# This file include by cocos/CMakeLists.txt.

target_include_directories(${COCOS2D_TARGET} PUBLIC "../extensions")

cocos_target_sources(${COCOS2D_TARGET} GROUP "extensions" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "../extensions/assets-manager/AssetsManager.cpp"
    "../extensions/assets-manager/AssetsManagerEx.cpp"
    "../extensions/assets-manager/CCEventAssetsManagerEx.cpp"
    "../extensions/assets-manager/CCEventListenerAssetsManagerEx.cpp"
    "../extensions/assets-manager/Downloader.cpp"
    "../extensions/assets-manager/Manifest.cpp"
    "../extensions/GUI/CCControlExtension/CCControl.cpp"
    "../extensions/GUI/CCControlExtension/CCControlButton.cpp"
    "../extensions/GUI/CCControlExtension/CCControlColourPicker.cpp"
    "../extensions/GUI/CCControlExtension/CCControlHuePicker.cpp"
    "../extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp"
    "../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp"
    "../extensions/GUI/CCControlExtension/CCControlSlider.cpp"
    "../extensions/GUI/CCControlExtension/CCControlStepper.cpp"
    "../extensions/GUI/CCControlExtension/CCControlSwitch.cpp"
    "../extensions/GUI/CCControlExtension/CCControlUtils.cpp"
    "../extensions/GUI/CCControlExtension/CCInvocation.cpp"
    "../extensions/GUI/CCScrollView/CCScrollView.cpp"
    "../extensions/GUI/CCScrollView/CCTableView.cpp"
    "../extensions/GUI/CCScrollView/CCTableViewCell.cpp"
    "../extensions/physics-nodes/CCPhysicsDebugNode.cpp"
    "../extensions/physics-nodes/CCPhysicsSprite.cpp"
)

if(COCOS_TARGET_SYSTEM_WINDOWS AND BUILD_SHARED_LIBS)
    target_compile_definitions(${COCOS2D_TARGET} PRIVATE _USREXDLL)
endif()

#===============================================================================
# CCPhysicsSprite support Chipmunk or Box2D.
option(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_BOX2D
    "Build CCPhysicsSprite with Box2D support."
    OFF
    )
option(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_CHIPMUNK
    "Build CCPhysicsSprite with Chipmunk support."
    ON
    )
if(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_BOX2D AND
        BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_CHIPMUNK)
    message(AUTHOR_WARNING "CCPhysicsSprite uses either Chipmunk or Box2D.")
endif()

if(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_BOX2D)
    target_compile_definitions(${COCOS2D_TARGET} PUBLIC
        CC_ENABLE_BOX2D_INTEGRATION=1
        )

    # Box2d (not prebuilded, exists as source)
    if(BUILD_USE_PREBUILT_LIBS)
        add_subdirectory("../external/Box2D" "external/Box2D")
    endif()
    cocos_use_package(${COCOS2D_TARGET} Box2D REQUIRED)

elseif(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_CHIPMUNK)
    target_compile_definitions(${COCOS2D_TARGET} PUBLIC
        CC_ENABLE_CHIPMUNK_INTEGRATION=1
        )

endif()

