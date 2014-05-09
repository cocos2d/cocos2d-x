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

#include "CCEditBoxImplWp8.h"
#include "CCEditBox.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
	return new CCEditBoxImplWp8(pEditBox);
}

CCEditBoxImplWp8::CCEditBoxImplWp8( CCEditBox* pEditText )
	: CCEditBoxImpl(pEditText)
	, m_pLabel(NULL)
	, m_pLabelPlaceHolder(NULL)
	, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
	, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
	, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
	, m_colText(ccWHITE)
	, m_colPlaceHolder(ccGRAY)
	, m_nMaxLength(-1)
{

}

CCEditBoxImplWp8::~CCEditBoxImplWp8()
{

}

void CCEditBoxImplWp8::openKeyboard()
{
	if (m_pDelegate != NULL)
	{
		m_pDelegate->editBoxEditingDidBegin(m_pEditBox);
	}

	CCEditBox* pEditBox = this->getCCEditBox();
	if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
	{
		cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
		pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
	}

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
		if (m_pDelegate != NULL) {
			m_pDelegate->editBoxTextChanged(m_pEditBox, getText());
			m_pDelegate->editBoxEditingDidEnd(m_pEditBox);
			m_pDelegate->editBoxReturn(m_pEditBox);
		}
	});

    CCEGLView::sharedOpenGLView()->OpenXamlEditBox(stringToPlatformString(placeHolder), stringToPlatformString(getText()), m_nMaxLength, m_eEditBoxInputMode, m_eEditBoxInputFlag, receiveHandler);
}

bool CCEditBoxImplWp8::initWithSize( const CCSize& size )
{
	//! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
	m_pLabel = CCLabelTTF::create("", "", size.height-12);
	// align the text vertically center
	m_pLabel->setAnchorPoint(ccp(0, 0.5f));
	m_pLabel->setPosition(ccp(5, size.height / 2.0f));
	m_pLabel->setColor(m_colText);
	m_pEditBox->addChild(m_pLabel);

	m_pLabelPlaceHolder = CCLabelTTF::create("", "", size.height-12);
	// align the text vertically center
	m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
	m_pLabelPlaceHolder->setPosition(ccp(5, size.height / 2.0f));
	m_pLabelPlaceHolder->setVisible(false);
	m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
	m_pEditBox->addChild(m_pLabelPlaceHolder);

	m_EditSize = size;
	return true;
}

void CCEditBoxImplWp8::setFont( const char* pFontName, int fontSize )
{
	if(m_pLabel != NULL) {
		m_pLabel->setFontName(pFontName);
		m_pLabel->setFontSize(fontSize);
	}

	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplWp8::setFontColor( const ccColor3B& color )
{
	m_colText = color;
	m_pLabel->setColor(color);
}

void CCEditBoxImplWp8::setPlaceholderFont( const char* pFontName, int fontSize )
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplWp8::setPlaceholderFontColor( const ccColor3B& color )
{
	m_colPlaceHolder = color;
	m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplWp8::setInputMode( EditBoxInputMode inputMode )
{
	m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplWp8::setInputFlag( EditBoxInputFlag inputFlag )
{
	m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplWp8::setMaxLength( int maxLength )
{
	m_nMaxLength = maxLength;
}

int CCEditBoxImplWp8::getMaxLength()
{
	return m_nMaxLength;
}

void CCEditBoxImplWp8::setReturnType( KeyboardReturnType returnType )
{
	m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplWp8::isEditing()
{
	return false;
}

void CCEditBoxImplWp8::setText( const char* pText )
{
	if (pText != NULL)
	{
		m_strText = pText;

		if (m_strText.length() > 0)
		{
			m_pLabelPlaceHolder->setVisible(false);

			std::string strToShow;

			if (kEditBoxInputFlagPassword == m_eEditBoxInputFlag)
			{
				long length = cc_utf8_strlen(m_strText.c_str());
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

const char* CCEditBoxImplWp8::getText( void )
{
	return m_strText.c_str();
}

void CCEditBoxImplWp8::setPlaceHolder( const char* pText )
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

void CCEditBoxImplWp8::setPosition( const CCPoint& pos )
{

}

void CCEditBoxImplWp8::setVisible( bool visible )
{

}

void CCEditBoxImplWp8::setContentSize( const CCSize& size )
{

}

void CCEditBoxImplWp8::setAnchorPoint( const CCPoint& anchorPoint )
{

}

void CCEditBoxImplWp8::visit( void )
{

}

void CCEditBoxImplWp8::doAnimationWhenKeyboardMove( float duration, float distance )
{

}

void CCEditBoxImplWp8::closeKeyboard()
{

}

void CCEditBoxImplWp8::onEnter( void )
{

}

Platform::String^ CCEditBoxImplWp8::stringToPlatformString( std::string strSrc )
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

std::string CCEditBoxImplWp8::PlatformStringTostring( Platform::String^ strSrc )
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

NS_CC_EXT_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
