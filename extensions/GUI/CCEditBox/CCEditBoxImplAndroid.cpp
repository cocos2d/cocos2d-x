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
#include "CCEditBox.h"
#include "jni/EditBoxJni.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplAndroid(pEditBox);
}

CCEditBoxImplAndroid::CCEditBoxImplAndroid(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pLabel(NULL)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_colText(ccWHITE)
, m_colPlaceHolder(ccGRAY)
, m_nMaxLength(-1)
{
    
}

CCEditBoxImplAndroid::~CCEditBoxImplAndroid()
{

}

void CCEditBoxImplAndroid::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on android platform.

}

bool CCEditBoxImplAndroid::initWithSize(const CCSize& size)
{
    m_pLabel = CCLabelTTF::create("", "", size.height-10);
    m_pLabel->setAnchorPoint(ccp(0, 0));
    m_pLabel->setPosition(ccp(5, 5));
    m_pEditBox->addChild(m_pLabel);

    return true;
}

void CCEditBoxImplAndroid::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    m_pLabel->setColor(color);
}

void CCEditBoxImplAndroid::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colPlaceHolder = color;
}

void CCEditBoxImplAndroid::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplAndroid::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
}

int CCEditBoxImplAndroid::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBoxImplAndroid::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplAndroid::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplAndroid::isEditing()
{
    return false;
}

void CCEditBoxImplAndroid::setText(const char* pText)
{
    if (pText != NULL)
    {
        m_strText = pText;
        m_pLabel->setString(pText);
    }
}

const char*  CCEditBoxImplAndroid::getText(void)
{
    return m_strText.c_str();
}

void CCEditBoxImplAndroid::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        m_strPlaceHolder = pText;
    }
}

void CCEditBoxImplAndroid::setPosition(const CCPoint& pos)
{ // don't need to be implemented on android platform.

}

void CCEditBoxImplAndroid::setContentSize(const CCSize& size)
{ // don't need to be implemented on android platform.

}

void CCEditBoxImplAndroid::visit(void)
{ // don't need to be implemented on android platform.
    
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    CCEditBoxImplAndroid* thiz = (CCEditBoxImplAndroid*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getCCEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getCCEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getCCEditBox());
    }
}

void CCEditBoxImplAndroid::openKeyboard()
{
    if (m_pDelegate != NULL)
    {
        m_pDelegate->editBoxEditingDidBegin(m_pEditBox);
    }

    showEditBoxActivityJni( m_strPlaceHolder.c_str(),
                            m_strText.c_str(),
                            m_eEditBoxInputMode,
                            m_eEditBoxInputFlag,
                            m_eKeyboardReturnType,
                            m_nMaxLength,
                            editBoxCallbackFunc,
                            (void*)this);

}

void CCEditBoxImplAndroid::closeKeyboard()
{

}

NS_CC_EXT_END

