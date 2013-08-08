

#ifndef __TestCpp__UIButtonTest__
#define __TestCpp__UIButtonTest__

#include "../UIScene.h"

class UIButtonTest : public UIScene
{
public:
    UIButtonTest();
    ~UIButtonTest();
    bool init();
    void touchBeganEvent(CCObject *pSender);
    void touchMovedEvent(CCObject *pSender);
    void touchEndedEvent(CCObject *pSender);

protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest)
    UILabel* m_pDisplayValueLabel;
};

class UIButtonTest_Scale9 : public UIScene
{
public:
    UIButtonTest_Scale9();
    ~UIButtonTest_Scale9();
    bool init();
    void touchBeganEvent(CCObject *pSender);
    void touchMovedEvent(CCObject *pSender);
    void touchEndedEvent(CCObject *pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIButtonTest_Scale9)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIButtonTest__) */
