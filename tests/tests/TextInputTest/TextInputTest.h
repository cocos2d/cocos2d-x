#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../testBasic.h"

class TextInputTest : public CCLayer, public CCIMEDelegate
{
public:
    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    virtual std::string title();
    virtual std::string subtitle();

    virtual void onEnter();
};

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

protected:
    CCNode * m_pTrackNode;
};

class TextFieldTTFTest : public KeyboardNotificationLayer
{
    CCPoint             m_beginPos;
    CCTextFieldTTF *    m_pTextField[2];
    int                 m_nSelected;
public:
    TextFieldTTFTest();

    virtual std::string subtitle();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif	// __TEXT_INPUT_TEST_H__