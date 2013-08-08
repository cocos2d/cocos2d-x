
#ifndef __TestCpp__UIImageViewTest__
#define __TestCpp__UIImageViewTest__

#include "../UIScene.h"

class UIImageViewTest : public UIScene
{
public:
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIImageViewTest)
};

class UIImageViewTest_Scale9 : public UIScene
{
public:    
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIImageViewTest_Scale9)
};

#endif /* defined(__TestCpp__UIImageViewTest__) */
