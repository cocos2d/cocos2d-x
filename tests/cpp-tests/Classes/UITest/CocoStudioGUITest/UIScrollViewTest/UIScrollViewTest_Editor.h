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

class UIScrollViewTest_Vertical_Editor : public UIScene_Editor
{
public:
    UIScrollViewTest_Vertical_Editor();
    ~UIScrollViewTest_Vertical_Editor();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UIScrollViewTest_Vertical_Editor)
    Text* _displayValueLabel;
};


class UIScrollViewTest_Horizontal_Editor : public UIScene_Editor
{
public:
    UIScrollViewTest_Horizontal_Editor();
    ~UIScrollViewTest_Horizontal_Editor();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UIScrollViewTest_Horizontal_Editor)
    Text* _displayValueLabel;
};


class UIScrollViewTest_Both_Editor : public UIScene_Editor
{
public:
    UIScrollViewTest_Both_Editor();
    ~UIScrollViewTest_Both_Editor();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UIScrollViewTest_Both_Editor)
    Text* _displayValueLabel;
};


class UIScrollViewTest_ScrollToPercentBothDirection_Editor : public UIScene_Editor
{
public:
    UIScrollViewTest_ScrollToPercentBothDirection_Editor();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Editor();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Editor)
    Text* _displayValueLabel;
};


class UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor : public UIScene_Editor
{
public:
    UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor();
    ~UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor)
    Text* _displayValueLabel;
};

#endif /* defined(__TestCpp__UIScrollViewTest_Editor__) */
