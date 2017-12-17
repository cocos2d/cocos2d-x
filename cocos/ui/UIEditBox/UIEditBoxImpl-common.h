/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren

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

#ifndef __UIEditBoxIMPLICOMMON_H__
#define __UIEditBoxIMPLICOMMON_H__

#include "platform/CCPlatformConfig.h"
#include "ui/UIEditBox/UIEditBoxImpl-common.h"
#include "ui/UIEditBox/UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {

class EditBox;

class CC_GUI_DLL EditBoxImplCommon : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplCommon(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplCommon();
    
    virtual bool initWithSize(const Size& size) override;
    
    virtual void setFont(const char* pFontName, int fontSize) override;
    virtual void setFontColor(const Color4B& color) override;
    virtual void setPlaceholderFont(const char* pFontName, int fontSize) override;
    virtual void setPlaceholderFontColor(const Color4B& color) override;
    virtual void setInputMode(EditBox::InputMode inputMode) override;
    virtual void setInputFlag(EditBox::InputFlag inputFlag) override;
    virtual void setReturnType(EditBox::KeyboardReturnType returnType) override;
    virtual void setText(const char* pText) override;
    virtual void setPlaceHolder(const char* pText) override;
    virtual void setVisible(bool visible) override;

    virtual void setMaxLength(int maxLength) override;
    virtual void setTextHorizontalAlignment(TextHAlignment alignment) override;

    virtual int  getMaxLength() override { return _maxLength; }
    virtual const char* getText(void) override { return _text.c_str(); }
    virtual const char* getPlaceHolder(void) override { return _placeHolder.c_str(); }

    virtual const char* getFontName() override { return _fontName.c_str(); }
    virtual int getFontSize() override { return _fontSize; }
    virtual const Color4B& getFontColor() override { return _colText; }

    virtual const char* getPlaceholderFontName() override { return _placeholderFontName.c_str(); }
    virtual int getPlaceholderFontSize() override { return _placeholderFontSize; }
    virtual const Color4B& getPlaceholderFontColor() override { return _colPlaceHolder; }

    virtual EditBox::InputMode getInputMode() override { return _editBoxInputMode; }
    virtual EditBox::InputFlag getInputFlag() override { return _editBoxInputFlag; }
    virtual EditBox::KeyboardReturnType getReturnType() override { return _keyboardReturnType; }
    virtual TextHAlignment getTextHorizontalAlignment() override { return _alignment; }

    virtual void refreshInactiveText();
    
    virtual void setContentSize(const Size& size) override;
    
    virtual void setAnchorPoint(const Vec2& anchorPoint) override {}
    virtual void setPosition(const Vec2& pos) override {}
    
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void) override;
    virtual void openKeyboard() override;
    virtual void closeKeyboard() override;

    virtual void onEndEditing(const std::string& text);
    
    void editBoxEditingDidBegin();
    void editBoxEditingChanged(const std::string& text);
    void editBoxEditingDidEnd(const std::string& text, EditBoxDelegate::EditBoxEndAction action = EditBoxDelegate::EditBoxEndAction::UNKNOWN);

    virtual bool isEditing() override = 0;
    virtual void createNativeControl(const Rect& frame) = 0;
    virtual void setNativeFont(const char* pFontName, int fontSize) = 0;
    virtual void setNativeFontColor(const Color4B& color) = 0;
    virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) = 0;
    virtual void setNativePlaceholderFontColor(const Color4B& color) = 0;
    virtual void setNativeInputMode(EditBox::InputMode inputMode) = 0;
    virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) = 0;
    virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) = 0;
    virtual void setNativeTextHorizontalAlignment(cocos2d::TextHAlignment alignment) = 0;
    virtual void setNativeText(const char* pText) = 0;
    virtual void setNativePlaceHolder(const char* pText) = 0;
    virtual void setNativeVisible(bool visible) = 0;
    virtual void updateNativeFrame(const Rect& rect) = 0;
    virtual const char* getNativeDefaultFontName() = 0;
    virtual void nativeOpenKeyboard() = 0;
    virtual void nativeCloseKeyboard() = 0;
    virtual void setNativeMaxLength(int maxLength) {};


protected:
    void         initInactiveLabels(const Size& size);
    void         setInactiveText(const char* pText);
    void         refreshLabelAlignment();
    void         placeInactiveLabels(const Size& size);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance)override {};

    Label* _label;
    Label* _labelPlaceHolder;
    EditBox::InputMode    _editBoxInputMode;
    EditBox::InputFlag    _editBoxInputFlag;
    EditBox::KeyboardReturnType  _keyboardReturnType;
    cocos2d::TextHAlignment _alignment;

    std::string _text;
    std::string _placeHolder;

    std::string _fontName;
    std::string _placeholderFontName;

    int _fontSize;
    int _placeholderFontSize;

    Color4B _colText;
    Color4B _colPlaceHolder;
    
    int   _maxLength;
    Size _contentSize;
    bool _editingMode;
};


}

NS_CC_END


#endif /* __UIEditBoxIMPLICOMMON_H__ */

