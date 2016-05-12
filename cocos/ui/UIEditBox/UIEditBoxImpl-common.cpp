/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren

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
#include "ui/UIEditBox/UIEditBoxImpl-common.h"

#define kLabelZOrder  9999

#include "ui/UIEditBox/UIEditBox.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#include "ui/UIHelper.h"

static const int CC_EDIT_BOX_PADDING = 5;

NS_CC_BEGIN

namespace ui {

EditBoxImplCommon::EditBoxImplCommon(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{
}

EditBoxImplCommon::~EditBoxImplCommon()
{
}


bool EditBoxImplCommon::initWithSize(const Size& size)
{
    do 
    {
        
        Rect rect = Rect(0, 0, size.width, size.height);
        
        this->createNativeControl(rect);
        
        initInactiveLabels(size);
        setContentSize(size);
        
        return true;
    }while (0);
    
    return false;
}

void EditBoxImplCommon::initInactiveLabels(const Size& size)
{
    const char* pDefaultFontName = this->getNativeDefaultFontName();

    _label = Label::create();
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setColor(Color3B::WHITE);
    _label->setVisible(false);
    _editBox->addChild(_label, kLabelZOrder);
    
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setColor(Color3B::GRAY);
    _editBox->addChild(_labelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void EditBoxImplCommon::placeInactiveLabels()
{
    _label->setPosition(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f);
    _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f);
}

void EditBoxImplCommon::setInactiveText(const char* pText)
{
    if(EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
    {
        std::string passwordString;
        for(int i = 0; i < strlen(pText); ++i)
            passwordString.append("\u25CF");
        _label->setString(passwordString);
    }
    else
    {
        _label->setString(pText);
    }
    // Clip the text width to fit to the text box
    float fMaxWidth = _editBox->getContentSize().width;
    float fMaxHeight = _editBox->getContentSize().height;
    Size labelSize = _label->getContentSize();
    if(labelSize.width > fMaxWidth || labelSize.height > fMaxHeight)
    {
        _label->setDimensions(fMaxWidth, fMaxHeight);
    }
}
    
void EditBoxImplCommon::setFont(const char* pFontName, int fontSize)
{
    this->setNativeFont(pFontName, fontSize * _label->getNodeToWorldAffineTransform().a);

    if(strlen(pFontName) > 0)
    {
        _label->setSystemFontName(pFontName);
    }
    if(fontSize > 0)
    {
        _label->setSystemFontSize(fontSize);
    }
}

void EditBoxImplCommon::setFontColor(const Color4B& color)
{
    this->setNativeFontColor(color);
    
    _label->setTextColor(color);
}

void EditBoxImplCommon::setPlaceholderFont(const char* pFontName, int fontSize)
{
    this->setNativePlaceholderFont(pFontName, fontSize * _labelPlaceHolder->getNodeToWorldAffineTransform().a);
    
    if( strlen(pFontName) > 0)
    {
        _labelPlaceHolder->setSystemFontName(pFontName);
    }
    if(fontSize > 0)
    {
        _labelPlaceHolder->setSystemFontSize(fontSize);
    }
}
    
void EditBoxImplCommon::setPlaceholderFontColor(const Color4B &color)
{
    this->setNativePlaceholderFontColor(color);
    
    _labelPlaceHolder->setTextColor(color);
}

void EditBoxImplCommon::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
    this->setNativeInputMode(inputMode);
}

void EditBoxImplCommon::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    this->setNativeMaxLength(maxLength);
}

int EditBoxImplCommon::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplCommon::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
    this->setNativeInputFlag(inputFlag);
}

void EditBoxImplCommon::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
    this->setNativeReturnType(returnType);
}
    
void EditBoxImplCommon::refreshInactiveText()
{
    setInactiveText(_text.c_str());
    if(_text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
    }
}

void EditBoxImplCommon::setText(const char* text)
{
    this->setNativeText(text);
    _text = text;
    refreshInactiveText();
}

const char*  EditBoxImplCommon::getText(void)
{
    return _text.c_str();
}

void EditBoxImplCommon::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }

        _labelPlaceHolder->setString(_placeHolder);
        this->setNativePlaceHolder(pText);
    }
}


void EditBoxImplCommon::setVisible(bool visible)
{
    this->setNativeVisible(visible);
}

void EditBoxImplCommon::setContentSize(const Size& size)
{
    _contentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
    placeInactiveLabels();
}

void EditBoxImplCommon::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(flags)
    {
        auto rect = ui::Helper::convertBoundingBoxToScreen(_editBox);
        this->updateNativeFrame(rect);
    }
}

void EditBoxImplCommon::onEnter(void)
{
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void EditBoxImplCommon::openKeyboard()
{
    _label->setVisible(false);
    _labelPlaceHolder->setVisible(false);

    this->nativeOpenKeyboard();
}

void EditBoxImplCommon::closeKeyboard()
{
    this->nativeCloseKeyboard();
}

void EditBoxImplCommon::onEndEditing(const std::string& text)
{
    this->setNativeVisible(false);
    
    if(text.size() == 0)
    {
        _label->setVisible(false);
        _labelPlaceHolder->setVisible(true);
    }
    else
    {
        _label->setVisible(true);
        _labelPlaceHolder->setVisible(false);
        setInactiveText(text.c_str());
    }
}
    
void EditBoxImplCommon::editBoxEditingDidBegin()
{
    // LOGD("textFieldShouldBeginEditing...");
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidBegin(_editBox);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "began", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

void EditBoxImplCommon::editBoxEditingDidEnd(const std::string& text)
{
    // LOGD("textFieldShouldEndEditing...");
    _text = text;
    this->refreshInactiveText();
    
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidEnd(_editBox);
        pDelegate->editBoxReturn(_editBox);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_editBox != nullptr && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "ended", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void *)&data;
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
    
    if (_editBox != nullptr)
    {
        this->onEndEditing(_text);
    }
}

void EditBoxImplCommon::editBoxEditingChanged(const std::string& text)
{
    // LOGD("editBoxTextChanged...");
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    _text = text;
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxTextChanged(_editBox, text);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
    {
        cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "changed", _editBox);
        cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}


}

NS_CC_END


