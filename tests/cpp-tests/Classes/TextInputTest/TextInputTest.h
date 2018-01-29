/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TEXT_INPUT_TEST_H__
#define __TEXT_INPUT_TEST_H__

#include "../BaseTest.h"

class KeyboardNotificationLayer;

DEFINE_TEST_SUITE(TextInputTests);

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public TestCase, public cocos2d::IMEDelegate
{
public:
    KeyboardNotificationLayer();
    virtual std::string title() const override;
    virtual void onClickTrackNode(bool bClicked, const cocos2d::Vec2& touchPos) = 0;

    virtual void keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo& info)override;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

protected:
    cocos2d::Node*  _trackNode;
    cocos2d::Vec2  _beginPos;
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
    virtual void onClickTrackNode(bool bClicked, const cocos2d::Vec2& touchPos) override;

    // Layer
    virtual void onEnter() override;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFActionTest : public KeyboardNotificationLayer, public cocos2d::TextFieldDelegate
{
    cocos2d::TextFieldTTF*    _textField;
    cocos2d::Action*          _textFieldAction;
    bool                _action;
    size_t              _charLimit;       // the textfield max char limit

public:
    CREATE_FUNC(TextFieldTTFActionTest);
    void callbackRemoveNodeWhenDidAction(Node * node);

    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked, const cocos2d::Vec2& touchPos) override;

    // Layer
    virtual void onEnter() override;
    virtual void onExit() override;

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF*  sender) override;
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF*  sender) override;
    virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF*  sender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF*  sender, const char * delText, size_t nLen) override;
    virtual bool onDraw(cocos2d::TextFieldTTF*  sender);
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFSecureTextEntryTest for test TextFieldTTF SecureTextEntry.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFSecureTextEntryTest : public TextFieldTTFDefaultTest
{
public:
    CREATE_FUNC(TextFieldTTFSecureTextEntryTest);
    
    virtual std::string subtitle() const override;
    // Layer
    virtual void onEnter() override;
};

//////////////////////////////////////////////////////////////////////////
// TextFieldTTSetCursorFromPoint for test TextFieldTTF setCursorFromPoint.
//////////////////////////////////////////////////////////////////////////

class TextFieldTTSetCursorFromPoint : public KeyboardNotificationLayer
{
public:
    CREATE_FUNC(TextFieldTTSetCursorFromPoint);
    // KeyboardNotificationLayer
    virtual std::string subtitle() const override;
    virtual void onClickTrackNode(bool bClicked, const cocos2d::Vec2& touchPos) override;

    // Layer
    virtual void onEnter() override;
};
#endif    // __TEXT_INPUT_TEST_H__
