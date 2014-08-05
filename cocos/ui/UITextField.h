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
#include "2d/CCTextFieldTTF.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN

namespace ui {

/**
 *  @js NA
 *  @lua NA
 */
class CC_GUI_DLL UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter() override;
    
    // static
    static UICCTextField* create(const std::string& placeholder, const std::string& fontName, float fontSize);
    
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
    bool isMaxLengthEnabled()const;
    void setMaxLength(int length);
    int getMaxLength()const;
    int getCharCount()const;
    
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled()const;
    void setPasswordStyleText(const std::string& styleText);
    void setPasswordText(const std::string& text);
    
    void setAttachWithIME(bool attach);
    bool getAttachWithIME()const;
    void setDetachWithIME(bool detach);
    bool getDetachWithIME()const;
    
    void setInsertText(bool insert);
    bool getInsertText()const;
    
    void setDeleteBackward(bool deleteBackward);
    bool getDeleteBackward()const;
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
class CC_GUI_DLL TextField : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class EventType
    {
        ATTACH_WITH_IME,
        DETACH_WITH_IME,
        INSERT_TEXT,
        DELETE_BACKWARD,
    };
    typedef std::function<void(Ref*, EventType)> ccTextFieldCallback;
    
    TextField();
    virtual ~TextField();
    static TextField* create();
    static TextField* create(const std::string& placeholder,
                             const std::string& fontName,
                             int fontSize);
    void setTouchSize(const Size &size);
    Size getTouchSize()const;
    void setTouchAreaEnabled(bool enable);
    virtual bool hitTest(const Vec2 &pt);
    
    void setPlaceHolder(const std::string& value);
    const std::string& getPlaceHolder()const;
    
    void setFontSize(int size);
    int getFontSize()const;
    void setFontName(const std::string& name);
    const std::string& getFontName()const;
    
    virtual void didNotSelectSelf();
    
    void setText(const std::string& text);
    const std::string& getStringValue()const;
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    
    void setMaxLengthEnabled(bool enable);
    bool isMaxLengthEnabled()const;
    void setMaxLength(int length);

    int getMaxLength()const;
    int getStringLength() const;
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled()const;
    void setPasswordStyleText(const char* styleText);
    const char* getPasswordStyleText()const;
    
    virtual void update(float dt) override;
    
    bool getAttachWithIME()const;
    void setAttachWithIME(bool attach);
    bool getDetachWithIME()const;
    void setDetachWithIME(bool detach);
    
    bool getInsertText()const;
    void setInsertText(bool insertText);
    
    bool getDeleteBackward()const;
    void setDeleteBackward(bool deleteBackward);
    
    CC_DEPRECATED_ATTRIBUTE void addEventListenerTextField(Ref* target, SEL_TextFieldEvent selecor);
    void addEventListener(const ccTextFieldCallback& callback);
    
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
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_TextFieldEvent _textFieldEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccTextFieldCallback _eventCallback;
    
    std::string _passwordStyleText;
    bool _textFieldRendererAdaptDirty;
private:
    enum class FontType
    {
        SYSTEM,
        TTF
    };

    std::string _fontName;
    int _fontSize;
    FontType _fontType;
};

}

NS_CC_END

#endif /* defined(__TextField__) */
