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

#ifndef __TestCpp__UIScrollViewTest__
#define __TestCpp__UIScrollViewTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIScrollViewTests);

class UIScrollViewTest_Vertical : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewTest_Vertical);

    UIScrollViewTest_Vertical();
    ~UIScrollViewTest_Vertical();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTest_Horizontal : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewTest_Horizontal);

    UIScrollViewTest_Horizontal();
    ~UIScrollViewTest_Horizontal();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTest_Both : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewTest_Both);

    UIScrollViewTest_Both();
    ~UIScrollViewTest_Both();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTest_ScrollToPercentBothDirection : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection);

    UIScrollViewTest_ScrollToPercentBothDirection();
    ~UIScrollViewTest_ScrollToPercentBothDirection();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTest_ScrollToPercentBothDirection_Bounce : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Bounce);

    UIScrollViewTest_ScrollToPercentBothDirection_Bounce();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Bounce();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewNestTest : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewNestTest);

    UIScrollViewNestTest();
    ~UIScrollViewNestTest();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewRotated : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewRotated);

    UIScrollViewRotated();
    ~UIScrollViewRotated();
    virtual bool init() override;
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewDisableTest : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewDisableTest);

    UIScrollViewDisableTest();
    ~UIScrollViewDisableTest();
    virtual bool init() override;

protected:

    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewInnerSize : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewInnerSize);

    UIScrollViewInnerSize();
    ~UIScrollViewInnerSize();
    virtual bool init() override;

protected:

    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTestEvents : public UIScene
{
public:
	CREATE_FUNC(UIScrollViewTestEvents);
	
	UIScrollViewTestEvents();
	virtual bool init() override;
	
protected:
	
	cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewStopScrollingTest : public UIScene
{
public:
    CREATE_FUNC(UIScrollViewStopScrollingTest);

    UIScrollViewStopScrollingTest();
    virtual bool init() override;

    virtual void update(float dt) override;

protected:

    cocos2d::ui::Text* _displayValueLabel;
    cocos2d::ui::ScrollView* _scrollView;
    float _remainingTime;
};
#endif /* defined(__TestCpp__UIScrollViewTest__) */
