cmake_minimum_required(VERSION 3.6)

set(APP_NAME cpp-tests)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR VS)
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME cpp_tests)
    list(APPEND GAME_HEADER
         Classes/JNITest/JNITest.h
         )
    list(APPEND GAME_SOURCE
         Classes/JNITest/JNITest.cpp
         proj.android/app/jni/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         ${cc_common_res}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios/Classes/testsAppDelegate.h
             proj.ios/Classes/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios/LaunchScreen.storyboard
            proj.ios/LaunchScreenBackground.png
            proj.ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios/main.m
             proj.ios/Classes/testsAppDelegate.mm
             proj.ios/Classes/RootViewController.mm
             proj.ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.mac/Icon.icns
            proj.mac/Info.plist
            proj.mac/Prefix.pch
            proj.mac/en.lproj/MainMenu.xib
            proj.mac/en.lproj/InfoPlist.strings
            )
        list(APPEND GAME_SOURCE
             proj.mac/main.cpp
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${cc_common_res})
endif()

list(APPEND GAME_HEADER
     Classes/ActionsEaseTest/ActionsEaseTest.h
     Classes/ParallaxTest/ParallaxTest.h
     Classes/testBasic.h
     Classes/ZwoptexTest/ZwoptexTest.h
     Classes/precheader.h
     Classes/CurlTest/CurlTest.h
     Classes/UnitTest/UnitTest.h
     Classes/UnitTest/RefPtrTest.h
     Classes/ConfigurationTest/ConfigurationTest.h
     Classes/CurrentLanguageTest/CurrentLanguageTest.h
     Classes/AppDelegate.h
     Classes/LabelTest/LabelTestNew.h
     Classes/LabelTest/LabelTest.h
     Classes/Particle3DTest/Particle3DTest.h
     Classes/AllocatorTest/AllocatorTest.h
     Classes/VibrateTest/VibrateTest.h
     Classes/ClippingNodeTest/ClippingNodeTest.h
     Classes/UserDefaultTest/UserDefaultTest.h
     Classes/tests.h
     Classes/DataVisitorTest/DataVisitorTest.h
     Classes/NewAudioEngineTest/NewAudioEngineTest.h
     Classes/BugsTest/Bug-422.h
     Classes/BugsTest/Bug-CCDrawNode.h
     Classes/BugsTest/BugsTest.h
     Classes/BugsTest/Bug-12847.h
     Classes/BugsTest/Bug-899.h
     Classes/BugsTest/Bug-1159.h
     Classes/BugsTest/Bug-350.h
     Classes/BugsTest/Bug-15594.h
     Classes/BugsTest/Bug-914.h
     Classes/BugsTest/Bug-624.h
     Classes/BugsTest/Bug-458/QuestionContainerSprite.h
     Classes/BugsTest/Bug-458/Bug-458.h
     Classes/BugsTest/Bug-886.h
     Classes/BugsTest/Bug-Child.h
     Classes/BugsTest/Bug-15776.h
     Classes/BugsTest/Bug-1174.h
     Classes/ActionsTest/ActionsTest.h
     Classes/TouchesTest/TouchesTest.h
     Classes/TouchesTest/Ball.h
     Classes/TouchesTest/Paddle.h
     Classes/ActionManagerTest/ActionManagerTest.h
     Classes/ClickAndMoveTest/ClickAndMoveTest.h
     Classes/MaterialSystemTest/MaterialSystemTest.h
     Classes/IntervalTest/IntervalTest.h
     Classes/TileMapTest/TileMapTest2.h
     Classes/TileMapTest/TileMapTest.h
     Classes/NewEventDispatcherTest/NewEventDispatcherTest.h
     Classes/ActionsProgressTest/ActionsProgressTest.h
     Classes/RotateWorldTest/RotateWorldTest.h
     Classes/Camera3DTest/Camera3DTest.h
     Classes/TextInputTest/TextInputTest.h
     Classes/Texture2dTest/Texture2dTest.h
     Classes/TerrainTest/TerrainTest.h
     Classes/controller.h
     Classes/TransitionsTest/TransitionsTest.h
     Classes/TextureCacheTest/TextureCacheTest.h
     Classes/MotionStreakTest/MotionStreakTest.h
     Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.h
     Classes/ExtensionsTest/ExtensionsTest.h
     Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.h
     Classes/ExtensionsTest/TableViewTest/TableViewTestScene.h
     Classes/ExtensionsTest/NetworkTest/WebSocketTest.h
     Classes/ExtensionsTest/NetworkTest/WebSocketDelayTest.h
     Classes/ExtensionsTest/NetworkTest/SocketIOTest.h
     Classes/ExtensionsTest/NetworkTest/HttpClientTest.h
     Classes/Sprite3DTest/Sprite3DTest.h
     Classes/Sprite3DTest/DrawNode3D.h
     Classes/BaseTest.h
     Classes/SceneTest/SceneTest.h
     Classes/ReleasePoolTest/ReleasePoolTest.h
     Classes/CocosDenshionTest/CocosDenshionTest.h
     Classes/InputTest/MouseTest.h
     Classes/SpineTest/SpineTest.h
     Classes/Scene3DTest/Scene3DTest.h
     Classes/ParticleTest/ParticleTest.h
     Classes/EffectsTest/EffectsTest.h
     Classes/UITest/UITest.h
     Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.h
     Classes/UITest/CocoStudioGUITest/CocosGUIScene.h
     Classes/UITest/CocoStudioGUITest/UITabControlTest/UITabControlTest.h
     Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.h
     Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.h
     Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.h
     Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.h
     Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.h
     Classes/UITest/CocoStudioGUITest/UIEditBoxTest.h
     Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.h
     Classes/UITest/CocoStudioGUITest/UIScene.h
     Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.h
     Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.h
     Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.h
     Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.h
     Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.h
     Classes/UITest/CocoStudioGUITest/UISceneManager.h
     Classes/UITest/CocoStudioGUITest/UIRadioButtonTest/UIRadioButtonTest.h
     Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.h
     Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.h
     Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.h
     Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.h
     Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.h
     Classes/DrawPrimitivesTest/DrawPrimitivesTest.h
     Classes/BillBoardTest/BillBoardTest.h
     Classes/SpriteFrameCacheTest/SpriteFrameCacheTest.h
     Classes/EffectsAdvancedTest/EffectsAdvancedTest.h
     Classes/SchedulerTest/SchedulerTest.h
     Classes/MultiTouchTest/MultiTouchTest.h
     Classes/testResource.h
     Classes/ShaderTest/ShaderTest.vsh.h
     Classes/ShaderTest/shaderTest.psh.h
     Classes/ShaderTest/ShaderTest.h
     Classes/ShaderTest/ShaderTest2.h
     Classes/NewRendererTest/NewRendererTest.h
     Classes/SpritePolygonTest/SpritePolygonTest.h
     Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.h
     Classes/NodeTest/NodeTest.h
     Classes/FileUtilsTest/FileUtilsTest.h
     Classes/RenderTextureTest/RenderTextureTest.h
     Classes/LayerTest/LayerTest.h
     Classes/SpriteTest/SpriteTest.h
     Classes/FontTest/FontTest.h
     Classes/LightTest/LightTest.h
     Classes/VisibleRect.h
     Classes/DownloaderTest/DownloaderTest.h
     Classes/OpenURLTest/OpenURLTest.h
     Classes/ConsoleTest/ConsoleTest.h
     Classes/MenuTest/MenuTest.h
     )

list(APPEND GAME_SOURCE
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
     Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp
     Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp
     Classes/ExtensionsTest/NetworkTest/WebSocketDelayTest.cpp
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
     Classes/NodeTest/NodeTest.cpp
     Classes/OpenURLTest/OpenURLTest.cpp
     Classes/ParallaxTest/ParallaxTest.cpp
     Classes/Particle3DTest/Particle3DTest.cpp
     Classes/ParticleTest/ParticleTest.cpp
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
     )

if(ANDROID OR IOS)
    list(APPEND GAME_HEADER
         Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.h
         Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.h
         )
    list(APPEND GAME_SOURCE
         Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.cpp
         Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.cpp
         )
endif()

if(WINDOWS OR MACOSX OR LINUX)
    list(APPEND GAME_HEADER
         Classes/WindowTest/WindowTest.h
         Classes/BugsTest/Bug-14327.h
         )
    list(APPEND GAME_SOURCE
         Classes/WindowTest/WindowTest.cpp
         Classes/BugsTest/Bug-14327.cpp
         )
endif()

list(APPEND GAME_HEADER
     Classes/Box2DTest/Box2dTest.cpp
     Classes/Box2DTestBed/Test.h
     Classes/Box2DTestBed/Tests/Chain.h
     Classes/Box2DTestBed/Tests/Confined.h
     Classes/Box2DTestBed/Tests/PolyCollision.h
     Classes/Box2DTestBed/Tests/EdgeTest.h
     Classes/Box2DTestBed/Tests/ApplyForce.h
     Classes/Box2DTestBed/Tests/Gears.h
     Classes/Box2DTestBed/Tests/SliderCrank.h
     Classes/Box2DTestBed/Tests/ContinuousTest.h
     Classes/Box2DTestBed/Tests/Revolute.h
     Classes/Box2DTestBed/Tests/TheoJansen.h
     Classes/Box2DTestBed/Tests/Bridge.h
     Classes/Box2DTestBed/Tests/CollisionProcessing.h
     Classes/Box2DTestBed/Tests/DistanceTest.h
     Classes/Box2DTestBed/Tests/PolyShapes.h
     Classes/Box2DTestBed/Tests/TimeOfImpact.h
     Classes/Box2DTestBed/Tests/ConveyorBelt.h
     Classes/Box2DTestBed/Tests/Tiles.h
     Classes/Box2DTestBed/Tests/BulletTest.h
     Classes/Box2DTestBed/Tests/MotorJoint.h
     Classes/Box2DTestBed/Tests/Car.h
     Classes/Box2DTestBed/Tests/Mobile.h
     Classes/Box2DTestBed/Tests/VaryingFriction.h
     Classes/Box2DTestBed/Tests/Rope.h
     Classes/Box2DTestBed/Tests/SensorTest.h
     Classes/Box2DTestBed/Tests/Pyramid.h
     Classes/Box2DTestBed/Tests/VaryingRestitution.h
     Classes/Box2DTestBed/Tests/RopeJoint.h
     Classes/Box2DTestBed/Tests/VerticalStack.h
     Classes/Box2DTestBed/Tests/MobileBalanced.h
     Classes/Box2DTestBed/Tests/CompoundShapes.h
     Classes/Box2DTestBed/Tests/CollisionFiltering.h
     Classes/Box2DTestBed/Tests/Pulleys.h
     Classes/Box2DTestBed/Tests/Breakable.h
     Classes/Box2DTestBed/Tests/BodyTypes.h
     Classes/Box2DTestBed/Tests/DumpShell.h
     Classes/Box2DTestBed/Tests/ShapeEditing.h
     Classes/Box2DTestBed/Tests/SphereStack.h
     Classes/Box2DTestBed/Tests/OneSidedPlatform.h
     Classes/Box2DTestBed/Tests/AddPair.h
     Classes/Box2DTestBed/Tests/Pinball.h
     Classes/Box2DTestBed/Tests/Tumbler.h
     Classes/Box2DTestBed/Tests/RayCast.h
     Classes/Box2DTestBed/Tests/ConvexHull.h
     Classes/Box2DTestBed/Tests/EdgeShapes.h
     Classes/Box2DTestBed/Tests/Prismatic.h
     Classes/Box2DTestBed/Tests/Dominos.h
     Classes/Box2DTestBed/Tests/Web.h
     Classes/Box2DTestBed/Tests/CharacterCollision.h
     Classes/Box2DTestBed/Tests/DynamicTreeTest.h
     Classes/Box2DTestBed/Tests/Cantilever.h
     Classes/Box2DTestBed/Box2dView.h
     Classes/Box2DTestBed/GLES-Render.h
     )
list(APPEND GAME_SOURCE
     Classes/Box2DTest/Box2dTest.cpp
     Classes/Box2DTestBed/Box2dView.cpp
     Classes/Box2DTestBed/GLES-Render.cpp
     Classes/Box2DTestBed/Test.cpp
     Classes/Box2DTestBed/TestEntries.cpp
     )

list(APPEND GAME_HEADER
     Classes/Physics3DTest/Physics3DTest.h
     Classes/NavMeshTest/NavMeshTest.h
     )
list(APPEND GAME_SOURCE
     Classes/Physics3DTest/Physics3DTest.cpp
     Classes/NavMeshTest/NavMeshTest.cpp
     )
list(APPEND GAME_HEADER
     Classes/PhysicsTest/PhysicsTest.h
     Classes/ChipmunkTest/ChipmunkTest.h
     )
list(APPEND GAME_SOURCE
     Classes/PhysicsTest/PhysicsTest.cpp
     Classes/ChipmunkTest/ChipmunkTest.cpp
     )

if(NOT LINUX)
    list(APPEND GAME_SOURCE
         Classes/UITest/CocoStudioGUITest/UIEditBoxTest.cpp
         )
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )

if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon-${APP_NAME}")
    endif()
elseif(WINDOWS)
    # "too large PDB" error often occurs in cpp-tests when using default "/Zi"
    target_compile_options(${APP_NAME} PRIVATE /Z7)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR}/..)
endif()

if(LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
