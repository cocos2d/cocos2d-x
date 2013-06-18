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

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplTizen(pEditBox);
}

CCEditBoxImplTizen::CCEditBoxImplTizen(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, _label(NULL)
, _labelPlaceHolder(NULL)
, _editBoxInputMode(kEditBoxInputModeSingleLine)
, _editBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, _keyboardReturnType(kKeyboardReturnTypeDefault)
, _colText(ccWHITE)
, _colPlaceHolder(ccGRAY)
, _maxLength(-1)
{
}

CCEditBoxImplTizen::~CCEditBoxImplTizen()
{
}

void CCEditBoxImplTizen::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

static const int CC_EDIT_BOX_PADDING = 5;

bool CCEditBoxImplTizen::initWithSize(const CCSize& size)
{
    int fontSize = (int)size.height-12;
    _label = CCLabelTTF::create("", "", size.height-12);
    // align the text vertically center
    _label->setAnchorPoint(ccp(0, 0.5f));
    _label->setPosition(ccp(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setColor(_colText);
    _editBox->addChild(_label);

    _labelPlaceHolder = CCLabelTTF::create("", "", size.height-12);
    // align the text vertically center
    _labelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
    _labelPlaceHolder->setPosition(ccp(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);

    _editSize = size;
    return true;
}

void CCEditBoxImplTizen::setFont(const char* pFontName, int fontSize)
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

void CCEditBoxImplTizen::setFontColor(const ccColor3B& color)
{
    _colText = color;
    _label->setColor(color);
}

void CCEditBoxImplTizen::setPlaceholderFont(const char* pFontName, int fontSize)
{
    if(_labelPlaceHolder != NULL) {
        _labelPlaceHolder->setFontName(pFontName);
        _labelPlaceHolder->setFontSize(fontSize);
    }
}

void CCEditBoxImplTizen::setPlaceholderFontColor(const ccColor3B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setColor(color);
}

void CCEditBoxImplTizen::setInputMode(EditBoxInputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void CCEditBoxImplTizen::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int CCEditBoxImplTizen::getMaxLength()
{
    return _maxLength;
}

void CCEditBoxImplTizen::setInputFlag(EditBoxInputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void CCEditBoxImplTizen::setReturnType(KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool CCEditBoxImplTizen::isEditing()
{
    return false;
}

void CCEditBoxImplTizen::setText(const char* pText)
{
    if (pText != NULL)
    {
        _text = pText;

        if (_text.length() > 0)
        {
            _labelPlaceHolder->setVisible(false);

            std::string strToShow;

            if (kEditBoxInputFlagPassword == _editBoxInputFlag)
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
            CCRect clippingRect = _label->getTextureRect();
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

const char*  CCEditBoxImplTizen::getText(void)
{
    return _text.c_str();
}

void CCEditBoxImplTizen::setPlaceHolder(const char* pText)
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

void CCEditBoxImplTizen::setPosition(const CCPoint& pos)
{
}

void CCEditBoxImplTizen::setVisible(bool visible)
{
}

void CCEditBoxImplTizen::setContentSize(const CCSize& size)
{
}

void CCEditBoxImplTizen::setAnchorPoint(const CCPoint& anchorPoint)
{
}

void CCEditBoxImplTizen::visit(void)
{
}

void CCEditBoxImplTizen::onEnter(void)
{
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    CCEditBoxImplTizen* thiz = (CCEditBoxImplTizen*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getCCEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getCCEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getCCEditBox());
    }
    
    CCEditBox* pEditBox = thiz->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "return",pEditBox);
    }
}

void CCEditBoxImplTizen::openKeyboard()
{
    if (_delegate != NULL)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }
    CCEditBox* pEditBox = this->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    }

    KeypadStyle keypadStyle = KEYPAD_STYLE_NORMAL;
    KeypadInputModeCategory keypadCategory = KEYPAD_MODE_ALPHA;
    bool bSingleLineEnabled = false;
    switch (_editBoxInputMode)
    {
    case kEditBoxInputModeAny:
        keypadStyle = KEYPAD_STYLE_NORMAL;
        break;
    case kEditBoxInputModeEmailAddr:
        keypadStyle = KEYPAD_STYLE_EMAIL;
        break;
    case kEditBoxInputModeNumeric:
    case kEditBoxInputModeDecimal:
        keypadStyle = KEYPAD_STYLE_NUMBER;
        keypadCategory = KEYPAD_MODE_NUMERIC;
        break;
    case kEditBoxInputModePhoneNumber:
        keypadStyle = KEYPAD_STYLE_PHONE_NUMBER;
        break;
    case kEditBoxInputModeUrl:
        keypadStyle = KEYPAD_STYLE_URL;
        break;
    case kEditBoxInputModeSingleLine:
        bSingleLineEnabled = true;
        break;
    default:
        keypadStyle = KEYPAD_STYLE_NORMAL;
        break;
    }

    bool bTextPrediction = true;
    switch (_editBoxInputFlag)
    {
    case kEditBoxInputFlagPassword:
        keypadStyle = KEYPAD_STYLE_PASSWORD;
        break;
    case kEditBoxInputFlagSensitive:
        bTextPrediction = false;
        break;
    default:
        break;
    }

    ((CCOspForm *)CCOspApplication::GetInstance()->getCCOspForm())->ShowKeypad(
        _text.c_str(),
        keypadStyle,
        keypadCategory,
        bSingleLineEnabled,
        bTextPrediction,
        _maxLength,
        editBoxCallbackFunc,
        (void*)this);
}

void CCEditBoxImplTizen::closeKeyboard()
{
    ((CCOspForm *)CCOspApplication::GetInstance()->getCCOspForm())->CloseKeypad();
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) */

