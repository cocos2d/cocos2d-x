cmake_minimum_required(VERSION 3.1)

set(APP_NAME cpp_tests)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
    
    include(CocosBuildSet)
    CocosBuildSet()
    if(NOT USE_COCOS_PREBUILT)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif()
endif()

set(res_res_folders 
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
)
if(APPLE OR VS)
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${res_res_folders})
endif()

if(WINDOWS)
    set(windows_src proj.win32/main.cpp)
    set(platform_specific_src ${cc_common_res} ${windows_src})
elseif(APPLE)
    if(IOS)
        set(ios_code_files
            proj.ios/main.m
            proj.ios/Classes/testsAppDelegate.mm
            proj.ios/Classes/RootViewController.mm
        )
        set(ios_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreen.storyboard
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files proj.mac/main.cpp)
        set(mac_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()
    set(platform_specific_src ${cc_common_res} ${apple_src_files})
elseif(LINUX)
    set(platform_specific_src proj.linux/main.cpp)
elseif(ANDROID)
    set(platform_specific_src
          Classes/JNITest/JNITest.cpp
          proj.android/app/jni/main.cpp)
elseif(IOS)
    set(platform_specific_src proj.ios/main.m)
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

set(TESTS_SRC
    Classes/ActionManagerTest/ActionManagerTest.cpp
    Classes/ActionsEaseTest/ActionsEaseTest.cpp
    Classes/ActionsProgressTest/ActionsProgressTest.cpp
    Classes/ActionsTest/ActionsTest.cpp
    Classes/AllocatorTest/AllocatorTest.cpp
    Classes/AppDelegate.cpp
    Classes/BaseTest.cpp
    Classes/BillBoardTest/BillBoardTest.cpp
    Classes/BugsTest/Bug-CCDrawNode.cpp
    Classes/BugsTest/Bug-1159.cpp
    Classes/BugsTest/Bug-1174.cpp
    Classes/BugsTest/Bug-350.cpp
    Classes/BugsTest/Bug-422.cpp
    Classes/BugsTest/Bug-458/Bug-458.cpp
    Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp
    Classes/BugsTest/Bug-624.cpp
    Classes/BugsTest/Bug-886.cpp
    Classes/BugsTest/Bug-899.cpp
    Classes/BugsTest/Bug-914.cpp
    Classes/BugsTest/Bug-12847.cpp
    Classes/BugsTest/Bug-15594.cpp
    Classes/BugsTest/Bug-15776.cpp
    Classes/BugsTest/Bug-Child.cpp
    Classes/BugsTest/BugsTest.cpp
    Classes/Camera3DTest/Camera3DTest.cpp
    Classes/ChipmunkTest/ChipmunkTest.cpp
    Classes/ClickAndMoveTest/ClickAndMoveTest.cpp
    Classes/ClippingNodeTest/ClippingNodeTest.cpp
    Classes/CocosDenshionTest/CocosDenshionTest.cpp
    Classes/ConfigurationTest/ConfigurationTest.cpp
    Classes/ConsoleTest/ConsoleTest.cpp
    Classes/CurlTest/CurlTest.cpp
    Classes/CurrentLanguageTest/CurrentLanguageTest.cpp
    Classes/DataVisitorTest/DataVisitorTest.cpp
    Classes/DownloaderTest/DownloaderTest.cpp
    Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp
    Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp
    Classes/EffectsTest/EffectsTest.cpp
    Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.cpp
    Classes/ExtensionsTest/ExtensionsTest.cpp
    Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp
    Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp
    Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp
    Classes/FileUtilsTest/FileUtilsTest.cpp
    Classes/FontTest/FontTest.cpp
    Classes/InputTest/MouseTest.cpp
    Classes/IntervalTest/IntervalTest.cpp
    Classes/LabelTest/LabelTest.cpp
    Classes/LabelTest/LabelTestNew.cpp
    Classes/LayerTest/LayerTest.cpp
    Classes/LightTest/LightTest.cpp
    Classes/MaterialSystemTest/MaterialSystemTest.cpp
    Classes/MenuTest/MenuTest.cpp
    Classes/MotionStreakTest/MotionStreakTest.cpp
    Classes/MultiTouchTest/MultiTouchTest.cpp
    Classes/NewAudioEngineTest/NewAudioEngineTest.cpp
    Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp
    Classes/NewRendererTest/NewRendererTest.cpp
    Classes/NavMeshTest/NavMeshTest.cpp
    Classes/NodeTest/NodeTest.cpp
    Classes/OpenURLTest/OpenURLTest.cpp
    Classes/ParallaxTest/ParallaxTest.cpp
    Classes/Particle3DTest/Particle3DTest.cpp
    Classes/ParticleTest/ParticleTest.cpp
    Classes/PhysicsTest/PhysicsTest.cpp
    Classes/ReleasePoolTest/ReleasePoolTest.cpp
    Classes/RenderTextureTest/RenderTextureTest.cpp
    Classes/RotateWorldTest/RotateWorldTest.cpp
    Classes/SceneTest/SceneTest.cpp
    Classes/SchedulerTest/SchedulerTest.cpp
    Classes/ShaderTest/ShaderTest.cpp
    Classes/ShaderTest/ShaderTest2.cpp
    Classes/SpineTest/SpineTest.cpp
    Classes/Scene3DTest/Scene3DTest.cpp
    Classes/Sprite3DTest/DrawNode3D.cpp
    Classes/Sprite3DTest/Sprite3DTest.cpp
    Classes/SpritePolygonTest/SpritePolygonTest.cpp
    Classes/SpriteTest/SpriteTest.cpp
    Classes/TerrainTest/TerrainTest.cpp
    Classes/TextInputTest/TextInputTest.cpp
    Classes/Texture2dTest/Texture2dTest.cpp
    Classes/TextureCacheTest/TextureCacheTest.cpp
    Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp
    Classes/TileMapTest/TileMapTest.cpp
    Classes/TileMapTest/TileMapTest2.cpp
    Classes/TouchesTest/Ball.cpp
    Classes/TouchesTest/Paddle.cpp
    Classes/TouchesTest/TouchesTest.cpp
    Classes/TransitionsTest/TransitionsTest.cpp
    Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp
    Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp
    Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp
    Classes/UITest/CocoStudioGUITest/UIRadioButtonTest/UIRadioButtonTest.cpp
    Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp
    Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp
    Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp
    Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp
    Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp
    Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp
    Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp
    Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp
    Classes/UITest/CocoStudioGUITest/UIScene.cpp
    Classes/UITest/CocoStudioGUITest/UISceneManager.cpp
    Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp
    Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp
    Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.cpp
    Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.cpp
    Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp
    Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.cpp
    Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp
    Classes/UITest/CocoStudioGUITest/UITabControlTest/UITabControlTest.cpp
    Classes/UITest/UITest.cpp
    Classes/UnitTest/RefPtrTest.cpp
    Classes/UnitTest/UnitTest.cpp
    Classes/UserDefaultTest/UserDefaultTest.cpp
    Classes/VisibleRect.cpp
    Classes/VibrateTest/VibrateTest.cpp
    Classes/ZwoptexTest/ZwoptexTest.cpp
    Classes/SpriteFrameCacheTest/SpriteFrameCacheTest.cpp
    Classes/controller.cpp
    # Classes/VRTest/VRTest.cpp
    # Classes/VRTest/VRTest.h
    ${platform_specific_src}
    )

if(ANDROID OR IOS)
    list(APPEND TESTS_SRC
        Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.cpp
        Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.cpp
        )
endif()

if(WIN32 OR MACOSX OR LINUX)
    list(APPEND TESTS_SRC
        Classes/WindowTest/WindowTest.cpp
        )
    list(APPEND TESTS_SRC
        Classes/BugsTest/Bug-14327.cpp
        )
endif()

if(USE_CHIPMUNK)
    include_directories(${CHIPMUNK_INCLUDE_DIRS})
endif()

if(USE_BOX2D)
    list(APPEND TESTS_SRC
        Classes/Box2DTest/Box2dTest.cpp
        Classes/Box2DTestBed/Box2dView.cpp
        Classes/Box2DTestBed/GLES-Render.cpp
        Classes/Box2DTestBed/Test.cpp
        Classes/Box2DTestBed/TestEntries.cpp
        )
    include_directories(${Box2D_INCLUDE_DIRS})
endif()

if(USE_BULLET)
    list(APPEND TESTS_SRC
            Classes/Physics3DTest/Physics3DTest.cpp
        )
    include_directories(${BULLET_INCLUDE_DIRS})
endif()

set(EXTENDED_TESTS_SRC
    Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp
    Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp
    Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp
    )

if(NOT LINUX)
    list(APPEND EXTENDED_TESTS_SRC
        Classes/UITest/CocoStudioGUITest/UIEditBoxTest.cpp
    )
endif()

include_directories(
    Classes
    ${COCOS2DX_ROOT_PATH}/cocos/editor-support
)

# mark app complie info and libs info
set(cocos_app_src 
    ${TESTS_SRC}
    ${EXTENDED_TESTS_SRC}
)
cocos_build_app(${APP_NAME}
    APP_SRC "${cocos_app_src}"
    DEPEND_COMMON_LIBS "cocos2d"
    DEPEND_ANDROID_LIBS "cocos2d_android"
    COMMON_USE_PKGS "FREETYPE" "CURL"
    LINUX_USE_PKGS "FONTCONFIG" "GTK3"
)

# mark app resources
if(APPLE)
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "Tests Cpp" INFO_STRING "test project for cpp")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif()

if(LINUX OR WINDOWS)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${res_res_folders})
endif()
