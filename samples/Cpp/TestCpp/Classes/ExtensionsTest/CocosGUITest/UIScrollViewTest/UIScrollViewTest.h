

#ifndef __TestCpp__UIScrollViewTest__
#define __TestCpp__UIScrollViewTest__

#include "../UIScene.h"

class UIScrollViewTest_Vertical : public UIScene
{
public:
    UIScrollViewTest_Vertical();
    ~UIScrollViewTest_Vertical();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_Vertical)
    UILabel* m_pDisplayValueLabel;
};

class UIScrollViewTest_Horizontal : public UIScene
{
public:
    UIScrollViewTest_Horizontal();
    ~UIScrollViewTest_Horizontal();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScrollViewTest_Horizontal)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIScrollViewTest__) */
