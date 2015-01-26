/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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
#ifndef __UIEditBoxIMPLWP8_H__
#define __UIEditBoxIMPLWP8_H__

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#include "UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {
    class EditBox;
    
    class CC_GUI_DLL UIEditBoxImplWp8 : public EditBoxImpl
    {
    public:
        UIEditBoxImplWp8(EditBox* pEditText);
        virtual ~UIEditBoxImplWp8();
        
        virtual bool initWithSize(const Size& size);
        virtual void setFont(const char* pFontName, int fontSize);
        virtual void setFontColor(const Color3B& color);
        virtual void setPlaceholderFont(const char* pFontName, int fontSize);
        virtual void setPlaceholderFontColor(const Color3B& color);
        virtual void setInputMode(EditBox::InputMode inputMode);
        virtual void setInputFlag(EditBox::InputFlag inputFlag);
        virtual void setMaxLength(int maxLength);
        virtual int  getMaxLength();
        virtual void setReturnType(EditBox::KeyboardReturnType returnType);
        virtual bool isEditing();
        
        virtual void setText(const char* pText);
        virtual const char* getText(void);
        virtual void setPlaceHolder(const char* pText);
        virtual void setPosition(const Vec2& pos);
        virtual void setVisible(bool visible);
        virtual void setContentSize(const Size& size);
        virtual void setAnchorPoint(const Vec2& anchorPoint);
        virtual void visit(void);
        virtual void doAnimationWhenKeyboardMove(float duration, float distance);
        virtual void openKeyboard();
        virtual void closeKeyboard();
        virtual void onEnter(void);
    private:
        Platform::String^ stringToPlatformString(std::string strSrc);
        std::string PlatformStringTostring(Platform::String^ strSrc);
    private:
        
        Label* m_pLabel;
        Label* m_pLabelPlaceHolder;
        EditBox::InputMode    m_eEditBoxInputMode;
        EditBox::InputFlag    m_eEditBoxInputFlag;
        (EditBox::KeyboardReturnType  m_eKeyboardReturnType;
         
         std::string m_strText;
         std::string m_strPlaceHolder;
         
         Color3B m_colText;
         Color3B m_colPlaceHolder;
         
         int   m_nMaxLength;
         Size m_EditSize;
    };
}

NS_CC_END

#endif //WP8

#endif
