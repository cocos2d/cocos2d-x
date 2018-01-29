/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    cocos2d::ui::Button* _toggleButton;
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
