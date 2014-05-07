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

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    virtual std::string title() const;
    void addKeyboardNotificationLayer(KeyboardNotificationLayer * layer);
    
    virtual void onEnter() override;
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
    Vector2  _beginPos;
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
    virtual void onEnter() override;
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
    virtual void onEnter() override;
    virtual void onExit() override;

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender);
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen) override;
    virtual bool onDraw(TextFieldTTF * sender);
};

class TextInputTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif    // __TEXT_INPUT_TEST_H__
