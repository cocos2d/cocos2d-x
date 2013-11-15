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

#include "gui/UITextField.h"

namespace gui {

UICCTextField::UICCTextField()
: _maxLengthEnabled(false)
, _maxLength(0)
, _passwordEnabled(false)
, _passwordStyleText("*")
, _attachWithIME(false)
, _detachWithIME(false)
, _insertText(false)
, _deleteBackward(false)
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
    
    return nullptr;
}

void UICCTextField::onEnter()
{
    cocos2d::TextFieldTTF::setDelegate(this);
}


bool UICCTextField::onTextFieldAttachWithIME(cocos2d::TextFieldTTF *pSender)
{
    setAttachWithIME(true);
    return false;
}

bool UICCTextField::onTextFieldInsertText(cocos2d::TextFieldTTF *pSender, const char *text, int nLen)
{
    if (nLen == 1 && strcmp(text, "\n") == 0)
    {
        return false;
    }
    setInsertText(true);
    if (_maxLengthEnabled)
    {
        if (cocos2d::TextFieldTTF::getCharCount() >= _maxLength)
        {
            return true;
        }
    }
    
    return false;
}

bool UICCTextField::onTextFieldDeleteBackward(cocos2d::TextFieldTTF *pSender, const char *delText, int nLen)
{
    setDeleteBackward(true);
    return false;
}

bool UICCTextField::onTextFieldDetachWithIME(cocos2d::TextFieldTTF *pSender)
{
    setDetachWithIME(true);
    return false;
}

void UICCTextField::insertText(const char * text, int len)
{
    std::string str_text = text;
    int str_len = cocos2d::TextFieldTTF::getString().size();
    
    if (strcmp(text, "\n") != 0)
    {
        if (_maxLengthEnabled)
        {
            int multiple = 1;
            char value = text[0];
            if (value < 0 || value > 127)
            {
                multiple = 3;
            }
            
            if (str_len + len > _maxLength * multiple)
            {
                str_text = str_text.substr(0, _maxLength * multiple);
                len = _maxLength * multiple;
                /*
                 int mod = str_len % 3;
                 int offset = (mod == 0) ? 0 : (3 - mod);
                 int amount = str_len + offset;
                 str_text = str_text.substr(0, _maxLength - amount);
                 //                CCLOG("str_test = %s", str_text.c_str());
                 */
            }
        }
    }
    cocos2d::TextFieldTTF::insertText(str_text.c_str(), len);
    
    // password
    if (_passwordEnabled)
    {
        if (cocos2d::TextFieldTTF::getCharCount() > 0)
        {
            setPasswordText(_inputText.c_str());
        }
    }
}

void UICCTextField::deleteBackward()
{
    cocos2d::TextFieldTTF::deleteBackward();
    
    if (cocos2d::TextFieldTTF::getCharCount() > 0)
    {
        // password
        if (_passwordEnabled)
        {
            setPasswordText(_inputText.c_str());
        }
    }
}

void UICCTextField::openIME()
{
    cocos2d::TextFieldTTF::attachWithIME();
}

void UICCTextField::closeIME()
{
    cocos2d::TextFieldTTF::detachWithIME();
}

void UICCTextField::setMaxLengthEnabled(bool enable)
{
    _maxLengthEnabled = enable;
}

bool UICCTextField::isMaxLengthEnabled()
{
    return _maxLengthEnabled;
}

void UICCTextField::setMaxLength(int length)
{
    _maxLength = length;
}

int UICCTextField::getMaxLength()
{
    return _maxLength;
}

int UICCTextField::getCharCount()
{
    return cocos2d::TextFieldTTF::getCharCount();
}

void UICCTextField::setPasswordEnabled(bool enable)
{
    _passwordEnabled = enable;
}

bool UICCTextField::isPasswordEnabled()
{
    return _passwordEnabled;
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
    _passwordStyleText = styleText;
}

void UICCTextField::setPasswordText(const char *text)
{
    std::string tempStr;
    for (size_t i = 0; i < strlen(text); ++i)
    {
        tempStr.append(_passwordStyleText);
    }
    cocos2d::LabelTTF::setString(tempStr.c_str());
}

void UICCTextField::setAttachWithIME(bool attach)
{
    _attachWithIME = attach;
}

bool UICCTextField::getAttachWithIME()
{
    return _attachWithIME;
}

void UICCTextField::setDetachWithIME(bool detach)
{
    _detachWithIME = detach;
}

bool UICCTextField::getDetachWithIME()
{
    return _detachWithIME;
}

void UICCTextField::setInsertText(bool insert)
{
    _insertText = insert;
}

bool UICCTextField::getInsertText()
{
    return _insertText;
}

void UICCTextField::setDeleteBackward(bool deleteBackward)
{
    _deleteBackward = deleteBackward;
}

bool UICCTextField::getDeleteBackward()
{
    return _deleteBackward;
}



    
UITextField::UITextField():
_textFieldRenderer(nullptr),
_touchWidth(0.0f),
_touchHeight(0.0f),
_useTouchArea(false),
_textFieldEventListener(nullptr),
_textFieldEventSelector(nullptr),
_passwordStyleText("")
{
}

UITextField::~UITextField()
{
    _textFieldEventListener = nullptr;
    _textFieldEventSelector = nullptr;
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
    return nullptr;
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

void UITextField::setTouchSize(const cocos2d::Size &size)
{
    _useTouchArea = true;
    _touchWidth = size.width;
    _touchHeight = size.height;
}

void UITextField::setText(const std::string& text)
{
	if (text.size()==0)
		return;

    _textFieldRenderer->setString(text);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setPlaceHolder(const std::string& value)
{
    _textFieldRenderer->setPlaceHolder(value);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setFontSize(int size)
{
    _textFieldRenderer->setFontSize(size);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::setFontName(const std::string& name)
{
    _textFieldRenderer->setFontName(name);
    textfieldRendererScaleChangedWithSize();
}

void UITextField::didNotSelectSelf()
{
    _textFieldRenderer->detachWithIME();
}

const std::string& UITextField::getStringValue()
{
    return _textFieldRenderer->getString();
}

bool UITextField::onTouchBegan(const cocos2d::Point &touchPoint)
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
    
    _passwordStyleText = styleText;
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
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_ATTACH_WITH_IME);
    }
}

void UITextField::detachWithIMEEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_DETACH_WITH_IME);
    }
}

void UITextField::insertTextEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_INSERT_TEXT);
    }
}

void UITextField::deleteBackwardEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_DELETE_BACKWARD);
    }
}

void UITextField::addEventListenerTextField(cocos2d::Object *target, SEL_TextFieldEvent selecor)
{
    _textFieldEventListener = target;
    _textFieldEventSelector = selecor;
}

void UITextField::setAnchorPoint(const cocos2d::Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _textFieldRenderer->setAnchorPoint(pt);
}

void UITextField::setColor(const cocos2d::Color3B &color)
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
        cocos2d::Size textureSize = getContentSize();
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

const cocos2d::Size& UITextField::getContentSize() const
{
    return _textFieldRenderer->getContentSize();
}

cocos2d::Node* UITextField::getVirtualRenderer()
{
    return _textFieldRenderer;
}

const char* UITextField::getDescription() const
{
    return "TextField";
}

void UITextField::attachWithIME()
{
    _textFieldRenderer->attachWithIME();
}

UIWidget* UITextField::createCloneInstance()
{
    return UITextField::create();
}

void UITextField::copySpecialProperties(UIWidget *widget)
{
    UITextField* textField = dynamic_cast<UITextField*>(widget);
    if (textField)
    {
        setText(textField->_textFieldRenderer->getString());
        setPlaceHolder(textField->getStringValue());
        setFontSize(textField->_textFieldRenderer->getFontSize());
        setFontName(textField->_textFieldRenderer->getFontName().c_str());
        setMaxLengthEnabled(textField->isMaxLengthEnabled());
        setMaxLength(textField->getMaxLength());
        setPasswordEnabled(textField->isPasswordEnabled());
        setPasswordStyleText(textField->_passwordStyleText.c_str());
        setAttachWithIME(textField->getAttachWithIME());
        setDetachWithIME(textField->getDetachWithIME());
        setInsertText(textField->getInsertText());
        setDeleteBackward(textField->getDeleteBackward());
    }
}

}