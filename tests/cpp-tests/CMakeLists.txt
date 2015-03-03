set(APP_NAME cpp-tests)

# Use same method as in cocos library
cocos_find_package(CURL CURL REQUIRED)

if(WIN32)
  set(PLATFORM_SRC proj.win32/main.cpp)
  set(RES_PREFIX "")
elseif(MACOSX)
  set(PLATFORM_SRC proj.mac/main.cpp)

  file(GLOB_RECURSE RES_FILES Resources/*)
  cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
  list(APPEND PLATFORM_SRC ${RES_FILES})

elseif(LINUX)
  set(PLATFORM_SRC proj.linux/main.cpp)
  set(RES_PREFIX "/Resources")
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

set(TESTS_SRC
  Classes/ActionManagerTest/ActionManagerTest.cpp
  Classes/ActionsEaseTest/ActionsEaseTest.cpp
  Classes/ActionsProgressTest/ActionsProgressTest.cpp
  Classes/ActionsTest/ActionsTest.cpp
  Classes/AllocatorTest/AllocatorTest.cpp
  Classes/BillBoardTest/BillBoardTest.cpp
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
  Classes/BugsTest/BugsTest.cpp
  Classes/BugsTest/Bug-Child.cpp
  Classes/Camera3DTest/Camera3DTest.cpp
  Classes/ChipmunkTest/ChipmunkTest.cpp
  Classes/ClickAndMoveTest/ClickAndMoveTest.cpp
  Classes/ClippingNodeTest/ClippingNodeTest.cpp
  Classes/CocosDenshionTest/CocosDenshionTest.cpp
  Classes/CurlTest/CurlTest.cpp
  Classes/CurrentLanguageTest/CurrentLanguageTest.cpp
  Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp
  Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp
  Classes/EffectsTest/EffectsTest.cpp
  Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp
  Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp
  Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp
  Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp
  Classes/ExtensionsTest/ExtensionsTest.cpp
  Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp
  Classes/UITest/CocoStudioGUITest/CocoStudioGUITest.cpp
  Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp
  Classes/UITest/CocoStudioGUITest/UIScene.cpp
  Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp
  Classes/UITest/CocoStudioGUITest/UISceneManager.cpp
  Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp
  Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp
  Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp
  Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp
  Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp
  Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp
  Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp
  Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp
  Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp
  Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp
  Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.cpp
  Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.cpp
  Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.cpp
  Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp
  Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp
  Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp
  Classes/NewRendererTest/NewRendererTest.cpp
  Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp
  Classes/NewAudioEngineTest/NewAudioEngineTest.cpp
  Classes/FontTest/FontTest.cpp
  Classes/IntervalTest/IntervalTest.cpp
  Classes/InputTest/MouseTest.cpp
  Classes/LabelTest/LabelTest.cpp
  Classes/LabelTest/LabelTestNew.cpp
  Classes/LayerTest/LayerTest.cpp
  Classes/LightTest/LightTest.cpp
  Classes/MenuTest/MenuTest.cpp
  Classes/MotionStreakTest/MotionStreakTest.cpp
  Classes/MutiTouchTest/MutiTouchTest.cpp
  Classes/NodeTest/NodeTest.cpp
  Classes/OpenURLTest/OpenURLTest.cpp
  Classes/ParallaxTest/ParallaxTest.cpp
  Classes/ParticleTest/ParticleTest.cpp
  Classes/PerformanceTest/PerformanceAllocTest.cpp
  Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp
  Classes/PerformanceTest/PerformanceParticleTest.cpp
  Classes/PerformanceTest/PerformanceSpriteTest.cpp
  Classes/PerformanceTest/PerformanceTest.cpp
  Classes/PerformanceTest/PerformanceTextureTest.cpp
  Classes/PerformanceTest/PerformanceTouchesTest.cpp
  Classes/PerformanceTest/PerformanceLabelTest.cpp
  Classes/PerformanceTest/PerformanceRendererTest.cpp
  Classes/PerformanceTest/PerformanceContainerTest.cpp
  Classes/PerformanceTest/PerformanceEventDispatcherTest.cpp
  Classes/PerformanceTest/PerformanceScenarioTest.cpp
  Classes/PerformanceTest/PerformanceCallbackTest.cpp
  Classes/PerformanceTest/PerformanceMathTest.cpp
  Classes/PhysicsTest/PhysicsTest.cpp
  Classes/ReleasePoolTest/ReleasePoolTest.cpp
  Classes/RenderTextureTest/RenderTextureTest.cpp
  Classes/RotateWorldTest/RotateWorldTest.cpp
  Classes/SceneTest/SceneTest.cpp
  Classes/SchedulerTest/SchedulerTest.cpp
  Classes/ShaderTest/ShaderTest.cpp
  Classes/ShaderTest/ShaderTest2.cpp
  Classes/SpriteTest/SpriteTest.cpp
  Classes/Sprite3DTest/Sprite3DTest.cpp
  Classes/Sprite3DTest/DrawNode3D.cpp
  Classes/TextInputTest/TextInputTest.cpp
  Classes/Texture2dTest/Texture2dTest.cpp
  Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp
  Classes/TextureCacheTest/TextureCacheTest.cpp
  Classes/TileMapTest/TileMapTest.cpp
  Classes/TileMapTest/TileMapTest2.cpp
  Classes/TouchesTest/Ball.cpp
  Classes/TouchesTest/Paddle.cpp
  Classes/TouchesTest/TouchesTest.cpp
  Classes/TransitionsTest/TransitionsTest.cpp
  Classes/UserDefaultTest/UserDefaultTest.cpp
  Classes/VibrateTest/VibrateTest.cpp
  Classes/ZwoptexTest/ZwoptexTest.cpp
  Classes/FileUtilsTest/FileUtilsTest.cpp
  Classes/ConfigurationTest/ConfigurationTest.cpp
  Classes/ConsoleTest/ConsoleTest.cpp
  Classes/UnitTest/RefPtrTest.cpp
  Classes/UnitTest/UnitTest.cpp
  Classes/UITest/UITest.cpp
  Classes/controller.cpp
  Classes/testBasic.cpp
  Classes/AppDelegate.cpp
  Classes/BaseTest.cpp
  Classes/VisibleRect.cpp
  ${PLATFORM_SRC}
)

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
endif()

if(LINUX)
    set(EXTENDED_TESTS_SRC
    )
else()
    set(EXTENDED_TESTS_SRC
        Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp
        Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp
        Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp

        Classes/UITest/CocoStudioGUITest/CocoStudioGUITest.cpp
        Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp
        Classes/UITest/CocoStudioGUITest/UIEditBoxTest.cpp
        Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp
        Classes/UITest/CocoStudioGUITest/UIScene.cpp
        Classes/UITest/CocoStudioGUITest/UISceneManager.cpp
    )
endif()


include_directories(
  Classes
)

# add the executable
add_executable(${APP_NAME}
  ${TESTS_SRC}
  ${EXTENDED_TESTS_SRC}
)

target_link_libraries(${APP_NAME}
  cocos2d
)

cocos_use_pkg(${APP_NAME} CURL)

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

else()
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}${RES_PREFIX}
      )
endif()

