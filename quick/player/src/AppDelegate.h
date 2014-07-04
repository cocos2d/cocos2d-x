#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "base/CCRef.h"
#include "CCApplication.h"
#include "ProjectConfig/SimulatorConfig.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : public cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

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
    
    void setProjectConfig(const ProjectConfig& config);
    void setOpenRecents(const LuaValueArray& recents);
    
private:
    ProjectConfig m_projectConfig;
    LuaValueArray m_openRecents;
    
    friend class StartupCall;
};



class StartupCall : public cocos2d::Ref
{
public:
    static StartupCall *create(AppDelegate *app);
    void startup();
    
private:
    AppDelegate *m_app;
};
#endif  // __APP_DELEGATE_H__

