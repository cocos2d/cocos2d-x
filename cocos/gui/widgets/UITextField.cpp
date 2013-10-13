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

UICCTextField::UICCTextField()
: m_bMaxLengthEnabled(false)
, m_nMaxLength(0)
, m_bPasswordEnabled(false)
, m_strPasswordStyleText("*")
, m_bAttachWithIME(false)
, m_bDetachWithIME(false)
, m_bInsertText(false)
, m_bDeleteBackward(false)
{
}

UICCTextField::~UICCTextField()
{
}

UICCTextField * UICCTextField::create(const char *placeholder, const char *fontName, float fontSize)
{
    UICCTextField *pRet = new UICCTextField();
    
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    
    return NULL;
}

void UICCTextField::onEnter()
{
    CCTextFieldTTF::setDelegate(this);
}


bool UICCTextField::onTextFieldAttachWithIME(TextFieldTTF *pSender)
{
    setAttachWithIME(true);
    return false;
}

bool UICCTextField::onTextFieldInsertText(TextFieldTTF *pSender, const char *text, int nLen)
{
    if (nLen == 1 && strcmp(text, "\n") == 0)
    {
        return false;
    }
    setInsertText(true);
    if (m_bMaxLengthEnabled)
    {
        if (CCTextFieldTTF::getCharCount() >= m_nMaxLength)
        {
            return true;
        }
    }
    
    return false;
}

bool UICCTextField::onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, int nLen)
{
    setDeleteBackward(true);
    return false;
}

bool UICCTextField::onTextFieldDetachWithIME(TextFieldTTF *pSender)
{
    setDetachWithIME(true);
    return false;
}

void UICCTextField::insertText(const char * text, int len)
{
    std::string str_text = text;
    int str_len = strlen(CCTextFieldTTF::getString());
    
    if (strcmp(text, "\n") != 0)
    {
        if (m_bMaxLengthEnabled)
        {
            int multiple = 1;
            char value = text[0];
            if (value < 0 || value > 127)
            {
                multiple = 3;
            }
            
            if (str_len + len > m_nMaxLength * multiple)
            {
                str_text = str_text.substr(0, m_nMaxLength * multiple);
                len = m_nMaxLength * multiple;
                /*
                 int mod = str_len % 3;
                 int offset = (mod == 0) ? 0 : (3 - mod);
                 int amount = str_len + offset;
                 str_text = str_text.substr(0, m_nMaxLength - amount);
                 //                CCLOG("str_test = %s", str_text.c_str());
                 */
            }
        }
    }
    CCTextFieldTTF::insertText(str_text.c_str(), len);
    
    // password
    if (m_bPasswordEnabled)
    {
        if (CCTextFieldTTF::getCharCount() > 0)
        {
            setPasswordText(_inputText->c_str());
        }
    }
}

void UICCTextField::deleteBackward()
{
    CCTextFieldTTF::deleteBackward();
    
    if (CCTextFieldTTF::getCharCount() > 0)
    {
        // password
        if (m_bPasswordEnabled)
        {
            setPasswordText(_inputText->c_str());
        }
    }
}

void UICCTextField::openIME()
{
    CCTextFieldTTF::attachWithIME();
}

void UICCTextField::closeIME()
{
    CCTextFieldTTF::detachWithIME();
}

void UICCTextField::setMaxLengthEnabled(bool enable)
{
    m_bMaxLengthEnabled = enable;
}

bool UICCTextField::isMaxLengthEnabled()
{
    return m_bMaxLengthEnabled;
}

void UICCTextField::setMaxLength(int length)
{
    m_nMaxLength = length;
}

int UICCTextField::getMaxLength()
{
    return m_nMaxLength;
}

int UICCTextField::getCharCount()
{
    return CCTextFieldTTF::getCharCount();
}

void UICCTextField::setPasswordEnabled(bool enable)
{
    m_bPasswordEnabled = enable;
}

bool UICCTextField::isPasswordEnabled()
{
    return m_bPasswordEnabled;
}

void UICCTextField::setPasswordStyleText(const char* styleText)
{
    if (strlen(styleText) > 1)
    {
        return;
    }
    char value = styleText[0];
    if (value < 33 || value > 126)
    {
        return;
    }
    m_strPasswordStyleText = styleText;
}

void UICCTextField::setPasswordText(const char *text)
{
    std::string tempStr;
    for (size_t i = 0; i < strlen(text); ++i)
    {
        tempStr.append(m_strPasswordStyleText);
    }
    CCLabelTTF::setString(tempStr.c_str());
}

void UICCTextField::setAttachWithIME(bool attach)
{
    m_bAttachWithIME = attach;
}

bool UICCTextField::getAttachWithIME()
{
    return m_bAttachWithIME;
}

void UICCTextField::setDetachWithIME(bool detach)
{
    m_bDetachWithIME = detach;
}

bool UICCTextField::getDetachWithIME()
{
    return m_bDetachWithIME;
}

void UICCTextField::setInsertText(bool insert)
{
    m_bInsertText = insert;
}

bool UICCTextField::getInsertText()
{
    return m_bInsertText;
}

void UICCTextField::setDeleteBackward(bool deleteBackward)
{
    m_bDeleteBackward = deleteBackward;
}

bool UICCTextField::getDeleteBackward()
{
    return m_bDeleteBackward;
}



    
UITextField::UITextField():
_textFieldRenderer(NULL),
_touchWidth(0.0f),
_touchHeight(0.0f),
_useTouchArea(false),
_eventListener(NULL),
_eventSelector(NULL)
{
}

UITextField::~UITextField()
{
}

UITextField* UITextField::create()
{
    UITextField* widget = new UITextField();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UITextField::init()
{
    if (UIWidget::init())
    {
        setUpdateEnabled(true);
        return true;
    }
    return false;
}

void UITextField::initRenderer()
{
    UIWidget::initRenderer();
    _textFieldRenderer = UICCTextField::create("input words here", "Thonburi", 20);
    _renderer->addChild(_textFieldRenderer);
}

void UITextField::setTouchSize(const Size &size)
{
    _useTouchArea = true;
    _touchWidth = size.width;
    _touchHeight = size.height;
}

void UITextField::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    _textFieldRenderer->setString(strText.c_str());
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setPlaceHolder(const char *value)
{
    _textFieldRenderer->setPlaceHolder(value);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setFontSize(int size)
{
    _textFieldRenderer->setFontSize(size);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setFontName(const char *name)
{
    _textFieldRenderer->setFontName(name);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::didNotSelectSelf()
{
    _textFieldRenderer->detachWithIME();
}

const char* UITextField::getStringValue()
{
    return _textFieldRenderer->getString();
}

bool UITextField::onTouchBegan(const Point &touchPoint)
{
    bool pass = UIWidget::onTouchBegan(touchPoint);
    _textFieldRenderer->attachWithIME();
    return pass;
}

void UITextField::setMaxLengthEnabled(bool enable)
{
    _textFieldRenderer->setMaxLengthEnabled(enable);
}

bool UITextField::isMaxLengthEnabled()
{
    return _textFieldRenderer->isMaxLengthEnabled();
}

void UITextField::setMaxLength(int length)
{
    _textFieldRenderer->setMaxLength(length);
}

int UITextField::getMaxLength()
{
    return _textFieldRenderer->getMaxLength();
}

void UITextField::setPasswordEnabled(bool enable)
{
    _textFieldRenderer->setPasswordEnabled(enable);
}

bool UITextField::isPasswordEnabled()
{
    return _textFieldRenderer->isPasswordEnabled();
}

void UITextField::setPasswordStyleText(const char *styleText)
{
    _textFieldRenderer->setPasswordStyleText(styleText);
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
        
        textfieldRendererScaleChangedWithSize();
    }
    if (getDeleteBackward())
    {
        deleteBackwardEvent();
        setDeleteBackward(false);
    }
}

bool UITextField::getAttachWithIME()
{
    return _textFieldRenderer->getAttachWithIME();
}

void UITextField::setAttachWithIME(bool attach)
{
    _textFieldRenderer->setAttachWithIME(attach);
}

bool UITextField::getDetachWithIME()
{
    return _textFieldRenderer->getDetachWithIME();
}

void UITextField::setDetachWithIME(bool detach)
{
    _textFieldRenderer->setDetachWithIME(detach);
}

bool UITextField::getInsertText()
{
    return _textFieldRenderer->getInsertText();
}

void UITextField::setInsertText(bool insertText)
{
    _textFieldRenderer->setInsertText(insertText);
}

bool UITextField::getDeleteBackward()
{
    return _textFieldRenderer->getDeleteBackward();
}

void UITextField::setDeleteBackward(bool deleteBackward)
{
    _textFieldRenderer->setDeleteBackward(deleteBackward);
}

void UITextField::attachWithIMEEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, TEXTFIELD_EVENT_ATTACH_WITH_IME);
    }
}

void UITextField::detachWithIMEEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, TEXTFIELD_EVENT_DETACH_WITH_IME);
    }
}

void UITextField::insertTextEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, TEXTFIELD_EVENT_INDERT_TEXT);
    }
}

void UITextField::deleteBackwardEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, TEXTFIELD_EVENT_DELETE_BACKWARD);
    }
}

void UITextField::addEventListener(Object *target, SEL_TextFieldEvent selecor)
{
    _eventListener = target;
    _eventSelector = selecor;
}

void UITextField::setAnchorPoint(const Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _textFieldRenderer->setAnchorPoint(pt);
}

void UITextField::setColor(const Color3B &color)
{
    UIWidget::setColor(color);
    _textFieldRenderer->setColor(color);
}

void UITextField::setOpacity(int opacity)
{
    UIWidget::setOpacity(opacity);
    _textFieldRenderer->setOpacity(opacity);
}

void UITextField::onSizeChanged()
{
    textfieldRendererScaleChangedWithSize();
}

void UITextField::textfieldRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _textFieldRenderer->setScale(1.0f);
        _size = getContentSize();
    }
    else
    {
        Size textureSize = getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _textFieldRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        _textFieldRenderer->setScaleX(scaleX);
        _textFieldRenderer->setScaleY(scaleY);
    }
}

const Size& UITextField::getContentSize() const
{
    return _textFieldRenderer->getContentSize();
}

Node* UITextField::getVirtualRenderer()
{
    return _textFieldRenderer;
}

const char* UITextField::getDescription() const
{
    return "TextField";
}

NS_CC_EXT_END