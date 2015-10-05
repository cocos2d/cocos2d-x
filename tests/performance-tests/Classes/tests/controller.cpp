#include "controller.h"
#include <functional>
#include <chrono>
#include "BaseTest.h"
#include "tests.h"
#include "Profile.h"

USING_NS_CC;

#define TEST_TIME_OUT 6000
#define CREATE_TIME_OUT 25
#define LOG_INDENTATION "  "
#define LOG_TAG "[TestController]"

static void initCrashCatch();
static void disableCrashCatch();

class RootTests : public TestList
{
public:
    RootTests()
    {
        addTest("Alloc Tests", []() { return new PerformceAllocTests(); });
        addTest("Node Children Tests", []() { return new PerformceNodeChildrenTests(); });
        addTest("Particle Tests", []() { return new PerformceParticleTests(); });
        addTest("Particle3D Tests", []() { return new PerformceParticle3DTests(); });
        addTest("Sprite Tests", []() { return new PerformceSpriteTests(); });
        addTest("Texture Tests", []() { return new PerformceTextureTests(); });
        addTest("Label Tests", []() { return new PerformceLabelTests(); });
        addTest("EventDispatcher Tests", []() { return new PerformceEventDispatcherTests(); });
        addTest("Scenario Tests", []() { return new PerformceScenarioTests(); });
        addTest("Callback Tests", []() { return new PerformceCallbackTests(); });
        addTest("Math Tests", []() { return new PerformceMathTests(); });
        addTest("Container Tests", []() { return new PerformceContainerTests(); });
    }
};

TestController::TestController()
: _stopAutoTest(true)
, _isRunInBackground(false)
, _testSuite(nullptr)
{
    _director = Director::getInstance();
    _rootTestList = new (std::nothrow) RootTests;
    _rootTestList->runThisTest();
}

TestController::~TestController()
{
    _rootTestList->release();
    _rootTestList = nullptr;
}

void TestController::startAutoTest()
{
    if (!_autoTestThread.joinable())
    {
        _stopAutoTest = false;
        _logIndentation = "";
        _autoTestThread = std::thread(&TestController::traverseThreadFunc, this);
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

void TestController::traverseThreadFunc()
{
    std::mutex sleepMutex;
    auto lock = std::unique_lock<std::mutex>(sleepMutex);
    _sleepUniqueLock = &lock;
    traverseTestList(_rootTestList);
    _sleepUniqueLock = nullptr;
    
    // write the test data into file.
    Profile::getInstance()->flush();
    Profile::destroyInstance();
}

void TestController::traverseTestList(TestList* testList)
{
    if (testList == _rootTestList)
    {
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
    }
    else
    {
        _logIndentation += LOG_INDENTATION;
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
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
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
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
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
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
    testSuite->_currTestIndex = -1;

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
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
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
                testSuite->_currTestIndex++;
                testCase->setTestSuite(testSuite);
                testCase->setTestCaseName(testName);
                testCase->setAutoTesting(true);
                _director->replaceScene(scene);

                testScene = scene;
            }
        });

        if (_stopAutoTest) break;

        //Wait for the test case be created.
        float waitTime = 0.0f;
        while (!testScene && !_stopAutoTest)
        {
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(50));
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
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(int(1000 * testCaseDuration)));

        if (transitionScene == nullptr)
        {
            waitTime = 0.0f;
            while (!_stopAutoTest && testCase->isAutoTesting())
            {
                _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(50));
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
        scheduler->performFunctionInCocosThread([parentTest](){
            parentTest->runThisTest();
        });

        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(1000));
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
    disableCrashCatch();

    logEx("%sCatch an crash event", LOG_TAG);

    if (!_stopAutoTest)
    {
        stopAutoTest();
    }
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

#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
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

    disableCrashCatch();
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
static void disableCrashCatch()
{
    SetUnhandledExceptionFilter(UnhandledExceptionFilter);
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
    for (auto sig : s_fatal_signals)
    {
        signal(sig, signalHandler);
    }
}

static void disableCrashCatch()
{
    for (auto sig : s_fatal_signals)
    {
        signal(sig, SIG_DFL);
    }
}

#else

static void initCrashCatch()
{
}

static void disableCrashCatch()
{
}

#endif
