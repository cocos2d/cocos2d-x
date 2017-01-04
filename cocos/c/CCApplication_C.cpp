//
//  CCApplication_C.cpp
//  cocos2d_libs
//
//  Created by Alsey Coleman Miller on 10/16/16.
//
//

#include "c/CCApplication_C.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCCommon.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCScriptSupport.h"
#include "base/CCAutoreleasePool.h"
#include "platform/CCApplication.h"
#include "platform/CCApplicationProtocol.h"

USING_NS_CC;

#pragma mark - Class Implementation

NS_CC_BEGIN

/** Special Application subclass for C API. */
class CC_DLL Application_C : private cocos2d::Application
{
public:
    Application_C();
    virtual ~Application_C();
    
    virtual void initGLContextAttrs();
    
    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();
    
    // instance variables
    CCApplicationInitGLContextAttributesCallback_C initGLContextAttrsCallback;
    CCApplicationDidFinishLaunchingCallback_C applicationDidFinishLaunchingCallback;
    CCApplicationDidEnterBackgroundCallback_C applicationDidEnterBackgroundCallback;
    CCApplicationWillEnterForegroundCallback_C applicationWillEnterForegroundCallback;
};

Application_C::Application_C() {
    
}

Application_C::~Application_C()
{
    initGLContextAttrsCallback = NULL;
    applicationDidFinishLaunchingCallback = NULL;
    applicationDidEnterBackgroundCallback = NULL;
    applicationWillEnterForegroundCallback = NULL;
}

void Application_C::initGLContextAttrs()
{
    if (this->initGLContextAttrsCallback) {
        
        this->initGLContextAttrsCallback();
    }
}

bool Application_C::applicationDidFinishLaunching()
{
    if (this->applicationDidFinishLaunchingCallback) {
        
        return this->applicationDidFinishLaunchingCallback();
        
    } else {
        
        return true; // default value
    }
}

void Application_C::applicationDidEnterBackground()
{
    if (this->applicationDidEnterBackgroundCallback) {
        
        this->applicationDidEnterBackgroundCallback();
    }
}

void Application_C::applicationWillEnterForeground()
{
    if (this->applicationWillEnterForegroundCallback) {
        
        this->applicationWillEnterForegroundCallback();
    }
}

NS_CC_END

#pragma mark - Initialization

extern "C" void CCApplicationInit()
{
    static Application_C* sharedApplication = nullptr;
    
    if (!sharedApplication) {
        
        *sharedApplication = Application_C();
    }
}

#pragma mark - Methods

extern "C" void CCApplicationRun()
{
    Application::getInstance()->run();
}

#pragma mark - Properties

extern "C" CCApplicationInitGLContextAttributesCallback_C _Nullable CCApplicationGetInitGLContextAttributesCallback()
{
    Application_C *application = (Application_C *)Application::getInstance();
    return application->initGLContextAttrsCallback;
}

extern "C" void CCApplicationSetInitGLContextAttributesCallback(CCApplicationInitGLContextAttributesCallback_C _Nullable callback)
{
    Application_C *application = (Application_C *)Application::getInstance();
    application->initGLContextAttrsCallback = callback;
}

extern "C" CCApplicationDidFinishLaunchingCallback_C _Nullable CCApplicationGetDidFinishLaunchingCallback()
{
    Application_C *application = (Application_C *)Application::getInstance();
    return application->applicationDidFinishLaunchingCallback;
}

extern "C" void CCApplicationSetDidFinishLaunchingCallback(CCApplicationDidFinishLaunchingCallback_C _Nullable callback)
{
    Application_C *application = (Application_C *)Application::getInstance();
    application->applicationDidFinishLaunchingCallback = callback;
}

extern "C" CCApplicationDidEnterBackgroundCallback_C _Nullable CCApplicationGetDidEnterBackgroundCallback()
{
    Application_C *application = (Application_C *)Application::getInstance();
    return application->applicationDidEnterBackgroundCallback;
}

extern "C" void CCApplicationSetDidEnterBackgroundCallback(CCApplicationDidEnterBackgroundCallback_C _Nullable callback)
{
    Application_C *application = (Application_C *)Application::getInstance();
    application->applicationDidEnterBackgroundCallback = callback;
}

extern "C" CCApplicationWillEnterForegroundCallback_C _Nullable CCApplicationGetWillEnterForegroundCallback()
{
    Application_C *application = (Application_C *)Application::getInstance();
    return application->applicationWillEnterForegroundCallback;
}

extern "C" void CCApplicationSetWillEnterForegroundCallback(CCApplicationWillEnterForegroundCallback_C _Nullable callback)
{
    Application_C *application = (Application_C *)Application::getInstance();
    application->applicationWillEnterForegroundCallback = callback;
}

