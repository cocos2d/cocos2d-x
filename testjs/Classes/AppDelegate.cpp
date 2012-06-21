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

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

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
    ScriptingCore::getInstance().runScript("JS/1to1/test_actions.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_ease_actions.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_particles.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_layer.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_sound.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_transitions.js");
//    ScriptingCore::getInstance().runScript("JS/1to1/test_require.js");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
