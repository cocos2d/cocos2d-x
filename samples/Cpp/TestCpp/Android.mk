LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_testcpp_common

LOCAL_MODULE_FILENAME := libtestcppcommon

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/Classes/AppDelegate.cpp \
$(LOCAL_PATH)/Classes/BaseTest.cpp \
$(LOCAL_PATH)/Classes/controller.cpp \
$(LOCAL_PATH)/Classes/testBasic.cpp \
$(LOCAL_PATH)/Classes/VisibleRect.cpp \
$(LOCAL_PATH)/Classes/AccelerometerTest/AccelerometerTest.cpp \
$(LOCAL_PATH)/Classes/ActionManagerTest/ActionManagerTest.cpp \
$(LOCAL_PATH)/Classes/ActionsEaseTest/ActionsEaseTest.cpp \
$(LOCAL_PATH)/Classes/ActionsProgressTest/ActionsProgressTest.cpp \
$(LOCAL_PATH)/Classes/ActionsTest/ActionsTest.cpp \
$(LOCAL_PATH)/Classes/Box2DTest/Box2dTest.cpp \
$(LOCAL_PATH)/Classes/Box2DTestBed/Box2dView.cpp \
$(LOCAL_PATH)/Classes/Box2DTestBed/GLES-Render.cpp \
$(LOCAL_PATH)/Classes/Box2DTestBed/Test.cpp \
$(LOCAL_PATH)/Classes/Box2DTestBed/TestEntries.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-1159.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-1174.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-350.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-422.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-624.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-886.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-899.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-914.cpp \
$(LOCAL_PATH)/Classes/BugsTest/BugsTest.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-458/Bug-458.cpp \
$(LOCAL_PATH)/Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
$(LOCAL_PATH)/Classes/ChipmunkTest/ChipmunkTest.cpp \
$(LOCAL_PATH)/Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
$(LOCAL_PATH)/Classes/ClippingNodeTest/ClippingNodeTest.cpp \
$(LOCAL_PATH)/Classes/CocosDenshionTest/CocosDenshionTest.cpp \
$(LOCAL_PATH)/Classes/ConfigurationTest/ConfigurationTest.cpp \
$(LOCAL_PATH)/Classes/CurlTest/CurlTest.cpp \
$(LOCAL_PATH)/Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
$(LOCAL_PATH)/Classes/DataVisitorTest/DataVisitorTest.cpp \
$(LOCAL_PATH)/Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
$(LOCAL_PATH)/Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
$(LOCAL_PATH)/Classes/EffectsTest/EffectsTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ExtensionsTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/AnimationsTest/AnimationsTestLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocosBuilderTest/TimelineCallbackTest/TimelineCallbackTestLayer.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioArmatureTest/ArmatureScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/ComponentsTestScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/EnemyController.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/GameOverScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/PlayerController.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/ProjectileController.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioComponentsTest/SceneController.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/CocosGUIScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UISceneManager.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIDragPanelTest/UIDragPanelTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest/UILabelAtlasTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest/UILabelBMFontTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UILabelTest/UILabelTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UINodeContainerTest/UINodeContainerTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIPanelTest/UIPanelTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UITextAreaTest/UITextAreaTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UITextButtonTest/UITextButtonTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/CocoStudioSceneTest/SceneEditorTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/EditBoxTest/EditBoxTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/Scale9SpriteTest/Scale9SpriteTest.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
$(LOCAL_PATH)/Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
$(LOCAL_PATH)/Classes/FileUtilsTest/FileUtilsTest.cpp \
$(LOCAL_PATH)/Classes/FontTest/FontTest.cpp \
$(LOCAL_PATH)/Classes/IntervalTest/IntervalTest.cpp \
$(LOCAL_PATH)/Classes/KeyboardTest/KeyboardTest.cpp \
$(LOCAL_PATH)/Classes/KeypadTest/KeypadTest.cpp \
$(LOCAL_PATH)/Classes/LabelTest/LabelTest.cpp \
$(LOCAL_PATH)/Classes/LabelTest/LabelTestNew.cpp \
$(LOCAL_PATH)/Classes/LayerTest/LayerTest.cpp \
$(LOCAL_PATH)/Classes/MenuTest/MenuTest.cpp \
$(LOCAL_PATH)/Classes/MotionStreakTest/MotionStreakTest.cpp \
$(LOCAL_PATH)/Classes/MutiTouchTest/MutiTouchTest.cpp \
$(LOCAL_PATH)/Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp \
$(LOCAL_PATH)/Classes/NodeTest/NodeTest.cpp \
$(LOCAL_PATH)/Classes/ParallaxTest/ParallaxTest.cpp \
$(LOCAL_PATH)/Classes/ParticleTest/ParticleTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceAllocTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceParticleTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceSpriteTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceTextureTest.cpp \
$(LOCAL_PATH)/Classes/PerformanceTest/PerformanceTouchesTest.cpp \
$(LOCAL_PATH)/Classes/PhysicsTest/PhysicsTest.cpp \
$(LOCAL_PATH)/Classes/RenderTextureTest/RenderTextureTest.cpp \
$(LOCAL_PATH)/Classes/RotateWorldTest/RotateWorldTest.cpp \
$(LOCAL_PATH)/Classes/SceneTest/SceneTest.cpp \
$(LOCAL_PATH)/Classes/SchedulerTest/SchedulerTest.cpp \
$(LOCAL_PATH)/Classes/ShaderTest/ShaderTest.cpp \
$(LOCAL_PATH)/Classes/ShaderTest/ShaderTest2.cpp \
$(LOCAL_PATH)/Classes/SpineTest/SpineTest.cpp \
$(LOCAL_PATH)/Classes/SpriteTest/SpriteTest.cpp \
$(LOCAL_PATH)/Classes/TextInputTest/TextInputTest.cpp \
$(LOCAL_PATH)/Classes/Texture2dTest/Texture2dTest.cpp \
$(LOCAL_PATH)/Classes/TextureCacheTest/TextureCacheTest.cpp \
$(LOCAL_PATH)/Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp \
$(LOCAL_PATH)/Classes/TileMapTest/TileMapTest.cpp \
$(LOCAL_PATH)/Classes/TouchesTest/Ball.cpp \
$(LOCAL_PATH)/Classes/TouchesTest/Paddle.cpp \
$(LOCAL_PATH)/Classes/TouchesTest/TouchesTest.cpp \
$(LOCAL_PATH)/Classes/TransitionsTest/TransitionsTest.cpp \
$(LOCAL_PATH)/Classes/UserDefaultTest/UserDefaultTest.cpp \
$(LOCAL_PATH)/Classes/ZwoptexTest/ZwoptexTest.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += gui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,chipmunk)
$(call import-module,2d)
$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,gui)
$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,curl/prebuilt/android)
