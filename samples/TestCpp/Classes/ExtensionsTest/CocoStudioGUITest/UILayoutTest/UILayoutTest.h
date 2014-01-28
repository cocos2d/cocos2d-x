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

#ifndef __TestCpp__UILayoutTest__
#define __TestCpp__UILayoutTest__

#include "../UIScene.h"

class UILayoutTest : public UIScene
{
public:
    UILayoutTest();
    ~UILayoutTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest)
};

class UILayoutTest_Color : public UIScene
{
public:
    UILayoutTest_Color();
    ~UILayoutTest_Color();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Color)
};

class UILayoutTest_Gradient : public UIScene
{
public:
    UILayoutTest_Gradient();
    ~UILayoutTest_Gradient();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Gradient)
};

class UILayoutTest_BackGroundImage : public UIScene
{
public:
    UILayoutTest_BackGroundImage();
    ~UILayoutTest_BackGroundImage();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_BackGroundImage)
};

class UILayoutTest_BackGroundImage_Scale9 : public UIScene
{
public:
    UILayoutTest_BackGroundImage_Scale9();
    ~UILayoutTest_BackGroundImage_Scale9();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_BackGroundImage_Scale9)
};

class UILayoutTest_Layout_Linear_Vertical : public UIScene
{
public:
    UILayoutTest_Layout_Linear_Vertical();
    ~UILayoutTest_Layout_Linear_Vertical();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Layout_Linear_Vertical)
};

class UILayoutTest_Layout_Linear_Horizontal : public UIScene
{
public:
    UILayoutTest_Layout_Linear_Horizontal();
    ~UILayoutTest_Layout_Linear_Horizontal();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Layout_Linear_Horizontal)
};

class UILayoutTest_Layout_Relative_Align_Parent : public UIScene
{
public:
    UILayoutTest_Layout_Relative_Align_Parent();
    ~UILayoutTest_Layout_Relative_Align_Parent();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Layout_Relative_Align_Parent)
};

class UILayoutTest_Layout_Relative_Location : public UIScene
{
public:
    UILayoutTest_Layout_Relative_Location();
    ~UILayoutTest_Layout_Relative_Location();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Layout_Relative_Location)
};

/*
class UILayoutTest_Layout_Grid : public UIScene
{
public:
    UILayoutTest_Layout_Grid();
    ~UILayoutTest_Layout_Grid();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UILayoutTest_Layout_Grid)
};
 */

#endif /* defined(__TestCpp__UILayoutTest__) */
