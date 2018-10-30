LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cpp_tests_shared

LOCAL_MODULE_FILENAME := libcpp_tests

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := main.cpp \
../../../Classes/ActionManagerTest/ActionManagerTest.cpp \
../../../Classes/ActionsEaseTest/ActionsEaseTest.cpp \
../../../Classes/ActionsProgressTest/ActionsProgressTest.cpp \
../../../Classes/ActionsTest/ActionsTest.cpp \
../../../Classes/AllocatorTest/AllocatorTest.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/BaseTest.cpp \
../../../Classes/BillBoardTest/BillBoardTest.cpp \
../../../Classes/Box2DTest/Box2dTest.cpp \
../../../Classes/Box2DTestBed/Box2dView.cpp \
../../../Classes/Box2DTestBed/GLES-Render.cpp \
../../../Classes/Box2DTestBed/Test.cpp \
../../../Classes/Box2DTestBed/TestEntries.cpp \
../../../Classes/BugsTest/Bug-CCDrawNode.cpp \
../../../Classes/BugsTest/Bug-1159.cpp \
../../../Classes/BugsTest/Bug-1174.cpp \
../../../Classes/BugsTest/Bug-350.cpp \
../../../Classes/BugsTest/Bug-422.cpp \
../../../Classes/BugsTest/Bug-458/Bug-458.cpp \
../../../Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
../../../Classes/BugsTest/Bug-624.cpp \
../../../Classes/BugsTest/Bug-886.cpp \
../../../Classes/BugsTest/Bug-899.cpp \
../../../Classes/BugsTest/Bug-914.cpp \
../../../Classes/BugsTest/Bug-12847.cpp \
../../../Classes/BugsTest/Bug-15594.cpp \
../../../Classes/BugsTest/Bug-15776.cpp \
../../../Classes/BugsTest/Bug-Child.cpp \
../../../Classes/BugsTest/BugsTest.cpp \
../../../Classes/Camera3DTest/Camera3DTest.cpp \
../../../Classes/ChipmunkTest/ChipmunkTest.cpp \
../../../Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
../../../Classes/ClippingNodeTest/ClippingNodeTest.cpp \
../../../Classes/CocosDenshionTest/CocosDenshionTest.cpp \
../../../Classes/ConfigurationTest/ConfigurationTest.cpp \
../../../Classes/ConsoleTest/ConsoleTest.cpp \
../../../Classes/CurlTest/CurlTest.cpp \
../../../Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
../../../Classes/DataVisitorTest/DataVisitorTest.cpp \
../../../Classes/DownloaderTest/DownloaderTest.cpp \
../../../Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
../../../Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
../../../Classes/EffectsTest/EffectsTest.cpp \
../../../Classes/ExtensionsTest/AssetsManagerExTest/AssetsManagerExTest.cpp \
../../../Classes/ExtensionsTest/ExtensionsTest.cpp \
../../../Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
../../../Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp \
../../../Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp \
../../../Classes/ExtensionsTest/NetworkTest/WebSocketDelayTest.cpp \
../../../Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
../../../Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
../../../Classes/FileUtilsTest/FileUtilsTest.cpp \
../../../Classes/FontTest/FontTest.cpp \
../../../Classes/InputTest/MouseTest.cpp \
../../../Classes/IntervalTest/IntervalTest.cpp \
../../../Classes/JNITest/JNITest.cpp \
../../../Classes/LabelTest/LabelTest.cpp \
../../../Classes/LabelTest/LabelTestNew.cpp \
../../../Classes/LayerTest/LayerTest.cpp \
../../../Classes/LightTest/LightTest.cpp \
../../../Classes/MaterialSystemTest/MaterialSystemTest.cpp \
../../../Classes/MenuTest/MenuTest.cpp \
../../../Classes/MotionStreakTest/MotionStreakTest.cpp \
../../../Classes/MultiTouchTest/MultiTouchTest.cpp \
../../../Classes/NewAudioEngineTest/NewAudioEngineTest.cpp \
../../../Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp \
../../../Classes/NewRendererTest/NewRendererTest.cpp \
../../../Classes/NavMeshTest/NavMeshTest.cpp \
../../../Classes/NodeTest/NodeTest.cpp \
../../../Classes/OpenURLTest/OpenURLTest.cpp \
../../../Classes/ParallaxTest/ParallaxTest.cpp \
../../../Classes/Particle3DTest/Particle3DTest.cpp \
../../../Classes/ParticleTest/ParticleTest.cpp \
../../../Classes/PhysicsTest/PhysicsTest.cpp \
../../../Classes/Physics3DTest/Physics3DTest.cpp \
../../../Classes/ReleasePoolTest/ReleasePoolTest.cpp \
../../../Classes/RenderTextureTest/RenderTextureTest.cpp \
../../../Classes/RotateWorldTest/RotateWorldTest.cpp \
../../../Classes/SceneTest/SceneTest.cpp \
../../../Classes/SchedulerTest/SchedulerTest.cpp \
../../../Classes/ShaderTest/ShaderTest.cpp \
../../../Classes/ShaderTest/ShaderTest2.cpp \
../../../Classes/SpineTest/SpineTest.cpp \
../../../Classes/Scene3DTest/Scene3DTest.cpp \
../../../Classes/Sprite3DTest/DrawNode3D.cpp \
../../../Classes/Sprite3DTest/Sprite3DTest.cpp \
../../../Classes/SpritePolygonTest/SpritePolygonTest.cpp \
../../../Classes/SpriteTest/SpriteTest.cpp \
../../../Classes/TerrainTest/TerrainTest.cpp \
../../../Classes/TextInputTest/TextInputTest.cpp \
../../../Classes/Texture2dTest/Texture2dTest.cpp \
../../../Classes/TextureCacheTest/TextureCacheTest.cpp \
../../../Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp \
../../../Classes/TileMapTest/TileMapTest.cpp \
../../../Classes/TileMapTest/TileMapTest2.cpp \
../../../Classes/TouchesTest/Ball.cpp \
../../../Classes/TouchesTest/Paddle.cpp \
../../../Classes/TouchesTest/TouchesTest.cpp \
../../../Classes/TransitionsTest/TransitionsTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIRadioButtonTest/UIRadioButtonTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIEditBoxTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIScale9SpriteTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIScene.cpp \
../../../Classes/UITest/CocoStudioGUITest/UISceneManager.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIWebViewTest/UIWebViewTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp \
../../../Classes/UITest/CocoStudioGUITest/UITabControlTest/UITabControlTest.cpp \
../../../Classes/UITest/UITest.cpp \
../../../Classes/UnitTest/RefPtrTest.cpp \
../../../Classes/UnitTest/UnitTest.cpp \
../../../Classes/UserDefaultTest/UserDefaultTest.cpp \
../../../Classes/VisibleRect.cpp \
../../../Classes/VibrateTest/VibrateTest.cpp \
../../../Classes/VRTest/VRTest.cpp \
../../../Classes/ZwoptexTest/ZwoptexTest.cpp \
../../../Classes/SpriteFrameCacheTest/SpriteFrameCacheTest.cpp \
../../../Classes/controller.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    $(LOCAL_PATH)/../../../../..

LOCAL_STATIC_LIBRARIES := cc_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)
