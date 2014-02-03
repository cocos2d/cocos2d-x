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

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);

    virtual std::string title() const;
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * layer);
    
    virtual void onEnter();
};

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public Layer, public IMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual std::string subtitle() const = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

    // Layer
    bool onTouchBegan(Touch  *touch, Event  *event);
    void onTouchEnded(Touch  *touch, Event  *event);

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
    virtual std::string subtitle() const override;
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
    void callbackRemoveNodeWhenDidAction(Node * node);

    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked);

    // Layer
    virtual void onEnter();
    virtual void onExit();

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, int nLen);
    virtual bool onDraw(TextFieldTTF * sender);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif    // __TEXT_INPUT_TEST_H__
