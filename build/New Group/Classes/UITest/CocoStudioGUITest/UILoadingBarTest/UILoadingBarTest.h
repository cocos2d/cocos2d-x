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

#ifndef __TestCpp__UILoadingBarTest__
#define __TestCpp__UILoadingBarTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UILoadingBarTests);

class UILoadingBarTest_Left : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Left);

    UILoadingBarTest_Left();
    ~UILoadingBarTest_Left();
    virtual bool init() override;
    void update(float delta)override;
    void printWidgetResources(cocos2d::Ref* sender);
    
protected:
    int _count;
    cocos2d::ui::LoadingBar* _loadingBar;
};

class UILoadingBarTest_Right : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Right);

    UILoadingBarTest_Right();
    ~UILoadingBarTest_Right();
    virtual bool init() override;
    void update(float delta)override;
    
protected:
    int _count;
};

class UILoadingBarTest_Left_Scale9 : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Left_Scale9);

    UILoadingBarTest_Left_Scale9();
    ~UILoadingBarTest_Left_Scale9();
    virtual bool init() override;
    void update(float delta)override;
    
protected:
    int _count;
};

class UILoadingBarTest_Right_Scale9 : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Right_Scale9);

    UILoadingBarTest_Right_Scale9();
    ~UILoadingBarTest_Right_Scale9();
    virtual bool init() override;
    void update(float delta)override;
    
protected:
    int _count;
};

class UILoadingBarTest_Scale9_State_Change : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Scale9_State_Change);

    UILoadingBarTest_Scale9_State_Change();
    ~UILoadingBarTest_Scale9_State_Change();
    virtual bool init() override;

protected:
    int _count;
};

class UILoadingBarReloadTexture : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarReloadTexture);

    UILoadingBarReloadTexture();
    ~UILoadingBarReloadTexture();
    void update(float dt) override;
    virtual bool init() override;
    
protected:
    int _count;
    
};

class UILoadingBarIssue12249 : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarIssue12249);
    
    UILoadingBarIssue12249();
    ~UILoadingBarIssue12249();
    virtual bool init() override;
    void update(float delta)override;
    
protected:
    int _count;
};

class UILoadingBarTest_Direction : public UIScene
{
public:
    CREATE_FUNC(UILoadingBarTest_Direction);

    UILoadingBarTest_Direction();
    ~UILoadingBarTest_Direction();
    virtual bool init() override;
protected:
    int _count;
    cocos2d::ui::LoadingBar* _loadingBar;
};

#endif /* defined(__TestCpp__UILoadingBarTest__) */
