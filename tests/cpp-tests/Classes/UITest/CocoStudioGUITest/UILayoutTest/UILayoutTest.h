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

#ifndef __TestCpp__UILayoutTest__
#define __TestCpp__UILayoutTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UILayoutTests);

class UILayoutTest : public UIScene
{
public:
    UILayoutTest();
    ~UILayoutTest();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest);
};

class UILayoutTest_Color : public UIScene
{
public:
    UILayoutTest_Color();
    ~UILayoutTest_Color();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Color);
};

class UILayoutTest_Gradient : public UIScene
{
public:
    UILayoutTest_Gradient();
    ~UILayoutTest_Gradient();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Gradient);
};

class UILayoutTest_BackGroundImage : public UIScene
{
public:
    UILayoutTest_BackGroundImage();
    ~UILayoutTest_BackGroundImage();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_BackGroundImage);

    void printWidgetResources(cocos2d::Ref* sender);
protected:
    cocos2d::ui::Layout* _layout;
};

class UILayoutTest_BackGroundImage_Scale9 : public UIScene
{
public:
    UILayoutTest_BackGroundImage_Scale9();
    ~UILayoutTest_BackGroundImage_Scale9();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_BackGroundImage_Scale9);
};

class UILayoutTest_Layout_Linear_Vertical : public UIScene
{
public:
    UILayoutTest_Layout_Linear_Vertical();
    ~UILayoutTest_Layout_Linear_Vertical();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Layout_Linear_Vertical);
};

class UILayoutTest_Layout_Linear_Horizontal : public UIScene
{
public:
    UILayoutTest_Layout_Linear_Horizontal();
    ~UILayoutTest_Layout_Linear_Horizontal();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Layout_Linear_Horizontal);
};

class UILayoutTest_Layout_Relative_Align_Parent : public UIScene
{
public:
    UILayoutTest_Layout_Relative_Align_Parent();
    ~UILayoutTest_Layout_Relative_Align_Parent();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Layout_Relative_Align_Parent);
};

class UILayoutTest_Layout_Relative_Location : public UIScene
{
public:
    UILayoutTest_Layout_Relative_Location();
    ~UILayoutTest_Layout_Relative_Location();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Layout_Relative_Location);
};

class UILayoutTest_Layout_Scaled_Widget : public UIScene
{
public:
    UILayoutTest_Layout_Scaled_Widget();
    ~UILayoutTest_Layout_Scaled_Widget();
    virtual bool init() override;
    
    CREATE_FUNC(UILayoutTest_Layout_Scaled_Widget);
};

class UILayoutComponentTest : public UIScene
{
public:
    CREATE_FUNC(UILayoutComponentTest);

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
protected:
    cocos2d::LayerColor* _baseLayer;
    
};

class UILayoutComponent_Berth_Test : public UILayoutComponentTest
{
public:
    virtual bool init() override;

    CREATE_FUNC(UILayoutComponent_Berth_Test);
};

class UILayoutComponent_Berth_Stretch_Test : public UILayoutComponentTest
{
public:
    virtual bool init() override;

    CREATE_FUNC(UILayoutComponent_Berth_Stretch_Test);
};

class UILayoutTest_Issue19890 : public UIScene
{
public:
    virtual bool init() override;

    CREATE_FUNC(UILayoutTest_Issue19890);
};

class UILayout_Clipping_Test : public UILayoutComponentTest
{
public:
    virtual bool init() override;

    CREATE_FUNC(UILayout_Clipping_Test);
};

#endif /* defined(__TestCpp__UILayoutTest__) */
