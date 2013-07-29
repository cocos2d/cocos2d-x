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

typedef void (cocos2d::Object::*SEL_TextFieldAttachWithIMEEvent)(cocos2d::Object*);
typedef void (cocos2d::Object::*SEL_TextFieldDetachWithIMEEvent)(cocos2d::Object*);
typedef void (cocos2d::Object::*SEL_TextFieldInsertTextEvent)(cocos2d::Object*);
typedef void (cocos2d::Object::*SEL_TextFieldDeleteBackwardEvent)(cocos2d::Object*);
#define coco_TextFieldAttachWithIMESelector(_SELECTOR) (SEL_TextFieldAttachWithIMEEvent)(&_SELECTOR)
#define coco_TextFieldDetachWithIMESelector(_SELECTOR) (SEL_TextFieldDetachWithIMEEvent)(&_SELECTOR)
#define coco_TextFieldInsertTextSelector(_SELECTOR) (SEL_TextFieldInsertTextEvent)(&_SELECTOR)
#define coco_TextFieldDeleteBackwardSelector(_SELECTOR) (SEL_TextFieldDeleteBackwardEvent)(&_SELECTOR)

class UITextField : public UIWidget
{
public:
    UITextField();
    virtual ~UITextField();
    static UITextField* create();
    virtual bool init();
    virtual void initNodes();
    void setTouchSize(const Size &size);
    void setText(const char* text);
    void setSize(const cocos2d::Size &size);
    void setPlaceHolder(const char* value);
    void setFontSize(int size);
    virtual void didNotSelectSelf();
    const char* getStringValue();
    virtual void onTouchBegan(cocos2d::Point &touchPoint);
    virtual bool pointAtSelfBody(cocos2d::Point &pt);
    void setCharacterLength(int length);
    void setIsPassWord(bool isPassword);
    void update(float dt);
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addAttachWithIMEEvent(cocos2d::Object* target, SEL_TextFieldAttachWithIMEEvent selecor);
    void addDetachWithIMEEvent(cocos2d::Object* target, SEL_TextFieldDetachWithIMEEvent selecor);
    void addInsertTextEvent(cocos2d::Object* target, SEL_TextFieldInsertTextEvent selecor);
    void addDeleteBackwardEvent(cocos2d::Object* target, SEL_TextFieldDeleteBackwardEvent selecor);
    virtual cocos2d::Node* getValidNode();
    virtual void setAnchorPoint(const cocos2d::Point &pt);
protected:
    // event
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
protected:
    float m_fTouchWidth;
    float m_fTouchHeight;
    bool m_bUseTouchArea;
    
    cocos2d::Object* m_pAttachWithIMEListener;
    cocos2d::Object* m_pDetachWithIMEListener;
    cocos2d::Object* m_pInsertTextListener;
    cocos2d::Object* m_pDeleteBackwardListener;
    
    SEL_TextFieldAttachWithIMEEvent m_pfnAttachWithIMESelector;
    SEL_TextFieldDetachWithIMEEvent m_pfnDetachWithIMESelector;
    SEL_TextFieldInsertTextEvent m_pfnInsertTextSelector;
    SEL_TextFieldDeleteBackwardEvent m_pfnDeleteBackwardSelector;
    
    TextFieldTTF * m_pRenderTextField;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UITextField__) */
