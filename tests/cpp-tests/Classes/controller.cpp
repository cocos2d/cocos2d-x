
// C++ includes
#include <map>
#include <functional>
#include <string>
#include <chrono>
#include <thread>
// test inclues
#include "AppDelegate.h"
#include "BaseTest.h"
#include "controller.h"
#include "testResource.h"
#include "tests.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <io.h>
#include <WS2tcpip.h>
#endif
#include "cocostudio/CocoStudio.h"
#include "UITest/UITest.h"

typedef struct _Controller{
	const char *test_name;
	std::function<TestScene*()> callback;
} Controller;
Controller g_aTestNames[] = {

    //
    // TESTS MUST BE ORDERED ALPHABETICALLY
    //     violators will be prosecuted
    //
	{ "ActionManager", [](){return new ActionManagerTestScene(); } },
	{ "Actions - Basic", [](){ return new ActionsTestScene(); } },
	{ "Actions - Ease", [](){return new ActionsEaseTestScene();} },
	{ "Actions - Progress", [](){return new ProgressActionsTestScene(); } },
	{ "Audio - CocosDenshion", []() { return new CocosDenshionTestScene(); } },
	{ "Box2d - Basic", []() { return new Box2DTestScene(); } },
	{ "Box2d - TestBed", []() { return new Box2dTestBedScene(); } },
	{ "Bugs", []() { return new BugsTestScene(); } },
	{ "Chipmunk", []() { return new ChipmunkAccelTouchTestScene(); } },
	{ "Click and Move", [](){return new ClickAndMoveTestScene(); } },
	{ "Configuration", []() { return new ConfigurationTestScene(); } },
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
	{ "Console", []() { return new ConsoleTestScene(); } },

#endif
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
	{ "Curl", []() { return new CurlTestScene(); } },
#endif
	{ "Current Language", []() { return new CurrentLanguageTestScene(); } },
    { "EventDispatcher", []() { return new EventDispatcherTestScene(); } },
	{ "Effects - Advanced", []() { return new EffectAdvanceScene(); } },
	{ "Effects - Basic", [](){return new EffectTestScene();} },
	{ "Extensions", []() { return new ExtensionsTestScene(); } },
	{ "FileUtils", []() { return new FileUtilsTestScene(); } },
	{ "Fonts", []() { return new FontTestScene(); } },
	{ "Interval", [](){return new IntervalTestScene(); } },
	{ "Node: Clipping", []() { return new ClippingNodeTestScene(); } },
	{ "Node: Draw", [](){return new DrawPrimitivesTestScene();} },
    { "Node: Label - New API", [](){return new AtlasTestSceneNew(); } },
	{ "Node: Label - Old API", [](){return new AtlasTestScene(); } },
	{ "Node: Layer", [](){return new LayerTestScene();} },
	{ "Node: Menu", [](){return new MenuTestScene();} },
	{ "Node: MotionStreak", [](){return new MotionStreakTestScene();} },
	{ "Node: Node", [](){return new CocosNodeTestScene();} },
	{ "Node: Parallax", [](){return new ParallaxTestScene(); } },
	{ "Node: Particles", [](){return new ParticleTestScene(); } },
	{ "Node: Physics", []() { return new PhysicsTestScene(); } },
	{ "Node: RenderTexture", [](){return new RenderTextureScene(); } },
	{ "Node: Scene", [](){return new SceneTestScene();} },
	{ "Node: Spine", []() { return new SpineTestScene(); } },
	{ "Node: Sprite", [](){return new SpriteTestScene(); } },
    { "Node: Sprite3D", [](){  return new Sprite3DTestScene(); }},
    { "Node: Camera 3D Test", [](){  return new Camera3DTestScene(); }},
	{ "Node: TileMap", [](){return new TileMapTestScene(); } },
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
	{ "Node: FastTileMap", [](){return new TileMapTestSceneNew(); } },
#endif
	{ "Node: Text Input", [](){return new TextInputTestScene(); } },
    { "Node: UI", [](){  return new UITestScene(); }},
    { "Mouse", []() { return new MouseTestScene(); } },
	{ "MutiTouch", []() { return new MutiTouchTestScene(); } },
	{ "Performance tests", []() { return new PerformanceTestScene(); } },
    { "Renderer", []() { return new NewRendererTestScene(); } },
    { "ReleasePool", [](){ return new ReleasePoolTestScene(); } },
	{ "Rotate World", [](){return new RotateWorldTestScene(); } },
	{ "Scheduler", [](){return new SchedulerTestScene(); } },
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8
	{ "Shader - Basic", []() { return new ShaderTestScene(); } },
    { "Shader - Sprite", []() { return new ShaderTestScene2(); } },
#endif
	{ "Texture2D", [](){return new TextureTestScene(); } },
	{ "TextureCache", []() { return new TextureCacheTestScene(); } },
	{ "TexturePacker Encryption", []() { return new TextureAtlasEncryptionTestScene(); } },
	{ "Touches", [](){return new PongScene();} },
	{ "Transitions", [](){return new TransitionsTestScene();} },
    { "Unit Test", []() { return new UnitTestScene(); }},
	{ "UserDefault", []() { return new UserDefaultTestScene(); } },
	{ "Zwoptex", []() { return new ZwoptexTestScene(); } },
};

static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
static Controller *currentController = nullptr;
#define LINE_SPACE          40

static Vec2 s_tCurPos = Vec2::ZERO;

//sleep for t seconds
static void wait(int t)
{
    std::chrono::milliseconds dura( t * 1000 );
    std::this_thread::sleep_for( dura );
}

TestController::TestController()
: _beginPos(Vec2::ZERO)
,_exitThread(false)
{
    // add close menu
    auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, CC_CALLBACK_1(TestController::closeCallback, this) );
    auto menu =Menu::create(closeItem, nullptr);

    menu->setPosition( Vec2::ZERO );
    closeItem->setPosition(Vec2( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for tests
    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    _itemMenu = Menu::create();
    for (int i = 0; i < g_testCount; ++i)
    {
        auto label = Label::createWithTTF(ttfConfig, g_aTestNames[i].test_name);       
        auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestController::menuCallback, this));

        _itemMenu->addChild(menuItem, i + 10000);
        menuItem->setPosition( Vec2( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
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

void TestController::menuCallback(Ref * sender)
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

void TestController::closeCallback(Ref * sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

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
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }

    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vec2(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
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
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(Vec2::ZERO);
        return;
    }

    if (nextPos.y > ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(Vec2(0, ((g_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    _itemMenu->setPosition(nextPos);
    s_tCurPos   = nextPos;
}

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
void TestController::runAllTests(int fd)
{
    AppDelegate* app = (AppDelegate *)Application::getInstance();
    Scheduler *sched = Director::getInstance()->getScheduler();
    for (int i = 0; i < g_testCount; i++)
    {

        // create the test scene and run it
        std::string  msg("autotest: running test:");
        msg += g_aTestNames[i].test_name;
        send(fd, msg.c_str(), strlen(msg.c_str()),0);
        send(fd, "\n",1,0);

        currentController = &g_aTestNames[i];
        sched->performFunctionInCocosThread( [&](){
            auto scene = currentController->callback();
            if(scene)
            {
                scene->runThisTest();
                scene->release();
            }
        } );
        wait(1);
        BaseTest* firstTest = app->getCurrentTest();
        if(firstTest == nullptr)
        {
            continue;
        }
        std::string  t1("");
        t1 += firstTest->subtitle();
        send(fd, t1.c_str(), strlen(t1.c_str()),0);
        send(fd, "\n",1,0);
        wait(2);

        while(1)
        {
            if(_exitThread)
            {
                return;
            }
            //currentTest->nextCallback(nullptr);
            sched->performFunctionInCocosThread( [&](){
                BaseTest *t = app->getCurrentTest();
                if(t != nullptr)
                {
                    t->nextCallback(nullptr);
                }
            } );
            wait(1);
            BaseTest * curTest = app->getCurrentTest();
            if(curTest == nullptr)
            {
                break;
            }
            std::string  title("");
            title += curTest->subtitle();
            send(fd, title.c_str(), strlen(title.c_str()),0);
            send(fd, "\n",1,0);
            wait(2);

            if(t1 == title)
            {
                break;
            }
        }
    }
    std::string  msg("autotest run successfully!");
    send(fd, msg.c_str(), strlen(msg.c_str()),0);
    send(fd, "\n",1,0);
    return;
}
void TestController::addConsoleAutoTest()
{
    auto console = Director::getInstance()->getConsole();
    
    static struct Console::Command autotest = {
        "autotest", 
        "testcpp autotest command, use -h to list available tests", 
        [this](int fd, const std::string& args)
        {
            Scheduler *sched = Director::getInstance()->getScheduler();
            if(args == "help" || args == "-h")
            {
                const char msg[] = "usage: autotest ActionsTest\n\tavailable tests: ";
                send(fd, msg, sizeof(msg),0);
                send(fd, "\n",1,0);
                for(int i = 0; i < g_testCount; i++)
                {
                    send(fd, "\t",1,0);
                    send(fd, g_aTestNames[i].test_name, strlen(g_aTestNames[i].test_name)+1,0);
                    send(fd, "\n",1,0);
                }
                const char help_main[] = "\tmain, return to main menu\n";
                send(fd, help_main, sizeof(help_main),0);

                const char help_next[] = "\tnext, run next test\n";
                send(fd, help_next, sizeof(help_next),0);
                
                const char help_back[] = "\tback, run prev test\n";
                send(fd, help_back, sizeof(help_back),0);
                
                const char help_restart[] = "\trestart, restart current test\n";
                send(fd, help_restart, sizeof(help_restart),0);
                return;
            }
            if(args == "main")
            {
                
                sched->performFunctionInCocosThread( [&]()
                {
                    auto scene = Scene::create();
                    auto layer = new TestController();
                    scene->addChild(layer);
                    layer->release();
                    Director::getInstance()->replaceScene(scene);
                    cocostudio::ArmatureDataManager::destroyInstance();
                } );
                return;
            }
            const char msg_notest[] = "autotest: can't detect running test.\n";
            AppDelegate* app = (AppDelegate *)Application::getInstance();
            BaseTest* currentTest = app->getCurrentTest();
            if(args == "next")
            {
                if(currentTest != nullptr)
                {
                    //currentTest->nextCallback(nullptr);
                    sched->performFunctionInCocosThread( [&](){
                            currentTest->nextCallback(nullptr);
                        } );
                }
                else
                {
                    send(fd, msg_notest, sizeof(msg_notest),0);
                }
                return;
            }
            if(args == "back")
            {
                if(currentTest != nullptr)
                {
                    sched->performFunctionInCocosThread( [&](){
                        currentTest->backCallback(nullptr);
                    } );
                }
                else
                {
                    send(fd, msg_notest, sizeof(msg_notest),0);
                }
                return;
            }

            if(args == "restart")
            {
                if(currentTest != nullptr)
                {
                    sched->performFunctionInCocosThread( [&](){
                        currentTest->restartCallback(nullptr);
                    } );
                }
                else
                {
                    send(fd, msg_notest, sizeof(msg_notest),0);
                }
                return;
            }

            if(args == "run")
            {
                _exitThread = false;
                std::thread t = std::thread( &TestController::runAllTests, this, fd);
                t.detach();
                return;
            }

            if(args == "stop")
            {
                _exitThread = true;
                std::string  msg("autotest: autotest stopped!");
                send(fd, msg.c_str(), strlen(msg.c_str()),0);
                send(fd, "\n",1,0);
                return;
            }

            for(int i = 0; i < g_testCount; i++)
            {
                if(args == g_aTestNames[i].test_name)
                {
                    currentController = &g_aTestNames[i];
                    std::string  msg("autotest: running test:");
                    msg += args;
                    send(fd, msg.c_str(), strlen(msg.c_str()),0);
                    send(fd, "\n",1,0);

                        
                    sched->performFunctionInCocosThread( [&](){
                        auto scene = currentController->callback();
                        if(scene)
                        {
                            scene->runThisTest();
                            scene->release();
                        }
                    } );
                    return;
                }
            }

            //no match found,print warning message
            std::string  msg("autotest: could not find test:");
            msg += args;
            send(fd, msg.c_str(), strlen(msg.c_str()),0);
            send(fd, "\n",1,0);
        }
        
    };
    console->addCommand(autotest);
}

void TestController::startAutoRun()
{
   
    std::thread t = std::thread( &TestController::autorun, this);
    t.detach();
}

ssize_t TestController::readline(int fd, char* ptr, size_t maxlen)
{
    size_t n, rc;
    char c;

    for( n = 0; n < maxlen - 1; n++ ) {
        if( (rc = recv(fd, &c, 1, 0)) ==1 ) {
            *ptr++ = c;
            if(c == '\n') {
                break;
            }
        } else if( rc == 0 ) {
            return 0;
        } else if( errno == EINTR ) {
            continue;
        } else {
            return -1;
        }
    }

    *ptr = 0;
    return n;
}

void TestController::autorun()
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* stream socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    s = getaddrinfo("localhost", "5678", &hints, &result);
    if (s != 0) 
    {
       CCLOG("autotest: getaddrinfo error");
        return;
    }

    /* getaddrinfo() returns a list of address structures.
      Try each address until we successfully connect(2).
      If socket(2) (or connect(2)) fails, we (close the socket
      and) try the next address. */

    for (rp = result; rp != nullptr; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                    rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        closesocket(sfd);
#else
        close(sfd);
#endif
    }

    if (rp == nullptr) {               /* No address succeeded */
        CCLOG("autotest: could not connect!");
        return;
    }

    freeaddrinfo(result);           /* No longer needed */
    
    std::string tmp = "autotest run\n";

    char cmd[512];

    strcpy(cmd, tmp.c_str());
    wait(3);
    send(sfd,cmd,strlen(cmd),0);
    while(true)
    {
        char resp[512];
        readline(sfd, resp, 512);
        if(strcmp(resp, "autotest run successfully!\n") == 0)
        {
            break;
        }
        wait(3);
    }
    
    tmp = "director end\n";
    strcpy(cmd, tmp.c_str());
    send(sfd,cmd,strlen(cmd),0);
    wait(1);
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        closesocket(sfd);
        WSACleanup();
#else
        close(sfd);
#endif
    return;
}

#endif

