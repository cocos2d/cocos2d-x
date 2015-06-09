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

#ifndef __TestCpp__UIListViewTest__
#define __TestCpp__UIListViewTest__

#include "../UIScene.h"
#include "ui/UIScrollView.h"

DEFINE_TEST_SUITE(UIListViewTests);

class UIListViewTest_Vertical : public UIScene
{
public:
    CREATE_FUNC(UIListViewTest_Vertical);

    UIListViewTest_Vertical();
    ~UIListViewTest_Vertical();

    virtual bool init() override;
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(cocos2d::Ref* sender, cocos2d::ui::ScrollView::EventType type);

protected:
    
    cocos2d::ui::Text* _displayValueLabel;
    
    std::vector<std::string> _array;
};

class UIListViewTest_Horizontal : public UIScene
{
public:
    CREATE_FUNC(UIListViewTest_Horizontal);

    UIListViewTest_Horizontal();
    ~UIListViewTest_Horizontal();

    virtual bool init() override;
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);

    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
    
    std::vector<std::string> _array;
};

#endif /* defined(__TestCpp__UIListViewTest__) */
