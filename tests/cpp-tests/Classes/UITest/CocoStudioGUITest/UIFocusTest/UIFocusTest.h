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

DEFINE_TEST_SUITE(UIFocusTests);

class UIFocusTestBase : public UIScene
{
public:
    UIFocusTestBase();
    virtual ~UIFocusTestBase();

    virtual bool init() override;
    
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
    CREATE_FUNC(UIFocusTestHorizontal);

    UIFocusTestHorizontal();
    virtual ~UIFocusTestHorizontal();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
    
protected:
    Layout *_horizontalLayout;
    Text *_loopText;
};

class UIFocusTestVertical : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestVertical);

    UIFocusTestVertical();
    virtual ~UIFocusTestVertical();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout1 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout1);

    UIFocusTestNestedLayout1();
    virtual ~UIFocusTestNestedLayout1();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout2 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout2);

    UIFocusTestNestedLayout2();
    virtual ~UIFocusTestNestedLayout2();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    Layout *_horizontalLayout;
    Text *_loopText;
};

class UIFocusTestNestedLayout3 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout3);

    UIFocusTestNestedLayout3();
    virtual ~UIFocusTestNestedLayout3();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    Layout *_verticalLayout;
    Text *_loopText;
};

class UIFocusTestListView : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestListView);

    UIFocusTestListView();
    virtual ~UIFocusTestListView();

    virtual bool init() override;
    
    void toggleFocusLoop(Ref*,Widget::TouchEventType);
protected:
    ListView *_listView;
    Text *_loopText;
};



#endif /* defined(__cocos2d_tests__UIFocusTest__) */
