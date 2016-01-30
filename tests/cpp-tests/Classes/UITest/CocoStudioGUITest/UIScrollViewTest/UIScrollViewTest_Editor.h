/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#ifndef __TestCpp__UIScrollViewTest_Editor__
#define __TestCpp__UIScrollViewTest_Editor__

#include "../UIScene_Editor.h"

DEFINE_TEST_SUITE(UIScrollViewEditorTests);

class UIScrollViewTest_Vertical_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_Vertical_Editor);

    UIScrollViewTest_Vertical_Editor();
    ~UIScrollViewTest_Vertical_Editor();

    virtual bool init() override;
protected:
    cocos2d::ui::Text* _displayValueLabel;
};


class UIScrollViewTest_Horizontal_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_Horizontal_Editor);

    UIScrollViewTest_Horizontal_Editor();
    ~UIScrollViewTest_Horizontal_Editor();

    virtual bool init() override;
protected:
    cocos2d::ui::Text* _displayValueLabel;
};


class UIScrollViewTest_Both_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_Both_Editor);

    UIScrollViewTest_Both_Editor();
    ~UIScrollViewTest_Both_Editor();

    virtual bool init() override;
protected:
    cocos2d::ui::Text* _displayValueLabel;
};


class UIScrollViewTest_ScrollToPercentBothDirection_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Editor);

    UIScrollViewTest_ScrollToPercentBothDirection_Editor();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Editor();

    virtual bool init() override;
 
protected:
    cocos2d::ui::Text* _displayValueLabel;
};


class UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor);

    UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor();

    virtual bool init() override;
    
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UIScrollViewTest_ClippingWithNode : public UIScene_Editor
{
public:
    CREATE_FUNC(UIScrollViewTest_ClippingWithNode);

    UIScrollViewTest_ClippingWithNode();
    ~UIScrollViewTest_ClippingWithNode();

    virtual bool init() override;
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UISscrollViewTestBar : public UIScene_Editor
{
public:
    CREATE_FUNC(UISscrollViewTestBar);

    UISscrollViewTestBar();
    ~UISscrollViewTestBar();

    virtual bool init() override;

};
#endif /* defined(__TestCpp__UIScrollViewTest_Editor__) */
