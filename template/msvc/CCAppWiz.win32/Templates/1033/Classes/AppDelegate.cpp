#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
[! if CC_USE_LUA]
#include "CCLuaEngine.h"
[! else]
#include "HelloWorldScene.h"
[! endif]
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
[! endif]

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
    SimpleAudioEngine::end();
[! endif]
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

[! if CC_USE_LUA]
    // register lua engine
    CCScriptEngineProtocol* pEngine = CCLuaEngine::engine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    unsigned long size;
    char *pFileContent = (char*)CCFileUtils::getFileData("hello.lua", "r", &size);

    if (pFileContent)
    {
        // copy the file contents and add '\0' at the end, or the lua parser can not parse it
        char *pCodes = new char[size + 1];
        pCodes[size] = '\0';
        memcpy(pCodes, pFileContent, size);
        delete[] pFileContent;

        pEngine->executeString(pCodes);
        delete []pCodes;
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	std::string path = CCFileUtils::fullPathFromRelativePath("hello.lua");
    pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
    pEngine->executeScriptFile(path.c_str());
#endif
[! else]
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
[! endif]
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
[! endif]
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
[! endif]
}
