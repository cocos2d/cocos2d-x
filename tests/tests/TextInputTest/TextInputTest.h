#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../testBasic.h"

class KeyboardNotificationLayer;

class TextInputTest : public CCLayer, public CCIMEDelegate
{
    KeyboardNotificationLayer * m_pNotificationLayer;
public:
    TextInputTest();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    std::string title();
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * pLayer);
    
    virtual void onEnter();
    virtual void onExit();
};

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle();
    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

protected:
    CCNode * m_pTrackNode;
};

class TextFieldTTFTest : public KeyboardNotificationLayer, public CCTextFieldDelegate
{
    CCPoint             m_beginPos;
    CCTextFieldTTF *    m_pTextField[2];
    CCAction *          m_pTextFieldAction;
    bool                m_bAction;
    int                 m_nSelected;
    int                 m_nCharLimit;       // the textfield max char limit

public:
    virtual std::string subtitle();

    // CCLayer
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onDraw(CCTextFieldTTF * pSender);

    void callbackRemoveNodeWhenDidAction(CCNode * pNode);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif	// __TEXT_INPUT_TEST_H__