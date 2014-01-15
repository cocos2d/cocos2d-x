/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UITEXTFIELD_H__
#define __UITEXTFIELD_H__

#include "gui/UIWidget.h"

NS_CC_BEGIN

namespace gui {

/**
 *  @js NA
 *  @lua NA
 */
class UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter();
    
    // static
    static UICCTextField* create(const char *placeholder, const char *fontName, float fontSize);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender) override;
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender, const char * text, int nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, int nLen) override;
    
    void insertText(const char* text, int len);
    void deleteBackward();
    
    void openIME();
    void closeIME();
    
    void setMaxLengthEnabled(bool enable);
    bool isMaxLengthEnabled();
    void setMaxLength(int length);
    int getMaxLength();
    int getCharCount();
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled();
    void setPasswordStyleText(const char* styleText);
    void setPasswordText(const char* text);
    void setAttachWithIME(bool attach);
    bool getAttachWithIME();
    void setDetachWithIME(bool detach);
    bool getDetachWithIME();
    void setInsertText(bool insert);
    bool getInsertText();
    void setDeleteBackward(bool deleteBackward);
    bool getDeleteBackward();
protected:
    bool _maxLengthEnabled;
    int _maxLength;
    bool _passwordEnabled;
    std::string _passwordStyleText;
    bool _attachWithIME;
    bool _detachWithIME;
    bool _insertText;
    bool _deleteBackward;
};

typedef enum
{
    TEXTFIELD_EVENT_ATTACH_WITH_IME,
    TEXTFIELD_EVENT_DETACH_WITH_IME,
    TEXTFIELD_EVENT_INSERT_TEXT,
    TEXTFIELD_EVENT_DELETE_BACKWARD,
}TextFiledEventType;

typedef void (Object::*SEL_TextFieldEvent)(Object*, TextFiledEventType);
#define textfieldeventselector(_SELECTOR) (SEL_TextFieldEvent)(&_SELECTOR)

/** class UITextField : public Widget
*   @js NA
*   @lua NA
*/
class TextField : public Widget
{
public:
    TextField();
    virtual ~TextField();
    static TextField* create();
    void setTouchSize(const Size &size);
    void setText(const std::string& text);
    void setPlaceHolder(const std::string& value);
    void setFontSize(int size);
    void setFontName(const std::string& name);
    virtual void didNotSelectSelf();
    const std::string& getStringValue();
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    void setMaxLengthEnabled(bool enable);
    bool isMaxLengthEnabled();
    void setMaxLength(int length);
    int getMaxLength();
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled();
    void setPasswordStyleText(const char* styleText);
    virtual void update(float dt) override;
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addEventListenerTextField(Object* target, SEL_TextFieldEvent selecor);

    virtual void setAnchorPoint(const Point &pt) override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    virtual const Size& getContentSize() const override;
    virtual Node* getVirtualRenderer() override;
    void attachWithIME();
    virtual void onEnter() override;
protected:
    // event
    virtual void initRenderer() override;
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged() override;
    void textfieldRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    UICCTextField* _textFieldRenderer;

    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    Object* _textFieldEventListener;
    SEL_TextFieldEvent _textFieldEventSelector;
    
    std::string _passwordStyleText;
};

}

NS_CC_END

#endif /* defined(__TextField__) */
