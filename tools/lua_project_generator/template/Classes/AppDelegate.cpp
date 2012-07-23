#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
:m_pLuaEngine(NULL)
{
}

AppDelegate::~AppDelegate()
{
	// end simple audio engine here, or it may crashed on win32
	SimpleAudioEngine::sharedEngine()->end();
    CCScriptEngineManager::sharedScriptEngineManager()->removeScriptEngine();
    CC_SAFE_DELETE(m_pLuaEngine);
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("cocos2d: LuaProjectTemplate"), 480, 320));

#endif  // CC_PLATFORM_WIN32
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		// OpenGLView initialized in HelloWorld/android/jni/helloworld/main.cpp
		// the default setting is to create a fullscreen view
		// if you want to use auto-scale, please enable view->create(320,480) in main.cpp

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView* pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_  
        // on wophone emulator, we copy resources files to Work7/NEWPLUS/TDA_DATA/Data/ folder instead of zip file
        cocos2d::CCFileUtils::setResource("LuaProjectTemplate.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
		// MaxAksenov said it's NOT a very elegant solution. I agree, haha
		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd|| ! pMainWnd->Create(this));
        CCFileUtils::setResourcePath("/Res/");
#endif
        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
    CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// register lua engine
    m_pLuaEngine = new LuaEngine; 
	CCScriptEngineManager::sharedScriptEngineManager()->setScriptEngine(m_pLuaEngine);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	unsigned long size;
	char *pFileContent = (char*)CCFileUtils::getFileData("main.lua", "r", &size);

	if (pFileContent)
	{
	    // copy the file contents and add '\0' at the end, or the lua parser can not parse it
	    char *pCodes = new char[size + 1];
	    pCodes[size] = '\0';
	    memcpy(pCodes, pFileContent, size);
	    delete[] pFileContent;

	    CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->executeString(pCodes);
	    delete []pCodes;
	}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string path = CCFileUtils::fullPathFromRelativePath("main.lua");
	CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
    CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->executeScriptFile(path.c_str());
#endif 

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
