#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"

class  AppDelegate  :  public  cocos2d::CCApplication
{
public:
    AppDelegate();
    ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

protected:
    cocos2d::CCEGLView *m_pMainWnd;
};
 
#endif  // __APP_DELEGATE_H__
