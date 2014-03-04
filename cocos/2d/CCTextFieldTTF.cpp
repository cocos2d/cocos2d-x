/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCGLView.h"

NS_CC_BEGIN

static int _calcCharCount(const char * text)
{
    int n = 0;
    char ch = 0;
    while ((ch = *text))
    {
        CC_BREAK_IF(! ch);

        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++text;
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
    return nullptr;
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
    return nullptr;
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
    bool ret = IMEDelegate::attachWithIME();
    if (ret)
    {
        // open keyboard
        GLView * pGlView = Director::getInstance()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(true);
        }
    }
    return ret;
}

bool TextFieldTTF::detachWithIME()
{
    bool ret = IMEDelegate::detachWithIME();
    if (ret)
    {
        // close keyboard
        GLView * glView = Director::getInstance()->getOpenGLView();
        if (glView)
        {
            glView->setIMEKeyboardState(false);
        }
    }
    return ret;
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
    std::string insert(text, len);

    // insert \n means input end
    int pos = static_cast<int>(insert.find('\n'));
    if ((int)insert.npos != pos)
    {
        len = pos;
        insert.erase(pos);
    }

    if (len > 0)
    {
        if (_delegate && _delegate->onTextFieldInsertText(this, insert.c_str(), len))
        {
            // delegate doesn't want to insert text
            return;
        }

        _charCount += _calcCharCount(insert.c_str());
        std::string sText(_inputText);
        sText.append(insert);
        setString(sText);
    }

    if ((int)insert.npos == pos) {
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
    size_t len = _inputText.length();
    if (! len)
    {
        // there is no string
        return;
    }

    // get the delete byte number
    size_t deleteLen = 1;    // default, erase 1 byte

    while(0x80 == (0xC0 & _inputText.at(len - deleteLen)))
    {
        ++deleteLen;
    }

    if (_delegate && _delegate->onTextFieldDeleteBackward(this, _inputText.c_str() + len - deleteLen, static_cast<int>(deleteLen)))
    {
        // delegate doesn't wan't to delete backwards
        return;
    }

    // if all text deleted, show placeholder string
    if (len <= deleteLen)
    {
        _inputText = "";
        _charCount = 0;
        LabelTTF::setString(_placeHolder);
        return;
    }

    // set new input text
    std::string text(_inputText.c_str(), len - deleteLen);
    setString(text);
}

const std::string& TextFieldTTF::getContentText()
{
    return _inputText;
}

void TextFieldTTF::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    if (_delegate && _delegate->onDraw(this))
    {
        return;
    }
    if (_inputText.length())
    {
        LabelTTF::draw(renderer, transform, transformUpdated);
        return;
    }

    // draw placeholder
    Color3B color = getColor();
    setColor(_colorSpaceHolder);
    LabelTTF::draw(renderer, transform, transformUpdated);
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
    size_t length;

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
