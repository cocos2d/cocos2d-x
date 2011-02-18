#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "ccxApplication.h"

#include <Windows.h>
#include "AppDelegate.h"
#include "CCXEGLView.h"

class Application : public cocos2d::ccxApplication
{
public:
    Application();
    virtual ~Application();

    /**
    @brief	Run the message loop.
    */
    int run();

    /**
    @brief	Call for init OpenGL instance, source path, etc...
    */
    virtual bool initInstance();

    /**
    @brief	Callback by CCDirector for limit FPS.
    @interval       The time, which expressed in second in second, between current frame and next. 
    */
    virtual void    setAnimationInterval(double interval);

    /**
    @brief	Callback by CCDirector for change device orientation.
    @orientation    The defination of orientation which CCDirector want change to.
    @return         The actual orientation of the application.
    */
    virtual Orientation setOrientation(Orientation orientation);

    /**
    @brief	Get status bar rectangle in EGLView window.
    */
    virtual void    statusBarFrame(cocos2d::CGRect * rect);

protected:
    cocos2d::CCXEGLView m_MainWnd;          // the OpenGLView window

    AppDelegate         m_Delegate;

    HINSTANCE           m_hInstance;
    HACCEL              m_hAccelTable;
    LARGE_INTEGER       m_nAnimationInterval;
};

#endif	// __APPLICATION_H__
