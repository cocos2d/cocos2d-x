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

#ifndef __UIEDITBOXIMPLANDROID_H__
#define __UIEDITBOXIMPLANDROID_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "UIEditBoxImpl.h"

NS_CC_BEGIN

class Label;

namespace ui {

class EditBox;

class EditBoxImplAndroid : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplAndroid(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplAndroid();
    
    virtual bool initWithSize(const Size& size) override;
    virtual void setFont(const char* pFontName, int fontSize) override;
    virtual void setFontColor(const Color4B& color) override;
    virtual void setPlaceholderFont(const char* pFontName, int fontSize) override;
    virtual void setPlaceholderFontColor(const Color4B& color) override;
    virtual void setInputMode(EditBox::InputMode inputMode) override;
    virtual void setInputFlag(EditBox::InputFlag inputFlag) override;
    virtual void setMaxLength(int maxLength) override;
    virtual int  getMaxLength() override;
    virtual void setReturnType(EditBox::KeyboardReturnType returnType) override;
    virtual bool isEditing() override;
    
    virtual void setText(const char* pText) override;
    virtual const char* getText(void) override;
    virtual void setPlaceHolder(const char* pText) override;
    virtual void setPosition(const Vec2& pos) override;
    virtual void setVisible(bool visible) override;
    virtual void setContentSize(const Size& size) override;
    virtual void setAnchorPoint(const Vec2& anchorPoint) override;
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
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) override;
    virtual void openKeyboard() override;
    virtual void closeKeyboard() override;


    void editBoxEditingDidBegin();
    void editBoxEditingChanged(const std::string& text);
    void editBoxEditingDidEnd(const std::string& text);
private:
    void			setInactiveText(const char* pText);
    void      onEndEditing(const std::string& text);
    void      refreshInactiveText();


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
    Size _editSize;
    
    int _editBoxIndex;
};


}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

#endif /* __UIEDITBOXIMPLANDROID_H__ */

