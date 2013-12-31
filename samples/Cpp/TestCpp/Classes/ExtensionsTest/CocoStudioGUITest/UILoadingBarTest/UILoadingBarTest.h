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

#ifndef __TestCpp__UILoadingBarTest__
#define __TestCpp__UILoadingBarTest__

#include "../UIScene.h"

class UILoadingBarTest_Left : public UIScene
{
public:
    UILoadingBarTest_Left();
    ~UILoadingBarTest_Left();
    bool init();
    void update(float delta);

	virtual void previousCallback(CCObject* sender, TouchEventType type);
    virtual void restartCallback(CCObject* sender, TouchEventType type);
    virtual void nextCallback(CCObject* sender, TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest_Left)
    int m_nCount;
};

class UILoadingBarTest_Right : public UIScene
{
public:
    UILoadingBarTest_Right();
    ~UILoadingBarTest_Right();
    bool init();
    void update(float delta);

	virtual void previousCallback(CCObject* sender, TouchEventType type);
    virtual void restartCallback(CCObject* sender, TouchEventType type);
    virtual void nextCallback(CCObject* sender, TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest_Right)
    int m_nCount;
};

class UILoadingBarTest_Left_Scale9 : public UIScene
{
public:
    UILoadingBarTest_Left_Scale9();
    ~UILoadingBarTest_Left_Scale9();
    bool init();
    void update(float delta);

	virtual void previousCallback(CCObject* sender, TouchEventType type);
    virtual void restartCallback(CCObject* sender, TouchEventType type);
    virtual void nextCallback(CCObject* sender, TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest_Left_Scale9)
    int m_nCount;
};

class UILoadingBarTest_Right_Scale9 : public UIScene
{
public:
    UILoadingBarTest_Right_Scale9();
    ~UILoadingBarTest_Right_Scale9();
    bool init();
    void update(float delta);

	virtual void previousCallback(CCObject* sender, TouchEventType type);
    virtual void restartCallback(CCObject* sender, TouchEventType type);
    virtual void nextCallback(CCObject* sender, TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest_Right_Scale9)
    int m_nCount;
};

#endif /* defined(__TestCpp__UILoadingBarTest__) */
