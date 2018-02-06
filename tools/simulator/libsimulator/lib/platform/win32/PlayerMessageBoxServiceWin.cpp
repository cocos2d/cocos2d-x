/****************************************************************************
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


#include "PlayerMessageBoxServiceWin.h"

PLAYER_NS_BEGIN

PlayerMessageBoxServiceWin::PlayerMessageBoxServiceWin(HWND hwnd)
: _hwnd(hwnd)
{
}

int PlayerMessageBoxServiceWin::showMessageBox(const std::string &title,
                                               const std::string &message,
                                               int buttonsType /* = BUTTONS_OK */)
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);
    std::u16string u16message;
    cocos2d::StringUtils::UTF8ToUTF16(message, u16message);

    CCLOG("PlayerMessageBoxServiceWin::showMessageBox() - title = %s, message = %s", title.c_str(), message.c_str());

    UINT mbtype = MB_APPLMODAL;
    switch (buttonsType)
    {
    case BUTTONS_OK_CANCEL:
        mbtype |= MB_OKCANCEL | MB_ICONQUESTION;
        break;

    case BUTTONS_YES_NO:
        mbtype |= MB_YESNO | MB_ICONQUESTION;
        break;

    case BUTTONS_YES_NO_CANCEL:
        mbtype |= MB_YESNOCANCEL | MB_ICONQUESTION;
        break;

    default:
        mbtype |= MB_OK | MB_ICONINFORMATION;
    }

    // MessageBox() used by cocos2d
    int result = ::MessageBoxW(_hwnd, (LPCTSTR)u16message.c_str(), (LPCTSTR)u16title.c_str(), mbtype);

    switch (result)
    {
    case IDCANCEL:
        result = BUTTON_CANCEL;
        break;

    case IDYES:
        result = BUTTON_YES;
        break;

    case IDNO:
        result = BUTTON_NO;
        break;

    default:
        result = BUTTON_OK;
    }

    CCLOG("PlayerMessageBoxServiceWin::showMessageBox() - result = %d", result);

    return result;
}

PLAYER_NS_END
