/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#ifndef __CCEditBoxIMPL_H__
#define __CCEditBoxIMPL_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCEditBox.h"

NS_CC_EXT_BEGIN


class EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImpl(EditBox* pEditBox) : _delegate(NULL),_editBox(pEditBox) {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImpl() {}
    
    virtual bool initWithSize(const Size& size) = 0;
    virtual void setFont(const char* pFontName, int fontSize) = 0;
    virtual void setFontColor(const Color3B& color) = 0;
    virtual void setPlaceholderFont(const char* pFontName, int fontSize) = 0;
    virtual void setPlaceholderFontColor(const Color3B& color) = 0;
    virtual void setInputMode(EditBox::InputMode inputMode) = 0;
    virtual void setInputFlag(EditBox::InputFlag inputFlag) = 0;
    virtual void setMaxLength(int maxLength) = 0;
    virtual int  getMaxLength() = 0;
    virtual void setReturnType(EditBox::KeyboardReturnType returnType) = 0;
    virtual bool isEditing() = 0;
    
    virtual void setText(const char* pText) = 0;
    virtual const char* getText(void) = 0;
    virtual void setPlaceHolder(const char* pText) = 0;
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) = 0;
    
    virtual void openKeyboard() = 0;
    virtual void closeKeyboard() = 0;
    
    virtual void setPosition(const Point& pos) = 0;
    virtual void setVisible(bool visible) = 0;
    virtual void setContentSize(const Size& size) = 0;
	virtual void setAnchorPoint(const Point& anchorPoint) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(void) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void) = 0;
    
    
    void setDelegate(EditBoxDelegate* pDelegate) { _delegate = pDelegate; };
    EditBoxDelegate* getDelegate() { return _delegate; };
    EditBox* getEditBox() { return _editBox; };
protected:
    EditBoxDelegate* _delegate;
    EditBox* _editBox;
};

// This method must be implemented at each subclass of EditBoxImpl.
extern EditBoxImpl* __createSystemEditBox(EditBox* pEditBox);


NS_CC_EXT_END

#endif /* __CCEditBoxIMPL_H__ */
