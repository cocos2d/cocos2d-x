#include "controller.h"
#include <functional>
#include <chrono>
#include "BaseTest.h"
#include "tests.h"

USING_NS_CC;

#define TEST_TIME_OUT 25
#define CREATE_TIME_OUT 25
#define LOG_INDENTATION "  "
#define LOG_TAG "[TestController]"

class RootTests : public TestList
{
public:
    RootTests()
    {
        addTest("ActionManager", [](){return new (std::nothrow) ActionManagerTests(); });
        addTest("Actions - Basic", [](){ return new (std::nothrow) ActionsTests(); });
        addTest("Actions - Ease", [](){return new (std::nothrow) ActionsEaseTests(); });
        addTest("Actions - Progress", [](){return new (std::nothrow) ActionsProgressTests(); });
        addTest("Allocator - Basic", [](){return new (std::nothrow) AllocatorTests(); });
        addTest("Audio - CocosDenshion", []() { return new (std::nothrow) CocosDenshionTests(); });
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        addTest("Audio - NewAudioEngine", []() { return new (std::nothrow) AudioEngineTests(); });
#endif
#if CC_ENABLE_BOX2D_INTEGRATION
        addTest("Box2d - Basic", []() { return new (std::nothrow) Box2DTests(); });
        addTest("Box2d - TestBed", []() { return new (std::nothrow) Box2dTestBedSuite(); });
#endif
        addTest("Bugs", []() { return new BugsTests(); });
        addTest("Chipmunk", []() { return new ChipmunkTests(); });
        addTest("Click and Move", [](){return new ClickAndMoveTest(); });
        addTest("Configuration", []() { return new ConfigurationTests(); });
        addTest("Console", []() { return new ConsoleTests(); });
        addTest("Curl", []() { return new CurlTests(); });
        addTest("Current Language", []() { return new CurrentLanguageTests(); });
        addTest("CocosStudio3D Test", []() { return new CocosStudio3DTests(); });
        addTest("EventDispatcher", []() { return new EventDispatcherTests(); });
        addTest("Effects - Advanced", []() { return new EffectAdvanceTests(); });
        addTest("Effects - Basic", [](){return new EffectTests(); });
        addTest("Extensions", []() { return new ExtensionsTests(); });
        addTest("FileUtils", []() { return new FileUtilsTests(); });
        addTest("Fonts", []() { return new FontTests(); });
        addTest("Interval", [](){return new IntervalTests(); });
        addTest("Node: BillBoard Test", [](){  return new BillBoardTests(); });
        addTest("Node: Camera 3D Test", [](){  return new Camera3DTests(); });
        addTest("Node: Clipping", []() { return new ClippingNodeTests(); });
        addTest("Node: Draw", [](){return new DrawPrimitivesTests(); });
        addTest("Node: Label - New API", [](){return new NewLabelTests(); });
        addTest("Node: Label - Old API", [](){return new LabelTests(); });
        addTest("Node: Layer", [](){return new LayerTests(); });
        addTest("Node: Light", [](){return new LightTests(); });
        addTest("Node: Menu", [](){return new MenuTests(); });
        addTest("Node: MotionStreak", [](){return new MotionStreakTests(); });
        addTest("Node: Node", [](){return new CocosNodeTests(); });
        addTest("Node: Parallax", [](){return new ParallaxTests(); });
        addTest("Node: Particles", [](){return new ParticleTests(); });
        addTest("Node: Particle3D (PU)", [](){return new Particle3DTests(); });
        addTest("Node: Physics", []() { return new PhysicsTests(); });
        addTest("Node: RenderTexture", [](){return new RenderTextureTests(); });
        addTest("Node: Scene", [](){return new SceneTests(); });
        addTest("Node: Spine", [](){return new SpineTests(); });
        addTest("Node: Sprite", [](){return new SpriteTests(); });
        addTest("Node: Sprite3D", [](){  return new Sprite3DTests(); });
        addTest("Node: Terrain", [](){  return new TerrainTests(); });
        addTest("Node: TileMap", [](){return new TileMapTests(); });
        addTest("Node: FastTileMap", [](){return new FastTileMapTests(); });
        addTest("Node: Text Input", [](){return new TextInputTests(); });
        addTest("Node: UI", [](){  return new UITests(); });
        addTest("Mouse", []() { return new MouseTests(); });
        addTest("MultiTouch", []() { return new MutiTouchTests(); });
        //addTest("Performance tests", []() { return new PerformanceTests(); });
        addTest("Renderer", []() { return new NewRendererTests(); });
        addTest("ReleasePool", [](){ return new ReleasePoolTests(); });
        addTest("Rotate World", [](){return new RotateWorldTests(); });
        addTest("Scheduler", [](){return new SchedulerTests(); });//!!!!!!
        addTest("Shader - Basic", []() { return new ShaderTests(); });
        addTest("Shader - Sprite", []() { return new Shader2Tests(); });
        addTest("Texture2D", [](){return new Texture2DTests(); });
        addTest("TextureCache", []() { return new TextureCacheTests(); });
        addTest("TexturePacker Encryption", []() { return new TextureAtlasEncryptionTests(); });
        addTest("Touches", [](){return new TouchesTests(); });
        addTest("Transitions", [](){return new TransitionsTests(); });
        addTest("Unit Test", []() { return new UnitTests(); });
        addTest("URL Open Test", []() { return new OpenURLTests(); });
        addTest("UserDefault", []() { return new UserDefaultTests(); });
        addTest("Zwoptex", []() { return new ZwoptexTests(); });
    }
};

TestController::TestController()
: _stopAutoTest(true)
, _isRunInBackground(false)
, _testSuite(nullptr)
{
    _rootTestList = new (std::nothrow) RootTests;  
    _rootTestList->runThisTest();
    _director = Director::getInstance();

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(TestController::blockTouchBegan, this);
    _touchListener->setSwallowTouches(true);

    _director->getEventDispatcher()->addEventListenerWithFixedPriority(_touchListener, -200);
}

TestController::~TestController()
{
    _director->getEventDispatcher()->removeEventListener(_touchListener);

    _rootTestList->release();
    _rootTestList = nullptr;
}

void TestController::startAutoTest()
{
    if (!_autoTestThread.joinable())
    {
        _stopAutoTest = false;
        _logIndentation = "";
        _autoTestThread = std::thread(&TestController::traverseTestList, this, _rootTestList);
        _autoTestThread.detach();
    }
}

void TestController::stopAutoTest()
{
    _stopAutoTest = true;
    
    if (_autoTestThread.joinable()) {
        _sleepCondition.notify_all();
        _autoTestThread.join();
    }
}

void TestController::traverseTestList(TestList* testList)
{
    if (testList == _rootTestList)
    {
        _sleepUniqueLock = std::unique_lock<std::mutex>(_sleepMutex);
        _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(500));
        //disable touch
    }
    else
    {
        _logIndentation += LOG_INDENTATION;
        _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(500));
    }
    logEx("%s%sBegin traverse TestList:%s", LOG_TAG, _logIndentation.c_str(), testList->getTestName().c_str());

    auto scheduler = _director->getScheduler();
    int testIndex = 0;
    for (auto& callback : testList->_testCallbacks)
    {
        if (_stopAutoTest) break;
        while (_isRunInBackground)
        {
            logEx("_director is paused");
            _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(500));
        }
        if (callback)
        {
            auto test = callback();
            test->setTestParent(testList);
            test->setTestName(testList->_childTestNames[testIndex++]);
            if (test->isTestList())
            {
                scheduler->performFunctionInCocosThread([&](){
                    test->runThisTest();
                });

                traverseTestList((TestList*)test);
            }
            else
            {
                traverseTestSuite((TestSuite*)test);
            }
        }
    }

    if (testList == _rootTestList)
    {
        _sleepUniqueLock.release();
        _stopAutoTest = true;
    }
    else
    {
        if (!_stopAutoTest)
        {
            //Backs up one level and release TestList object.
            scheduler->performFunctionInCocosThread([&](){
                testList->_parentTest->runThisTest();
            });
            _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(500));
            testList->release();
        }
        
        _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
    }
}

void TestController::traverseTestSuite(TestSuite* testSuite)
{
    auto scheduler = _director->getScheduler();
    int testIndex = 0;
    float testCaseDuration = 0.0f;
    _logIndentation += LOG_INDENTATION;
    logEx("%s%sBegin traverse TestSuite:%s", LOG_TAG, _logIndentation.c_str(), testSuite->getTestName().c_str());

    _logIndentation += LOG_INDENTATION;

    auto logIndentation = _logIndentation;
    for (auto& callback : testSuite->_testCallbacks)
    {
        auto testName = testSuite->_childTestNames[testIndex++];
        
        Scene* testScene = nullptr;
        TestCase* testCase = nullptr;
        TransitionScene* transitionScene = nullptr;

        if (_stopAutoTest) break;
        while (_isRunInBackground)
        {
            logEx("_director is paused");
            _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(500));
        }
        //Run test case in the cocos[GL] thread.
        scheduler->performFunctionInCocosThread([&, logIndentation, testName](){
            if (_stopAutoTest) return;
            logEx("%s%sRun test:%s.", LOG_TAG, logIndentation.c_str(), testName.c_str());

            auto scene = callback();
            if (_stopAutoTest) return;

            if (scene)
            {
                transitionScene = dynamic_cast<TransitionScene*>(scene);
                if (transitionScene)
                {
                    testCase = (TestCase*)transitionScene->getInScene();
                    testCaseDuration = transitionScene->getDuration() + 0.5f;
                }
                else
                {
                    testCase = (TestCase*)scene;
                    testCaseDuration = testCase->getDuration();
                }
                testCase->setTestSuite(testSuite);
                testCase->setTestCaseName(testName);
                _director->replaceScene(scene);

                testScene = scene;
            }
        });

        if (_stopAutoTest) break;

        //Wait for the test case be created.
        float waitTime = 0.0f;
        while (!testScene && !_stopAutoTest)
        {
            _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(50));
            if (!_isRunInBackground)
            {
                waitTime += 0.05f;
            }

            if (waitTime > CREATE_TIME_OUT)
            {
                logEx("%sCreate test %s time out", LOG_TAG, testName.c_str());
                _stopAutoTest = true;
                break;
            }
        }

        if (_stopAutoTest) break;

        //Wait for test completed.
        _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(int(1000 * testCaseDuration)));

        if (transitionScene == nullptr)
        {
            waitTime = 0.0f;
            while (!_stopAutoTest && testCase->getRunTime() < testCaseDuration)
            {
                _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(50));
                if (!_isRunInBackground)
                {
                    waitTime += 0.05f;
                }

                if (waitTime > TEST_TIME_OUT)
                {
                    logEx("%sRun test %s time out", LOG_TAG, testName.c_str());
                    _stopAutoTest = true;
                    break;
                }
            }

            if (!_stopAutoTest)
            {
                //Check the result of test.
                checkTest(testCase);
            }
        }
    }

    if (!_stopAutoTest)
    {
        //Backs up one level and release TestSuite object.
        auto parentTest = testSuite->_parentTest;
        scheduler->performFunctionInCocosThread([&](){
            parentTest->runThisTest();
        });

        _sleepCondition.wait_for(_sleepUniqueLock, std::chrono::milliseconds(1000));
        testSuite->release();
    }

    _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
    _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
}

bool TestController::checkTest(TestCase* testCase)
{
    if (testCase)
    {
        switch (testCase->getTestType())
        {
        case TestCase::Type::UNIT:
        {
            if (testCase && testCase->getExpectedOutput() != testCase->getActualOutput())
            {
                logEx("%s %s test fail", LOG_TAG, testCase->getTestCaseName().c_str());
            }
            else
            {
                logEx("%s %s test pass", LOG_TAG, testCase->getTestCaseName().c_str());
            }
            break;
        }
        case TestCase::Type::ROBUSTNESS:
        {
            break;
        }
        case TestCase::Type::MANUAL:
        {
            break;
        }
        default:
            break;
        }
    }

    return true;
}

void TestController::handleCrash()
{
    logEx("%sCatch an crash event", LOG_TAG);

    if (!_stopAutoTest)
    {
        stopAutoTest();
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    exit(1);
#endif
}

void TestController::onEnterBackground()
{
    _isRunInBackground = true;
}

void TestController::onEnterForeground()
{
    _isRunInBackground = false;
}

void TestController::logEx(const char * format, ...)
{
    char buff[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(buff, 1020, format, args);
    strcat(buff, "\n");

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info", "%s", buff);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
    WCHAR wszBuf[1024] = { 0 };
    MultiByteToWideChar(CP_UTF8, 0, buff, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);

#else
    // Linux, Mac, iOS, etc
    fprintf(stdout, "%s", buff);
    fflush(stdout);
#endif
    va_end(args);
}

static TestController* s_testController = nullptr;

static void initCrashCatch();

TestController* TestController::getInstance()
{
    if (s_testController == nullptr)
    {
        s_testController = new (std::nothrow) TestController;

        initCrashCatch();
    }

    return s_testController;
}

void TestController::destroyInstance()
{
    if (s_testController)
    {
        s_testController->stopAutoTest();
        delete s_testController;
        s_testController = nullptr;
    }
}

bool TestController::blockTouchBegan(Touch* touch, Event* event)
{
    return !_stopAutoTest;
}

//==================================================================================================
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <windows.h>

static long __stdcall windowExceptionFilter(_EXCEPTION_POINTERS* excp)
{
    if (s_testController)
    {
        s_testController->handleCrash();
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

static void initCrashCatch()
{
    SetUnhandledExceptionFilter(windowExceptionFilter);
}

#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
static int s_fatal_signals[] = {
    SIGILL,
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGSEGV,
    SIGSTKFLT,
    SIGPIPE,
};
#else
static int s_fatal_signals[] = {
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGILL,
    SIGSEGV,
    SIGTRAP,
    SIGTERM,
    SIGKILL,
};
#endif

static void signalHandler(int sig)
{
    if (s_testController)
    {
        s_testController->handleCrash();
    }
}

static void initCrashCatch()
{
    for (auto sig : s_fatal_signals) {
        signal(sig, signalHandler);
    }
}

#else

static void initCrashCatch()
{

}

#endif
