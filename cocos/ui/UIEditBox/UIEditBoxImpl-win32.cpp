/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013 Jozef Pridavok
Copyright (c) 2013-2017 zilongshanren

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
        LONG style = GetWindowLong(s_hwndCocos, GWL_STYLE);
        SetWindowLong(s_hwndCocos, GWL_STYLE, style | WS_CLIPCHILDREN);
        s_isInitialized = true;
        s_previousFocusWnd = s_hwndCocos;

        s_hInstance = GetModuleHandle(NULL);


        s_prevCocosWndProc = (WNDPROC)SetWindowLongPtr(s_hwndCocos, GWL_WNDPROC, (LONG_PTR)hookGLFWWindowProc);

    }

    EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
    {
        return new (std::nothrow) EditBoxImplWin(pEditBox);
    }

    EditBoxImplWin::EditBoxImplWin(EditBox* pEditText)
        : EditBoxImplCommon(pEditText),
        _fontSize(40),
        _changedTextManually(false),
        _hasFocus(false)
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
        if (hwndEdit)
        {
            SetWindowLongPtr(hwndEdit, GWL_WNDPROC, (LONG_PTR)_prevWndProc);
            DestroyWindow(hwndEdit);
            _hasFocus = false;
            _changedTextManually = false;
            _editingMode = false;
            hwndEdit = NULL;
        }
    }

    void EditBoxImplWin::createSingleLineEditCtrl()
    {
        this->cleanupEditCtrl();
        if (!hwndEdit)
        {
            hwndEdit = CreateWindowEx(
                WS_EX_CLIENTEDGE, L"EDIT",   // predefined class 
                NULL,         // no window title 
                WS_CHILD | ES_LEFT | WS_BORDER | WS_EX_TRANSPARENT | WS_TABSTOP | ES_AUTOHSCROLL,
                0,
                0,
                0,
                0,   // set size in WM_SIZE message 
                s_hwndCocos,         // parent window 
                (HMENU)s_editboxChildID,   // edit control ID 
                s_hInstance,
                this);        // pointer not needed 

            SetWindowLongPtr(hwndEdit, GWL_USERDATA, (LONG_PTR)this);
            _prevWndProc = (WNDPROC)SetWindowLongPtr(hwndEdit, GWL_WNDPROC, (LONG_PTR)WindowProc);

            ::SendMessageW(hwndEdit, EM_LIMITTEXT, this->_maxLength, 0);
            s_previousFocusWnd = s_hwndCocos;
            this->setNativeFont(this->getNativeDefaultFontName(), this->_fontSize);
            this->setNativeText(this->_text.c_str());
        }
    }

    void EditBoxImplWin::createMultilineEditCtrl()
    {
        this->cleanupEditCtrl();
        if (!hwndEdit)
        {
            hwndEdit = CreateWindowEx(
                WS_EX_CLIENTEDGE, L"EDIT",   // predefined class 
                NULL,         // no window title 
                WS_CHILD | ES_LEFT | WS_BORDER | WS_EX_TRANSPARENT | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL,
                0,
                0,
                0,
                0,   // set size in WM_SIZE message 
                s_hwndCocos,         // parent window 
                (HMENU)s_editboxChildID,   // edit control ID 
                s_hInstance,
                this);        // pointer not needed 

                              //register new window proc func
            SetWindowLongPtr(hwndEdit, GWL_USERDATA, (LONG_PTR)this);
            _prevWndProc = (WNDPROC)SetWindowLongPtr(hwndEdit, GWL_WNDPROC, (LONG_PTR)WindowProc);
            s_previousFocusWnd = s_hwndCocos;
            ::SendMessageW(hwndEdit, EM_LIMITTEXT, this->_maxLength, 0);
            this->setNativeFont(this->getNativeDefaultFontName(), this->_fontSize);
            this->setNativeText(this->_text.c_str());

        }
    }

    void EditBoxImplWin::createNativeControl(const Rect & frame)
    {

        this->createMultilineEditCtrl();
    }

    void EditBoxImplWin::setNativeFont(const char * pFontName, int fontSize)
    {
        //not implemented yet
        this->_fontSize = fontSize;
        HFONT hFont = CreateFontW(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

        SendMessage(hwndEdit,             // Handle of edit control
            WM_SETFONT,         // Message to change the font
            (WPARAM)hFont,     // handle of the font
            MAKELPARAM(TRUE, 0) // Redraw text
        );
    }

    void EditBoxImplWin::setNativeFontColor(const Color4B & color)
    {
        //not implemented yet
    }

    void EditBoxImplWin::setNativePlaceholderFont(const char * pFontName, int fontSize)
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
            this->createMultilineEditCtrl();
        }
        else if (_editBoxInputMode == cocos2d::ui::EditBox::InputMode::NUMERIC
            || _editBoxInputMode == cocos2d::ui::EditBox::InputMode::DECIMAL
            || _editBoxInputMode == cocos2d::ui::EditBox::InputMode::PHONE_NUMBER)
        {
            this->createSingleLineEditCtrl();
            ::SetWindowLongW(hwndEdit, GWL_STYLE, ::GetWindowLongW(hwndEdit, GWL_STYLE) | ES_NUMBER);
        }
        else
        {
            this->createSingleLineEditCtrl();
        }

        if (this->_editBoxInputFlag != cocos2d::ui::EditBox::InputFlag::PASSWORD)
        {
            PostMessage(hwndEdit, EM_SETPASSWORDCHAR, (WPARAM)0, (LPARAM)0);
        }
    }
    void EditBoxImplWin::setNativeInputFlag(EditBox::InputFlag inputFlag)
    {
        if (inputFlag == EditBox::InputFlag::PASSWORD)
        {
            this->createSingleLineEditCtrl();
        }
       
        else
        {
            if (_editBoxInputMode != cocos2d::ui::EditBox::InputMode::ANY)
            {
                this->createSingleLineEditCtrl();

                if (inputFlag == EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
                {
                    ::SetWindowLongW(hwndEdit, GWL_STYLE, ::GetWindowLongW(hwndEdit, GWL_STYLE) | ES_UPPERCASE);
                }
                // Clear the password style
                PostMessage(hwndEdit, EM_SETPASSWORDCHAR, (WPARAM)0, (LPARAM)0);
            }
        }
    }
    void EditBoxImplWin::setNativeReturnType(EditBox::KeyboardReturnType returnType)
    {
        //not implemented yet
    }
    void EditBoxImplWin::setNativeText(const char* pText)
    {
        std::u16string utf16Result;
        std::string text(pText);
        cocos2d::StringUtils::UTF8ToUTF16(text, utf16Result);
        this->_changedTextManually = true;
        ::SetWindowTextW(hwndEdit, (LPCWSTR)utf16Result.c_str());
        int textLen = text.size();
        SendMessage(hwndEdit, EM_SETSEL, textLen, textLen);
        if (_editBoxInputMode == cocos2d::ui::EditBox::InputMode::ANY)
        {
            SendMessage(hwndEdit, EM_SCROLLCARET, 0, 0);
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
            ::ShowWindow(hwndEdit, SW_SHOW);
        }
        else
        {
            ::ShowWindow(hwndEdit, SW_HIDE);
        }
    }
    void EditBoxImplWin::updateNativeFrame(const Rect& rect)

    {
        ::SetWindowPos(
            hwndEdit,
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
        ::PostMessage(hwndEdit, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
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

        ::SendMessageW(hwndEdit, EM_LIMITTEXT, maxLength, 0);

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
                        ::ShowWindow(s_previousFocusWnd, SW_HIDE);
                        ::SendMessage(s_hwndCocos, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
                        s_previousFocusWnd = s_hwndCocos;
                    }
                }
            }
            break;
        case WM_SETFOCUS:
            if (hwnd != s_previousFocusWnd)
            {
                ::PostMessage(hwnd, WM_ACTIVATE, (WPARAM)s_previousFocusWnd, 0);
                ::PostMessage(hwnd, WM_SETCURSOR, (WPARAM)s_previousFocusWnd, 0);
                s_previousFocusWnd = hwndEdit;
                _hasFocus = true;
                this->_changedTextManually = false;
            }
           
            break;
        case WM_KILLFOCUS:
            _hasFocus = false;
            //when app enter background, this message also be called.
            if (this->_editingMode && !IsWindowVisible(hwnd))
            {
                this->editBoxEditingDidEnd(this->getText());
            }
            break;
        default:
            break;

        }
    }

    std::string EditBoxImplWin::getText()const
    {
        std::u16string wstrResult;
        std::string utf8Result;


        int inputLength = ::GetWindowTextLengthW(this->hwndEdit);
        wstrResult.resize(inputLength);

        ::GetWindowTextW(this->hwndEdit, (LPWSTR) const_cast<char16_t*>(wstrResult.c_str()), inputLength + 1);
        bool conversionResult = cocos2d::StringUtils::UTF16ToUTF8(wstrResult, utf8Result);
        if (!conversionResult)
        {
            CCLOG("warning, editbox input text convertion error.");
        }
        return std::move(utf8Result);
    }

    LRESULT EditBoxImplWin::hookGLFWWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_COMMAND:
            if (HIWORD(wParam) == EN_CHANGE) {
                EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
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

                EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtr(s_previousFocusWnd, GWLP_USERDATA);
                if (!pThis->_hasFocus)
                {
                    if (pThis->_editingMode && !IsWindowVisible(s_previousFocusWnd))
                    {
                        pThis->editBoxEditingDidEnd(pThis->getText());
                    }
                }
                else
                {
                    ::PostMessage(s_hwndCocos, WM_SETFOCUS, (WPARAM)s_previousFocusWnd, 0);
                }
                s_previousFocusWnd = s_hwndCocos;
            }

            break;
        default:
            break;
        }

        return CallWindowProc(s_prevCocosWndProc, hwnd, uMsg, wParam, lParam);
    }

    LRESULT EditBoxImplWin::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        EditBoxImplWin* pThis = (EditBoxImplWin*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (pThis)
        {
            pThis->_WindowProc(hwnd, uMsg, wParam, lParam);
        }

        return CallWindowProc(pThis->_prevWndProc, hwnd, uMsg, wParam, lParam);

    }
}

NS_CC_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */