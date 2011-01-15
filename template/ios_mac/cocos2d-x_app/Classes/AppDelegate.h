//
//  AppDelegate.h
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCXApplication.h"
#include "CCXEGLView.h"

class  AppDelegate  :  public cocos2d::CCXApplication
{
public:
	AppDelegate();
	~AppDelegate();

	virtual bool    applicationDidFinishLaunching();
    virtual void    applicationDidEnterBackground();
    virtual void    applicationWillEnterForeground();

protected:
    cocos2d::CCXEGLView *   m_pMainWnd;
};
 

#endif // _APP_DELEGATE_H_

