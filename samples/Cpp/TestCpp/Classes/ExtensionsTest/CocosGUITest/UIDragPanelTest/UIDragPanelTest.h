

#ifndef __TestCpp__UIDragPanelTest__
#define __TestCpp__UIDragPanelTest__

#include "../UIScene.h"

class UIDragPanelTest : public UIScene
{
public:
    UIDragPanelTest();
    ~UIDragPanelTest();
    bool init();
    void berthToLeftBottomEvent(CCObject* pSender);
    void berthToLeftTopEvent(CCObject* pSender);
    void berthToRightBottomEvent(CCObject* pSender);
    void berthToRightTopEvent(CCObject* pSender);
    void berthToLeftEvent(CCObject* pSender);
    void berthToTopEvent(CCObject* pSender);
    void berthToRightEvent(CCObject* pSender);
    void berthToBottomEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIDragPanelTest)
    UILabel *m_pDisplayValueLabel;
};

class UIDragPanelTest_Bounce : public UIScene
{
public:
    UIDragPanelTest_Bounce();
    ~UIDragPanelTest_Bounce();
    bool init();
    void bounceToLeftBottomEvent(CCObject* pSender);
    void bounceToRightBottomEvent(CCObject* pSender);
    void bounceToLeftTopEvent(CCObject* pSender);
    void bounceToRightTopEvent(CCObject* pSender);
    void bounceToLeftEvent(CCObject* pSender);
    void bounceToTopEvent(CCObject* pSender);
    void bounceToRightEvent(CCObject* pSender);
    void bounceToBottomEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIDragPanelTest_Bounce)
    UILabel *m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIDragPanelTest__) */
