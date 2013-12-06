
include(game.pri)

OBJECTS_DIR = $$shadowed($$PWD)/obj/$${TARGET}
MOC_DIR = $$shadowed($$PWD)/moc/$${TARGET}
RCC_DIR = $$shadowed($PWD)/rcc/$${TARGET}
UI_DIR = $$shadowed($$PWD)/ui/$${TARGET}

CC_GAME_ROOT = $${PWD}/../../samples/Cpp/TestCpp
TARGET = $$cc_get_target_path($${CC_GAME_ROOT}/$${TARGET})

INCLUDEPATH += $${CC_GAME_ROOT}/Classes

TESTCPP_FOLDERS = \
    ActionManagerTest \
    ActionsEaseTest \
    ActionsProgressTest \
    ActionsTest \
    Box2DTest \
    Box2DTestBed \
    BugsTest \
    ChipmunkTest \
    ClickAndMoveTest \
    ClippingNodeTest \
    CocosDenshionTest \
    ConfigurationTest \
    CurlTest \
    CurrentLanguageTest \
    DataVisitorTest \
    DrawPrimitivesTest \
    EffectsAdvancedTest \
    EffectsTest \
    ExtensionsTest \
    FileUtilsTest \
    FontTest \
    InputTest \
    IntervalTest \
    KeyboardTest \
    KeypadTest \
    LabelTest \
    LayerTest \
    MenuTest \
    MotionStreakTest \
    MutiTouchTest \
    NewEventDispatcherTest \
    NodeTest \
    ParallaxTest \
    ParticleTest \
    PerformanceTest \
    PhysicsTest \
    RenderTextureTest \
    RotateWorldTest \
    SceneTest \
    SchedulerTest \
    ShaderTest \
    SpineTest \
    SpriteTest \
    TextInputTest \
    Texture2dTest \
    TextureCacheTest \
    TexturePackerEncryptionTest \
    TileMapTest \
    TouchesTest \
    TransitionsTest \
    UserDefaultTest \
    ZwoptexTest \
    AccelerometerTest \
    ExtensionsTest/NotificationCenterTest \
    ExtensionsTest/Scale9SpriteTest \
    ExtensionsTest/TableViewTest \
    ExtensionsTest/CocosBuilderTest \
    ExtensionsTest/CocoStudioArmatureTest \
    ExtensionsTest/CocoStudioComponentsTest \
    ExtensionsTest/CocoStudioGUITest \
    ExtensionsTest/CocoStudioSceneTest \
    ExtensionsTest/ControlExtensionTest \
    ExtensionsTest/EditBoxTest \
    Box2DTestBed/Tests \
    BugsTest/Bug-458 \
    ExtensionsTest/ControlExtensionTest/CCControlSliderTest \
    ExtensionsTest/ControlExtensionTest/CCControlStepperTest \
    ExtensionsTest/ControlExtensionTest/CCControlSwitchTest \
    ExtensionsTest/ControlExtensionTest/CCControlButtonTest \
    ExtensionsTest/ControlExtensionTest/CCControlColourPicker \
    ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest \
    ExtensionsTest/CocoStudioGUITest/UIScrollViewTest \
    ExtensionsTest/CocoStudioGUITest/UISliderTest \
    ExtensionsTest/CocoStudioGUITest/UITextAreaTest \
    ExtensionsTest/CocoStudioGUITest/UITextButtonTest \
    ExtensionsTest/CocoStudioGUITest/UITextFieldTest \
    ExtensionsTest/CocoStudioGUITest/UIButtonTest \
    ExtensionsTest/CocoStudioGUITest/UICheckBoxTest \
    ExtensionsTest/CocoStudioGUITest/UIDragPanelTest \
    ExtensionsTest/CocoStudioGUITest/UIImageViewTest \
    ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest \
    ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest \
    ExtensionsTest/CocoStudioGUITest/UILabelTest \
    ExtensionsTest/CocoStudioGUITest/UIListViewTest \
    ExtensionsTest/CocoStudioGUITest/UILoadingBarTest \
    ExtensionsTest/CocoStudioGUITest/UINodeContainerTest \
    ExtensionsTest/CocoStudioGUITest/UIPageViewTest \
    ExtensionsTest/CocoStudioGUITest/UIPanelTest \
    ExtensionsTest/CocosBuilderTest/HelloCocosBuilder \
    ExtensionsTest/CocosBuilderTest/LabelTest \
    ExtensionsTest/CocosBuilderTest/MenuTest \
    ExtensionsTest/CocosBuilderTest/ParticleSystemTest \
    ExtensionsTest/CocosBuilderTest/ScrollViewTest \
    ExtensionsTest/CocosBuilderTest/SpriteTest \
    ExtensionsTest/CocosBuilderTest/TestHeader \
    ExtensionsTest/CocosBuilderTest/TimelineCallbackTest \
    ExtensionsTest/CocosBuilderTest/AnimationsTest \
    ExtensionsTest/CocosBuilderTest/ButtonTest

HEADERS += $$files($${CC_GAME_ROOT}/Classes/*.h)
SOURCES += $$files($${CC_GAME_ROOT}/Classes/*.cpp)

for (FOLDER, TESTCPP_FOLDERS) {
    HEADERS += $$files($${CC_GAME_ROOT}/Classes/$${FOLDER}/*.h)
    SOURCES += $$files($${CC_GAME_ROOT}/Classes/$${FOLDER}/*.cpp)
}

HEADERS += $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/HttpClientTest.h
SOURCES += $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp

!*linux-* {
    HEADERS += \
        $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/SocketIOTest.h \
        $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/WebSocketTest.h
    SOURCES += \
        $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/SocketIOTest.cpp \
        $${CC_GAME_ROOT}/Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp
}

cocos2d_qt_api {
    SOURCES += $${CC_GAME_ROOT}/proj.qt5/main.cpp
}

cocos2d_native_api {
    SOURCES += $${CC_GAME_ROOT}/proj.$${CC_OS_TYPE}/main.cpp
}
