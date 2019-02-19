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

#ifndef __TestCpp__UIImageViewTest__
#define __TestCpp__UIImageViewTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIImageViewTests);

class UIImageViewTest : public UIScene
{
public:
    CREATE_FUNC(UIImageViewTest);

    virtual bool init() override;

    void printWidgetResources(cocos2d::Ref* sender);
protected:
    cocos2d::ui::ImageView* _image;
};

class UIImageViewTest_Scale9 : public UIScene
{
public:
    CREATE_FUNC(UIImageViewTest_Scale9);

    virtual bool init() override;
};

class UIImageViewTest_Scale9_State_Change : public UIScene
{
public:
    CREATE_FUNC(UIImageViewTest_Scale9_State_Change);

    virtual bool init() override;
};

class UIImageViewTest_ContentSize : public UIScene
{
public:
    CREATE_FUNC(UIImageViewTest_ContentSize);

    virtual bool init() override;
};

class UIImageViewFlipTest : public UIScene
{
public:
    CREATE_FUNC(UIImageViewFlipTest);

    virtual bool init() override;
};

class UIImageViewIssue12249Test : public UIScene
{
public:
    CREATE_FUNC(UIImageViewIssue12249Test);
    
    virtual bool init() override;
};

#endif /* defined(__TestCpp__UIImageViewTest__) */
