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

TextFieldTTF::TextFieldTTF()
: _delegate(0)
, _charCount(0)
, _inputText("")
, _placeHolder("")   // prevent LabelTTF initWithString assertion
, _secureTextEntry(false)
{
    _colorSpaceHolder.r = _colorSpaceHolder.g = _colorSpaceHolder.b = 127;
}

TextFieldTTF::~TextFieldTTF()
{
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////

TextFieldTTF * TextFieldTTF::textFieldWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize)
{
    TextFieldTTF *ret = new TextFieldTTF();
    if(ret && ret->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
    {
        ret->autorelease();
        if (placeholder.size()>0)
        {
            ret->setPlaceHolder(placeholder);
        }
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return NULL;
}

TextFieldTTF * TextFieldTTF::textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize)
{
    TextFieldTTF *ret = new TextFieldTTF();
    if(ret && ret->initWithString("", fontName, fontSize))
    {
        ret->autorelease();
        if (placeholder.size()>0)
        {
            ret->setPlaceHolder(placeholder);
        }
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return NULL;
}

//////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////

bool TextFieldTTF::initWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize)
{
    _placeHolder = placeholder;
    return LabelTTF::initWithString(_placeHolder, fontName, fontSize, dimensions, alignment);
}
bool TextFieldTTF::initWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize)
{
    _placeHolder = std::string(placeholder);
    return LabelTTF::initWithString(_placeHolder, fontName, fontSize);
}

//////////////////////////////////////////////////////////////////////////
// IMEDelegate
//////////////////////////////////////////////////////////////////////////

bool TextFieldTTF::attachWithIME()
{
    bool bRet = IMEDelegate::attachWithIME();
    if (bRet)
    {
        // open keyboard
        EGLView * pGlView = Director::getInstance()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(true);
        }
    }
    return bRet;
}

bool TextFieldTTF::detachWithIME()
{
    bool bRet = IMEDelegate::detachWithIME();
    if (bRet)
    {
        // close keyboard
        EGLView * pGlView = Director::getInstance()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(false);
        }
    }
    return bRet;
}

bool TextFieldTTF::canAttachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldAttachWithIME(this)) : true;
}

bool TextFieldTTF::canDetachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldDetachWithIME(this)) : true;
}

void TextFieldTTF::insertText(const char * text, int len)
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
        std::string sText(_inputText);
        sText.append(sInsert);
        setString(sText);
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

void TextFieldTTF::deleteBackward()
{
    int nStrLen = _inputText.length();
    if (! nStrLen)
    {
        // there is no string
        return;
    }

    // get the delete byte number
    int nDeleteLen = 1;    // default, erase 1 byte

    while(0x80 == (0xC0 & _inputText.at(nStrLen - nDeleteLen)))
    {
        ++nDeleteLen;
    }

    if (_delegate && _delegate->onTextFieldDeleteBackward(this, _inputText.c_str() + nStrLen - nDeleteLen, nDeleteLen))
    {
        // delegate doesn't wan't to delete backwards
        return;
    }

    // if all text deleted, show placeholder string
    if (nStrLen <= nDeleteLen)
    {
        _inputText = "";
        _charCount = 0;
        LabelTTF::setString(_placeHolder);
        return;
    }

    // set new input text
    std::string sText(_inputText.c_str(), nStrLen - nDeleteLen);
    setString(sText);
}

const char * TextFieldTTF::getContentText()
{
    return _inputText.c_str();
}

void TextFieldTTF::draw()
{
    if (_delegate && _delegate->onDraw(this))
    {
        return;
    }
    if (_inputText.length())
    {
        LabelTTF::draw();
        return;
    }

    // draw placeholder
    Color3B color = getColor();
    setColor(_colorSpaceHolder);
    LabelTTF::draw();
    setColor(color);
}

const Color3B& TextFieldTTF::getColorSpaceHolder()
{
    return _colorSpaceHolder;
}

void TextFieldTTF::setColorSpaceHolder(const Color3B& color)
{
    _colorSpaceHolder = color;
}

//////////////////////////////////////////////////////////////////////////
// properties
//////////////////////////////////////////////////////////////////////////

// input text property
void TextFieldTTF::setString(const std::string &text)
{
    static char bulletString[] = {(char)0xe2, (char)0x80, (char)0xa2, (char)0x00};
    std::string displayText;
    int length;

    if (text.length()>0)
    {
        _inputText = text;
        displayText = _inputText;
        if (_secureTextEntry)
        {
            displayText = "";
            length = _inputText.length();
            while (length)
            {
                displayText.append(bulletString);
                --length;
            }
        }
    }
    else
    {
        _inputText = "";
    }

    // if there is no input text, display placeholder instead
    if (! _inputText.length())
    {
        LabelTTF::setString(_placeHolder);
    }
    else
    {
        LabelTTF::setString(displayText);
    }
    _charCount = _calcCharCount(_inputText.c_str());
}

const std::string& TextFieldTTF::getString() const
{
    return _inputText;
}

// place holder text property
void TextFieldTTF::setPlaceHolder(const std::string& text)
{
    _placeHolder = text;
    if (! _inputText.length())
    {
        LabelTTF::setString(_placeHolder);
    }
}

const std::string& TextFieldTTF::getPlaceHolder() const
{
    return _placeHolder;
}

// secureTextEntry
void TextFieldTTF::setSecureTextEntry(bool value)
{
    if (_secureTextEntry != value)
    {
        _secureTextEntry = value;
        setString(getString());
    }
}

bool TextFieldTTF::isSecureTextEntry()
{
    return _secureTextEntry;
}

NS_CC_END
