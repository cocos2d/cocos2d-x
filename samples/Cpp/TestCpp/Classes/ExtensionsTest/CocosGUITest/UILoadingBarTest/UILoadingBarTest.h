

#ifndef __TestCpp__UILoadingBarTest__
#define __TestCpp__UILoadingBarTest__

#include "../UIScene.h"

class UILoadingBarTest : public UIScene
{
public:
    UILoadingBarTest();
    ~UILoadingBarTest();
    bool init();
    void update(float delta);
    
protected:
    UI_SCENE_CREATE_FUNC(UILoadingBarTest)
    int m_nCount;
};

#endif /* defined(__TestCpp__UILoadingBarTest__) */
