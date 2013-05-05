//
//  GCTestAppDelegate.h
//  GCTest
//
//  Created by Rohan Kuruvilla on 06/08/2012.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "jsapi.h"

/**
 @brief    The cocos2d Application.
 
 The reason for implement as private inheritance is to hide some interface call by CCDirector.
 */


class  AppDelegate : private cocos2d::CCApplication
{
public:
    bool isRetina, isIPhone;
    
    AppDelegate();
    virtual ~AppDelegate();
    
    /**
     @brief    Implement CCDirector and CCScene init code here.
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
    void initGameView();
   
};

bool runMainScene();
bool handle_eval_script(const char *script, jsval *out);
void openEditBox();
void updatePairingLabel(const char *);
void handle_ccb_stop();
void handle_connected();
void handle_disconnected();
void handle_set_orient(float w, float h);
void handle_set_message(const char *msg);
void handle_set_status(const char *msg);

#endif // _APP_DELEGATE_H_

