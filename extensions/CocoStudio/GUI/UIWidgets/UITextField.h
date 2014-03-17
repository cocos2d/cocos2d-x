/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "../BaseClasses/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
 *  @js NA
 *  @lua NA
 */
class UICCTextField: public CCTextFieldTTF, public CCTextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter();
    
    // static
    static UICCTextField* create(const char *placeholder, const char *fontName, float fontSize);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    
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

typedef void (CCObject::*SEL_TextFieldEvent)(CCObject*, TextFiledEventType);
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
    void setTouchSize(const CCSize &size);
    CCSize getTouchSize();
    void setTouchAreaEnabled(bool enable);
    virtual bool hitTest(const CCPoint &pt);
    void setText(const std::string& text);
    void setPlaceHolder(const std::string& value);
    const char* getPlaceHolder();
    void setFontSize(int size);
    int getFontSize();
    void setFontName(const std::string& name);
    const char* getFontName();
    virtual void didNotSelectSelf();
    const char* getStringValue();
    virtual bool onTouchBegan(CCTouch *touch, CCEvent *unused_event);
    void setMaxLengthEnabled(bool enable);
    bool isMaxLengthEnabled();
    void setMaxLength(int length);
    int getMaxLength();
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled();
    void setPasswordStyleText(const char* styleText);
    const char* getPasswordStyleText();
    virtual void update(float dt);
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addEventListenerTextField(CCObject* target, SEL_TextFieldEvent selecor);

    virtual void setAnchorPoint(const CCPoint &pt);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;

    virtual const CCSize& getContentSize() const;
    virtual CCNode* getVirtualRenderer();
    void attachWithIME();
    virtual void onEnter();
    
    void setTextAreaSize(const CCSize &size);
    void setTextHorizontalAlignment(CCTextAlignment alignment);
    void setTextVerticalAlignment(CCVerticalTextAlignment alignment);
    /*=*/
    
protected:
    virtual bool init();
    virtual void initRenderer();
    // event
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged();
    virtual void updateTextureColor();
    virtual void updateTextureOpacity();
    virtual void updateTextureRGBA();
    void textfieldRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
protected:
    UICCTextField* _textFieldRenderer;

    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    CCObject* _textFieldEventListener;
    SEL_TextFieldEvent _textFieldEventSelector;
    
    std::string _passwordStyleText;
};

}

NS_CC_END

#endif /* defined(__TextField__) */
