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

#ifndef __TestCpp__UIPageViewTest_Editor__
#define __TestCpp__UIPageViewTest_Editor__

#include "../UIScene_Editor.h"

DEFINE_TEST_SUITE(UIPageViewEditorTests);

class UIPageViewTest_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UIPageViewTest_Editor);

    UIPageViewTest_Editor();
    ~UIPageViewTest_Editor();

    virtual bool init() override;
    
    void pageViewEvent(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type);
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

#endif /* defined(__TestCpp__UIPageViewTest_Editor__) */
