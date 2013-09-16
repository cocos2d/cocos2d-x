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


NS_CC_EXT_BEGIN

class UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    UICCTextField();
    ~UICCTextField();
    
    virtual void onEnter();
    
    // static
    static UICCTextField* create(const char *placeholder, const char *fontName, float fontSize);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender);
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, int nLen);
    
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


typedef void (Object::*SEL_TextFieldAttachWithIMEEvent)(Object*);
#define coco_TextField_AttachWithIME_selector(_SELECTOR) (SEL_TextFieldAttachWithIMEEvent)(&_SELECTOR)
typedef void (Object::*SEL_TextFieldDetachWithIMEEvent)(Object*);
#define coco_TextField_DetachWithIME_selector(_SELECTOR) (SEL_TextFieldDetachWithIMEEvent)(&_SELECTOR)
typedef void (Object::*SEL_TextFieldInsertTextEvent)(Object*);
#define coco_TextField_InsertText_selector(_SELECTOR) (SEL_TextFieldInsertTextEvent)(&_SELECTOR)
typedef void (Object::*SEL_TextFieldDeleteBackwardEvent)(Object*);
#define coco_TextField_DeleteBackward_selector(_SELECTOR) (SEL_TextFieldDeleteBackwardEvent)(&_SELECTOR)

//class UITextField : public UIWidget
class UITextField : public UIWidget
{
public:
    UITextField();
    virtual ~UITextField();
    static UITextField* create();
    virtual bool init();
    virtual void initRenderer();
    void setTouchSize(const Size &size);
    void setText(const char* text);
    void setPlaceHolder(const char* value);
    void setFontSize(int size);
    void setFontName(const char* name);
    virtual void didNotSelectSelf();
    const char* getStringValue();
    virtual bool onTouchBegan(const Point &touchPoint);
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
    void addAttachWithIMEEvent(Object* target, SEL_TextFieldAttachWithIMEEvent selecor);
    void addDetachWithIMEEvent(Object* target, SEL_TextFieldDetachWithIMEEvent selecor);
    void addInsertTextEvent(Object* target, SEL_TextFieldInsertTextEvent selecor);
    void addDeleteBackwardEvent(Object* target, SEL_TextFieldDeleteBackwardEvent selecor);
    virtual void setAnchorPoint(const Point &pt);
    virtual void setColor(const Color3B &color);
    virtual void setOpacity(int opacity);
    
    /*compatibel*/
    /**
     * These methods will be removed
     */
    void setMaxLengthEnable(bool is){setMaxLengthEnabled(is);};
    void setPasswordEnable(bool is){setPasswordEnabled(is);};
    /************/
    virtual const Size& getContentSize() const;
    virtual Node* getVirtualRenderer();
protected:
    // event
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged();
    void textfieldRendererScaleChangedWithSize();
protected:
    float m_fTouchWidth;
    float m_fTouchHeight;
    bool m_bUseTouchArea;
    
    Object* m_pAttachWithIMEListener;
    Object* m_pDetachWithIMEListener;
    Object* m_pInsertTextListener;
    Object* m_pDeleteBackwardListener;
    
    SEL_TextFieldAttachWithIMEEvent m_pfnAttachWithIMESelector;
    SEL_TextFieldDetachWithIMEEvent m_pfnDetachWithIMESelector;
    SEL_TextFieldInsertTextEvent m_pfnInsertTextSelector;
    SEL_TextFieldDeleteBackwardEvent m_pfnDeleteBackwardSelector;
    
    UICCTextField* m_pTextFieldRenderer;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UITextField__) */
