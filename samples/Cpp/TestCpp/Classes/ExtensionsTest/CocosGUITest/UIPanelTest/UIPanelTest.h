

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
