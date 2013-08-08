

#ifndef __TestCpp__UITextFieldTest__
#define __TestCpp__UITextFieldTest__

#include "../UIScene.h"

class UITextFieldTest : public UIScene
{
public:
    UITextFieldTest();
    ~UITextFieldTest();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest)
    UILabel* m_pDisplayValueLabel;
};

class UITextFieldTest_MaxLength : public UIScene
{
public:
    UITextFieldTest_MaxLength();
    ~UITextFieldTest_MaxLength();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest_MaxLength)
    UILabel* m_pDisplayValueLabel;
};

class UITextFieldTest_Password : public UIScene
{
public:
    UITextFieldTest_Password();
    ~UITextFieldTest_Password();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest_Password)
    UILabel* m_pDisplayValueLabel;
};
#endif /* defined(__TestCpp__UITextFieldTest__) */
