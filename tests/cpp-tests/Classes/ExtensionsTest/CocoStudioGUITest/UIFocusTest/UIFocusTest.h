//
//  UIFocusTest.h
//  cocos2d_tests
//
//  Created by guanghui on 5/4/14.
//
//

#ifndef __cocos2d_tests__UIFocusTest__
#define __cocos2d_tests__UIFocusTest__

#include "../UIScene.h"

class UIFocusTestBase : public UIScene
{
public:
    UIFocusTestBase();
    virtual ~UIFocusTestBase();
    bool init();
    
    virtual void onLeftKeyPressed() = 0;
    virtual void onRightKeyPressed() = 0;
    virtual void onUpKeyPressed() = 0;
    virtual void onDownKeyPressed() = 0;
    virtual void onFocusChanged(Widget* widgetLostFocus, Widget* widgetGetFocus) = 0;
protected:
    Menu *_dpadMenu;
    Widget *_firstFocusedWidget;
    EventListenerFocus *_eventListener;
};

class UIFocusTestHorizontal : public UIFocusTestBase
{
public:
    UIFocusTestHorizontal();
    virtual ~UIFocusTestHorizontal();
    bool init();
    virtual void onLeftKeyPressed() ;
    virtual void onRightKeyPressed();
    virtual void onUpKeyPressed() ;
    virtual void onDownKeyPressed() ;
    virtual void onFocusChanged(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    void toggleFocusLoop(Ref*,TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestHorizontal);
    Layout *_horizontalLayout;
    Text *_loopText;
};

class UIFocusTestVertical : public UIFocusTestBase
{
public:
    UIFocusTestVertical();
    virtual ~UIFocusTestVertical();
    bool init();
    virtual void onLeftKeyPressed() ;
    virtual void onRightKeyPressed();
    virtual void onUpKeyPressed() ;
    virtual void onDownKeyPressed() ;
    virtual void onFocusChanged(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    void toggleFocusLoop(Ref*,TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestVertical);
    Layout *_verticalLayout;
    Text *_loopText;
};


#endif /* defined(__cocos2d_tests__UIFocusTest__) */
