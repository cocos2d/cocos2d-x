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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define PASSWORD_CHAR "*"
#else
#define PASSWORD_CHAR "\u25CF"
#endif

NS_CC_BEGIN

namespace ui {

EditBoxImplCommon::EditBoxImplCommon(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _fontSize(-1)
, _placeholderFontSize(-1)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
, _alignment(TextHAlignment::LEFT)
, _editingMode(false)
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
    _label->setAnchorPoint(Vec2(0,1));
    _label->setOverflow(Label::Overflow::CLAMP);
    _label->setVisible(false);
    _editBox->addChild(_label, kLabelZOrder);
    
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 1.0f));
    _labelPlaceHolder->setTextColor(Color4B::GRAY);
    _labelPlaceHolder->enableWrap(false);
    _editBox->addChild(_labelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void EditBoxImplCommon::placeInactiveLabels(const Size& size)
{
    _label->setDimensions(size.width, size.height);
    
    auto placeholderSize = _labelPlaceHolder->getContentSize();
    
    if(_editBoxInputMode == EditBox::InputMode::ANY){
        _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height - CC_EDIT_BOX_PADDING));
        _label->setVerticalAlignment(TextVAlignment::TOP);
        _label->enableWrap(true);
        
        _labelPlaceHolder->setPosition(Vec2(CC_EDIT_BOX_PADDING,
                                            size.height - CC_EDIT_BOX_PADDING));
        _labelPlaceHolder->setVerticalAlignment(TextVAlignment::TOP);
    }
    else {
        _label->enableWrap(false);
        _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height));
        _label->setVerticalAlignment(TextVAlignment::CENTER);
        
        _labelPlaceHolder->setPosition(Vec2(CC_EDIT_BOX_PADDING,
                                            (size.height + placeholderSize.height) / 2));
        _labelPlaceHolder->setVerticalAlignment(TextVAlignment::CENTER);
    }
}

void EditBoxImplCommon::setInactiveText(const char* pText)
{
    if(EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
    {
        std::string passwordString;
        for(size_t i = 0; i < strlen(pText); ++i)
            passwordString.append(PASSWORD_CHAR);
        _label->setString(passwordString);
    }
    else
    {
        _label->setString(pText);
    }
    // Clip the text width to fit to the text box
    const auto& editBoxSize = _editBox->getContentSize();
    const auto maxSize = applyPadding(cocos2d::Size(editBoxSize.width, editBoxSize.height));
    Size labelSize = _label->getContentSize();
    if(labelSize.width > maxSize.width || labelSize.height > maxSize.height)
    {
        _label->setDimensions(maxSize.width, maxSize.height);
    }
}
    
void EditBoxImplCommon::setFont(const char* pFontName, int fontSize)
{
    _fontName = pFontName;
    _fontSize = fontSize;
    this->setNativeFont(pFontName, fontSize * _label->getNodeToWorldAffineTransform().a);
    if (!_fontName.empty())
    {
        _label->setSystemFontName(pFontName);
    }
    if (fontSize > 0)
    {
        _label->setSystemFontSize(fontSize);
    }
}

void EditBoxImplCommon::setFontColor(const Color4B& color)
{
    _colText = color;
    this->setNativeFontColor(color);
    _label->setTextColor(color);
}

void EditBoxImplCommon::setPlaceholderFont(const char* pFontName, int fontSize)
{
    _placeholderFontName = pFontName;
    _placeholderFontSize = fontSize;
    this->setNativePlaceholderFont(pFontName, fontSize * _labelPlaceHolder->getNodeToWorldAffineTransform().a);
    if (!_placeholderFontName.empty())
    {
        _labelPlaceHolder->setSystemFontName(pFontName);
    }
    if (fontSize > 0)
    {
        _labelPlaceHolder->setSystemFontSize(fontSize);
    }
}
    
void EditBoxImplCommon::setPlaceholderFontColor(const Color4B &color)
{
    _colPlaceHolder = color;
    this->setNativePlaceholderFontColor(color);
    _labelPlaceHolder->setTextColor(color);
}

void EditBoxImplCommon::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
    this->setNativeInputMode(inputMode);
    this->placeInactiveLabels(applyPadding(_editBox->getContentSize()));
}

void EditBoxImplCommon::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
    this->setNativeMaxLength(maxLength);
}

void EditBoxImplCommon::setTextHorizontalAlignment(cocos2d::TextHAlignment alignment)
{
    _alignment = alignment;
    this->setNativeTextHorizontalAlignment(alignment);
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

    refreshLabelAlignment();
    if (!_editingMode) {
        if (_text.size() == 0) {
            _label->setVisible(false);
            _labelPlaceHolder->setVisible(true);
        } else {
            _label->setVisible(true);
            _labelPlaceHolder->setVisible(false);
        }
    }
}

void EditBoxImplCommon::refreshLabelAlignment()
{
    _label->setHorizontalAlignment(_alignment);
    _labelPlaceHolder->setHorizontalAlignment(_alignment);
}

void EditBoxImplCommon::setText(const char* text)
{
    if (nullptr != text) {
        this->setNativeText(text);
        _text = text;
        refreshInactiveText();
    }
}

void EditBoxImplCommon::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        this->setNativePlaceHolder(pText);
        _labelPlaceHolder->setString(_placeHolder);
    }
}

void EditBoxImplCommon::setVisible(bool visible)
{
    if(visible) {
        refreshInactiveText();
    } else {
        this->setNativeVisible(visible);
        _label->setVisible(visible);
        _labelPlaceHolder->setVisible(visible);
    }
}

void EditBoxImplCommon::setContentSize(const Size& size)
{
    _contentSize = applyPadding(size);
    CCLOG("[Edit text] content size = (%f, %f)", _contentSize.width, _contentSize.height);
    placeInactiveLabels(_contentSize);
}

void EditBoxImplCommon::draw(Renderer* /*renderer*/, const Mat4& /*transform*/, uint32_t flags)
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
    _editingMode = true;
    this->setNativeVisible(true);
    this->nativeOpenKeyboard();
}

void EditBoxImplCommon::closeKeyboard()
{
    this->nativeCloseKeyboard();
    _editingMode = false;
}

void EditBoxImplCommon::onEndEditing(const std::string& /*text*/)
{
    _editingMode = false;
    this->setNativeVisible(false);
    refreshInactiveText();
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

void EditBoxImplCommon::editBoxEditingDidEnd(const std::string& text, EditBoxDelegate::EditBoxEndAction action)
{
    // LOGD("textFieldShouldEndEditing...");
    _text = text;
    
    cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
    if (pDelegate != nullptr)
    {
        pDelegate->editBoxEditingDidEndWithAction(_editBox, action);
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
        pDelegate->editBoxEditingDidEnd(_editBox);
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
        
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

Size ui::EditBoxImplCommon::applyPadding(const Size& sizeToCorrect) const {
  constexpr auto paddingLeftRight = CC_EDIT_BOX_PADDING * 2;
  return Size(sizeToCorrect.width - paddingLeftRight, sizeToCorrect.height);
}

NS_CC_END


