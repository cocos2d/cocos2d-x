

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
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest_Right_Scale9)
    int m_nCount;
};

#endif /* defined(__TestCpp__UILoadingBarTest__) */
