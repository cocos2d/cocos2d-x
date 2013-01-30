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
#include "CCEditBox.h"
#include "proj.win32/Win32InputBox.h"

NS_CC_BEGIN
extern long cc_utf8_strlen (const char * p, int max);
NS_CC_END

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
    m_pLabel->setAnchorPoint(ccp(0, 0));
    m_pLabel->setPosition(ccp(5, 2));
    m_pLabel->setColor(m_colText);
    m_pEditBox->addChild(m_pLabel);

    m_pLabelPlaceHolder = CCLabelTTF::create("", "", size.height-12);
    m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0));
    m_pLabelPlaceHolder->setPosition(ccp(5, 2));
    m_pLabelPlaceHolder->setVisible(false);
    m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
    m_pEditBox->addChild(m_pLabelPlaceHolder);
    
    m_EditSize = size;
    return true;
}

void CCEditBoxImplWin::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    m_pLabel->setColor(color);
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
                long length = strlen(m_strText.c_str());
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

void CCEditBoxImplWin::setContentSize(const CCSize& size)
{
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

NS_CC_EXT_END

/*

#include "CCEditBoxImplWin.h"
#include "CCEditBox.h"
#include "CCEGLView.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplWin(pEditBox);
}

//#define GET_IMPL ((CCEditBoxImplWin*)m_pSysEdit)

CCEditBoxImplWin::CCEditBoxImplWin(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pSysEdit(NULL)
, m_nMaxTextLength(-1)
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
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
		CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();

		HWND hParent = pMainWnd->getHWnd();
        m_pSysEdit = ::CreateWindowA("EDIT", "text", WS_CHILD|WS_CLIPCHILDREN|WS_VISIBLE, 0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY(), hParent, NULL, NULL, NULL);
        if (!m_pSysEdit) 
			break;

        return true;
    } while (0);
    
    return false;
}

void CCEditBoxImplWin::setFontColor(const ccColor3B& color)
{
    //GET_IMPL.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
}

void CCEditBoxImplWin::setPlaceholderFontColor(const ccColor3B& color)
{
    // TODO need to be implemented.
}

void CCEditBoxImplWin::setInputMode(EditBoxInputMode inputMode)
{
}

void CCEditBoxImplWin::setMaxLength(int maxLength)
{
    m_nMaxTextLength = maxLength;
}

int CCEditBoxImplWin::getMaxLength()
{
    return m_nMaxTextLength;
}

void CCEditBoxImplWin::setInputFlag(EditBoxInputFlag inputFlag)
{
	// TODO: ES_PASSWORD 
}

void CCEditBoxImplWin::setReturnType(KeyboardReturnType returnType)
{
}

bool CCEditBoxImplWin::isEditing()
{
    return true; //GET_IMPL->isEditState() ? true : false;
}

void CCEditBoxImplWin::setText(const char* pText)
{
	::SetWindowTextA(m_pSysEdit, pText);
    //GET_IMPL.textField.text = [NSString stringWithUTF8String:pText];
}

const char*  CCEditBoxImplWin::getText(void)
{
	int nCharacters = ::GetWindowTextLength(m_pSysEdit);
	char *szBuff = (char *)malloc(nCharacters + 1);
	::GetWindowText(m_pSysEdit, szBuff, nCharacters);
	return szBuff;
}

void CCEditBoxImplWin::setPlaceHolder(const char* pText)
{
}

void CCEditBoxImplWin::setPosition(const CCPoint& pos)
{
    //TODO should consider anchor point, the default value is (0.5, 0,5)
	RECT rect;
	::GetWindowRect(m_pSysEdit, &rect);
	POINT pt;
	pt.x = rect.left;
	pt.y = rect.top;
	CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();
	::ScreenToClient(pMainWnd->getHWnd(), &pt);
	::SetWindowPos(m_pSysEdit, NULL, pt.x + pos.x-m_tContentSize.width/2, pt.y + pos.y+m_tContentSize.height/2, 0, 0, SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_NOCOPYBITS);
    //GET_IMPL->setPosition(ccp(pos.x-m_tContentSize.width/2, pos.y+m_tContentSize.height/2));;
}

void CCEditBoxImplWin::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
}

void CCEditBoxImplWin::visit(void)
{
    
}

void CCEditBoxImplWin::openKeyboard()
{
}

void CCEditBoxImplWin::closeKeyboard()
{
}

NS_CC_EXT_END

*/