/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013 Lee, Jae-Hong
 
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

#include "CCEditBoxImplTizen.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)

#include "CCEditBox.h"
#include "platform/tizen/CCOspForm.h"

using namespace Tizen::Ui::Controls;

NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplTizen(pEditBox);
}

EditBoxImplTizen::EditBoxImplTizen(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(NULL)
, _labelPlaceHolder(NULL)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{
}

EditBoxImplTizen::~EditBoxImplTizen()
{
}

void EditBoxImplTizen::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplTizen::initWithSize(const Size& size)
{
//    int fontSize = (int)size.height-12;
    _label = LabelTTF::create("", "", size.height-12);
    // align the text vertically center
    _label->setAnchorPoint(Point(0, 0.5f));
    _label->setPosition(Point(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setColor(_colText);
    _editBox->addChild(_label);

    _labelPlaceHolder = LabelTTF::create("", "", size.height-12);
    // align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Point(0, 0.5f));
    _labelPlaceHolder->setPosition(Point(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);

    _editSize = size;
    return true;
}

void EditBoxImplTizen::setFont(const char* pFontName, int fontSize)
{
    if(_label != NULL) {
        _label->setFontName(pFontName);
        _label->setFontSize(fontSize);
    }
    
    if(_labelPlaceHolder != NULL) {
        _labelPlaceHolder->setFontName(pFontName);
        _labelPlaceHolder->setFontSize(fontSize);
    }
}

void EditBoxImplTizen::setFontColor(const Color3B& color)
{
    _colText = color;
    _label->setColor(color);
}

void EditBoxImplTizen::setPlaceholderFont(const char* pFontName, int fontSize)
{
    if(_labelPlaceHolder != NULL) {
        _labelPlaceHolder->setFontName(pFontName);
        _labelPlaceHolder->setFontSize(fontSize);
    }
}

void EditBoxImplTizen::setPlaceholderFontColor(const Color3B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setColor(color);
}

void EditBoxImplTizen::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplTizen::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplTizen::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplTizen::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplTizen::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplTizen::isEditing()
{
    return false;
}

void EditBoxImplTizen::setText(const char* pText)
{
    if (pText != NULL)
    {
        _text = pText;

        if (_text.length() > 0)
        {
            _labelPlaceHolder->setVisible(false);

            std::string strToShow;

            if (EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
            {
                long length = cc_utf8_strlen(_text.c_str(), -1);
                for (long i = 0; i < length; i++)
                {
                    strToShow.append("*");
                }
            }
            else
            {
                strToShow = _text;
            }

            _label->setString(strToShow.c_str());

            // Clip the text width to fit to the text box
            float fMaxWidth = _editSize.width - CC_EDIT_BOX_PADDING * 2;
            Rect clippingRect = _label->getTextureRect();
            if(clippingRect.size.width > fMaxWidth) {
                clippingRect.size.width = fMaxWidth;
                _label->setTextureRect(clippingRect);
            }

        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }

    }
}

const char*  EditBoxImplTizen::getText(void)
{
    return _text.c_str();
}

void EditBoxImplTizen::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }

        _labelPlaceHolder->setString(_placeHolder.c_str());
    }
}

void EditBoxImplTizen::setPosition(const Point& pos)
{
}

void EditBoxImplTizen::setVisible(bool visible)
{
}

void EditBoxImplTizen::setContentSize(const Size& size)
{
}

void EditBoxImplTizen::setAnchorPoint(const Point& anchorPoint)
{
}

void EditBoxImplTizen::visit(void)
{
}

void EditBoxImplTizen::onEnter(void)
{
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    EditBoxImplTizen* thiz = (EditBoxImplTizen*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getEditBox());
    }
    
    EditBox* pEditBox = thiz->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {       
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName,0,64*sizeof(char));
        strncpy(data.eventName,"ended",64);
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName,0,64*sizeof(char));
        strncpy(data.eventName,"return",64);
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
}

void EditBoxImplTizen::openKeyboard()
{
    if (_delegate != NULL)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }
    EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }

    KeypadStyle keypadStyle = KEYPAD_STYLE_NORMAL;
    KeypadInputModeCategory keypadCategory = KEYPAD_MODE_ALPHA;
    bool bSingleLineEnabled = false;
    switch (_editBoxInputMode)
    {
    case EditBox::InputMode::ANY:
        keypadStyle = KEYPAD_STYLE_NORMAL;
        break;
    case EditBox::InputMode::EMAIL_ADDRESS:
        keypadStyle = KEYPAD_STYLE_EMAIL;
        break;
    case EditBox::InputMode::NUMERIC:
    case EditBox::InputMode::DECIMAL:
        keypadStyle = KEYPAD_STYLE_NUMBER;
        keypadCategory = KEYPAD_MODE_NUMERIC;
        break;
    case EditBox::InputMode::PHONE_NUMBER:
        keypadStyle = KEYPAD_STYLE_PHONE_NUMBER;
        break;
    case EditBox::InputMode::URL:
        keypadStyle = KEYPAD_STYLE_URL;
        break;
    case EditBox::InputMode::SINGLE_LINE:
        bSingleLineEnabled = true;
        break;
    default:
        keypadStyle = KEYPAD_STYLE_NORMAL;
        break;
    }

    bool bTextPrediction = true;
    switch (_editBoxInputFlag)
    {
    case EditBox::InputFlag::PASSWORD:
        keypadStyle = KEYPAD_STYLE_PASSWORD;
        break;
    case EditBox::InputFlag::SENSITIVE:
        bTextPrediction = false;
        break;
    default:
        break;
    }

    ((OspForm *)OspApplication::GetInstance()->getOspForm())->ShowKeypad(
        _text.c_str(),
        keypadStyle,
        keypadCategory,
        bSingleLineEnabled,
        bTextPrediction,
        _maxLength,
        editBoxCallbackFunc,
        (void*)this);
}

void EditBoxImplTizen::closeKeyboard()
{
    ((OspForm *)OspApplication::GetInstance()->getOspForm())->CloseKeypad();
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) */

