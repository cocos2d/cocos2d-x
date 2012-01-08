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

class CCTextFieldTTF;

class CC_DLL CCTextFieldDelegate
{
public:
    /**
    @brief	If the sender doesn't want to attach with IME, return true;
    */
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * sender)
    { 
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief	If the sender doesn't want to detach with IME, return true;
    */
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief	If the sender doesn't want to insert the text, return true;
    */
    virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char * text, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief	If the sender doesn't want to delete the delText, return true;
    */
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * sender, const char * delText, int nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief	If doesn't want draw sender as default, return true.
    */
    virtual bool onDraw(CCTextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
@brief	A simple text input field with TTF font.
*/
class CC_DLL CCTextFieldTTF : public CCLabelTTF, public CCIMEDelegate
{
public:
    CCTextFieldTTF();
    virtual ~CCTextFieldTTF();

    //char * description();

    /** creates a CCTextFieldTTF from a fontname, alignment, dimension and font size */
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** creates a CCLabelTTF from a fontname and font size */
    static CCTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name, alignment, dimension and font size */
    bool initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
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
    
    CC_SYNTHESIZE(CCTextFieldDelegate *, m_pDelegate, Delegate);
    CC_SYNTHESIZE_READONLY(int, m_nCharCount, CharCount);
	CC_SYNTHESIZE_PASS_BY_REF(ccColor3B, m_ColorSpaceHolder, ColorSpaceHolder);

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
protected:

    virtual void draw();

    //////////////////////////////////////////////////////////////////////////
    // CCIMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME();
    virtual bool canDetachWithIME();
    virtual void insertText(const char * text, int len);
    virtual void deleteBackward();
    virtual const char * getContentText();
private:
    class LengthStack;
    LengthStack * m_pLens;
};

NS_CC_END;

#endif	// __CC_TEXT_FIELD_H__