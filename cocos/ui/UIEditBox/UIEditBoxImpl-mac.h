/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 Jozef Pridavok
 
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

#ifndef __UIEditBoxIMPLMAC_H__
#define __UIEditBoxIMPLMAC_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "UIEditBoxImpl.h"

@class UIEditBoxImplMac;

NS_CC_BEGIN

namespace ui {
    
class EditBox;

class EditBoxImplMac : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplMac(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplMac();
    
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
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) override;
    virtual void openKeyboard() override;
    virtual void closeKeyboard() override;
    virtual void updatePosition(float dt) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void) override;
private:
    NSPoint    convertDesignCoordToScreenCoord(const Vec2& designCoord, bool bInRetinaMode);
    void       adjustTextFieldPosition();
    NSFont*    constructFont(const char* fontName, int fontSize);
    Size              _contentSize;
    Vec2              _position;
    Vec2              _anchorPoint;
    int               _maxTextLength;
    bool              _inRetinaMode;
    UIEditBoxImplMac* _sysEdit;
};


}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#endif /* __UIEditBoxIMPLMAC_H__ */

