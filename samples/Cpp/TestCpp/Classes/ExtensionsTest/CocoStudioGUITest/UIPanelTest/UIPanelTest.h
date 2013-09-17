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

#ifndef __TestCpp__UIPanelTest__
#define __TestCpp__UIPanelTest__

#include "../UIScene.h"

class UIPanelTest : public UIScene
{
public:
    UIPanelTest();
    ~UIPanelTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest)
};

class UIPanelTest_Color : public UIScene
{
public:
    UIPanelTest_Color();
    ~UIPanelTest_Color();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_Color)
};

class UIPanelTest_Gradient : public UIScene
{
public:
    UIPanelTest_Gradient();
    ~UIPanelTest_Gradient();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_Gradient)
};

class UIPanelTest_BackGroundImage : public UIScene
{
public:
    UIPanelTest_BackGroundImage();
    ~UIPanelTest_BackGroundImage();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_BackGroundImage)
};

class UIPanelTest_BackGroundImage_Scale9 : public UIScene
{
public:
    UIPanelTest_BackGroundImage_Scale9();
    ~UIPanelTest_BackGroundImage_Scale9();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_BackGroundImage_Scale9)
};

class UIPanelTest_Layout_Linear_Vertical : public UIScene
{
public:
    UIPanelTest_Layout_Linear_Vertical();
    ~UIPanelTest_Layout_Linear_Vertical();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_Layout_Linear_Vertical)
};

class UIPanelTest_Layout_Linear_Horizontal : public UIScene
{
public:
    UIPanelTest_Layout_Linear_Horizontal();
    ~UIPanelTest_Layout_Linear_Horizontal();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_Layout_Linear_Horizontal)
};

class UIPanelTest_Layout_Relative : public UIScene
{
public:
    UIPanelTest_Layout_Relative();
    ~UIPanelTest_Layout_Relative();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPanelTest_Layout_Relative)
};

#endif /* defined(__TestCpp__UIPanelTest__) */
