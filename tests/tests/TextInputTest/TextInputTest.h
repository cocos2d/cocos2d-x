#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../testBasic.h"

class KeyboardNotificationLayer;

/**
@brief    TextInputTest for retain prev, reset, next, main menu buttons.
*/
class TextInputTest : public CCLayer
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
};

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    // CCLayer
    virtual void onEnter();
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFActionTest : public KeyboardNotificationLayer, public CCTextFieldDelegate
{
    CCTextFieldTTF *    m_pTextField;
    CCAction *          m_pTextFieldAction;
    bool                m_bAction;
    int                 m_nCharLimit;       // the textfield max char limit

public:
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);

    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    // CCLayer
    virtual void onEnter();
    virtual void onExit();

    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onDraw(CCTextFieldTTF * pSender);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif    // __TEXT_INPUT_TEST_H__
