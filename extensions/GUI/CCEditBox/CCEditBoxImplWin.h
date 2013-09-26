/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013 Jozef Pridavok
 
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

#ifndef __CCEditBoxIMPLWIN_H__
#define __CCEditBoxIMPLWIN_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "ExtensionMacros.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

class CCEditBox;
/**
 *  @js NA
 *  @lua NA
 */
class CCEditBoxImplWin : public CCEditBoxImpl
{
public:
    CCEditBoxImplWin(CCEditBox* pEditText);
    virtual ~CCEditBoxImplWin();
    
    virtual bool initWithSize(const CCSize& size);
	virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const ccColor3B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const ccColor3B& color);
    virtual void setInputMode(EditBoxInputMode inputMode);
    virtual void setInputFlag(EditBoxInputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setReturnType(KeyboardReturnType returnType);
    virtual bool isEditing();
    
    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const CCPoint& pos);
	virtual void setVisible(bool visible);
    virtual void setContentSize(const CCSize& size);
    virtual void setAnchorPoint(const CCPoint& anchorPoint);
    virtual void visit(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
    virtual void onEnter(void);
private:

    CCLabelTTF* m_pLabel;
    CCLabelTTF* m_pLabelPlaceHolder;
    EditBoxInputMode    m_eEditBoxInputMode;
    EditBoxInputFlag    m_eEditBoxInputFlag;
    KeyboardReturnType  m_eKeyboardReturnType;
    
    std::string m_strText;
    std::string m_strPlaceHolder;
    
    ccColor3B m_colText;
    ccColor3B m_colPlaceHolder;

    int   m_nMaxLength;
    CCSize m_EditSize;

	/*
    CCSize     m_tContentSize;
    HWND       m_pSysEdit;
    int        m_nMaxTextLength;
	*/
};


NS_CC_EXT_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#endif /* __CCEditBoxIMPLWIN_H__ */

