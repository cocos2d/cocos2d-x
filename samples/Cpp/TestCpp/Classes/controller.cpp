
// C++ includes
#include <map>
#include <functional>
#include <string>

// test inclues
#include "controller.h"
#include "testResource.h"
#include "tests.h"


struct {
	const char *test_name;
	std::function<TestScene*()> callback;
} g_aTestNames[] = {

    //
    // TESTS MUST BE ORDERED ALPHABETICALLY
    //     violators will be prosecuted
    //
    { "AUnitTest", []() { return new UnitTestScene(); }},
    { "ANewRenderTest", []() { return new NewRendererTestScene(); } },
	{ "Accelerometer", []() { return new AccelerometerTestScene(); } },
	{ "ActionManagerTest", [](){return new ActionManagerTestScene(); } },
	{ "ActionsEaseTest", [](){return new ActionsEaseTestScene();} },
	{ "ActionsProgressTest", [](){return new ProgressActionsTestScene(); } },
	{ "ActionsTest", [](){ return new ActionsTestScene(); } },
	{ "Box2dTest", []() { return new Box2DTestScene(); } },
	{ "Box2dTestBed", []() { return new Box2dTestBedScene(); } },
	{ "BugsTest", []() { return new BugsTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
	{ "ChipmunkTest", []() { return new ChipmunkAccelTouchTestScene(); } },
#endif
	{ "ClickAndMoveTest", [](){return new ClickAndMoveTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
	{ "ClippingNodeTest", []() { return new ClippingNodeTestScene(); } },
#endif
	{ "CocosDenshionTest", []() { return new CocosDenshionTestScene(); } },
	{ "ConfigurationTest", []() { return new ConfigurationTestScene(); } },
	{ "ConsoleTest", []() { return new ConsoleTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_NACL)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
	{ "CurlTest", []() { return new CurlTestScene(); } },
#endif
#endif
#endif
#endif
	{ "CurrentLanguageTest", []() { return new CurrentLanguageTestScene(); } },
	{ "DrawPrimitivesTest", [](){return new DrawPrimitivesTestScene();} },
    { "EventDispatcherTest(NEW)", []() { return new EventDispatcherTestScene(); } },
	{ "EffectAdvancedTest", []() { return new EffectAdvanceScene(); } },
	{ "EffectsTest", [](){return new EffectTestScene();} },
	{ "ExtensionsTest", []() { return new ExtensionsTestScene(); } },
	{ "FileUtilsTest", []() { return new FileUtilsTestScene(); } },
	{ "FontTest", []() { return new FontTestScene(); } },
	{ "IntervalTest", [](){return new IntervalTestScene(); } },
	{ "KeyboardTest", []() { return new KeyboardTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
	{ "KeypadTest", []() { return new KeypadTestScene(); } },
#endif
	{ "LabelTest", [](){return new AtlasTestScene(); } },
    { "LabelTestNew", [](){return new AtlasTestSceneNew(); } },
	{ "LayerTest", [](){return new LayerTestScene();} },
	{ "MenuTest", [](){return new MenuTestScene();} },
	{ "MotionStreakTest", [](){return new MotionStreakTestScene();} },
    { "MouseTest", []() { return new MouseTestScene(); } },
	{ "MutiTouchTest", []() { return new MutiTouchTestScene(); } },
	{ "NodeTest", [](){return new CocosNodeTestScene();} },
	{ "ParallaxTest", [](){return new ParallaxTestScene(); } },
	{ "ParticleTest", [](){return new ParticleTestScene(); } },
	{ "PerformanceTest", []() { return new PerformanceTestScene(); } },
	{ "PhysicsTest", []() { return new PhysicsTestScene(); } },
    { "ReleasePoolTest", [](){ return new ReleasePoolTestScene(); } },
	{ "RenderTextureTest", [](){return new RenderTextureScene(); } },
	{ "RotateWorldTest", [](){return new RotateWorldTestScene(); } },
	{ "SceneTest", [](){return new SceneTestScene();} },
	{ "SchedulerTest", [](){return new SchedulerTestScene(); } },
	{ "ShaderTest", []() { return new ShaderTestScene(); } },
    { "ShaderTestSprite", []() { return new ShaderTestScene2(); } },
	{ "SpineTest", []() { return new SpineTestScene(); } },
	{ "SpriteTest", [](){return new SpriteTestScene(); } },
	{ "TextInputTest", [](){return new TextInputTestScene(); } },
	{ "Texture2DTest", [](){return new TextureTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
	{ "TextureCacheTest", []() { return new TextureCacheTestScene(); } },
#endif
	{ "TexturePackerEncryption", []() { return new TextureAtlasEncryptionTestScene(); } },
	{ "TileMapTest", [](){return new TileMapTestScene(); } },
	{ "TouchesTest", [](){return new PongScene();} },
	{ "TransitionsTest", [](){return new TransitionsTestScene();} },
	{ "UserDefaultTest", []() { return new UserDefaultTestScene(); } },
	{ "ZwoptexTest", []() { return new ZwoptexTestScene(); } },
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);

#define LINE_SPACE          40

static Point s_tCurPos = Point::ZERO;

TestController::TestController()
: _beginPos(Point::ZERO)
{
    // add close menu
    auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, CC_CALLBACK_1(TestController::closeCallback, this) );
    auto menu =Menu::create(closeItem, NULL);

    menu->setPosition( Point::ZERO );
    closeItem->setPosition(Point( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for tests
    _itemMenu = Menu::create();
    for (int i = 0; i < g_testCount; ++i)
    {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//         auto label = LabelBMFont::create(g_aTestNames[i].c_str(),  "fonts/arial16.fnt");
// #else
        auto label = LabelTTF::create( g_aTestNames[i].test_name, "Arial", 24);
// #endif        
        auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestController::menuCallback, this));

        _itemMenu->addChild(menuItem, i + 10000);
        menuItem->setPosition( Point( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
    }

    _itemMenu->setContentSize(Size(VisibleRect::getVisibleRect().size.width, (g_testCount + 1) * (LINE_SPACE)));
    _itemMenu->setPosition(s_tCurPos);
    addChild(_itemMenu);

    addChild(menu, 1);

    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TestController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TestController::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseScroll = CC_CALLBACK_1(TestController::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

TestController::~TestController()
{
}

void TestController::menuCallback(Object * sender)
{
	Director::getInstance()->purgeCachedData();

    // get the userdata, it's the index of the menu item clicked
    auto menuItem = static_cast<MenuItem *>(sender);
    int idx = menuItem->getLocalZOrder() - 10000;

    // create the test scene and run it
    auto scene = g_aTestNames[idx].callback();

    if (scene)
    {
        scene->runThisTest();
        scene->release();
    }
}

void TestController::closeCallback(Object * sender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool TestController::onTouchBegan(Touch* touch, Event  *event)
{
    _beginPos = touch->getLocation();
    return true;
}

void TestController::onTouchMoved(Touch* touch, Event  *event)
{
    auto touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;

    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Point(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Point::ZERO);
        return;
    }

    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Point(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

void TestController::onMouseScroll(Event *event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    float nMoveY = mouseEvent->getScrollY() * 6;

    auto curPos  = _itemMenu->getPosition();
    auto nextPos = Point(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Point::ZERO);
        return;
    }

    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Point(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    _itemMenu->setPosition(nextPos);
    s_tCurPos   = nextPos;
}
