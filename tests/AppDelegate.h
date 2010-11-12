#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"

class  AppDelegate  :  public  cocos2d::CCXApplication
{
public:
	AppDelegate();
	~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

protected:
    cocos2d::CCXEGLView *m_pMainWnd;

// private:
//    Int32 m_nTimer;
};
 

#endif	// __APP_DELEGATE_H__

