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

#ifndef __TestCpp__UIProgressTimerTest__
#define __TestCpp__UIProgressTimerTest__

#include "../UIScene.h"

class UIProgressTimerTest_Radial : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_Radial)
};

class UIProgressTimerTest_Horizontal : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_Horizontal)
};

class UIProgressTimerTest_Vertical : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_Vertical)
};

class UIProgressTimerTest_RadialMidpointChanged : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_RadialMidpointChanged)
};

class UIProgressTimerTest_BarVarious : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_BarVarious)
};

class UIProgressTimerTest_BarTintAndFade : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_BarTintAndFade)
};

class UIProgressTimerTest_WithSpriteFrame : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIProgressTimerTest_WithSpriteFrame)
};

#endif /* defined(__TestCpp__UIProgressTimerTest__) */
