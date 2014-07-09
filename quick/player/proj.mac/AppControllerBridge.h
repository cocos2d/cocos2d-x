
#include "cocos2d.h"

using namespace cocos2d;

class AppControllerBridge : public CCObject
{
public:
    AppControllerBridge(void *controller)
    : m_controller(controller)
    {
    }
    
    void onWelcomeNewProject(CCObject *object);
    void onWelcomeOpen(CCObject *object);
    void onWelcomeSamples(CCObject *object);
    void onWelcomeGetStarted(CCObject *object);
    void onWelcomeGetCommunity(CCObject *object);
    void onWelcomeOpenRecent(CCObject *object);

private:
    void *m_controller;
};
