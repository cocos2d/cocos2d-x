#ifndef  __COCOS2D_HELLOWORLD_APP_H__
#define  __COCOS2D_HELLOWORLD_APP_H__
#include "TG3.h"
#include "cocos2d.h"
#include "AppDelegate.h"

class  Application : public  TApplication, public cocos2d::ccxApplication
{
public:
    Application();
    virtual ~Application();

    virtual Boolean EventHandler(EventType * pEvent);

public:
    // implement the virtual interface of class ccxApplication
    virtual void        setAnimationInterval(double interval);
    virtual Orientation setOrientation(Orientation orientation);
    virtual void        statusBarFrame(cocos2d::CGRect * rect);
    virtual const char* getAppDataPath();
    virtual void        switchNotify(int nTurnOn);

protected:
    bool isInBackground();
    void StartMainLoop();
    void StopMainLoop();

private:
    static Int32 _OnAppIdle(MESSAGE_t * pMsg, UInt32 uData);

    MESSAGE_t   m_tMsg;
    bool        m_bRunning;
    bool        m_bNeedStop;
    bool        m_bInBackground;
    char        m_AppDataPath[EOS_FILE_MAX_PATH];
    AppDelegate m_Delegate;
};


#endif
