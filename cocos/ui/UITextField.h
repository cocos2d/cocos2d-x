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

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
 *  @js NA
 *  @lua NA
 */
class UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter() override;
    
    // static
    static UICCTextField* create(const char *placeholder, const char *fontName, float fontSize);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender) override;
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender, const char * text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, size_t nLen) override;
    
    void insertText(const char* text, size_t len);
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

typedef void (Ref::*SEL_TextFieldEvent)(Ref*, TextFiledEventType);
#define textfieldeventselector(_SELECTOR) (SEL_TextFieldEvent)(&_SELECTOR)

/** class UITextField : public Widget
*   @js NA
*   @lua NA
*/
class TextField : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    TextField();
    virtual ~TextField();
    static TextField* create();
    static TextField* create(const std::string& placeholder,
                             const std::string& fontName,
                             int fontSize);
    void setTouchSize(const Size &size);
    Size getTouchSize();
    void setTouchAreaEnabled(bool enable);
    virtual bool hitTest(const Vector2 &pt);
    void setText(const std::string& text);
    void setPlaceHolder(const std::string& value);
    const std::string& getPlaceHolder();
    void setFontSize(int size);
    int getFontSize();
    void setFontName(const std::string& name);
    const std::string& getFontName();
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
    const char* getPasswordStyleText();
    virtual void update(float dt) override;
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addEventListenerTextField(Ref* target, SEL_TextFieldEvent selecor);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    virtual const Size& getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    void attachWithIME();
    virtual void onEnter() override;
    
    void setTextAreaSize(const Size &size);
    void setTextHorizontalAlignment(TextHAlignment alignment);
    void setTextVerticalAlignment(TextVAlignment alignment);
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void initRenderer() override;
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void textfieldRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    UICCTextField* _textFieldRenderer;

    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    Ref* _textFieldEventListener;
    SEL_TextFieldEvent _textFieldEventSelector;
    
    std::string _passwordStyleText;
    bool _textFieldRendererAdaptDirty;
};

}

NS_CC_END

#endif /* defined(__TextField__) */
