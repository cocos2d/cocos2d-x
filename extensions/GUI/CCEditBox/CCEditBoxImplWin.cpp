/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013 Jozef Pridavok
 
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
#include "CCEditBoxImplWin.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "CCEditBox.h"
#include "proj.win32/Win32InputBox.h"

NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplWin(pEditBox);
}

EditBoxImplWin::EditBoxImplWin(EditBox* pEditText)
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

EditBoxImplWin::~EditBoxImplWin()
{
}

void EditBoxImplWin::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

bool EditBoxImplWin::initWithSize(const Size& size)
{
    //! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
    _label = LabelTTF::create("", "", size.height-12);
	// align the text vertically center
    _label->setAnchorPoint(Point(0, 0.5f));
    _label->setPosition(Point(5, size.height / 2.0f));
    _label->setColor(_colText);
    _editBox->addChild(_label);

    _labelPlaceHolder = LabelTTF::create("", "", size.height-12);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Point(0, 0.5f));
    _labelPlaceHolder->setPosition(Point(5, size.height / 2.0f));
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);
    
    _editSize = size;
    return true;
}

void EditBoxImplWin::setFont(const char* pFontName, int fontSize)
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

void EditBoxImplWin::setFontColor(const Color3B& color)
{
    _colText = color;
    _label->setColor(color);
}

void EditBoxImplWin::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(_labelPlaceHolder != NULL) {
		_labelPlaceHolder->setFontName(pFontName);
		_labelPlaceHolder->setFontSize(fontSize);
	}
}

void EditBoxImplWin::setPlaceholderFontColor(const Color3B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setColor(color);
}

void EditBoxImplWin::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplWin::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplWin::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplWin::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplWin::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplWin::isEditing()
{
    return false;
}

void EditBoxImplWin::setText(const char* pText)
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

            //! std::string strWithEllipsis = getStringWithEllipsisJni(strToShow.c_str(), _editSize.width, _editSize.height-12);
            //! _label->setString(strWithEllipsis.c_str());
			_label->setString(strToShow.c_str());
        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }

    }
}

const char*  EditBoxImplWin::getText(void)
{
    return _text.c_str();
}

void EditBoxImplWin::setPlaceHolder(const char* pText)
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

void EditBoxImplWin::setPosition(const Point& pos)
{
	//_label->setPosition(pos);
	//_labelPlaceHolder->setPosition(pos);
}

void EditBoxImplWin::setVisible(bool visible)
{ // don't need to be implemented on win32 platform.
}

void EditBoxImplWin::setContentSize(const Size& size)
{
}

void EditBoxImplWin::setAnchorPoint(const Point& anchorPoint)
{ // don't need to be implemented on win32 platform.
	
}

void EditBoxImplWin::visit(void)
{   
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    EditBoxImplWin* thiz = (EditBoxImplWin*)ctx;
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

void EditBoxImplWin::openKeyboard()
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
    
	std::string placeHolder = _labelPlaceHolder->getString();
	if (placeHolder.length() == 0)
		placeHolder = "Enter value";

	char pText[100]= {0};
	std::string text = getText();
	if (text.length())
		strncpy(pText, text.c_str(), 100);
	bool didChange = CWin32InputBox::InputBox("Input", placeHolder.c_str(), pText, 100, false) == IDOK;
	
	if (didChange) 	
		setText(pText);

	if (_delegate != NULL) {
		if (didChange)
			_delegate->editBoxTextChanged(_editBox, getText());
		_delegate->editBoxEditingDidEnd(_editBox);
		_delegate->editBoxReturn(_editBox);
	}
}

void EditBoxImplWin::closeKeyboard()
{

}

void EditBoxImplWin::onEnter(void)
{

}

NS_CC_EXT_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */
