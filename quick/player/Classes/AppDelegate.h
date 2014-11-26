#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

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
    
    void setProjectConfig(const ProjectConfig &config);
    
private:
    ProjectConfig _project;
    
    friend class StartupCall;
};


class StartupCall : public cocos2d::Ref
{
public:
    static StartupCall *create(AppDelegate *app);
    void startup();
    
private:
    void trackEvent(const char *eventName);
    void trackLaunchEvent();
    
private:
    AppDelegate *_app;
};


#endif  // __APP_DELEGATE_H__

