#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "ide-support/CodeIDESupport.h"

#include "runtime/Runtime.h"

// Lua
#include "ide-support/RuntimeLuaImpl.h"

// Js
#include "ide-support/RuntimeJsImpl.h"


using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);
    
    auto runtimeEngine = RuntimeEngine::getInstance();
    runtimeEngine->setEventTrackingEnable(true);
    runtimeEngine->addRuntime(RuntimeLuaImpl::create(), kRuntimeEngineLua);
    auto jsRuntime = RuntimeJsImpl::create();
    runtimeEngine->addRuntime(jsRuntime, kRuntimeEngineJs);
    runtimeEngine->start();
    
    // js need special debug port
    if (runtimeEngine->getProjectConfig().getDebuggerType() != kCCRuntimeDebuggerNone)
    {
        jsRuntime->startWithDebugger();
    }


    // Runtime end
    cocos2d::log("iShow!");
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
