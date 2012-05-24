//
//  testjsAppDelegate.cpp
//  testjs
//
//  Created by Rolando Abarca on 3/19/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "simple_native_generated.hpp"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	delete m_scripting;
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
            || ! pMainWnd->Create(TEXT("cocos2d: Hello World"), 480, 320));

#endif  // CC_PLATFORM_WIN32
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // OpenGLView is initialized in AppDelegate.mm on ios platform, nothing need to do here.
#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)        
        // OpenGLView is initialized in HelloWorld/android/jni/helloworld/main.cpp
		// the default setting is to create a fullscreen view
		// if you want to use auto-scale, please enable view->create(320,480) in main.cpp
#endif  // CC_PLATFORM_ANDROID
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView* pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_  
        // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        cocos2d::CCFileUtils::setResource("HelloWorld.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
		// MaxAksenov said it's NOT a very elegant solution. I agree, haha
		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
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

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

	// sets landscape mode
	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// add our generated bindings
    /*
	JSContext *cx = ScriptingCore::getInstance().getGlobalContext();
	JSObject *obj = JS_GetGlobalObject(cx);
	// since we pass the global object as the second argument, so these classes
	// will also be "global" much like properties added to "window" or "document"
	// in a browser
	S_SimpleNativeClass::jsCreateClass(cx, obj, "SimpleNativeClass");
	S_AnotherClass::jsCreateClass(cx, obj, "AnotherClass");
	register_enums_simple_native_generated(obj);
    ScriptingCore::getInstance().runScript("Javascript/1to1/test_bindings.js");
     */
    
	// run the main script
	ScriptingCore::getInstance().runScript("Javascript/1to1/test_actions.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_ease_actions.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_particles.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_layer.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_sound.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_transitions.js");
//	ScriptingCore::getInstance().runScript("Javascript/1to1/test_require.js");

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
