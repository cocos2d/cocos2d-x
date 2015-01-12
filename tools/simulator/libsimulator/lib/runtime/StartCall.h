//
//  StartCall.h
//  simulator
//
//

#ifndef __simulator__StartCall__
#define __simulator__StartCall__

#include "cocos2d.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

class StartupCall : public cocos2d::Ref
{
public:
    static StartupCall *create();
    void startup();
    
private:
    StartupCall();
    
    void trackEvent(const char *eventName);
    void trackLaunchEvent();
    
    void onPreviewCocosCSD(const std::string &path);
    void onPreviewCocosCSB(const std::string &path);
    void onPreviewLua(const std::string &path);
    void onPreviewJs(const std::string &path);
    
    void updateConfigParser(const ProjectConfig& project);
    void updatePreviewFuncForPath(const std::string &path);
    
private:
    std::function<void(const std::string &)> _previewFunc;
    std::string _launchEvent;
};

#endif /* defined(__simulator__StartCall__) */
