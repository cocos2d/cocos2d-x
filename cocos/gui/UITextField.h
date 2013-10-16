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

#include "gui/UIWidget.h"


namespace gui {

class UICCTextField: public cocos2d::TextFieldTTF, public cocos2d::TextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter();
    
    // static
    static UICCTextField* create(const char *placeholder, const char *fontName, float fontSize);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF *pSender);
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF * pSender, const char * delText, int nLen);
    
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
    bool m_bMaxLengthEnabled;
    int m_nMaxLength;
    bool m_bPasswordEnabled;
    std::string m_strPasswordStyleText;
    bool m_bAttachWithIME;
    bool m_bDetachWithIME;
    bool m_bInsertText;
    bool m_bDeleteBackward;
};


typedef enum
{
    TEXTFIELD_EVENT_ATTACH_WITH_IME,
    TEXTFIELD_EVENT_DETACH_WITH_IME,
    TEXTFIELD_EVENT_INDERT_TEXT,
    TEXTFIELD_EVENT_DELETE_BACKWARD,
}TextFiledEventType;

typedef void (cocos2d::Object::*SEL_TextFieldEvent)(cocos2d::Object*, TextFiledEventType);
#define textfieldeventselector(_SELECTOR) (SEL_TextFieldEvent)(&_SELECTOR)

//class UITextField : public UIWidget
class UITextField : public UIWidget
{
public:
    UITextField();
    virtual ~UITextField();
    static UITextField* create();
    virtual bool init();
    virtual void initRenderer();
    void setTouchSize(const cocos2d::Size &size);
    void setText(const char* text);
    void setPlaceHolder(const char* value);
    void setFontSize(int size);
    void setFontName(const char* name);
    virtual void didNotSelectSelf();
    const char* getStringValue();
    virtual bool onTouchBegan(const cocos2d::Point &touchPoint);
    void setMaxLengthEnabled(bool enable);
    bool isMaxLengthEnabled();
    void setMaxLength(int length);
    int getMaxLength();
    void setPasswordEnabled(bool enable);
    bool isPasswordEnabled();
    void setPasswordStyleText(const char* styleText);
    virtual void update(float dt);
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addEventListener(cocos2d::Object* target, SEL_TextFieldEvent selecor);
    virtual void setAnchorPoint(const cocos2d::Point &pt);
    virtual void setColor(const cocos2d::Color3B &color);
    virtual void setOpacity(int opacity);
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    /*compatibel*/
    /**
     * These methods will be removed
     */
    void setMaxLengthEnable(bool is){setMaxLengthEnabled(is);};
    void setPasswordEnable(bool is){setPasswordEnabled(is);};
    /************/
    virtual const cocos2d::Size& getContentSize() const;
    virtual cocos2d::Node* getVirtualRenderer();
protected:
    // event
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged();
    void textfieldRendererScaleChangedWithSize();
protected:
    UICCTextField* _textFieldRenderer;
    
    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    cocos2d::Object* _eventListener;
    SEL_TextFieldEvent _eventSelector;
    
};

}

#endif /* defined(__CocoGUI__UITextField__) */
