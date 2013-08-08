
#ifndef __TestCpp__UICheckBoxTest__
#define __TestCpp__UICheckBoxTest__

#include "../UIScene.h"

class UICheckBoxTest : public UIScene
{
public:
    UICheckBoxTest();
    ~UICheckBoxTest();
    bool init();
    void selectedEvent(CCObject* pSender);
    void unSelectedEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UICheckBoxTest)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UICheckBoxTest__) */
