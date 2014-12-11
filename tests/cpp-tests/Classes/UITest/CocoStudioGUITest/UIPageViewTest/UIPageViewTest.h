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

#ifndef __TestCpp__UIPageViewTest__
#define __TestCpp__UIPageViewTest__

#include "../UIScene.h"

class UIPageViewTest : public UIScene
{
public:
    UIPageViewTest();
    ~UIPageViewTest();
    bool init();
    
    void pageViewEvent(Ref* pSender, PageView::EventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIPageViewTest)
    Text* _displayValueLabel;
};

class UIPageViewButtonTest : public UIScene
{
public:
    UIPageViewButtonTest();
    ~UIPageViewButtonTest();
    bool init();
    
    void pageViewEvent(Ref* pSender, PageView::EventType type);
    void onButtonClicked(Ref* pSender, Widget::TouchEventType type);
protected:
    UI_SCENE_CREATE_FUNC(UIPageViewButtonTest)
    Text* _displayValueLabel;
};

class UIPageViewCustomScrollThreshold : public UIScene
{
public:
    UIPageViewCustomScrollThreshold();
    ~UIPageViewCustomScrollThreshold();
    bool init();
    
    void sliderEvent(Ref* pSender, Slider::EventType type);

    void pageViewEvent(Ref* pSender, PageView::EventType type);
protected:
    UI_SCENE_CREATE_FUNC(UIPageViewCustomScrollThreshold)
    Text* _displayValueLabel;
};

class UIPageViewTouchPropagationTest : public UIScene
{
public:
    UIPageViewTouchPropagationTest();
    ~UIPageViewTouchPropagationTest();
    bool init();
    
    void pageViewEvent(Ref* pSender, PageView::EventType type);
    void onButtonClicked(Ref* pSender, Widget::TouchEventType type);

protected:
    UI_SCENE_CREATE_FUNC(UIPageViewTouchPropagationTest)
    Text* _displayValueLabel;
};

class UIPageViewDynamicAddAndRemoveTest : public UIScene
{
public:
    UIPageViewDynamicAddAndRemoveTest();
    ~UIPageViewDynamicAddAndRemoveTest();
    bool init();
    
    void pageViewEvent(Ref* pSender, PageView::EventType type);
    void onButtonClicked(Ref* pSender, Widget::TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIPageViewDynamicAddAndRemoveTest)
    Text* _displayValueLabel;
};

#endif /* defined(__TestCpp__UIPageViewTest__) */
