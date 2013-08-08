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

#include "UITextField.h"

NS_CC_EXT_BEGIN
    
UITextField::UITextField():
m_fTouchWidth(0.0),
m_fTouchHeight(0.0),
m_bUseTouchArea(false),
m_pRenderTextField(NULL),
m_pAttachWithIMEListener(NULL),
m_pDetachWithIMEListener(NULL),
m_pInsertTextListener(NULL),
m_pDeleteBackwardListener(NULL),
m_pfnAttachWithIMESelector(NULL),
m_pfnDetachWithIMESelector(NULL),
m_pfnInsertTextSelector(NULL),
m_pfnDeleteBackwardSelector(NULL)
{
    m_WidgetName = WIDGET_TEXTFIELD;
}

UITextField::~UITextField()
{
    
}

UITextField* UITextField::create()
{
    UITextField* widget = new UITextField();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UITextField::init()
{
    if (UIWidget::init())
    {
        setUpdateEnable(true);
        return true;
    }
    return false;
}

void UITextField::initNodes()
{
    UIWidget::initNodes();
    m_pRenderTextField = UICCTextField::create("input words here", "Thonburi", 20);
    m_pRender->addChild(m_pRenderTextField);
}

void UITextField::setTouchSize(const CCSize &size)
{
    m_bUseTouchArea = true;
    m_fTouchWidth = size.width;
    m_fTouchHeight = size.height;
}

void UITextField::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pRenderTextField->setString(strText.c_str());
}

//void UITextField::setSize(const CCSize &size)
//{
//    m_pRenderTextField->setDimensions(size);
//}

void UITextField::setPlaceHolder(const char *value)
{
    m_pRenderTextField->setPlaceHolder(value);
}

void UITextField::setFontSize(int size)
{
    m_pRenderTextField->setFontSize(size);
}

void UITextField::setFontName(const char *name)
{
    m_pRenderTextField->setFontName(name);
}

void UITextField::didNotSelectSelf()
{
    m_pRenderTextField->detachWithIME();
}

const char* UITextField::getStringValue()
{
    return m_pRenderTextField->getString();
}

void UITextField::onTouchBegan(const CCPoint &touchPoint)
{
    UIWidget::onTouchBegan(touchPoint);
    m_pRenderTextField->attachWithIME();
}

bool UITextField::pointAtSelfBody(const CCPoint &pt)
{
    if (!m_bUseTouchArea){
        return UIWidget::pointAtSelfBody(pt);
    }
    if (!getAbsoluteVisible()) {
        return false;
    }
    return false;
}

void UITextField::setMaxLengthEnable(bool enable)
{
    m_pRenderTextField->setMaxLengthEnable(enable);
}

bool UITextField::isMaxLengthEnable()
{
    return m_pRenderTextField->isMaxLengthEnable();
}

void UITextField::setMaxLength(int length)
{
    m_pRenderTextField->setMaxLength(length);
}

int UITextField::getMaxLength()
{
    return m_pRenderTextField->getMaxLength();
}

void UITextField::setPasswordEnable(bool enable)
{
    m_pRenderTextField->setPasswordEnable(enable);
}

bool UITextField::isPasswordEnable()
{
    return m_pRenderTextField->isPasswordEnable();
}

void UITextField::setPasswordStyleText(const char *styleText)
{
    m_pRenderTextField->setPasswordStyleText(styleText);
}

void UITextField::update(float dt)
{
    if (getAttachWithIME())
    {
        attachWithIMEEvent();
        setAttachWithIME(false);
    }
    if (getDetachWithIME())
    {
        detachWithIMEEvent();
        setDetachWithIME(false);
    }
    if (getInsertText())
    {
        insertTextEvent();
        setInsertText(false);
    }
    if (getDeleteBackward())
    {
        deleteBackwardEvent();
        setDeleteBackward(false);
    }
}

bool UITextField::getAttachWithIME()
{
    return m_pRenderTextField->getAttachWithIME();
}

void UITextField::setAttachWithIME(bool attach)
{
    m_pRenderTextField->setAttachWithIME(attach);
}

bool UITextField::getDetachWithIME()
{
    return m_pRenderTextField->getDetachWithIME();
}

void UITextField::setDetachWithIME(bool detach)
{
    m_pRenderTextField->setDetachWithIME(detach);
}

bool UITextField::getInsertText()
{
    return m_pRenderTextField->getInsertText();
}

void UITextField::setInsertText(bool insertText)
{
    m_pRenderTextField->setInsertText(insertText);
}

bool UITextField::getDeleteBackward()
{
    return m_pRenderTextField->getDeleteBackward();
}

void UITextField::setDeleteBackward(bool deleteBackward)
{
    m_pRenderTextField->setDeleteBackward(deleteBackward);
}

void UITextField::attachWithIMEEvent()
{
    if (m_pAttachWithIMEListener && m_pfnAttachWithIMESelector)
    {
        (m_pAttachWithIMEListener->*m_pfnAttachWithIMESelector)(this);
    }
}

void UITextField::detachWithIMEEvent()
{
    if (m_pDetachWithIMEListener && m_pfnDetachWithIMESelector)
    {
        (m_pDetachWithIMEListener->*m_pfnDetachWithIMESelector)(this);
    }
}

void UITextField::insertTextEvent()
{
    if (m_pInsertTextListener && m_pfnInsertTextSelector)
    {
        (m_pInsertTextListener->*m_pfnInsertTextSelector)(this);
    }
}

void UITextField::deleteBackwardEvent()
{
    if (m_pDeleteBackwardListener && m_pfnDeleteBackwardSelector)
    {
        (m_pDeleteBackwardListener->*m_pfnDeleteBackwardSelector)(this);
    }
}

void UITextField::addAttachWithIMEEvent(CCObject *target, SEL_TextFieldAttachWithIMEEvent selecor)
{
    m_pAttachWithIMEListener = target;
    m_pfnAttachWithIMESelector = selecor;
}

void UITextField::addDetachWithIMEEvent(CCObject *target, SEL_TextFieldDetachWithIMEEvent selecor)
{
    m_pDetachWithIMEListener = target;
    m_pfnDetachWithIMESelector = selecor;
}

void UITextField::addInsertTextEvent(CCObject *target, SEL_TextFieldInsertTextEvent selecor)
{
    m_pInsertTextListener = target;
    m_pfnInsertTextSelector = selecor;
}

void UITextField::addDeleteBackwardEvent(CCObject *target, SEL_TextFieldDeleteBackwardEvent selecor)
{
    m_pDeleteBackwardListener = target;
    m_pfnDeleteBackwardSelector = selecor;
}

CCNode* UITextField::getValidNode()
{
    return m_pRenderTextField;
}

void UITextField::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pRenderTextField->setAnchorPoint(pt);
}

void UITextField::setColor(const ccColor3B &color)
{
    UIWidget::setColor(color);
    m_pRenderTextField->setColor(color);
}

void UITextField::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    m_pRenderTextField->setOpacity(opacity);
}

NS_CC_EXT_END