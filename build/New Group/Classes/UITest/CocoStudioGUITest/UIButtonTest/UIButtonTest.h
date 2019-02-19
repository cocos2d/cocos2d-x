/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
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

#ifndef __TestCpp__UIButtonTest__
#define __TestCpp__UIButtonTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIButtonTests);

class UIButtonTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonTest);

    UIButtonTest();
    ~UIButtonTest();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

    void printWidgetResources(cocos2d::Ref* sender);
protected:
    cocos2d::ui::Text* _displayValueLabel;
    cocos2d::ui::Button* _button;
};

class UIButtonTest_Scale9 : public UIScene
{
public:
    CREATE_FUNC(UIButtonTest_Scale9);

    UIButtonTest_Scale9();
    ~UIButtonTest_Scale9();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTest_Scale9_State_Change : public UIScene
{
public:
    CREATE_FUNC(UIButtonTest_Scale9_State_Change);

    UIButtonTest_Scale9_State_Change();
    ~UIButtonTest_Scale9_State_Change();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
        cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTest_PressedAction : public UIScene
{
public:
    CREATE_FUNC(UIButtonTest_PressedAction);

    UIButtonTest_PressedAction();
    ~UIButtonTest_PressedAction();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTest_Title : public UIScene
{
public:
    CREATE_FUNC(UIButtonTest_Title);

    UIButtonTest_Title();
    ~UIButtonTest_Title();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTestRemoveSelf : public UIScene
{
public:
    CREATE_FUNC(UIButtonTestRemoveSelf);

    UIButtonTestRemoveSelf();
    ~UIButtonTestRemoveSelf();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTestSwitchScale9 : public UIScene
{
public:
    CREATE_FUNC(UIButtonTestSwitchScale9);

    UIButtonTestSwitchScale9();
    ~UIButtonTestSwitchScale9();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTestZoomScale : public UIScene
{
public:
    CREATE_FUNC(UIButtonTestZoomScale);

    UIButtonTestZoomScale();
    ~UIButtonTestZoomScale();

    virtual bool init() override;
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTextOnly : public UIScene
{
public:
    CREATE_FUNC(UIButtonTextOnly);

    UIButtonTextOnly();
    ~UIButtonTextOnly();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonIgnoreContentSizeTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonIgnoreContentSizeTest);

    UIButtonIgnoreContentSizeTest();
    ~UIButtonIgnoreContentSizeTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonTitleEffectTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonTitleEffectTest);

    UIButtonTitleEffectTest();
    ~UIButtonTitleEffectTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonFlipTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonFlipTest);

    UIButtonFlipTest();
    ~UIButtonFlipTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonNormalDefaultTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonNormalDefaultTest);

    UIButtonNormalDefaultTest();
    ~UIButtonNormalDefaultTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonDisableDefaultTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonDisableDefaultTest);

    UIButtonDisableDefaultTest();
    ~UIButtonDisableDefaultTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIButtonCloneTest : public UIScene
{
public:
    CREATE_FUNC(UIButtonCloneTest);

    UIButtonCloneTest();
    ~UIButtonCloneTest();

    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class Issue12249 : public UIScene
{
public:
    CREATE_FUNC(Issue12249);
    
    Issue12249();
    
    virtual bool init() override;
    
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class Issue17116: public UIScene
{
public:
    CREATE_FUNC(Issue17116);

    Issue17116();

    virtual bool init() override;
};

class UIButtonWithPolygonInfo: public UIScene
{
public:
    CREATE_FUNC(UIButtonWithPolygonInfo);
    
    UIButtonWithPolygonInfo();
    
    virtual bool init() override;
};

class UIButtonScale9ChangeSpriteFrame: public UIScene
{
public:
    CREATE_FUNC(UIButtonScale9ChangeSpriteFrame);
    
    UIButtonScale9ChangeSpriteFrame();
    
    virtual bool init() override;
};

#endif /* defined(__TestCpp__UIButtonTest__) */
