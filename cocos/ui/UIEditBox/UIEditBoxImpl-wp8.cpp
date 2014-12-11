/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#include "UIEditBoxImpl-wp8.h"
#include "UIEditBox.h"
#include "CCGLViewImpl-wp8.h"
#include "base/CCScriptSupport.h"
#include "base/ccUTF8.h"
#include "2d/CCLabel.h"

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
	return new UIEditBoxImplWp8(pEditBox);
}

UIEditBoxImplWp8::UIEditBoxImplWp8( EditBox* pEditText )
	: EditBoxImpl(pEditText)
	, m_pLabel(NULL)
	, m_pLabelPlaceHolder(NULL)
	, m_eEditBoxInputMode(EditBox::InputMode::SINGLE_LINE)
	, m_eEditBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
	, m_eKeyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
	, m_colText(Color3B::WHITE)
	, m_colPlaceHolder(Color3B::GRAY)
	, m_nMaxLength(-1)
{

}

UIEditBoxImplWp8::~UIEditBoxImplWp8()
{

}

void UIEditBoxImplWp8::openKeyboard()
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
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
	}
#endif
	std::string placeHolder = m_pLabelPlaceHolder->getString();
	if (placeHolder.length() == 0)
		placeHolder = "Enter value";

	char pText[100]= {0};
	std::string text = getText();
	if (text.length())
		strncpy(pText, text.c_str(), 100);

	Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler = ref new Windows::Foundation::EventHandler<Platform::String^>(
		[this](Platform::Object^ sender, Platform::String^ arg)
	{
		setText(PlatformStringTostring(arg).c_str());
		if (_delegate != NULL) {
			_delegate->editBoxTextChanged(_editBox, getText());
			_delegate->editBoxEditingDidEnd(_editBox);
			_delegate->editBoxReturn(_editBox);
		}
	});

    GLViewImpl::sharedOpenGLView()->OpenXamlEditBox(stringToPlatformString(placeHolder), stringToPlatformString(getText()), m_nMaxLength, (int)m_eEditBoxInputMode, (int)m_eEditBoxInputFlag, receiveHandler);
}

bool UIEditBoxImplWp8::initWithSize( const Size& size )
{
	//! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
	m_pLabel = Label::createWithSystemFont("", "", size.height-12);
	// align the text vertically center
	m_pLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	m_pLabel->setPosition(Vec2(5.0, size.height / 2.0f));
	m_pLabel->setColor(m_colText);
	_editBox->addChild(m_pLabel);

	m_pLabelPlaceHolder = Label::createWithSystemFont("", "", size.height-12);
	// align the text vertically center
	m_pLabelPlaceHolder->setAnchorPoint(Vec2(0.0f, 0.5f));
	m_pLabelPlaceHolder->setPosition(Vec2(5.0f, size.height / 2.0f));
	m_pLabelPlaceHolder->setVisible(false);
	m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
	_editBox->addChild(m_pLabelPlaceHolder);

	m_EditSize = size;
	return true;
}

void UIEditBoxImplWp8::setFont( const char* pFontName, int fontSize )
{
	if(m_pLabel != NULL) {
		m_pLabel->setSystemFontName(pFontName);
		m_pLabel->setSystemFontSize(fontSize);
	}

	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setSystemFontName(pFontName);
		m_pLabelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void UIEditBoxImplWp8::setFontColor( const Color3B& color )
{
	m_colText = color;
	m_pLabel->setColor(color);
}

void UIEditBoxImplWp8::setPlaceholderFont( const char* pFontName, int fontSize )
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setSystemFontName(pFontName);
		m_pLabelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void UIEditBoxImplWp8::setPlaceholderFontColor( const Color3B& color )
{
	m_colPlaceHolder = color;
	m_pLabelPlaceHolder->setColor(color);
}

void UIEditBoxImplWp8::setInputMode( EditBox::InputMode inputMode )
{
	m_eEditBoxInputMode = inputMode;
}

void UIEditBoxImplWp8::setInputFlag(EditBox::InputFlag inputFlag )
{
	m_eEditBoxInputFlag = inputFlag;
}

void UIEditBoxImplWp8::setMaxLength( int maxLength )
{
	m_nMaxLength = maxLength;
}

int UIEditBoxImplWp8::getMaxLength()
{
	return m_nMaxLength;
}

void UIEditBoxImplWp8::setReturnType( EditBox::KeyboardReturnType returnType )
{
	m_eKeyboardReturnType = returnType;
}

bool UIEditBoxImplWp8::isEditing()
{
	return false;
}

void UIEditBoxImplWp8::setText( const char* pText )
{
	if (pText != NULL)
	{
		m_strText = pText;

		if (m_strText.length() > 0)
		{
			m_pLabelPlaceHolder->setVisible(false);

			std::string strToShow;

			if (EditBox::InputFlag::PASSWORD == m_eEditBoxInputFlag)
			{
				long length = cc_utf8_strlen(m_strText.c_str(), -1);
				for (long i = 0; i < length; i++)
				{
					strToShow.append("*");
				}
			}
			else
			{
				strToShow = m_strText;
			}

			//! std::string strWithEllipsis = getStringWithEllipsisJni(strToShow.c_str(), m_EditSize.width, m_EditSize.height-12);
			//! m_pLabel->setString(strWithEllipsis.c_str());
			m_pLabel->setString(strToShow.c_str());
		}
		else
		{
			m_pLabelPlaceHolder->setVisible(true);
			m_pLabel->setString("");
		}

	}
}

const char* UIEditBoxImplWp8::getText( void )
{
	return m_strText.c_str();
}

void UIEditBoxImplWp8::setPlaceHolder( const char* pText )
{
	if (pText != NULL)
	{
		m_strPlaceHolder = pText;
		if (m_strPlaceHolder.length() > 0 && m_strText.length() == 0)
		{
			m_pLabelPlaceHolder->setVisible(true);
		}

		m_pLabelPlaceHolder->setString(m_strPlaceHolder.c_str());
	}
}

void UIEditBoxImplWp8::setPosition( const Vec2& pos )
{

}

void UIEditBoxImplWp8::setVisible( bool visible )
{

}

void UIEditBoxImplWp8::setContentSize( const Size& size )
{

}

void UIEditBoxImplWp8::setAnchorPoint( const Vec2& anchorPoint )
{

}

void UIEditBoxImplWp8::visit( void )
{

}

void UIEditBoxImplWp8::doAnimationWhenKeyboardMove( float duration, float distance )
{

}

void UIEditBoxImplWp8::closeKeyboard()
{

}

void UIEditBoxImplWp8::onEnter( void )
{

}

Platform::String^ UIEditBoxImplWp8::stringToPlatformString( std::string strSrc )
{
	// to wide char
	int nStrLen = MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, NULL, 0);  
	wchar_t* pWStr = new wchar_t[nStrLen + 1];  
	memset(pWStr, 0, nStrLen + 1);  
	MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, pWStr, nStrLen);  
	Platform::String^ strDst = ref new Platform::String(pWStr);
	delete[] pWStr;
	return strDst;
}

std::string UIEditBoxImplWp8::PlatformStringTostring( Platform::String^ strSrc )
{
	const wchar_t* pWStr = strSrc->Data();
	int nStrLen = WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, NULL, 0, NULL, NULL);  
	char* pStr = new char[nStrLen + 1];  
	memset(pStr, 0, nStrLen + 1);  
	WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, pStr, nStrLen, NULL, NULL);  ;  

	std::string strDst = std::string(pStr);

	delete[] pStr;
	return strDst;
}

}

NS_CC_END

#endif // WP8
