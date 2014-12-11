/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

class UIButtonTest : public UIScene
{
public:
    UIButtonTest();
    ~UIButtonTest();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);

protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest)
    Text* _displayValueLabel;
};

class UIButtonTest_Scale9 : public UIScene
{
public:
    UIButtonTest_Scale9();
    ~UIButtonTest_Scale9();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest_Scale9)
    Text* _displayValueLabel;
};

class UIButtonTest_PressedAction : public UIScene
{
public:
    UIButtonTest_PressedAction();
    ~UIButtonTest_PressedAction();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest_PressedAction)
    Text* _displayValueLabel;
};

class UIButtonTest_Title : public UIScene
{
public:
    UIButtonTest_Title();
    ~UIButtonTest_Title();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest_Title)
    Text* _displayValueLabel;
};

class UIButtonTestRemoveSelf : public UIScene
{
public:
    UIButtonTestRemoveSelf();
    ~UIButtonTestRemoveSelf();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTestRemoveSelf)
    Text* _displayValueLabel;
};

class UIButtonTestSwitchScale9 : public UIScene
{
public:
    UIButtonTestSwitchScale9();
    ~UIButtonTestSwitchScale9();
    bool init();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTestSwitchScale9)
    Text* _displayValueLabel;
};

class UIButtonTestZoomScale : public UIScene
{
public:
    UIButtonTestZoomScale();
    ~UIButtonTestZoomScale();
    bool init();
    void sliderEvent(Ref* pSender, Slider::EventType type);

protected:
    UI_SCENE_CREATE_FUNC(UIButtonTestZoomScale)
    Text* _displayValueLabel;
};

class UIButtonTextOnly : public UIScene
{
public:
    UIButtonTextOnly();
    ~UIButtonTextOnly();
    bool init();

protected:
    UI_SCENE_CREATE_FUNC(UIButtonTextOnly)
    Text* _displayValueLabel;
};

class UIButtonIgnoreContentSizeTest : public UIScene
{
public:
    UIButtonIgnoreContentSizeTest();
    ~UIButtonIgnoreContentSizeTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonIgnoreContentSizeTest)
    Text* _displayValueLabel;
};

class UIButtonTitleEffectTest : public UIScene
{
public:
    UIButtonTitleEffectTest();
    ~UIButtonTitleEffectTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTitleEffectTest)
    Text* _displayValueLabel;
};

class UIButtonFlipTest : public UIScene
{
public:
    UIButtonFlipTest();
    ~UIButtonFlipTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonFlipTest)
    Text* _displayValueLabel;
};
#endif /* defined(__TestCpp__UIButtonTest__) */
