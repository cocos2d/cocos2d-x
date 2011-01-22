#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCXEGLView.h"

class  AppDelegate
{
public:
	AppDelegate();
	~AppDelegate();

    /**
    @brief	Implement Window create, CCDirector and CCScene init code here.
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

protected:
    cocos2d::CCXEGLView *   m_pMainWnd;
};
 

#endif // _APP_DELEGATE_H_

