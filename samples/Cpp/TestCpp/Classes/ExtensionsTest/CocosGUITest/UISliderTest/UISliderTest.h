

#ifndef __TestCpp__UISliderTest__
#define __TestCpp__UISliderTest__

#include "../UIScene.h"

class UISliderTest : public UIScene
{
public:
    UISliderTest();
    ~UISliderTest();
    bool init();
    void percentChangedEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UISliderTest)
    UILabel* m_pDisplayValueLabel;
};

class UISliderTest_Scale9 : public UIScene
{
public:
    UISliderTest_Scale9();
    ~UISliderTest_Scale9();
    bool init();
    void percentChangedEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UISliderTest_Scale9)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UISliderTest__) */
