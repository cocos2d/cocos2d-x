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

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplWin(pEditBox);
}

CCEditBoxImplWin::CCEditBoxImplWin(CCEditBox* pEditText)
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

CCEditBoxImplWin::~CCEditBoxImplWin()
{
}

void CCEditBoxImplWin::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

bool CCEditBoxImplWin::initWithSize(const CCSize& size)
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

void CCEditBoxImplWin::setFont(const char* pFontName, int fontSize)
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

void CCEditBoxImplWin::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    m_pLabel->setColor(color);
}

void CCEditBoxImplWin::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplWin::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colPlaceHolder = color;
    m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplWin::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplWin::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
}

int CCEditBoxImplWin::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBoxImplWin::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplWin::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplWin::isEditing()
{
    return false;
}

void CCEditBoxImplWin::setText(const char* pText)
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

const char*  CCEditBoxImplWin::getText(void)
{
    return m_strText.c_str();
}

void CCEditBoxImplWin::setPlaceHolder(const char* pText)
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

void CCEditBoxImplWin::setPosition(const CCPoint& pos)
{
	//m_pLabel->setPosition(pos);
	//m_pLabelPlaceHolder->setPosition(pos);
}

void CCEditBoxImplWin::setVisible(bool visible)
{ // don't need to be implemented on win32 platform.
}

void CCEditBoxImplWin::setContentSize(const CCSize& size)
{
}

void CCEditBoxImplWin::setAnchorPoint(const CCPoint& anchorPoint)
{ // don't need to be implemented on win32 platform.
	
}

void CCEditBoxImplWin::visit(void)
{   
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    CCEditBoxImplWin* thiz = (CCEditBoxImplWin*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getCCEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getCCEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getCCEditBox());
    }
}

void CCEditBoxImplWin::openKeyboard()
{
    if (m_pDelegate != NULL)
    {
        m_pDelegate->editBoxEditingDidBegin(m_pEditBox);
    }

	std::string placeHolder = m_pLabelPlaceHolder->getString();
	if (placeHolder.length() == 0)
		placeHolder = "Enter value";

	char pText[100]= {0};
	std::string text = getText();
	if (text.length())
		strncpy(pText, text.c_str(), 100);
	bool didChange = CWin32InputBox::InputBox("Input", placeHolder.c_str(), pText, 100, false) == IDOK;
	
	if (didChange) 	
		setText(pText);

	if (m_pDelegate != NULL) {
		if (didChange)
			m_pDelegate->editBoxTextChanged(m_pEditBox, getText());
		m_pDelegate->editBoxEditingDidEnd(m_pEditBox);
		m_pDelegate->editBoxReturn(m_pEditBox);
	}
}

void CCEditBoxImplWin::closeKeyboard()
{

}

void CCEditBoxImplWin::onEnter(void)
{

}

NS_CC_EXT_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */
