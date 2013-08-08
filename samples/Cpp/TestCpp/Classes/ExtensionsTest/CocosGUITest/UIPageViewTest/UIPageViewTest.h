

#ifndef __TestCpp__UIPageViewTest__
#define __TestCpp__UIPageViewTest__

#include "../UIScene.h"

class UIPageViewTest : public UIScene
{
public:
    UIPageViewTest();
    ~UIPageViewTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIPageViewTest)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIPageViewTest__) */
