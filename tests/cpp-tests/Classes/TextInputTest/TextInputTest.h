#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../testBasic.h"
#include "../BaseTest.h"

class KeyboardNotificationLayer;

DEFINE_TEST_SUITE(TextInputTests);

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public TestCase, public IMEDelegate
{
public:
    KeyboardNotificationLayer();
    virtual std::string title() const override;
    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);

    bool onTouchBegan(Touch  *touch, Event  *event);
    void onTouchEnded(Touch  *touch, Event  *event);

protected:
    Node * _trackNode;
    Vec2  _beginPos;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    CREATE_FUNC(TextFieldTTFDefaultTest);
    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked) override;

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
    CREATE_FUNC(TextFieldTTFActionTest);
    void callbackRemoveNodeWhenDidAction(Node * node);

    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked) override;

    // Layer
    virtual void onEnter() override;
    virtual void onExit() override;

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender) override;
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender) override;
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen) override;
    virtual bool onDraw(TextFieldTTF * sender);
};

#endif    // __TEXT_INPUT_TEST_H__
