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

#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_BEGIN

static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);

        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////

CCTextFieldTTF::CCTextFieldTTF()
: _delegate(0)
, _charCount(0)
, _inputText(new std::string)
, _placeHolder(new std::string)   // prevent CCLabelTTF initWithString assertion
, _secureTextEntry(false)
{
    _colorSpaceHolder.r = _colorSpaceHolder.g = _colorSpaceHolder.b = 127;
}

CCTextFieldTTF::~CCTextFieldTTF()
{
    CC_SAFE_DELETE(_inputText);
    CC_SAFE_DELETE(_placeHolder);
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////

CCTextFieldTTF * CCTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
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

bool CCTextFieldTTF::initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(_placeHolder);
        _placeHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(_placeHolder->c_str(), fontName, fontSize, dimensions, alignment);
}
bool CCTextFieldTTF::initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(_placeHolder);
        _placeHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(_placeHolder->c_str(), fontName, fontSize);
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

bool CCTextFieldTTF::detachWithIME()
{
    bool bRet = CCIMEDelegate::detachWithIME();
    if (bRet)
    {
        // close keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(false);
        }
    }
    return bRet;
}

bool CCTextFieldTTF::canAttachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldAttachWithIME(this)) : true;
}

bool CCTextFieldTTF::canDetachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldDetachWithIME(this)) : true;
}

void CCTextFieldTTF::insertText(const char * text, int len)
{
    std::string sInsert(text, len);

    // insert \n means input end
    int nPos = sInsert.find('\n');
    if ((int)sInsert.npos != nPos)
    {
        len = nPos;
        sInsert.erase(nPos);
    }

    if (len > 0)
    {
        if (_delegate && _delegate->onTextFieldInsertText(this, sInsert.c_str(), len))
        {
            // delegate doesn't want to insert text
            return;
        }

        _charCount += _calcCharCount(sInsert.c_str());
        std::string sText(*_inputText);
        sText.append(sInsert);
        setString(sText.c_str());
    }

    if ((int)sInsert.npos == nPos) {
        return;
    }

    // '\n' inserted, let delegate process first
    if (_delegate && _delegate->onTextFieldInsertText(this, "\n", 1))
    {
        return;
    }

    // if delegate hasn't processed, detach from IME by default
    detachWithIME();
}

void CCTextFieldTTF::deleteBackward()
{
    int nStrLen = _inputText->length();
    if (! nStrLen)
    {
        // there is no string
        return;
    }

    // get the delete byte number
    int nDeleteLen = 1;    // default, erase 1 byte

    while(0x80 == (0xC0 & _inputText->at(nStrLen - nDeleteLen)))
    {
        ++nDeleteLen;
    }

    if (_delegate && _delegate->onTextFieldDeleteBackward(this, _inputText->c_str() + nStrLen - nDeleteLen, nDeleteLen))
    {
        // delegate doesn't wan't to delete backwards
        return;
    }

    // if all text deleted, show placeholder string
    if (nStrLen <= nDeleteLen)
    {
        CC_SAFE_DELETE(_inputText);
        _inputText = new std::string;
        _charCount = 0;
        CCLabelTTF::setString(_placeHolder->c_str());
        return;
    }

    // set new input text
    std::string sText(_inputText->c_str(), nStrLen - nDeleteLen);
    setString(sText.c_str());
}

const char * CCTextFieldTTF::getContentText()
{
    return _inputText->c_str();
}

void CCTextFieldTTF::draw()
{
    if (_delegate && _delegate->onDraw(this))
    {
        return;
    }
    if (_inputText->length())
    {
        CCLabelTTF::draw();
        return;
    }

    // draw placeholder
    ccColor3B color = getColor();
    setColor(_colorSpaceHolder);
    CCLabelTTF::draw();
    setColor(color);
}

const ccColor3B& CCTextFieldTTF::getColorSpaceHolder()
{
    return _colorSpaceHolder;
}

void CCTextFieldTTF::setColorSpaceHolder(const ccColor3B& color)
{
    _colorSpaceHolder = color;
}

//////////////////////////////////////////////////////////////////////////
// properties
//////////////////////////////////////////////////////////////////////////

// input text property
void CCTextFieldTTF::setString(const char *text)
{
    static char bulletString[] = {(char)0xe2, (char)0x80, (char)0xa2, (char)0x00};
    std::string displayText;
    int length;

    CC_SAFE_DELETE(_inputText);

    if (text)
    {
        _inputText = new std::string(text);
        displayText = *_inputText;
        if (_secureTextEntry)
        {
            displayText = "";
            length = _inputText->length();
            while (length)
            {
                displayText.append(bulletString);
                --length;
            }
        }
    }
    else
    {
        _inputText = new std::string;
    }

    // if there is no input text, display placeholder instead
    if (! _inputText->length())
    {
        CCLabelTTF::setString(_placeHolder->c_str());
    }
    else
    {
        CCLabelTTF::setString(displayText.c_str());
    }
    _charCount = _calcCharCount(_inputText->c_str());
}

const char* CCTextFieldTTF::getString(void)
{
    return _inputText->c_str();
}

// place holder text property
void CCTextFieldTTF::setPlaceHolder(const char * text)
{
    CC_SAFE_DELETE(_placeHolder);
    _placeHolder = (text) ? new std::string(text) : new std::string;
    if (! _inputText->length())
    {
        CCLabelTTF::setString(_placeHolder->c_str());
    }
}

const char * CCTextFieldTTF::getPlaceHolder(void)
{
    return _placeHolder->c_str();
}

// secureTextEntry
void CCTextFieldTTF::setSecureTextEntry(bool value)
{
    if (_secureTextEntry != value)
    {
        _secureTextEntry = value;
        setString(getString());
    }
}

bool CCTextFieldTTF::isSecureTextEntry()
{
    return _secureTextEntry;
}

NS_CC_END
