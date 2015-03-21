project(CPP_TESTS)

#===============================================================================
# Define target.
set(app_name cpp-tests)

if(COCOS_TARGET_SYSTEM_ANDROID)
    add_library(${app_name} SHARED ${CMAKE_CURRENT_LIST_FILE})
else()
    add_executable(${app_name} ${CMAKE_CURRENT_LIST_FILE})
endif()
set_target_properties(${app_name} PROPERTIES
    FOLDER "tests"
    )

#===============================================================================
# Set include directories.
target_include_directories(${app_name} PRIVATE
    "Classes"
    "../../"
    "../../external"
)

#===============================================================================
# Add tests sources.

cocos_target_sources(${app_name} GROUP "Classes" FILES
    "Classes/ActionManagerTest/ActionManagerTest.cpp"
    "Classes/ActionsEaseTest/ActionsEaseTest.cpp"
    "Classes/ActionsProgressTest/ActionsProgressTest.cpp"
    "Classes/ActionsTest/ActionsTest.cpp"
    "Classes/AllocatorTest/AllocatorTest.cpp"
    "Classes/BillBoardTest/BillBoardTest.cpp"
    "Classes/BugsTest/Bug-1159.cpp"
    "Classes/BugsTest/Bug-1174.cpp"
    "Classes/BugsTest/Bug-350.cpp"
    "Classes/BugsTest/Bug-422.cpp"
    "Classes/BugsTest/Bug-458/Bug-458.cpp"
    "Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp"
    "Classes/BugsTest/Bug-624.cpp"
    "Classes/BugsTest/Bug-886.cpp"
    "Classes/BugsTest/Bug-899.cpp"
    "Classes/BugsTest/Bug-914.cpp"
    "Classes/BugsTest/BugsTest.cpp"
    "Classes/BugsTest/Bug-Child.cpp"
    "Classes/Camera3DTest/Camera3DTest.cpp"
    "Classes/ChipmunkTest/ChipmunkTest.cpp"
    "Classes/ClickAndMoveTest/ClickAndMoveTest.cpp"
    "Classes/ClippingNodeTest/ClippingNodeTest.cpp"
    "Classes/CocosDenshionTest/CocosDenshionTest.cpp"
    "Classes/CurlTest/CurlTest.cpp"
    "Classes/CurrentLanguageTest/CurrentLanguageTest.cpp"
    "Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp"
    "Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp"
    "Classes/EffectsTest/EffectsTest.cpp"
    "Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp"
    "Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp"
    "Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp"
    "Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp"
    "Classes/ExtensionsTest/ExtensionsTest.cpp"
    "Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp"
    "Classes/NewRendererTest/NewRendererTest.cpp"
    "Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp"
    "Classes/NewAudioEngineTest/NewAudioEngineTest.cpp"
    "Classes/FontTest/FontTest.cpp"
    "Classes/IntervalTest/IntervalTest.cpp"
    "Classes/InputTest/MouseTest.cpp"
    "Classes/LabelTest/LabelTest.cpp"
    "Classes/LabelTest/LabelTestNew.cpp"
    "Classes/LayerTest/LayerTest.cpp"
    "Classes/LightTest/LightTest.cpp"
    "Classes/MenuTest/MenuTest.cpp"
    "Classes/MotionStreakTest/MotionStreakTest.cpp"
    "Classes/MutiTouchTest/MutiTouchTest.cpp"
    "Classes/NodeTest/NodeTest.cpp"
    "Classes/OpenURLTest/OpenURLTest.cpp"
    "Classes/ParallaxTest/ParallaxTest.cpp"
    "Classes/ParticleTest/ParticleTest.cpp"
    "Classes/PerformanceTest/PerformanceAllocTest.cpp"
    "Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp"
    "Classes/PerformanceTest/PerformanceParticleTest.cpp"
    "Classes/PerformanceTest/PerformanceSpriteTest.cpp"
    "Classes/PerformanceTest/PerformanceTest.cpp"
    "Classes/PerformanceTest/PerformanceTextureTest.cpp"
    "Classes/PerformanceTest/PerformanceTouchesTest.cpp"
    "Classes/PerformanceTest/PerformanceLabelTest.cpp"
    "Classes/PerformanceTest/PerformanceRendererTest.cpp"
    "Classes/PerformanceTest/PerformanceContainerTest.cpp"
    "Classes/PerformanceTest/PerformanceEventDispatcherTest.cpp"
    "Classes/PerformanceTest/PerformanceScenarioTest.cpp"
    "Classes/PerformanceTest/PerformanceCallbackTest.cpp"
    "Classes/PerformanceTest/PerformanceMathTest.cpp"
    "Classes/PhysicsTest/PhysicsTest.cpp"
    "Classes/ReleasePoolTest/ReleasePoolTest.cpp"
    "Classes/RenderTextureTest/RenderTextureTest.cpp"
    "Classes/RotateWorldTest/RotateWorldTest.cpp"
    "Classes/SceneTest/SceneTest.cpp"
    "Classes/SchedulerTest/SchedulerTest.cpp"
    "Classes/ShaderTest/ShaderTest.cpp"
    "Classes/ShaderTest/ShaderTest2.cpp"
    "Classes/SpriteTest/SpriteTest.cpp"
    "Classes/Sprite3DTest/Sprite3DTest.cpp"
    "Classes/Sprite3DTest/DrawNode3D.cpp"
    "Classes/TextInputTest/TextInputTest.cpp"
    "Classes/Texture2dTest/Texture2dTest.cpp"
    "Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp"
    "Classes/TextureCacheTest/TextureCacheTest.cpp"
    "Classes/TileMapTest/TileMapTest.cpp"
    "Classes/TileMapTest/TileMapTest2.cpp"
    "Classes/TouchesTest/Ball.cpp"
    "Classes/TouchesTest/Paddle.cpp"
    "Classes/TouchesTest/TouchesTest.cpp"
    "Classes/TransitionsTest/TransitionsTest.cpp"
    "Classes/UserDefaultTest/UserDefaultTest.cpp"
    "Classes/ZwoptexTest/ZwoptexTest.cpp"
    "Classes/FileUtilsTest/FileUtilsTest.cpp"
    "Classes/ConfigurationTest/ConfigurationTest.cpp"
    "Classes/ConsoleTest/ConsoleTest.cpp"
    "Classes/UnitTest/RefPtrTest.cpp"
    "Classes/UnitTest/UnitTest.cpp"
    "Classes/UITest/UITest.cpp"
    "Classes/controller.cpp"
    "Classes/testBasic.cpp"
    "Classes/AppDelegate.cpp"
    "Classes/BaseTest.cpp"
    "Classes/VisibleRect.cpp"
)

if(NOT COCOS_TARGET_SYSTEM_LINUX)
    cocos_target_sources(${app_name} GROUP "Classes" FILES
        "Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp"
        "Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp"
        "Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp"
        )
endif()

# Platform specific sources.
if(COCOS_TARGET_SYSTEM_MACOSX)
    set(platform_src
        "proj.mac/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(platform_src
        "proj.win32/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(platform_src
        "proj.linux/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    set(platform_src
        "proj.ios/Classes/RootViewController.h"
        "proj.ios/Classes/RootViewController.mm"
        "proj.ios/Classes/testsAppDelegate.h"
        "proj.ios/Classes/testsAppDelegate.mm"
        "proj.ios/main.m"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(platform_src
        "proj.android/jni/main.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build for unsupported system.")
endif()

cocos_target_sources(${app_name} GROUP "proj" FILES ${platform_src})

# Module specific sources.
if(BUILD_EXTENSIONS_CCPHYSICSSPRITE_SUPPORT_BOX2D)
    cocos_target_sources(${app_name} GROUP "Classes" FILES
        "Classes/Box2DTest/Box2dTest.cpp"
        "Classes/Box2DTestBed/Box2dView.cpp"
        "Classes/Box2DTestBed/GLES-Render.cpp"
        "Classes/Box2DTestBed/Test.cpp"
        "Classes/Box2DTestBed/TestEntries.cpp"
        )
endif()

cocos_target_sources(${app_name} GROUP "Classes" FILES
    "Classes/UITest/CocoStudioGUITest/CocoStudioGUITest.cpp"
    "Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp"
    "Classes/UITest/CocoStudioGUITest/UIScene.cpp"
    "Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UISceneManager.cpp"
    "Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp"
    "Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp"
    )
if(NOT COCOS_TARGET_SYSTEM_LINUX)
    cocos_target_sources(${app_name} GROUP "Classes" FILES
        "Classes/UITest/CocoStudioGUITest/CocoStudioGUITest.cpp"
        "Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp"
        "Classes/UITest/CocoStudioGUITest/UIEditBoxTest.cpp"
        "Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp"
        "Classes/UITest/CocoStudioGUITest/UIScene.cpp"
        "Classes/UITest/CocoStudioGUITest/UISceneManager.cpp"
        )
endif()
if(COCOS_TARGET_SYSTEM_IOS OR COCOS_TARGET_SYSTEM_ANDROID)
    cocos_target_sources(${app_name} GROUP "Classes" FILES
        "Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.cpp"
        "Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.cpp"
        )
endif()

#===============================================================================
# GLOB Resources.
file(GLOB_RECURSE res_files "Resources/*")

#===============================================================================
# Link depedent library.
target_link_libraries(${app_name} ${COCOS2D_TARGET})

#===============================================================================
# Specific settings.

# If build chipmunktests, it's type Recte...will conflict with mac and ios type.
# Define macro to resove this program.
if(COCOS_TARGET_SYSTEM_MACOSX OR COCOS_TARGET_SYSTEM_IOS)
    target_compile_definitions(${app_name} PRIVATE "CP_USE_CGPOINTS=0")
endif()

if(COCOS_TARGET_SYSTEM_MACOSX)
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "Resources"
        FILES ${res_files}
        BASEDIR "Resources"
        )
    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "${CMAKE_CURRENT_LIST_DIR}/proj.mac/Icon.icns"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    # The default Debug Information Format is '/Zi', which cause the compile error
    #   C3130: failed to write injected code block to PDB.
    target_compile_options(${app_name} PRIVATE "/Z7")

    set_target_properties(${app_name} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    cocos_use_package(${app_name} GLFW3 REQUIRED)
elseif(COCOS_TARGET_SYSTEM_IOS)
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "."
        FILES ${res_files}
        BASEDIR "Resources"
        )

    set(ios_res
        "proj.ios/Default-568h@2x.png"
        "proj.ios/Default-667h@2x.png"
        "proj.ios/Default-736h@3x.png"
        "proj.ios/Default.png"
        "proj.ios/Default@2x.png"
        "proj.ios/Icon-100.png"
        "proj.ios/Icon-114.png"
        "proj.ios/Icon-120.png"
        "proj.ios/Icon-144.png"
        "proj.ios/Icon-152.png"
        "proj.ios/Icon-29.png"
        "proj.ios/Icon-40.png"
        "proj.ios/Icon-50.png"
        "proj.ios/Icon-57.png"
        "proj.ios/Icon-58.png"
        "proj.ios/Icon-72.png"
        "proj.ios/Icon-76.png"
        "proj.ios/Icon-80.png"
        )
    cocos_target_resource(${app_name} GROUP "proj"
        LOCATION "."
        FLAT_TO_LOCATION TRUE
        FILES ${ios_res}
        )
    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "Icon-57.png"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/proj.ios/InfoCMake.plist"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${COCOS2D_X_VERSION}"
        )
endif()

#===============================================================================
# Copy resources.
if(XCODE_VERSION)
    # Nothing to do.
elseif(MSVC_IDE)
    cocos_add_copy_depends_dll_command(${app_name})

    # Copy resource folder "Resources" to WorkingDir(is $(ProjectDir) in VS).
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/Resources" res_dir)
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND xcopy /Y /Q /E
        "\"${res_dir}\""
        "\"$(ProjectDir)\""
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # TODO
else()
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${app_name}>/Resources"
        )
endif()

