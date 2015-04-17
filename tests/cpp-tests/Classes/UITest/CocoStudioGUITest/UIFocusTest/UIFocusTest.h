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
    virtual void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);

    void onImageViewClicked(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType touchType);

protected:
    cocos2d::Menu* _dpadMenu;
    cocos2d::ui::Widget* _firstFocusedWidget;
    cocos2d::EventListenerFocus* _eventListener;
};

class UIFocusTestHorizontal : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestHorizontal);

    UIFocusTestHorizontal();
    virtual ~UIFocusTestHorizontal();

    virtual bool init() override;

    void toggleFocusLoop(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType);

protected:
    cocos2d::ui::Layout* _horizontalLayout;
    cocos2d::ui::Text* _loopText;
};

class UIFocusTestVertical : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestVertical);

    UIFocusTestVertical();
    virtual ~UIFocusTestVertical();

    virtual bool init() override;

    void toggleFocusLoop(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType);
protected:
    cocos2d::ui::Layout* _verticalLayout;
    cocos2d::ui::Text* _loopText;
};

class UIFocusTestNestedLayout1 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout1);

    UIFocusTestNestedLayout1();
    virtual ~UIFocusTestNestedLayout1();

    virtual bool init() override;

    void toggleFocusLoop(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType);
protected:
    cocos2d::ui::Layout* _verticalLayout;
    cocos2d::ui::Text* _loopText;
};

class UIFocusTestNestedLayout2 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout2);

    UIFocusTestNestedLayout2();
    virtual ~UIFocusTestNestedLayout2();

    virtual bool init() override;

    void toggleFocusLoop(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType);
protected:
    cocos2d::ui::Layout* _horizontalLayout;
    cocos2d::ui::Text* _loopText;
};

class UIFocusTestNestedLayout3 : public UIFocusTestBase
{
public:
    CREATE_FUNC(UIFocusTestNestedLayout3);

    UIFocusTestNestedLayout3();
    virtual ~UIFocusTestNestedLayout3();

    virtual bool init() override;

    void toggleFocusLoop(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType);
protected:
    cocos2d::ui::Layout* _verticalLayout;
    cocos2d::ui::Text* _loopText;
};



#endif /* defined(__cocos2d_tests__UIFocusTest__) */
