/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013 Jozef Pridavok
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "ui/UIEditBox/UIEditBoxImpl-common.h"

NS_CC_BEGIN

namespace ui {

    class EditBox;

    class CC_GUI_DLL EditBoxImplWin : public EditBoxImplCommon
    {
    public:

        EditBoxImplWin(EditBox* pEditText);
        virtual ~EditBoxImplWin();

        virtual bool isEditing() override;
        virtual void createNativeControl(const Rect& frame) override;
        virtual void setNativeFont(const char* pFontName, int fontSize) override;
        virtual void setNativeFontColor(const Color4B& color) override;
        virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) override;
        virtual void setNativePlaceholderFontColor(const Color4B& color) override;
        virtual void setNativeInputMode(EditBox::InputMode inputMode) override;
        virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) override;
        virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) override;
        virtual void setNativeTextHorizontalAlignment(TextHAlignment alignment) override;
        virtual void setNativeText(const char* pText) override;
        virtual void setNativePlaceHolder(const char* pText) override;
        virtual void setNativeVisible(bool visible) override;
        virtual void updateNativeFrame(const Rect& rect) override;
        virtual const char* getNativeDefaultFontName() override;
        virtual void nativeOpenKeyboard() override;
        virtual void nativeCloseKeyboard() override;
        virtual void setNativeMaxLength(int maxLength) override;

    private:
        void createEditCtrl(bool singleLine);
        void cleanupEditCtrl();
        std::string getText() const;
        void _WindowProc(HWND, UINT, WPARAM, LPARAM);

        WNDPROC _prevWndProc;
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK hookGLFWWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        HWND _hwndEdit;
        bool _changedTextManually;
        bool _hasFocus;
        EditBoxDelegate::EditBoxEndAction _endAction;
        static WNDPROC s_prevCocosWndProc;

        static HINSTANCE s_hInstance;
        static HWND s_hwndCocos;
        static HWND s_previousFocusWnd;
        static bool s_isInitialized;
        static int s_editboxChildID;
        static void lazyInit();
    };

}

NS_CC_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#endif /* __UIEditBoxIMPLWIN_H__ */

