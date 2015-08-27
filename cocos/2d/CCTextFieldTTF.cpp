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

#include "2d/CCTextFieldTTF.h"

#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN

#define CURSOR_TIME_SHOW_HIDE 0.3f
#define CURSOR_DEFAULT_CHAR '|'

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
, _placeHolder("")   // prevent Label initWithString assertion
, _colorText(Color4B::WHITE)
, _secureTextEntry(false)
, _cursorUse(false)
, _cursorPosition(0)
, _cursorChar(CURSOR_DEFAULT_CHAR)
, _cursorShowingTime(0.0f)
, _isAttachWithIME(false)
{
    _colorSpaceHolder.r = _colorSpaceHolder.g = _colorSpaceHolder.b = 127;
    _colorSpaceHolder.a = 255;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    // On desktop default enable cursor
    setCursorUse(true);
#endif
}

TextFieldTTF::~TextFieldTTF()
{
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////

TextFieldTTF * TextFieldTTF::textFieldWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize)
{
    TextFieldTTF *ret = new (std::nothrow) TextFieldTTF();
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
    TextFieldTTF *ret = new (std::nothrow) TextFieldTTF();
    if(ret && ret->initWithPlaceHolder("", fontName, fontSize))
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
    setDimensions(dimensions.width,dimensions.height);
    setSystemFontName(fontName);
    setSystemFontSize(fontSize);
    setAlignment(alignment,TextVAlignment::CENTER);
    Label::setTextColor(_colorSpaceHolder);
    Label::setString(_placeHolder);

    return true;
}
bool TextFieldTTF::initWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize)
{
    _placeHolder = std::string(placeholder);
    setSystemFontName(fontName);
    setSystemFontSize(fontSize);
    Label::setTextColor(_colorSpaceHolder);
    Label::setString(_placeHolder);

    return true;
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
        auto pGlView = Director::getInstance()->getOpenGLView();
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
        auto glView = Director::getInstance()->getOpenGLView();
        if (glView)
        {
            glView->setIMEKeyboardState(false);
        }
    }
    return ret;
}

void cocos2d::TextFieldTTF::didAttachWithIME()
{
    setAttachWithIME(true);
}

void cocos2d::TextFieldTTF::didDetachWithIME()
{
    setAttachWithIME(false);
}

bool TextFieldTTF::canAttachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldAttachWithIME(this)) : true;
}

bool TextFieldTTF::canDetachWithIME()
{
    return (_delegate) ? (! _delegate->onTextFieldDetachWithIME(this)) : true;
}

void TextFieldTTF::insertText(const char * text, size_t len)
{
    std::string insert(text, len);

    // insert \n means input end
    int pos = static_cast<int>(insert.find((char)TextFormatter::NewLine));
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

        int countInsertChar = _calcCharCount(insert.c_str());
        _charCount += countInsertChar;

        if (_cursorUse)
        {
            StringUtils::StringUTF8 stringUTF8;

            stringUTF8.set(_inputText);
            stringUTF8.insert(_cursorPosition, insert);

            setCursorPosition(_cursorPosition + countInsertChar);            

            setString(stringUTF8.getAsCharSequence());
        }
        else
        {
            std::string sText(_inputText);
            sText.append(insert);
            setString(sText);
        }
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
        // delegate doesn't want to delete backwards
        return;
    }

    // if all text deleted, show placeholder string
    if (len <= deleteLen)
    {
        _inputText = "";
        _charCount = 0;
        setCursorPosition(0);
        setString(_inputText);
        return;
    }

    // set new input text
    if (_cursorUse)
    {
        if (_cursorPosition)
        {
            setCursorPosition(_cursorPosition - 1);

            StringUtils::StringUTF8 stringUTF8;

            stringUTF8.set(_inputText);
            stringUTF8.deleteChar(_cursorPosition);

            _charCount = stringUTF8.length();
            setString(stringUTF8.getAsCharSequence());
        }
    }
    else
    {
        std::string text(_inputText.c_str(), len - deleteLen);
        setString(text);
    }
}

const std::string& TextFieldTTF::getContentText()
{
    return _inputText;
}

void cocos2d::TextFieldTTF::setCursorPosition(std::size_t cursorPosition)
{
    if (_cursorUse && cursorPosition <= _charCount)
    {
        _cursorPosition = cursorPosition;
        _cursorShowingTime = CURSOR_TIME_SHOW_HIDE;
    }
}

void cocos2d::TextFieldTTF::setCursorFromPoint(const Vec2 &point, const Camera* camera)
{
    if (_cursorUse)
    {
        // Reset Label, no cursor
        bool oldIsAttachWithIME = _isAttachWithIME;
        _isAttachWithIME = false;
        updateCursorDisplayText();

        Rect rect;
        rect.size = getContentSize();
        if (isScreenPointInRect(point, camera, getWorldToNodeTransform(), rect, nullptr))
        {
            std::size_t latterPosition = 0;
            for (; latterPosition < _lengthOfString; ++latterPosition)
            {
                if (_lettersInfo[latterPosition].valid)
                {
                    auto sprite = getLetter(latterPosition);
                    rect.size = sprite->getContentSize();
                    if (isScreenPointInRect(point, camera, sprite->getWorldToNodeTransform(), rect, nullptr))
                    {
                        setCursorPosition(latterPosition);
                        break;
                    }
                }
            }
            if (latterPosition == _lengthOfString)
            {
                setCursorPosition(latterPosition);
            }
        }

        // Set cursor
        _isAttachWithIME = oldIsAttachWithIME;
        updateCursorDisplayText();
    }
}

void cocos2d::TextFieldTTF::setAttachWithIME(bool isAttachWithIME)
{
    if (isAttachWithIME != _isAttachWithIME)
    {
        _isAttachWithIME = isAttachWithIME;

        if (_isAttachWithIME)
        {
            setCursorPosition(_charCount);
        }
        updateCursorDisplayText();
    }
}

void TextFieldTTF::setTextColor(const Color4B &color)
{
    _colorText = color;
    if (_inputText.length() > 0) 
    {
        Label::setTextColor(_colorText);
    }
}

void TextFieldTTF::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (_delegate && _delegate->onVisit(this,renderer,parentTransform,parentFlags))
    {
        return;
    }
    Label::visit(renderer,parentTransform,parentFlags);
}

void cocos2d::TextFieldTTF::update(float delta)
{
    if (_cursorUse && _isAttachWithIME)
    {
        _cursorShowingTime -= delta;
        if (_cursorShowingTime < -CURSOR_TIME_SHOW_HIDE)
        {
            _cursorShowingTime = CURSOR_TIME_SHOW_HIDE;
        }
        // before cursor inserted '\b', need next letter
        auto sprite = getLetter(_cursorPosition + 1);

        if (sprite)
        {
            if (_cursorShowingTime >= 0.0f)
            {
                sprite->setOpacity(255);
            }
            else
            {
                sprite->setOpacity(0);
            }
            sprite->setDirty(true);
        }
    }
}

const Color4B& TextFieldTTF::getColorSpaceHolder()
{
    return _colorSpaceHolder;
}

void TextFieldTTF::setColorSpaceHolder(const Color3B& color)
{
    _colorSpaceHolder.r = color.r;
    _colorSpaceHolder.g = color.g;
    _colorSpaceHolder.b = color.b;
    _colorSpaceHolder.a = 255;
    if (0 == _inputText.length())
    {
        Label::setTextColor(_colorSpaceHolder);
    }
}

void TextFieldTTF::setColorSpaceHolder(const Color4B& color)
{
    _colorSpaceHolder = color;
    if (0 == _inputText.length()) {
        Label::setTextColor(_colorSpaceHolder);
    }
}

//////////////////////////////////////////////////////////////////////////
// properties
//////////////////////////////////////////////////////////////////////////

// input text property
void TextFieldTTF::setString(const std::string &text)
{
    static char bulletString[] = {(char)0xe2, (char)0x80, (char)0xa2, (char)0x00};
    std::string displayText;

    int charCount = 0;
    if (!text.empty())
    {
        _inputText = text;
        displayText = _inputText;
        charCount = _calcCharCount(_inputText.c_str());
        if (_secureTextEntry)
        {
            displayText = "";
            size_t length = charCount;
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

    if (_cursorUse && charCount != _charCount)
    {
        _cursorPosition = charCount;
    }

    if (_cursorUse)
    {
        // Need for recreate all letters in Label
        Label::removeAllChildrenWithCleanup(false);
    }

    // if there is no input text, display placeholder instead
    if (_inputText.empty() && (!_cursorUse || !_isAttachWithIME))
    {
        Label::setTextColor(_colorSpaceHolder);
        Label::setString(_placeHolder);
    }
    else
    {
        makeStringSupportCursor(displayText);

        Label::setTextColor(_colorText);
        Label::setString(displayText);
    }
    _charCount = charCount;
}

void cocos2d::TextFieldTTF::appendString(const std::string& text)
{
    insertText(text.c_str(), text.length());
}

void cocos2d::TextFieldTTF::makeStringSupportCursor(std::string& displayText)
{
    if (_cursorUse && _isAttachWithIME)
    {
        if (displayText.empty())
        {
            // \b - Next char not change x position
            displayText.push_back((char)TextFormatter::NextCharNoChangeX);
            displayText.push_back(_cursorChar);
        }
        else
        {
            StringUtils::StringUTF8 stringUTF8;

            stringUTF8.set(displayText);

            if (_cursorPosition > stringUTF8.length())
            {
                _cursorPosition = stringUTF8.length();
            }
            std::string cursorChar;
            // \b - Next char not change x position
            cursorChar.push_back((char)TextFormatter::NextCharNoChangeX);
            cursorChar.push_back(_cursorChar);
            stringUTF8.insert(_cursorPosition, cursorChar);

            displayText = stringUTF8.getAsCharSequence();
        }
    }
}

void cocos2d::TextFieldTTF::updateCursorDisplayText()
{
    // Update Label content
    setString(_inputText);
}

void cocos2d::TextFieldTTF::setCursorChar(char cursor)
{
    if (_cursorChar != cursor)
    {
        _cursorChar = cursor;
        updateCursorDisplayText();
    }
}

void cocos2d::TextFieldTTF::controlKey(EventKeyboard::KeyCode keyCode)
{
    if (_cursorUse)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_HOME:
        case EventKeyboard::KeyCode::KEY_KP_HOME:
            setCursorPosition(0);
            updateCursorDisplayText();
            break;
        case EventKeyboard::KeyCode::KEY_END:
            setCursorPosition(_charCount);
            updateCursorDisplayText();
            break;
        case EventKeyboard::KeyCode::KEY_DELETE:
        case EventKeyboard::KeyCode::KEY_KP_DELETE:
            if (_cursorPosition < _charCount)
            {
                StringUtils::StringUTF8 stringUTF8;

                stringUTF8.set(_inputText);
                stringUTF8.deleteChar(_cursorPosition);
                setCursorPosition(_cursorPosition);
                _charCount = stringUTF8.length();
                setString(stringUTF8.getAsCharSequence());
            }
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if (_cursorPosition)
            {
                setCursorPosition(_cursorPosition - 1);
                updateCursorDisplayText();
            }
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (_cursorPosition < _charCount)
            {
                setCursorPosition(_cursorPosition + 1);
                updateCursorDisplayText();
            }
            break;
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            detachWithIME();
            break;
        default:
            break;
        }
    }
}

const std::string& TextFieldTTF::getString() const
{
    return _inputText;
}

// place holder text property
void TextFieldTTF::setPlaceHolder(const std::string& text)
{
    _placeHolder = text;
    if (0 == _inputText.length())
    {
        Label::setTextColor(_colorSpaceHolder);
        Label::setString(_placeHolder);
    }
}

const std::string& TextFieldTTF::getPlaceHolder() const
{
    return _placeHolder;
}

void cocos2d::TextFieldTTF::setCursorUse(bool value)
{
    if (_cursorUse != value)
    {
        _cursorUse = value;
        if (_cursorUse)
        {
            _cursorPosition = _charCount;
        }
        else
        {
            _cursorPosition = 0;
        }
    }
}

// secureTextEntry
void TextFieldTTF::setSecureTextEntry(bool value)
{
    if (_secureTextEntry != value)
    {
        _secureTextEntry = value;
        setString(_inputText);
    }
}

bool TextFieldTTF::isSecureTextEntry()
{
    return _secureTextEntry;
}

NS_CC_END
