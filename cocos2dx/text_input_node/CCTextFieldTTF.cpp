/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCTextFieldTTF.h"

#include <vector>

#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_BEGIN;

/**
@brief	Use std::vector store every input text length.
*/
class CCTextFieldTTF::LengthStack : public std::vector< unsigned short >
{
};

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////

CCTextFieldTTF::CCTextFieldTTF()
: m_pInputText(new std::string)
, m_pPlaceHolder(new std::string)   // prevent CCLabelTTF initWithString assertion
, m_pLens(new LengthStack)
, m_bLock(false)
{
}

CCTextFieldTTF::~CCTextFieldTTF()
{
    CC_SAFE_DELETE(m_pInputText);
    CC_SAFE_DELETE(m_pPlaceHolder);
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////

CCTextFieldTTF * CCTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{		
    CCTextFieldTTF *pRet = new CCTextFieldTTF();
    if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
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

CCTextFieldTTF * CCTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    CCTextFieldTTF *pRet = new CCTextFieldTTF();
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

//////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////

bool CCTextFieldTTF::initWithPlaceHolder(const char *placeholder, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(m_pPlaceHolder);
        m_pPlaceHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(m_pPlaceHolder->c_str(), dimensions, alignment, fontName, fontSize);
}
bool CCTextFieldTTF::initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(m_pPlaceHolder);
        m_pPlaceHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(m_pPlaceHolder->c_str(), fontName, fontSize);
}

//////////////////////////////////////////////////////////////////////////
// CCIMEDelegate
//////////////////////////////////////////////////////////////////////////

bool CCTextFieldTTF::attachWithIME()
{
    bool bRet = CCIMEDelegate::attachWithIME();
    if (bRet)
    {
        // open keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(true);
        }
    }
    return bRet;
}

bool CCTextFieldTTF::canAttachWithIME()
{
    return true;
}

bool CCTextFieldTTF::canDetatchWithIME()
{
    return true;
}

void CCTextFieldTTF::detatchWithIME()
{
    CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
    if (pGlView)
    {
        pGlView->setIMEKeyboardState(false);
    }
}

void CCTextFieldTTF::insertText(const char * text, int len)
{
    m_bLock = true;
    std::string sText(*m_pInputText);
    sText.append(text, len);
    m_pLens->push_back((unsigned short)len);
    setString(sText.c_str());
    m_bLock = false;
}

void CCTextFieldTTF::deleteBackward()
{
    int nStrLen = m_pInputText->length();
    if (! nStrLen)
    {
        // there is no string
        return;
    }

    m_bLock = true;

    // get the delete byte number
    int nStackSize = m_pLens->size();
    unsigned short uDeleteLen = 1;    // default, erase 1 byte
    if (nStackSize) 
    {
        // get the last input text size
        uDeleteLen = m_pLens->at(nStackSize - 1);
        m_pLens->pop_back();
    }

    // if delete all text, show space holder string
    if (nStrLen <= uDeleteLen)
    {
        CC_SAFE_DELETE(m_pInputText);
        m_pInputText = new std::string;
        CCLabelTTF::setString(m_pPlaceHolder->c_str());
        return;
    }

    // set new input text
    std::string sText(m_pInputText->c_str(), nStrLen - uDeleteLen);
    setString(sText.c_str());
    m_bLock = false;
}

//////////////////////////////////////////////////////////////////////////
// properties
//////////////////////////////////////////////////////////////////////////

// input text property
void CCTextFieldTTF::setString(const char *text)
{
    CC_SAFE_DELETE(m_pInputText);
    if (false == m_bLock)
    {
        // user use this function to set string value, clear lenStack
        m_pLens->clear();
    }
    if (text)
    {
        m_pInputText = new std::string(text);
    }
    else
    {
        m_pInputText = new std::string;
    }

    // if there is no input text, display placeholder instead    if (! m_pInputText->length())    {        CCLabelTTF::setString(m_pPlaceHolder->c_str());    }    else
    {
        CCLabelTTF::setString(m_pInputText->c_str());
    }
}

const char* CCTextFieldTTF::getString(void)
{
    return m_pInputText->c_str();
}

// place holder text property
void CCTextFieldTTF::setPlaceHolder(const char * text)
{
    CC_SAFE_DELETE(m_pPlaceHolder);
    m_pPlaceHolder = (text) ? new std::string(text) : new std::string;
    if (! m_pInputText->length())
    {
        CCLabelTTF::setString(m_pPlaceHolder->c_str());
    }
}

const char * CCTextFieldTTF::getPlaceHolder(void)
{
    return m_pPlaceHolder->c_str();
}

NS_CC_END;
