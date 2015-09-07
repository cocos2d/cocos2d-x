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

#ifndef __UIEditBoxIMPLICOMMON_H__
#define __UIEditBoxIMPLICOMMON_H__

#include "platform/CCPlatformConfig.h"

#include "UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {

class EditBox;

class EditBoxImplCommon : public EditBoxImpl
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
    
    virtual bool initWithSize(const Size& size);
    
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const Color4B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const Color4B& color);
    virtual void setInputMode(EditBox::InputMode inputMode);
    virtual void setInputFlag(EditBox::InputFlag inputFlag);
    virtual void setReturnType(EditBox::KeyboardReturnType returnType);
    virtual void setText(const char* pText);
    virtual void setPlaceHolder(const char* pText);
    virtual void setVisible(bool visible);


    virtual void setMaxLength(int maxLength);
    virtual int  getMaxLength();
    
    virtual const char* getText(void);
    virtual void refreshInactiveText();
    
    virtual void setContentSize(const Size& size);
    
    virtual void setAnchorPoint(const Vec2& anchorPoint){}
    virtual void setPosition(const Vec2& pos) {}
    
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void);
    virtual void openKeyboard();
    virtual void closeKeyboard();

    virtual void onEndEditing(const std::string& text);
    
    void editBoxEditingDidBegin();
    void editBoxEditingChanged(const std::string& text);
    void editBoxEditingDidEnd(const std::string& text);
    
    virtual bool isEditing() = 0;
    virtual void createNativeControl(const Rect& frame) = 0;
    virtual void setNativeFont(const char* pFontName, int fontSize) = 0;
    virtual void setNativeFontColor(const Color4B& color) = 0;
    virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) = 0;
    virtual void setNativePlaceholderFontColor(const Color4B& color) = 0;
    virtual void setNativeInputMode(EditBox::InputMode inputMode) = 0;
    virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) = 0;
    virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) = 0;
    virtual void setNativeText(const char* pText) = 0;
    virtual void setNativePlaceHolder(const char* pText) = 0;
    virtual void setNativeVisible(bool visible) = 0;
    virtual void updateNativeFrame(const Rect& rect) = 0;
    virtual void setNativeContentSize(const Size& size) = 0;
    virtual const char* getNativeDefaultFontName() = 0;
    virtual void nativeOpenKeyboard() = 0;
    virtual void nativeCloseKeyboard() = 0;
    virtual void setNativeMaxLength(int maxLength) {};


private:
	void			initInactiveLabels(const Size& size);
	void			setInactiveText(const char* pText);
    void            placeInactiveLabels();
	
    Label* _label;
    Label* _labelPlaceHolder;
    EditBox::InputMode    _editBoxInputMode;
    EditBox::InputFlag    _editBoxInputFlag;
    EditBox::KeyboardReturnType  _keyboardReturnType;
    
    std::string _text;
    std::string _placeHolder;
    
    Color4B _colText;
    Color4B _colPlaceHolder;
    
    int   _maxLength;
    Size _contentSize;
};


}

NS_CC_END


#endif /* __UIEditBoxIMPLICOMMON_H__ */

