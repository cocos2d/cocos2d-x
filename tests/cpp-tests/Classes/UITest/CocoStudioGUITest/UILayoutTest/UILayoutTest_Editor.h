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

#ifndef __TestCpp__UILayoutTest_Editor__
#define __TestCpp__UILayoutTest_Editor__

#include "../UIScene_Editor.h"

class UILayoutTest_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Editor();
    ~UILayoutTest_Editor();
    bool init();    
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Editor)
};


class UILayoutTest_Color_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Color_Editor();
    ~UILayoutTest_Color_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Color_Editor)
};


class UILayoutTest_Gradient_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Gradient_Editor();
    ~UILayoutTest_Gradient_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Gradient_Editor)
};


class UILayoutTest_BackGroundImage_Editor : public UIScene_Editor
{
public:
    UILayoutTest_BackGroundImage_Editor();
    ~UILayoutTest_BackGroundImage_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_BackGroundImage_Editor)
};


class UILayoutTest_BackGroundImage_Scale9_Editor : public UIScene_Editor
{
public:
    UILayoutTest_BackGroundImage_Scale9_Editor();
    ~UILayoutTest_BackGroundImage_Scale9_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_BackGroundImage_Scale9_Editor)
};


class UILayoutTest_Layout_Linear_Vertical_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Layout_Linear_Vertical_Editor();
    ~UILayoutTest_Layout_Linear_Vertical_Editor();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
    bool init();
    
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Layout_Linear_Vertical_Editor)
};


class UILayoutTest_Layout_Linear_Horizontal_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Layout_Linear_Horizontal_Editor();
    ~UILayoutTest_Layout_Linear_Horizontal_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Layout_Linear_Horizontal_Editor)
};


class UILayoutTest_Layout_Relative_Align_Parent_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Layout_Relative_Align_Parent_Editor();
    ~UILayoutTest_Layout_Relative_Align_Parent_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Layout_Relative_Align_Parent_Editor)
};


class UILayoutTest_Layout_Relative_Location_Editor : public UIScene_Editor
{
public:
    UILayoutTest_Layout_Relative_Location_Editor();
    ~UILayoutTest_Layout_Relative_Location_Editor();
    bool init();
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutTest_Layout_Relative_Location_Editor)
};

class UILayoutComponentTest_Editor : public UIScene_Editor
{
public:
    UILayoutComponentTest_Editor();
    ~UILayoutComponentTest_Editor();
    virtual bool init();
    void configureGUIScene();
protected:
    LayerColor* _baseLayer;
    UI_SCENE_EDITOR_CREATE_FUNC(UILayoutComponentTest_Editor)
};

#endif /* defined(__TestCpp__UILayoutTest_Editor__) */
