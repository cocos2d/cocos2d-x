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

#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__

#include "label_nodes/CCLabelTTF.h"
#include "text_input_node/CCIMEDelegate.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"

NS_CC_BEGIN

class TextFieldTTF;

/**
 * @addtogroup input
 * @{
 */

class CC_DLL TextFieldDelegate
{
public:
    /**
    @brief    If the sender doesn't want to attach to the IME, return true;
    */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief    If the sender doesn't want to detach from the IME, return true;
    */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief    If the sender doesn't want to insert the text, return true;
    */
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief    If the sender doesn't want to delete the delText, return true;
    */
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief    If the sender doesn't want to draw, return true.
    */
    virtual bool onDraw(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
@brief    A simple text input field with TTF font.
*/
class CC_DLL TextFieldTTF : public LabelTTF, public IMEDelegate
{
public:
    TextFieldTTF();
    virtual ~TextFieldTTF();

    //char * description();

    /** creates a TextFieldTTF from a fontname, alignment, dimension and font size */
    static TextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const Size& dimensions, Label::HAlignment alignment, const char *fontName, float fontSize);
    /** creates a LabelTTF from a fontname and font size */
    static TextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    /** initializes the TextFieldTTF with a font name, alignment, dimension and font size */
    bool initWithPlaceHolder(const char *placeholder, const Size& dimensions, Label::HAlignment alignment, const char *fontName, float fontSize);
    /** initializes the TextFieldTTF with a font name and font size */
    bool initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);

    /**
    @brief    Open keyboard and receive input text.
    */
    virtual bool attachWithIME();

    /**
    @brief    End text input and close keyboard.
    */
    virtual bool detachWithIME();

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////

    inline TextFieldDelegate* getDelegate() const { return _delegate; };
    inline void setDelegate(TextFieldDelegate* delegate) { _delegate = delegate; };

    inline int getCharCount() const { return _charCount; };
    virtual const Color3B& getColorSpaceHolder();
    virtual void setColorSpaceHolder(const Color3B& color);

    // input text property
public:
    virtual void setString(const char *text);
    virtual const char* getString(void) const;
protected:
    TextFieldDelegate * _delegate;
    int _charCount;
    
    std::string * _inputText;

    // place holder text property
    // place holder text displayed when there is no text in the text field.
public:
    virtual void setPlaceHolder(const char * text);
    virtual const char * getPlaceHolder(void);
protected:
    std::string * _placeHolder;
    Color3B _colorSpaceHolder;
public:
    virtual void setSecureTextEntry(bool value);
    virtual bool isSecureTextEntry();
protected:
    bool _secureTextEntry;
protected:

    virtual void draw();

    //////////////////////////////////////////////////////////////////////////
    // IMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME();
    virtual bool canDetachWithIME();
    virtual void insertText(const char * text, int len);
    virtual void deleteBackward();
    virtual const char * getContentText();
private:
    class LengthStack;
    LengthStack * _lens;
};

// end of input group
/// @}

NS_CC_END

#endif    // __CC_TEXT_FIELD_H__
