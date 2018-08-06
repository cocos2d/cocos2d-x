/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013 Jozef Pridavok
Copyright (c) 2013-2017 zilongshanren
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
#include "ui/UIEditBox/UIEditBoxImpl-win32.h"

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "ui/UIEditBox/UIEditBox.h"
#include <tchar.h>
#include <stdio.h>
#include "2d/CCLabel.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include <Commctrl.h>
#include <windows.h>
#include "ui/UIHelper.h"


NS_CC_BEGIN

namespace ui {

    bool EditBoxImplWin::s_isInitialized = false;
    int EditBoxImplWin::s_editboxChildID = 100;
    HWND EditBoxImplWin::s_previousFocusWnd = 0;
    WNDPROC EditBoxImplWin::s_prevCocosWndProc = 0;
    HINSTANCE EditBoxImplWin::s_hInstance = 0;
    HWND EditBoxImplWin::s_hwndCocos = 0;

    void EditBoxImplWin::lazyInit()
    {
        s_hwndCocos = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
        LONG style = ::GetWindowLongW(s_hwndCocos, GWL_STYLE);
        ::SetWindowLongW(s_hwndCocos, GWL_STYLE, style | WS_CLIPCHILDREN);
        s_isInitialized = true;
        s_previousFocusWnd = s_hwndCocos;

        s_hInstance = ::GetModuleHandleW(nullptr);

        s_prevCocosWndProc = (WNDPROC)SetWindowLongPtrW(s_hwndCocos, GWL_WNDPROC, (LONG_PTR)hookGLFWWindowProc);
    }

    EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
    {
        return new (std::nothrow) EditBoxImplWin(pEditBox);
    }

    EditBoxImplWin::EditBoxImplWin(EditBox* pEditText)
        : EditBoxImplCommon(pEditText),
        _changedTextManually(false),
        _hasFocus(false),
        _endAction(EditBoxDelegate::EditBoxEndAction::UNKNOWN)
    {
        if (!s_isInitialized)
        {
            lazyInit();
        }

        s_editboxChildID++;
    }

    EditBoxImplWin::~EditBoxImplWin()
    {
        this->cleanupEditCtrl();
    }

    bool EditBoxImplWin::isEditing()
    {
        return false;
    }

    void EditBoxImplWin::cleanupEditCtrl()
    {
        if (_hwndEdit)
        {
            SetWindowLongPtrW(_hwndEdit, GWL_WNDPROC, (LONG_PTR)_prevWndProc);
            ::DestroyWindow(_hwndEdit);
            _hasFocus = false;
            _changedTextManually = false;
            _editingMode = false;
            _hwndEdit = NULL;
        }
    }

    void EditBoxImplWin::createEditCtrl(bool singleLine)
    {
        this->cleanupEditCtrl();
        if (!_hwndEdit)
        {
            _hwndEdit = ::CreateWindowExW(
                WS_EX_CLIENTEDGE, L"EDIT",   // predefined class 
                NULL,         // no window title 
                WS_CHILD | ES_LEFT | WS_BORDER | WS_EX_TRANSPARENT | WS_TABSTOP | ES_AUTOHSCROLL | (singleLine ? 0 : ES_MULTILINE),
                0,
                0,
                0,
                0,   // set size in WM_SIZE message 
                s_hwndCocos,         // parent window 
                (HMENU)s_editboxChildID,   // edit control ID 
                s_hInstance,
                this);        // pointer not needed 

            SetWindowLongPtrW(_hwndEdit, GWL_USERDATA, (LONG_PTR)this);
            _prevWndProc = (WNDPROC)SetWindowLongPtrW(_hwndEdit, GWL_WNDPROC, (LONG_PTR)WindowProc);

            ::SendMessageW(_hwndEdit, EM_LIMITTEXT, this->_maxLength, 0);
            s_previousFocusWnd = s_hwndCocos;
            this->setNativeFont(this->getNativeDefaultFontName(), this->_fontSize);
            this->setNativeText(this->_text.c_str());
        }
    }

    void EditBoxImplWin::createNativeControl(const Rect& frame)
    {
        this->createEditCtrl(false);
    }

    void EditBoxImplWin::setNativeFont(const char* pFontName, int fontSize)
    {
        auto glView = Director::getInstance()->getOpenGLView();
        HFONT hFont = ::CreateFontW(static_cast<int>(fontSize * glView->getScaleX()), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, L"Arial");

        ::SendMessageW(_hwndEdit,             // Handle of edit control
            WM_SETFONT,         // Message to change the font
            (WPARAM)hFont,     // handle of the font
            MAKELPARAM(TRUE, 0) // Redraw text
        );
    }

    void EditBoxImplWin::setNativeFontColor(const Color4B& color)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativePlaceholderFont(const char* pFontName, int fontSize)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativePlaceholderFontColor(const Color4B& color)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativeInputMode(EditBox::InputMode inputMode)
    {
        if (_editBoxInputMode == cocos2d::ui::EditBox::InputMode::ANY)
        {
            this->createEditCtrl(false);
        }
        else if (_editBoxInputMode == cocos2d::ui::EditBox::InputMode::NUMERIC
            || _editBoxInputMode == cocos2d::ui::EditBox::InputMode::DECIMAL
            || _editBoxInputMode == cocos2d::ui::EditBox::InputMode::PHONE_NUMBER)
        {
            this->createEditCtrl(true);
            ::SetWindowLongW(_hwndEdit, GWL_STYLE, ::GetWindowLongW(_hwndEdit, GWL_STYLE) | ES_NUMBER);
        }
        else
        {
            this->createEditCtrl(true);
        }

        if (this->_editBoxInputFlag != cocos2d::ui::EditBox::InputFlag::PASSWORD)
        {
            ::PostMessageW(_hwndEdit, EM_SETPASSWORDCHAR, (WPARAM)0, (LPARAM)0);
        }
    }
    void EditBoxImplWin::setNativeInputFlag(EditBox::InputFlag inputFlag)
    {
        if (inputFlag == EditBox::InputFlag::PASSWORD)
        {
            this->createEditCtrl(true);
        }
        else
        {
            if (_editBoxInputMode != cocos2d::ui::EditBox::InputMode::ANY)
            {
                this->createEditCtrl(true);

                if (inputFlag == EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
                {
                    ::SetWindowLongW(_hwndEdit, GWL_STYLE, ::GetWindowLongW(_hwndEdit, GWL_STYLE) | ES_UPPERCASE);
                }
                // Clear the password style
                ::PostMessageW(_hwndEdit, EM_SETPASSWORDCHAR, (WPARAM)0, (LPARAM)0);
            }
        }
    }

    void EditBoxImplWin::setNativeReturnType(EditBox::KeyboardReturnType returnType)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativeTextHorizontalAlignment(TextHAlignment alignment)
    {
        LONG style = ::GetWindowLongW(_hwndEdit, GWL_STYLE);
        switch (alignment)
        {
        case TextHAlignment::LEFT:
            style = (style & ~ES_CENTER & ~ES_RIGHT) | ES_LEFT;
            break;
        case TextHAlignment::CENTER:
            style = (style & ~ES_LEFT & ~ES_RIGHT) | ES_CENTER;
            break;
        case TextHAlignment::RIGHT:
            style = (style & ~ES_LEFT & ~ES_CENTER) | ES_RIGHT;
            break;
        }
        ::SetWindowLongW(_hwndEdit, GWL_STYLE, style);
    }

    void EditBoxImplWin::setNativeText(const char* pText)
    {
        std::u16string utf16Result;
        std::string text(pText);
        cocos2d::StringUtils::UTF8ToUTF16(text, utf16Result);
        this->_changedTextManually = true;
        ::SetWindowTextW(_hwndEdit, (LPCWSTR)utf16Result.c_str());
        int textLen = text.size();
        ::SendMessageW(_hwndEdit, EM_SETSEL, textLen, textLen);

        if (_editBoxInputMode == cocos2d::ui::EditBox::InputMode::ANY)
        {
            ::SendMessageW(_hwndEdit, EM_SCROLLCARET, 0, 0);
        }
    }

    void EditBoxImplWin::setNativePlaceHolder(const char* pText)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativeVisible(bool visible)
    {
        if (visible)
        {
            ::ShowWindow(_hwndEdit, SW_SHOW);
        }
        else
        {
            ::ShowWindow(_hwndEdit, SW_HIDE);
        }
    }

    void EditBoxImplWin::updateNativeFrame(const Rect& rect)
    {
        ::SetWindowPos(
            _hwndEdit,
            HWND_NOTOPMOST,
            rect.origin.x,
            rect.origin.y,
            rect.size.width,
            rect.size.height,
            SWP_NOZORDER);
    }

    const char* EditBoxImplWin::getNativeDefaultFontName()
    {
        return "Arial";
    }

    void EditBoxImplWin::nativeOpenKeyboard()
    {
        ::PostMessageW(_hwndEdit, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
//        s_previousFocusWnd = hwndEdit;
        this->editBoxEditingDidBegin();

        auto rect = ui::Helper::convertBoundingBoxToScreen(_editBox);
        this->updateNativeFrame(rect);
    }

    void EditBoxImplWin::nativeCloseKeyboard()
    {
        //don't need to implement
    }

    void EditBoxImplWin::setNativeMaxLength(int maxLength)
    {
        ::SendMessageW(_hwndEdit, EM_LIMITTEXT, maxLength, 0);
    }

    void EditBoxImplWin::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CHAR:
            if (wParam == VK_RETURN)
            {
                if (_editBoxInputMode != cocos2d::ui::EditBox::InputMode::ANY) {
                    if (s_previousFocusWnd != s_hwndCocos) {
                        switch (_keyboardReturnType)
                        {
                        case EditBox::KeyboardReturnType::DEFAULT:
                            _endAction = EditBoxDelegate::EditBoxEndAction::UNKNOWN;
                            break;
                        case EditBox::KeyboardReturnType::DONE:
                            _endAction = EditBoxDelegate::EditBoxEndAction::RETURN;
                            break;
                        case EditBox::KeyboardReturnType::SEND:
                            _endAction = EditBoxDelegate::EditBoxEndAction::RETURN;
                            break;
                        case EditBox::KeyboardReturnType::SEARCH:
                            _endAction = EditBoxDelegate::EditBoxEndAction::RETURN;
                            break;
                        case EditBox::KeyboardReturnType::GO:
                            _endAction = EditBoxDelegate::EditBoxEndAction::RETURN;
                            break;
                        case EditBox::KeyboardReturnType::NEXT:
                            _endAction = EditBoxDelegate::EditBoxEndAction::TAB_TO_NEXT;
                            break;
                        default:
                            _endAction = EditBoxDelegate::EditBoxEndAction::UNKNOWN;
                            break;
                        }
                        ::ShowWindow(s_previousFocusWnd, SW_HIDE);
                        ::SendMessageW(s_hwndCocos, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
                        s_previousFocusWnd = s_hwndCocos;
                    }
                }
            }
            break;
        case WM_SETFOCUS:
            if (hwnd != s_previousFocusWnd)
            {
                ::PostMessageW(hwnd, WM_ACTIVATE, (WPARAM)s_previousFocusWnd, 0);
                ::PostMessageW(hwnd, WM_SETCURSOR, (WPARAM)s_previousFocusWnd, 0);
                s_previousFocusWnd = _hwndEdit;
                _hasFocus = true;
                this->_changedTextManually = false;
            }
            break;
        case WM_KILLFOCUS:
            _hasFocus = false;
            //when app enter background, this message also be called.
            if (this->_editingMode && !::IsWindowVisible(hwnd))
            {
                this->editBoxEditingDidEnd(this->getText(), _endAction);
            }
            break;
        default:
            break;
        }
    }

    std::string EditBoxImplWin::getText() const
    {
        std::u16string wstrResult;
        std::string utf8Result;

        int inputLength = ::GetWindowTextLengthW(_hwndEdit);
        wstrResult.resize(inputLength);

        ::GetWindowTextW(_hwndEdit, (LPWSTR)&wstrResult[0], inputLength + 1);
        bool conversionResult = cocos2d::StringUtils::UTF16ToUTF8(wstrResult, utf8Result);
        if (!conversionResult)
        {
            CCLOG("warning, editbox input text conversion error.");
        }
        return std::move(utf8Result);
    }

    LRESULT EditBoxImplWin::hookGLFWWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_COMMAND:
            if (HIWORD(wParam) == EN_CHANGE) {
                EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtrW((HWND)lParam, GWLP_USERDATA);
                if (pThis && !pThis->_changedTextManually)
                {
                    pThis->editBoxEditingChanged(pThis->getText());
                    pThis->_changedTextManually = false;
                }

            }
            break;
        case WM_LBUTTONDOWN:
            if (s_previousFocusWnd != s_hwndCocos) {
                ::ShowWindow(s_previousFocusWnd, SW_HIDE);

                EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtrW(s_previousFocusWnd, GWLP_USERDATA);
                if (pThis!=nullptr && !pThis->_hasFocus)
                {
                    if (pThis->_editingMode && !IsWindowVisible(s_previousFocusWnd))
                    {
                        pThis->editBoxEditingDidEnd(pThis->getText());
                    }
                }
                else
                {
                    ::PostMessageW(s_hwndCocos, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
                }
                s_previousFocusWnd = s_hwndCocos;
            }

            break;
        default:
            break;
        }

        return ::CallWindowProcW(s_prevCocosWndProc, hwnd, uMsg, wParam, lParam);
    }

    LRESULT EditBoxImplWin::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
        if (pThis)
        {
            pThis->_WindowProc(hwnd, uMsg, wParam, lParam);
        }

        return ::CallWindowProcW(pThis->_prevWndProc, hwnd, uMsg, wParam, lParam);
    }
}

NS_CC_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */
