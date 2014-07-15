LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_cpp_tests_common

LOCAL_MODULE_FILENAME := libcpp_tests_common

LOCAL_SRC_FILES := \
Classes/AppDelegate.cpp \
Classes/BaseTest.cpp \
Classes/controller.cpp \
Classes/testBasic.cpp \
Classes/VisibleRect.cpp \
Classes/ActionManagerTest/ActionManagerTest.cpp \
Classes/ActionsEaseTest/ActionsEaseTest.cpp \
Classes/ActionsProgressTest/ActionsProgressTest.cpp \
Classes/ActionsTest/ActionsTest.cpp \
Classes/Box2DTest/Box2dTest.cpp \
Classes/Box2DTestBed/Box2dView.cpp \
Classes/Box2DTestBed/GLES-Render.cpp \
Classes/Box2DTestBed/Test.cpp \
Classes/Box2DTestBed/TestEntries.cpp \
Classes/BugsTest/Bug-1159.cpp \
Classes/BugsTest/Bug-1174.cpp \
Classes/BugsTest/Bug-350.cpp \
Classes/BugsTest/Bug-422.cpp \
Classes/BugsTest/Bug-624.cpp \
Classes/BugsTest/Bug-886.cpp \
Classes/BugsTest/Bug-899.cpp \
Classes/BugsTest/Bug-914.cpp \
Classes/BugsTest/BugsTest.cpp \
Classes/BugsTest/Bug-Child.cpp \
Classes/BugsTest/Bug-458/Bug-458.cpp \
Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
Classes/ChipmunkTest/ChipmunkTest.cpp \
Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
Classes/ClippingNodeTest/ClippingNodeTest.cpp \
Classes/CocosDenshionTest/CocosDenshionTest.cpp \
Classes/ConfigurationTest/ConfigurationTest.cpp \
Classes/ConsoleTest/ConsoleTest.cpp \
Classes/CurlTest/CurlTest.cpp \
Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
Classes/DataVisitorTest/DataVisitorTest.cpp \
Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
Classes/EffectsTest/EffectsTest.cpp \
Classes/ExtensionsTest/ExtensionsTest.cpp \
Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.cpp \
Classes/ExtensionsTest/CocosBuilderTest/AnimationsTest/AnimationsTestLayer.cpp \
Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.cpp \
Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.cpp \
Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.cpp \
Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.cpp \
Classes/ExtensionsTest/CocosBuilderTest/TimelineCallbackTest/TimelineCallbackTestLayer.cpp \
Classes/ExtensionsTest/CocoStudioArmatureTest/ArmatureScene.cpp \
Classes/ExtensionsTest/CocoStudioActionTimelineTest/ActionTimelineTestScene.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/ComponentsTestScene.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/EnemyController.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/GameOverScene.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/PlayerController.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/ProjectileController.cpp \
Classes/ExtensionsTest/CocoStudioComponentsTest/SceneController.cpp \
Classes/UITest/CocoStudioGUITest/CocoStudioGUITest.cpp \
Classes/UITest/CocoStudioGUITest/CocosGUIScene.cpp \
Classes/UITest/CocoStudioGUITest/CocostudioParserTest/CocostudioParserJsonTest.cpp \
Classes/UITest/CocoStudioGUITest/CocostudioParserTest.cpp \
Classes/UITest/CocoStudioGUITest/GUIEditorTest.cpp \
Classes/UITest/CocoStudioGUITest/CustomGUIScene.cpp \
Classes/UITest/CocoStudioGUITest/UIScene.cpp \
Classes/UITest/CocoStudioGUITest/UISceneManager.cpp \
Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp \
Classes/UITest/CocoStudioGUITest/UIFocusTest/UIFocusTest.cpp \
Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp \
Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp \
Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp \
Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp \
Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp \
Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp \
Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp \
Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp \
Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest.cpp \
Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest.cpp \
Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest.cpp \
Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp \
Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp \
Classes/UITest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp \
Classes/UITest/CocoStudioGUITest/UIScene_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UISceneManager_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIButtonTest/UIButtonTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UILayoutTest/UILayoutTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIListViewTest/UIListViewTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UISliderTest/UISliderTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UITextTest/UITextTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UITextAtlasTest/UITextAtlasTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UITextBMFontTest/UITextBMFontTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest_Editor.cpp \
Classes/UITest/CocoStudioGUITest/UIVideoPlayerTest/UIVideoPlayerTest.cpp \
Classes/UITest/CocoStudioGUITest/CustomWidget/CustomImageView.cpp \
Classes/UITest/CocoStudioGUITest/CustomWidget/CustomImageViewReader.cpp \
Classes/UITest/CocoStudioGUITest/CustomWidget/CustomParticleWidget.cpp \
Classes/UITest/CocoStudioGUITest/CustomWidget/CustomParticleWidgetReader.cpp \
Classes/UITest/CocoStudioGUITest/CustomWidget/CustomReader.cpp \
Classes/UITest/CocoStudioGUITest/CustomTest/CustomImageTest/CustomImageTest.cpp \
Classes/UITest/CocoStudioGUITest/CustomTest/CustomParticleWidgetTest/CustomParticleWidgetTest.cpp \
Classes/ExtensionsTest/CocoStudioSceneTest/SceneEditorTest.cpp \
Classes/ExtensionsTest/CocoStudioSceneTest/TriggerCode/acts.cpp \
Classes/ExtensionsTest/CocoStudioSceneTest/TriggerCode/cons.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp \
Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp \
Classes/ExtensionsTest/EditBoxTest/EditBoxTest.cpp \
Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp \
Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp \
Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.cpp \
Classes/ExtensionsTest/Scale9SpriteTest/Scale9SpriteTest.cpp \
Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
Classes/FileUtilsTest/FileUtilsTest.cpp \
Classes/FontTest/FontTest.cpp \
Classes/InputTest/MouseTest.cpp \
Classes/IntervalTest/IntervalTest.cpp \
Classes/LabelTest/LabelTest.cpp \
Classes/LabelTest/LabelTestNew.cpp \
Classes/LayerTest/LayerTest.cpp \
Classes/MenuTest/MenuTest.cpp \
Classes/MotionStreakTest/MotionStreakTest.cpp \
Classes/MutiTouchTest/MutiTouchTest.cpp \
Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp \
Classes/NewRendererTest/NewRendererTest.cpp \
Classes/NodeTest/NodeTest.cpp \
Classes/ParallaxTest/ParallaxTest.cpp \
Classes/ParticleTest/ParticleTest.cpp \
Classes/PerformanceTest/PerformanceAllocTest.cpp \
Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp \
Classes/PerformanceTest/PerformanceParticleTest.cpp \
Classes/PerformanceTest/PerformanceSpriteTest.cpp \
Classes/PerformanceTest/PerformanceTest.cpp \
Classes/PerformanceTest/PerformanceTextureTest.cpp \
Classes/PerformanceTest/PerformanceTouchesTest.cpp \
Classes/PerformanceTest/PerformanceLabelTest.cpp \
Classes/PerformanceTest/PerformanceRendererTest.cpp \
Classes/PerformanceTest/PerformanceContainerTest.cpp \
Classes/PerformanceTest/PerformanceEventDispatcherTest.cpp \
Classes/PerformanceTest/PerformanceScenarioTest.cpp \
Classes/PerformanceTest/PerformanceCallbackTest.cpp \
Classes/PhysicsTest/PhysicsTest.cpp \
Classes/ReleasePoolTest/ReleasePoolTest.cpp \
Classes/RenderTextureTest/RenderTextureTest.cpp \
Classes/RotateWorldTest/RotateWorldTest.cpp \
Classes/SceneTest/SceneTest.cpp \
Classes/SchedulerTest/SchedulerTest.cpp \
Classes/ShaderTest/ShaderTest.cpp \
Classes/ShaderTest/ShaderTest2.cpp \
Classes/SpineTest/SpineTest.cpp \
Classes/SpriteTest/SpriteTest.cpp \
Classes/Sprite3DTest/Sprite3DTest.cpp \
Classes/TextInputTest/TextInputTest.cpp \
Classes/Texture2dTest/Texture2dTest.cpp \
Classes/TextureCacheTest/TextureCacheTest.cpp \
Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp \
Classes/TileMapTest/TileMapTest.cpp \
Classes/TileMapTest/TileMapTest2.cpp \
Classes/TouchesTest/Ball.cpp \
Classes/TouchesTest/Paddle.cpp \
Classes/TouchesTest/TouchesTest.cpp \
Classes/TransitionsTest/TransitionsTest.cpp \
Classes/UnitTest/RefPtrTest.cpp \
Classes/UnitTest/UnitTest.cpp \
Classes/UITest/UITest.cpp \
Classes/UserDefaultTest/UserDefaultTest.cpp \
Classes/ZwoptexTest/ZwoptexTest.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Classes
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,.)
