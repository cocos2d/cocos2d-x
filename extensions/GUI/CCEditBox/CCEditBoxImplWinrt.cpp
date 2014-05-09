/****************************************************************************
 Copyright (c) 2010-2014 cocos2d-x.org
 
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
#include "CCEditBoxImplWinrt.h"
#include "CCEditBox.h"
#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplWinrt(pEditBox);
}

CCEditBoxImplWinrt::CCEditBoxImplWinrt(CCEditBox* pEditText)
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

CCEditBoxImplWinrt::~CCEditBoxImplWinrt()
{
}

void CCEditBoxImplWinrt::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

bool CCEditBoxImplWinrt::initWithSize(const CCSize& size)
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

void CCEditBoxImplWinrt::setFont(const char* pFontName, int fontSize)
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

void CCEditBoxImplWinrt::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    m_pLabel->setColor(color);
}

void CCEditBoxImplWinrt::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplWinrt::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colPlaceHolder = color;
    m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplWinrt::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplWinrt::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
}

int CCEditBoxImplWinrt::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBoxImplWinrt::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplWinrt::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplWinrt::isEditing()
{
    return false;
}

void CCEditBoxImplWinrt::setText(const char* pText)
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

const char*  CCEditBoxImplWinrt::getText(void)
{
    return m_strText.c_str();
}

void CCEditBoxImplWinrt::setPlaceHolder(const char* pText)
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

void CCEditBoxImplWinrt::setPosition(const CCPoint& pos)
{
	//m_pLabel->setPosition(pos);
	//m_pLabelPlaceHolder->setPosition(pos);
}

void CCEditBoxImplWinrt::setVisible(bool visible)
{ // don't need to be implemented on win32 platform.
}

void CCEditBoxImplWinrt::setContentSize(const CCSize& size)
{
}

void CCEditBoxImplWinrt::setAnchorPoint(const CCPoint& anchorPoint)
{ // don't need to be implemented on win32 platform.
	
}

void CCEditBoxImplWinrt::visit(void)
{   
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    CCEditBoxImplWinrt* thiz = (CCEditBoxImplWinrt*)ctx;
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

void CCEditBoxImplWinrt::openKeyboard()
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

	CCEGLView *glView = CCDirector::sharedDirector()->getOpenGLView();
	CCEditBoxParam^ param = ref new CCEditBoxParam();
	param->SetPlaceHolder(stringToPlatformString(placeHolder));
	param->SetEditText(stringToPlatformString(getText()));
	param->SetEditLength(m_nMaxLength);
	param->SetInputMode(m_eEditBoxInputMode);
	param->SetInputFlag(m_eEditBoxInputFlag);
	param->SetRespondsHandler(ref new Windows::Foundation::EventHandler<Platform::String^>(
		[this](Platform::Object^ sender, Platform::String^ arg)
	{
		setText(PlatformStringTostring(arg).c_str());
		if (m_pDelegate != NULL) {
			m_pDelegate->editBoxTextChanged(m_pEditBox, getText());
			m_pDelegate->editBoxEditingDidEnd(m_pEditBox);
			m_pDelegate->editBoxReturn(m_pEditBox);
		}
	}));
	glView->openEditBox(param);
}

void CCEditBoxImplWinrt::closeKeyboard()
{

}

void CCEditBoxImplWinrt::onEnter(void)
{

}

Platform::String^ CCEditBoxImplWinrt::stringToPlatformString( std::string strSrc )
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

std::string CCEditBoxImplWinrt::PlatformStringTostring( Platform::String^ strSrc )
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

