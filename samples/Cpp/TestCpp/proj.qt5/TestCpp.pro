
include(../../../../cocos2dx/proj.qt5/common.pri)

TARGET = cocos2dx_TestCpp

INCLUDEPATH += ..
INCLUDEPATH += ../Classes

SOURCES += main.cpp \
    ../Classes/Box2DTest/Box2dTest.cpp \
    ../Classes/Box2DTestBed/Box2dView.cpp \
    ../Classes/Box2DTestBed/GLES-Render.cpp \
    ../Classes/Box2DTestBed/Test.cpp \
    ../Classes/Box2DTestBed/TestEntries.cpp \
    ../Classes/ChipmunkTest/ChipmunkTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioArmatureTest/ArmatureScene.cpp \
    ../Classes/ExtensionsTest/EditBoxTest/EditBoxTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/SceneController.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/ProjectileController.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/PlayerController.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/GameOverScene.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/EnemyController.cpp \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/ComponentsTestScene.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UISceneManager.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIScene.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/CocosGUIScene.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIDragPanelTest/UIDragPanelTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest/UILabelAtlasTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest/UILabelBMFontTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelTest/UILabelTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UINodeContainerTest/UINodeContainerTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIPanelTest/UIPanelTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextAreaTest/UITextAreaTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextButtonTest/UITextButtonTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp \
    ../Classes/ExtensionsTest/CocoStudioSceneTest/SceneEditorTest.cpp \
    ../Classes/ShaderTest/ShaderTest2.cpp \
    ../Classes/PhysicsTest/PhysicsTest.cpp \
    ../Classes/LabelTest/LabelTestNew.cpp
SOURCES += ../Classes/AccelerometerTest/AccelerometerTest.cpp \
	../Classes/ActionManagerTest/ActionManagerTest.cpp \
	../Classes/ActionsEaseTest/ActionsEaseTest.cpp \
	../Classes/ActionsProgressTest/ActionsProgressTest.cpp \
        ../Classes/ActionsTest/ActionsTest.cpp \
	../Classes/BugsTest/Bug-1159.cpp \
	../Classes/BugsTest/Bug-1174.cpp \
	../Classes/BugsTest/Bug-350.cpp \
	../Classes/BugsTest/Bug-422.cpp \
	../Classes/BugsTest/Bug-458/Bug-458.cpp \
	../Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
	../Classes/BugsTest/Bug-624.cpp \
	../Classes/BugsTest/Bug-886.cpp \
	../Classes/BugsTest/Bug-899.cpp \
	../Classes/BugsTest/Bug-914.cpp \
        ../Classes/BugsTest/BugsTest.cpp \
	../Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
	../Classes/ClippingNodeTest/ClippingNodeTest.cpp \
	../Classes/CocosDenshionTest/CocosDenshionTest.cpp \
	../Classes/CurlTest/CurlTest.cpp \
	../Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
	../Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
	../Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
	../Classes/EffectsTest/EffectsTest.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/AnimationsTest/AnimationsTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/TimelineCallbackTest/TimelineCallbackTestLayer.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp \
	../Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
	../Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
	../Classes/ExtensionsTest/ExtensionsTest.cpp \
	../Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.cpp \
        ../Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
    ../Classes/ExtensionsTest/Scale9SpriteTest/Scale9SpriteTest.cpp \
    ../Classes/NewEventDispatcherTest/NewEventDispatcherTest.cpp \
	../Classes/FontTest/FontTest.cpp \
	../Classes/IntervalTest/IntervalTest.cpp \
    ../Classes/KeyboardTest/KeyboardTest.cpp \
	../Classes/KeypadTest/KeypadTest.cpp \
	../Classes/LabelTest/LabelTest.cpp \
	../Classes/LayerTest/LayerTest.cpp \
	../Classes/MenuTest/MenuTest.cpp \
	../Classes/MotionStreakTest/MotionStreakTest.cpp \
	../Classes/MutiTouchTest/MutiTouchTest.cpp \
	../Classes/NodeTest/NodeTest.cpp \
	../Classes/ParallaxTest/ParallaxTest.cpp \
	../Classes/ParticleTest/ParticleTest.cpp \
	../Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp \
	../Classes/PerformanceTest/PerformanceParticleTest.cpp \
	../Classes/PerformanceTest/PerformanceSpriteTest.cpp \
	../Classes/PerformanceTest/PerformanceTest.cpp \
	../Classes/PerformanceTest/PerformanceTextureTest.cpp \
	../Classes/PerformanceTest/PerformanceTouchesTest.cpp \
        ../Classes/PerformanceTest/PerformanceAllocTest.cpp \
	../Classes/RenderTextureTest/RenderTextureTest.cpp \
	../Classes/RotateWorldTest/RotateWorldTest.cpp \
	../Classes/SceneTest/SceneTest.cpp \
	../Classes/SchedulerTest/SchedulerTest.cpp \
	../Classes/ShaderTest/ShaderTest.cpp \
	../Classes/SpriteTest/SpriteTest.cpp \
	../Classes/TextInputTest/TextInputTest.cpp \
	../Classes/Texture2dTest/Texture2dTest.cpp \
	../Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp \
	../Classes/TextureCacheTest/TextureCacheTest.cpp \
	../Classes/TileMapTest/TileMapTest.cpp \
	../Classes/TouchesTest/Ball.cpp \
	../Classes/TouchesTest/Paddle.cpp \
	../Classes/TouchesTest/TouchesTest.cpp \
	../Classes/TransitionsTest/TransitionsTest.cpp \
	../Classes/UserDefaultTest/UserDefaultTest.cpp \
	../Classes/ZwoptexTest/ZwoptexTest.cpp \
	../Classes/FileUtilsTest/FileUtilsTest.cpp \
	../Classes/SpineTest/SpineTest.cpp \
	../Classes/DataVisitorTest/DataVisitorTest.cpp \
	../Classes/ConfigurationTest/ConfigurationTest.cpp \
	../Classes/controller.cpp \
	../Classes/testBasic.cpp \
	../Classes/AppDelegate.cpp \
    ../Classes/BaseTest.cpp \
	../Classes/VisibleRect.cpp

LIBS += $${LINK_AGAINST_COCOS2DX}
LIBS += $${LINK_AGAINST_COCOSDENSHION}
LIBS += $${LINK_AGAINST_COCOSEXTENSION}

INSTALLS += target
target.path = /opt/$${TARGET}

INSTALLS += desktop
desktop.files = $${TARGET}.desktop
desktop.path = $${DESKTOP_INSTALL_DIR}

INSTALLS += resources
resources.files = icon.png ../Resources
resources.path = /opt/$${TARGET}

HEADERS += \
    ../Classes/ExtensionsTest/CocoStudioArmatureTest/ArmatureScene.h \
    ../Classes/ExtensionsTest/EditBoxTest/EditBoxTest.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/SceneController.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/ProjectileController.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/PlayerController.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/GameOverScene.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/EnemyController.h \
    ../Classes/ExtensionsTest/CocoStudioComponentsTest/ComponentsTestScene.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UISceneManager.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIScene.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/CocosGUIScene.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIButtonTest/UIButtonTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIDragPanelTest/UIDragPanelTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest/UILabelAtlasTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest/UILabelBMFontTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILabelTest/UILabelTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIListViewTest/UIListViewTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UINodeContainerTest/UINodeContainerTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIPanelTest/UIPanelTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UISliderTest/UISliderTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextAreaTest/UITextAreaTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextButtonTest/UITextButtonTest.h \
    ../Classes/ExtensionsTest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.h \
    ../Classes/ExtensionsTest/CocoStudioSceneTest/SceneEditorTest.h \
    ../Classes/ShaderTest/ShaderTest2.h \
    ../Classes/PhysicsTest/PhysicsTest.h \
    ../Classes/LabelTest/LabelTestNew.h \
    ../Classes/LabelTest/LabelTest.h

