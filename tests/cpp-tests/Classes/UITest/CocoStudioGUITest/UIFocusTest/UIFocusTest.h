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
    
    virtual void onLeftKeyPressed();
    virtual void onRightKeyPressed();
    virtual void onUpKeyPressed();
    virtual void onDownKeyPressed();
    virtual void onFocusChanged(Widget* widgetLostFocus, Widget* widgetGetFocus);

    void onImageViewClicked(Ref* ref, Widget::TouchEventType touchType);

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
   
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
    
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
   
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestVertical);
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout1 : public UIFocusTestBase
{
public:
    UIFocusTestNestedLayout1();
    virtual ~UIFocusTestNestedLayout1();
    bool init();
    
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestNestedLayout1);
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout2 : public UIFocusTestBase
{
public:
    UIFocusTestNestedLayout2();
    virtual ~UIFocusTestNestedLayout2();
    bool init();
    
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestNestedLayout2);
    Layout *_horizontalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout3 : public UIFocusTestBase
{
public:
    UIFocusTestNestedLayout3();
    virtual ~UIFocusTestNestedLayout3();
    bool init();
    
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestNestedLayout3);
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestListView : public UIFocusTestBase
{
public:
    UIFocusTestListView();
    virtual ~UIFocusTestListView();
    bool init();
    
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    UI_SCENE_CREATE_FUNC(UIFocusTestListView);
    ListView *_listView;
    Text *_loopText;
};



#endif /* defined(__cocos2d_tests__UIFocusTest__) */
