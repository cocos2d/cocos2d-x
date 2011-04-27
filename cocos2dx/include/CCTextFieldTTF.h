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

#include "CCLabelTTF.h"
#include "CCIMEDelegate.h"
#include "CCTouchDelegateProtocol.h"

NS_CC_BEGIN;

/**
@brief	A simple text input field with system TTF font.
*/

class CC_DLL CCTextFieldTTF : public CCLabelTTF, public CCIMEDelegate//, public CCTargetedTouchDelegate
{
public:
    CCTextFieldTTF();
    virtual ~CCTextFieldTTF();

    //char * description();

    /** creates a CCTextFieldTTF from a fontname, alignment, dimension and font size */
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** creates a CCLabelTTF from a fontname and font size */
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name, alignment, dimension and font size */
    bool initWithPlaceHolder(const char *placeholder, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name and font size */
    bool initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);

    /**
    @brief	Open keyboard and receive input text.
    */
    virtual bool attachWithIME();

    /**
    @brief	End text input  and close keyboard.
    */
    virtual bool detachWithIME();

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////
    
    // input text property
public:
    virtual void setString(const char *text);
    virtual const char* getString(void);
protected:
    std::string * m_pInputText;

    // place holder text property
    // place holder text displayed when there is no text in the text field.
public:
    virtual void setPlaceHolder(const char * text);
    virtual const char * getPlaceHolder(void);
protected:
    std::string * m_pPlaceHolder;
    bool          m_bLock;          // when insertText or deleteBackward called, m_bLock is true
protected:

    //////////////////////////////////////////////////////////////////////////
    // CCIMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME();
    virtual bool canDetachWithIME();
    virtual void insertText(const char * text, int len);
    virtual void deleteBackward();

private:
    class LengthStack;
    LengthStack * m_pLens;
};

NS_CC_END;

#endif	// __CC_TEXT_FIELD_H__