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

#include "ui/UITextField.h"

NS_CC_BEGIN

namespace ui {
    
static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

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
    
    if(pRet && pRet->initWithPlaceHolder("", fontName, fontSize))
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
    TextFieldTTF::setDelegate(this);
}


bool UICCTextField::onTextFieldAttachWithIME(TextFieldTTF *pSender)
{
    setAttachWithIME(true);
    return false;
}

bool UICCTextField::onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen)
{
    if (nLen == 1 && strcmp(text, "\n") == 0)
    {
        return false;
    }
    setInsertText(true);
    if (_maxLengthEnabled)
    {
        if (TextFieldTTF::getCharCount() >= _maxLength)
        {
            return true;
        }
    }
    
    return false;
}

bool UICCTextField::onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen)
{
    setDeleteBackward(true);
    return false;
}

bool UICCTextField::onTextFieldDetachWithIME(TextFieldTTF *pSender)
{
    setDetachWithIME(true);
    return false;
}

void UICCTextField::insertText(const char * text, size_t len)
{
    std::string input_text = text;
    
    if (strcmp(text, "\n") != 0)
    {
        if (_maxLengthEnabled)
        {
            int text_count = _calcCharCount(getString().c_str());
            if (text_count >= _maxLength)
            {
                // password
                if (_passwordEnabled)
                {
                    setPasswordText(getString().c_str());
                }
                return;
            }
            
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32))
            int input_count = _calcCharCount(text);
            int total = total = text_count + input_count;
            
            if (total > _maxLength)
            {
                int end = 0;
                int length = _maxLength - text_count;
                
                for (int i = 0; i < length; ++i)
                {
                    char value = text[i];
                    
                    if (value >= 0 && value <= 127) // ascii
                    {
                        end++;
                    }
                    else
                    {
                        end += 3;
                    }
                }
                input_text = input_text.substr(0, end);
                len  = end;
            }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            int input_count = _calcCharCount(text);
            int total = text_count + input_count;
            if (total > _maxLength)
            {
                int ascii = 0;
                int unicode = 0;
                int end = 0;
                int count = 0;
                
                for (int i = 0; i < total * 3; ++i)
                {
                    char value = text[i];
                    
                    if (value >= 0 && value <= 127) // ascii
                    {
                        ascii++;
                        count++;
                    }
                    else
                    {
                        unicode++;
                        if (unicode % 3 == 0)
                        {
                            count++;
                        }
                    }
                    
                    if (count == _maxLength)
                    {
                        break;
                    }
                }
                end = ascii + unicode;
                input_text = input_text.substr(0, end);
                len  = end;
            }
#endif
        }
    }
    TextFieldTTF::insertText(input_text.c_str(), len);
    
    // password
    if (_passwordEnabled)
    {
        if (TextFieldTTF::getCharCount() > 0)
        {
            setPasswordText(getString().c_str());
        }
    }
}

void UICCTextField::deleteBackward()
{
    TextFieldTTF::deleteBackward();
    
    if (TextFieldTTF::getCharCount() > 0)
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
    TextFieldTTF::attachWithIME();
}

void UICCTextField::closeIME()
{
    TextFieldTTF::detachWithIME();
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
    return TextFieldTTF::getCharCount();
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
    std::string tempStr = "";
    int text_count = _calcCharCount(text);
    int max = text_count;
    
    if (_maxLengthEnabled)
    {
        if (text_count > _maxLength)
        {
            max = _maxLength;
        }
    }
    
    for (int i = 0; i < max; ++i)
    {
        tempStr.append(_passwordStyleText);
    }
    
    Label::setString(tempStr);
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

static const int TEXTFIELD_RENDERER_Z = (-1);

IMPLEMENT_CLASS_GUI_INFO(TextField)
    
    
TextField::TextField():
_textFieldRenderer(nullptr),
_touchWidth(0.0f),
_touchHeight(0.0f),
_useTouchArea(false),
_textFieldEventListener(nullptr),
_textFieldEventSelector(nullptr),
_passwordStyleText("")
{
}

TextField::~TextField()
{
    _textFieldEventListener = nullptr;
    _textFieldEventSelector = nullptr;
}

TextField* TextField::create()
{
    TextField* widget = new TextField();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
TextField* TextField::create(const std::string &placeholder, const std::string &fontName, int fontSize)
{
    TextField* widget = new TextField();
    if (widget && widget->init())
    {
        widget->setTouchEnabled(true);
        widget->setPlaceHolder(placeholder);
        widget->setFontName(fontName);
        widget->setFontSize(fontSize);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool TextField::init()
{
    if (Widget::init())
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}
    
void TextField::onEnter()
{
    Widget::onEnter();
    scheduleUpdate();
}

void TextField::initRenderer()
{
    _textFieldRenderer = UICCTextField::create("input words here", "Thonburi", 20);
    addProtectedChild(_textFieldRenderer, TEXTFIELD_RENDERER_Z, -1);
}

void TextField::setTouchSize(const Size &size)
{
    _touchWidth = size.width;
    _touchHeight = size.height;
}
    
void TextField::setTouchAreaEnabled(bool enable)
{
    _useTouchArea = enable;
}
    
bool TextField::hitTest(const Point &pt)
{
    if (_useTouchArea)
    {
        Point nsp = convertToNodeSpace(pt);
        Rect bb = Rect(-_touchWidth * _anchorPoint.x, -_touchHeight * _anchorPoint.y, _touchWidth, _touchHeight);
        if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
        {
            return true;
        }
    }
    else
    {
        return Widget::hitTest(pt);
    }
    
    return false;
}
    
Size TextField::getTouchSize()
{
    return Size(_touchWidth, _touchHeight);
}

void TextField::setText(const std::string& text)
{
    std::string strText(text);
    
    if (isMaxLengthEnabled())
    {
        int max = _textFieldRenderer->getMaxLength();
        int text_count = _calcCharCount(text.c_str());
        int total = text_count + _calcCharCount(getStringValue().c_str());
        if (total > max)
        {
            int ascii = 0;
            int unicode = 0;
            int end = 0;
            int count = 0;
            
            for (int i = 0; i < total * 3; ++i)
            {
                char value = text[i];
                
                if (value >= 0 && value <= 127) // ascii
                {
                    ascii++;
                    count++;
                }
                else
                {
                    unicode++;
                    if (unicode % 3 == 0)
                    {
                        count++;
                    }
                }
                
                if (count == max)
                {
                    break;
                }
            }
            end = ascii + unicode;
            strText = strText.substr(0, end);
        }
    }
    
    const char* content = strText.c_str();
    if (isPasswordEnabled())
    {
        _textFieldRenderer->setPasswordText(content);
        _textFieldRenderer->setString("");
        _textFieldRenderer->insertText(content, strlen(content));
    }
    else
    {
        _textFieldRenderer->setString(content);
    }
    
    textfieldRendererScaleChangedWithSize();
}

void TextField::setPlaceHolder(const std::string& value)
{
    _textFieldRenderer->setPlaceHolder(value);
    textfieldRendererScaleChangedWithSize();
}
    
const std::string& TextField::getPlaceHolder()
{
    return _textFieldRenderer->getPlaceHolder();
}

void TextField::setFontSize(int size)
{
    _textFieldRenderer->setSystemFontSize(size);
    textfieldRendererScaleChangedWithSize();
}
    
int TextField::getFontSize()
{
    return _textFieldRenderer->getSystemFontSize();
}

void TextField::setFontName(const std::string& name)
{
    _textFieldRenderer->setSystemFontName(name);
    textfieldRendererScaleChangedWithSize();
}
    
const std::string& TextField::getFontName()
{
    return _textFieldRenderer->getSystemFontName();
}

void TextField::didNotSelectSelf()
{
    _textFieldRenderer->detachWithIME();
}

const std::string& TextField::getStringValue()
{
    return _textFieldRenderer->getString();
}

bool TextField::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Widget::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        _textFieldRenderer->attachWithIME();
    }
    return pass;
}

void TextField::setMaxLengthEnabled(bool enable)
{
    _textFieldRenderer->setMaxLengthEnabled(enable);
}

bool TextField::isMaxLengthEnabled()
{
    return _textFieldRenderer->isMaxLengthEnabled();
}

void TextField::setMaxLength(int length)
{
    _textFieldRenderer->setMaxLength(length);
    
    setText(getStringValue());
}

int TextField::getMaxLength()
{
    return _textFieldRenderer->getMaxLength();
}

void TextField::setPasswordEnabled(bool enable)
{
    _textFieldRenderer->setPasswordEnabled(enable);
}

bool TextField::isPasswordEnabled()
{
    return _textFieldRenderer->isPasswordEnabled();
}

void TextField::setPasswordStyleText(const char *styleText)
{
    _textFieldRenderer->setPasswordStyleText(styleText);
    
    _passwordStyleText = styleText;
    
    setText(getStringValue());
}
    
const char* TextField::getPasswordStyleText()
{
    return _passwordStyleText.c_str();
}

void TextField::update(float dt)
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
        
        textfieldRendererScaleChangedWithSize();
    }
}

bool TextField::getAttachWithIME()
{
    return _textFieldRenderer->getAttachWithIME();
}

void TextField::setAttachWithIME(bool attach)
{
    _textFieldRenderer->setAttachWithIME(attach);
}

bool TextField::getDetachWithIME()
{
    return _textFieldRenderer->getDetachWithIME();
}

void TextField::setDetachWithIME(bool detach)
{
    _textFieldRenderer->setDetachWithIME(detach);
}

bool TextField::getInsertText()
{
    return _textFieldRenderer->getInsertText();
}

void TextField::setInsertText(bool insertText)
{
    _textFieldRenderer->setInsertText(insertText);
}

bool TextField::getDeleteBackward()
{
    return _textFieldRenderer->getDeleteBackward();
}

void TextField::setDeleteBackward(bool deleteBackward)
{
    _textFieldRenderer->setDeleteBackward(deleteBackward);
}

void TextField::attachWithIMEEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_ATTACH_WITH_IME);
    }
}

void TextField::detachWithIMEEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_DETACH_WITH_IME);
    }
}

void TextField::insertTextEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_INSERT_TEXT);
    }
}

void TextField::deleteBackwardEvent()
{
    if (_textFieldEventListener && _textFieldEventSelector)
    {
        (_textFieldEventListener->*_textFieldEventSelector)(this, TEXTFIELD_EVENT_DELETE_BACKWARD);
    }
}

void TextField::addEventListenerTextField(Ref *target, SEL_TextFieldEvent selecor)
{
    _textFieldEventListener = target;
    _textFieldEventSelector = selecor;
}

void TextField::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _textFieldRenderer->setAnchorPoint(pt);
}

void TextField::onSizeChanged()
{
    Widget::onSizeChanged();
    textfieldRendererScaleChangedWithSize();
}

void TextField::textfieldRendererScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _textFieldRenderer->setDimensions(0,0);
        _textFieldRenderer->setScale(1.0f);
        _size = getContentSize();
    }
    else
    {
        _textFieldRenderer->setDimensions(_size.width,_size.height);
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

const Size& TextField::getContentSize() const
{
    return _textFieldRenderer->getContentSize();
}

Node* TextField::getVirtualRenderer()
{
    return _textFieldRenderer;
}

std::string TextField::getDescription() const
{
    return "TextField";
}
    
void TextField::updateTextureColor()
{
    updateColorToRenderer(_textFieldRenderer);
}

void TextField::updateTextureOpacity()
{
    updateOpacityToRenderer(_textFieldRenderer);
}

void TextField::updateTextureRGBA()
{
    updateRGBAToRenderer(_textFieldRenderer);
}

void TextField::attachWithIME()
{
    _textFieldRenderer->attachWithIME();
}

Widget* TextField::createCloneInstance()
{
    return TextField::create();
}

void TextField::copySpecialProperties(Widget *widget)
{
    TextField* textField = dynamic_cast<TextField*>(widget);
    if (textField)
    {
        setText(textField->_textFieldRenderer->getString());
        setPlaceHolder(textField->getStringValue());
        setFontSize(textField->_textFieldRenderer->getSystemFontSize());
        setFontName(textField->_textFieldRenderer->getSystemFontName());
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
    
void TextField::setTextAreaSize(const Size &size)
{
    _textFieldRenderer->setDimensions(size.width,size.height);
}

void TextField::setTextHorizontalAlignment(TextHAlignment alignment)
{
    _textFieldRenderer->setHorizontalAlignment(alignment);
}

void TextField::setTextVerticalAlignment(TextVAlignment alignment)
{
    _textFieldRenderer->setVerticalAlignment(alignment);
}

}

NS_CC_END
