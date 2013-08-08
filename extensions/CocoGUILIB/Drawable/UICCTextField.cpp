/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "UICCTextField.h"

NS_CC_EXT_BEGIN

UICCTextField::UICCTextField()
: m_bMaxLengthEnable(false)
, m_nMaxLength(0)
, m_bPasswordEnable(false)
, m_strPasswordStyleText("*")
, m_bAttachWithIME(false)
, m_bDetachWithIME(false)
, m_bInsertText(false)
, m_bDeleteBackward(false)
{
}

UICCTextField::~UICCTextField()
{
}

UICCTextField * UICCTextField::create(const char *placeholder, const char *fontName, float fontSize)
{
    UICCTextField *pRet = new UICCTextField();
    
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    
    return NULL;
}

void UICCTextField::onEnter()
{
    CCTextFieldTTF::setDelegate(this);
}


bool UICCTextField::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)
{
    setAttachWithIME(true);
    return false;
}

bool UICCTextField::onTextFieldInsertText(CCTextFieldTTF *pSender, const char *text, int nLen)
{
    if (nLen == 1 && strcmp(text, "\n") == 0)
    {
        return false;
    }
    setInsertText(true);
    if (m_bMaxLengthEnable)
    {
        if (CCTextFieldTTF::getCharCount() >= m_nMaxLength)
        {
            return true;
        }
    }
    
    return false;
}

bool UICCTextField::onTextFieldDeleteBackward(CCTextFieldTTF *pSender, const char *delText, int nLen)
{
    setDeleteBackward(true);
    return false;
}

bool UICCTextField::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)
{
    setDetachWithIME(true);
    return false;
}

void UICCTextField::insertText(const char * text, int len)
{
    std::string str_text = text;
    int str_len = strlen(CCTextFieldTTF::getString());
    
    if (strcmp(text, "\n") != 0)
    {
        if (m_bMaxLengthEnable)
        {
            int multiple = 1;
            char value = text[0];
            if (value < 0 || value > 127)
            {
                multiple = 3;
            }            
            
            if (str_len + len > m_nMaxLength * multiple)
            {
                str_text = str_text.substr(0, m_nMaxLength * multiple);
                len = m_nMaxLength * multiple;
                /*
                 int mod = str_len % 3;
                 int offset = (mod == 0) ? 0 : (3 - mod);
                 int amount = str_len + offset;
                 str_text = str_text.substr(0, m_nMaxLength - amount);
                 //                CCLOG("str_test = %s", str_text.c_str());
                 */
            }
        }
    }
    CCTextFieldTTF::insertText(str_text.c_str(), len);
    
    // password
    if (m_bPasswordEnable)
    {
        setPasswordText(m_pInputText->c_str());
    }
}

void UICCTextField::deleteBackward()
{
    CCTextFieldTTF::deleteBackward();
    
    if (CCTextFieldTTF::getCharCount() > 0)
    {
        // password
        if (m_bPasswordEnable)
        {
            setPasswordText(m_pInputText->c_str());
        }
    }        
}

void UICCTextField::openIME()
{
    CCTextFieldTTF::attachWithIME();
}

void UICCTextField::closeIME()
{
    CCTextFieldTTF::detachWithIME();
}

void UICCTextField::setMaxLengthEnable(bool enable)
{
    m_bMaxLengthEnable = enable;
}

bool UICCTextField::isMaxLengthEnable()
{
    return m_bMaxLengthEnable;
}

void UICCTextField::setMaxLength(int length)
{
    m_nMaxLength = length;
}

int UICCTextField::getMaxLength()
{
    return m_nMaxLength;
}

int UICCTextField::getCharCount()
{
    return CCTextFieldTTF::getCharCount();
}

void UICCTextField::setPasswordEnable(bool enable)
{
    m_bPasswordEnable = enable;
}

bool UICCTextField::isPasswordEnable()
{
    return m_bPasswordEnable;
}

void UICCTextField::setPasswordStyleText(const char* styleText)
{
    if (strlen(styleText) > 1)
    {
        return;
    }
    char value = styleText[0];
    if (value < 33 || value > 126)
    {
        return;
    }
    m_strPasswordStyleText = styleText;
}

void UICCTextField::setPasswordText(const char *text)
{
    std::string tempStr;
    for (int i = 0; i < strlen(text); ++i)
    {
        tempStr.append(m_strPasswordStyleText);
    }
    CCLabelTTF::setString(tempStr.c_str());
}

void UICCTextField::setAttachWithIME(bool attach)
{
    m_bAttachWithIME = attach;
}

bool UICCTextField::getAttachWithIME()
{
    return m_bAttachWithIME;
}

void UICCTextField::setDetachWithIME(bool detach)
{
    m_bDetachWithIME = detach;
}

bool UICCTextField::getDetachWithIME()
{
    return m_bDetachWithIME;
}

void UICCTextField::setInsertText(bool insert)
{
    m_bInsertText = insert;
}

bool UICCTextField::getInsertText()
{
    return m_bInsertText;
}

void UICCTextField::setDeleteBackward(bool deleteBackward)
{
    m_bDeleteBackward = deleteBackward;
}

bool UICCTextField::getDeleteBackward()
{
    return m_bDeleteBackward;
}

NS_CC_EXT_END