/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#include "CCEditBoxImplAndroid.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "CCEditBox.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"


NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplAndroid(pEditBox);
}

EditBoxImplAndroid::EditBoxImplAndroid(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{
    
}

EditBoxImplAndroid::~EditBoxImplAndroid()
{
	
}

void EditBoxImplAndroid::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on android platform.
	
}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplAndroid::initWithSize(const Size& size)
{
    int fontSize = getFontSizeAccordingHeightJni(size.height-12);
    _label = Label::create();
    _label->setSystemFontSize(size.height-12);
	// align the text vertically center
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setColor(_colText);
    _editBox->addChild(_label);
	
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setSystemFontSize(size.height-12);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);
    
    _editSize = size;
    return true;
}

void EditBoxImplAndroid::setFont(const char* pFontName, int fontSize)
{
	if(_label != NULL) {
		_label->setSystemFontName(pFontName);
		_label->setSystemFontSize(fontSize);
	}
	
	if(_labelPlaceHolder != NULL) {
		_labelPlaceHolder->setSystemFontName(pFontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplAndroid::setFontColor(const Color3B& color)
{
    _colText = color;
    _label->setColor(color);
}

void EditBoxImplAndroid::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(_labelPlaceHolder != NULL) {
		_labelPlaceHolder->setSystemFontName(pFontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplAndroid::setPlaceholderFontColor(const Color3B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setColor(color);
}

void EditBoxImplAndroid::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplAndroid::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplAndroid::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplAndroid::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplAndroid::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplAndroid::isEditing()
{
    return false;
}

void EditBoxImplAndroid::setText(const char* pText)
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
            auto labelSize = _label->getContentSize();
            if(labelSize.width > fMaxWidth) {
                _label->setDimensions(fMaxWidth,labelSize.height);
            }
        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }
		
    }
}

const char*  EditBoxImplAndroid::getText(void)
{
    return _text.c_str();
}

void EditBoxImplAndroid::setPlaceHolder(const char* pText)
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

void EditBoxImplAndroid::setPosition(const Vec2& pos)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::setVisible(bool visible)
{ // don't need to be implemented on android platform.

}

void EditBoxImplAndroid::setContentSize(const Size& size)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::setAnchorPoint(const Vec2& anchorPoint)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::visit(void)
{ // don't need to be implemented on android platform.
    
}

void EditBoxImplAndroid::onEnter(void)
{ // don't need to be implemented on android platform.
    
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    EditBoxImplAndroid* thiz = (EditBoxImplAndroid*)ctx;
    thiz->setText(pText);
	
    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = thiz->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "ended", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}

void EditBoxImplAndroid::openKeyboard()
{
    if (_delegate != NULL)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
	
    showEditTextDialogJNI(  _placeHolder.c_str(),
						  _text.c_str(),
						  (int)_editBoxInputMode,
						  (int)_editBoxInputFlag,
						  (int)_keyboardReturnType,
						  _maxLength,
						  editBoxCallbackFunc,
						  (void*)this  );
	
}

void EditBoxImplAndroid::closeKeyboard()
{
	
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

