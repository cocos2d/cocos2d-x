

#ifndef __TestCpp__UITextButtonTest__
#define __TestCpp__UITextButtonTest__

#include "../UIScene.h"

class UITextButtonTest : public UIScene
{
public:
    UITextButtonTest();
    ~UITextButtonTest();
    bool init();
    void touchBeganEvent(CCObject *pSender);
    void touchMovedEvent(CCObject *pSender);
    void touchEndedEvent(CCObject *pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextButtonTest)
    UILabel* m_pDisplayValueLabel;
};

class UITextButtonTest_Scale9 : public UIScene
{
public:
    UITextButtonTest_Scale9();
    ~UITextButtonTest_Scale9();
    bool init();
    void touchBeganEvent(CCObject *pSender);
    void touchMovedEvent(CCObject *pSender);
    void touchEndedEvent(CCObject *pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextButtonTest_Scale9)
//    CC_SYNTHESIZE_RETAIN(CCLabelTTF *, m_pDisplayValueLabel, DisplayValueLabel)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UITextButtonTest__) */
