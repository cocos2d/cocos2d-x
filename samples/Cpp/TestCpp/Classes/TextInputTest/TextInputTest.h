#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

class KeyboardNotificationLayer;

/**
@brief    TextInputTest for retain prev, reset, next, main menu buttons.
*/
class TextInputTest : public BaseTest
{
    KeyboardNotificationLayer * _notificationLayer;
public:
    TextInputTest();

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);

    std::string title();
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * pLayer);
    
    virtual void onEnter();
};

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public Layer, public IMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

    // Layer
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);

protected:
    Node * _trackNode;
    Point  _beginPos;
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

    // Layer
    virtual void onEnter();
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFActionTest : public KeyboardNotificationLayer, public TextFieldDelegate
{
    TextFieldTTF *    _textField;
    Action *          _textFieldAction;
    bool                _action;
    int                 _charLimit;       // the textfield max char limit

public:
    void callbackRemoveNodeWhenDidAction(Node * pNode);

    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);

    // Layer
    virtual void onEnter();
    virtual void onExit();

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onDraw(TextFieldTTF * pSender);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif    // __TEXT_INPUT_TEST_H__
