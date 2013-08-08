

#ifndef __TestCpp__UIControlButtonTest__
#define __TestCpp__UIControlButtonTest__

#include "../UIScene.h"

class UIZoomButtonTest : public UIScene
{
public:
    UIZoomButtonTest();
    ~UIZoomButtonTest();
    bool init();    
    void touchBeganEvent(CCObject *pSender);
    void touchMovedEvent(CCObject *pSender);
    void touchEndedEvent(CCObject *pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIZoomButtonTest)
//    CC_SYNTHESIZE_RETAIN(CCLabelTTF *, m_pDisplayValueLabel, DisplayValueLabel)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIControlButtonTest__) */
