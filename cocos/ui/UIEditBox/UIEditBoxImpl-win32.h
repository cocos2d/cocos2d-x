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

#ifndef __UIEditBoxIMPLWIN_H__
#define __UIEditBoxIMPLWIN_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "ui/UIEditBox/UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {

class EditBox;

class CC_GUI_DLL EditBoxImplWin : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplWin(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplWin();
    
    virtual bool initWithSize(const Size& size);
	virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const Color4B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const Color4B& color);
    virtual void setInputMode(EditBox::InputMode inputMode);
    virtual void setInputFlag(EditBox::InputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    virtual void setTextHorizontalAlignment(TextHAlignment alignment) { _alignment = alignment; }
    virtual void setReturnType(EditBox::KeyboardReturnType returnType);
    virtual bool isEditing();

    virtual const char* getFontName() override { return _fontName.c_str(); }
    virtual int getFontSize() override { return _fontSize; }
    virtual const Color4B& getFontColor() override { return _colText; }

    virtual const char* getPlaceholderFontName() override { return _placeholderFontName.c_str(); }
    virtual int getPlaceholderFontSize() override { return _placeholderFontSize; }
    virtual const Color4B& getPlaceholderFontColor() override { return _colPlaceHolder; }

    virtual EditBox::InputMode getInputMode() override { return _editBoxInputMode; }
    virtual EditBox::InputFlag getInputFlag() override { return _editBoxInputFlag; }
    virtual EditBox::KeyboardReturnType getReturnType() override { return _keyboardReturnType; }
    virtual TextHAlignment getTextHorizontalAlignment() { return _alignment; }

    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual const char* getPlaceHolder(void);
    virtual void setPosition(const Vec2& pos);
	virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void);
private:

    Label* _label;
    Label* _labelPlaceHolder;
    EditBox::InputMode    _editBoxInputMode;
    EditBox::InputFlag    _editBoxInputFlag;
    EditBox::KeyboardReturnType  _keyboardReturnType;
    TextHAlignment _alignment;
    
    std::string _text;
    std::string _placeHolder;

    std::string _fontName;
    std::string _placeholderFontName;

    int _fontSize;
    int _placeholderFontSize;

    Color4B _colText;
    Color4B _colPlaceHolder;

    int   _maxLength;
    Size _editSize;

	/*
    Size     _contentSize;
    HWND       _sysEdit;
    int        _maxTextLength;
	*/
    std::string _editingText;
    std::string _originalText;
    bool _isEditing;

    void onWin32InputBoxTextChange(const char *pText);
    void onWin32InputBoxClose(INT_PTR buttonId);
};


}

NS_CC_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#endif /* __UIEditBoxIMPLWIN_H__ */

