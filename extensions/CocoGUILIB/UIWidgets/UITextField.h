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
#include "../Drawable/UICCTextField.h"


NS_CC_EXT_BEGIN

typedef void (CCObject::*SEL_TextFieldAttachWithIMEEvent)(CCObject*);
#define coco_TextField_AttachWithIME_selector(_SELECTOR) (SEL_TextFieldAttachWithIMEEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_TextFieldDetachWithIMEEvent)(CCObject*);
#define coco_TextField_DetachWithIME_selector(_SELECTOR) (SEL_TextFieldDetachWithIMEEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_TextFieldInsertTextEvent)(CCObject*);
#define coco_TextField_InsertText_selector(_SELECTOR) (SEL_TextFieldInsertTextEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_TextFieldDeleteBackwardEvent)(CCObject*);
#define coco_TextField_DeleteBackward_selector(_SELECTOR) (SEL_TextFieldDeleteBackwardEvent)(&_SELECTOR)

//class UITextField : public UIWidget
class UITextField : public UIWidget
{
public:
    UITextField();
    virtual ~UITextField();
    static UITextField* create();
    virtual bool init();
    virtual void initNodes();
    void setTouchSize(const CCSize &size);
    void setText(const char* text);
    //void setSize(const CCSize &size);
    void setPlaceHolder(const char* value);
    void setFontSize(int size);
    void setFontName(const char* name);
    virtual void didNotSelectSelf();
    const char* getStringValue();
    virtual void onTouchBegan(const CCPoint &touchPoint);
    virtual bool pointAtSelfBody(const CCPoint &pt);
    void setMaxLengthEnable(bool enable);
    bool isMaxLengthEnable();
    void setMaxLength(int length);
    int getMaxLength();
    void setPasswordEnable(bool enable);
    bool isPasswordEnable();
    void setPasswordStyleText(const char* styleText);
    void update(float dt);
    bool getAttachWithIME();
    void setAttachWithIME(bool attach);
    bool getDetachWithIME();
    void setDetachWithIME(bool detach);
    bool getInsertText();
    void setInsertText(bool insertText);
    bool getDeleteBackward();
    void setDeleteBackward(bool deleteBackward);
    void addAttachWithIMEEvent(CCObject* target, SEL_TextFieldAttachWithIMEEvent selecor);
    void addDetachWithIMEEvent(CCObject* target, SEL_TextFieldDetachWithIMEEvent selecor);
    void addInsertTextEvent(CCObject* target, SEL_TextFieldInsertTextEvent selecor);
    void addDeleteBackwardEvent(CCObject* target, SEL_TextFieldDeleteBackwardEvent selecor);
    virtual CCNode* getValidNode();
    virtual void setAnchorPoint(const CCPoint &pt);
    virtual void setColor(const ccColor3B &color);
    virtual void setOpacity(int opacity);
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
    
    CCObject* m_pAttachWithIMEListener;
    CCObject* m_pDetachWithIMEListener;
    CCObject* m_pInsertTextListener;
    CCObject* m_pDeleteBackwardListener;
    
    SEL_TextFieldAttachWithIMEEvent m_pfnAttachWithIMESelector;
    SEL_TextFieldDetachWithIMEEvent m_pfnDetachWithIMESelector;
    SEL_TextFieldInsertTextEvent m_pfnInsertTextSelector;
    SEL_TextFieldDeleteBackwardEvent m_pfnDeleteBackwardSelector;
    
    UICCTextField* m_pRenderTextField;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UITextField__) */
