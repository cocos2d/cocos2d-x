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

#ifndef __TestCpp__UIScrollViewTest__
#define __TestCpp__UIScrollViewTest__

#include "../UIScene.h"

class UIScrollViewTest_Vertical : public UIScene
{
public:
    UIScrollViewTest_Vertical();
    ~UIScrollViewTest_Vertical();
    bool init();
    
    void touchEvent(CCObject* pSender, TouchEventType type);
    void scrollEvent(CCObject* pSender, ScrollviewEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_Vertical)
    UILabel* m_pDisplayValueLabel;
};

class UIScrollViewTest_Horizontal : public UIScene
{
public:
    UIScrollViewTest_Horizontal();
    ~UIScrollViewTest_Horizontal();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_Horizontal)
    UILabel* m_pDisplayValueLabel;
};

/*===*/
class UIScrollViewTest_Both : public UIScene
{
public:
    UIScrollViewTest_Both();
    ~UIScrollViewTest_Both();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_Both)
    UILabel* m_pDisplayValueLabel;
};

class UIScrollViewTest_ScrollToPercentBothDirection : public UIScene
{
public:
    UIScrollViewTest_ScrollToPercentBothDirection();
    ~UIScrollViewTest_ScrollToPercentBothDirection();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection)
    UILabel* m_pDisplayValueLabel;
};

class UIScrollViewTest_ScrollToPercentBothDirection_Bounce : public UIScene
{
public:
    UIScrollViewTest_ScrollToPercentBothDirection_Bounce();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Bounce();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Bounce)
    UILabel* m_pDisplayValueLabel;
};
/*=*/

#endif /* defined(__TestCpp__UIScrollViewTest__) */
