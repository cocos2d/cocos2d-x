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


#include <string>

#include "stdafx.h"
#include "cocos2d.h"
#include "PlayerEditBoxServiceWin.h"

PLAYER_NS_BEGIN

PlayerEditBoxServiceWin::PlayerEditBoxServiceWin(HWND hwnd)
: _hfont(NULL)
{
    _hwnd = hwnd;
    HINSTANCE instance = (HINSTANCE)GetWindowLong(_hwnd, GWL_HINSTANCE);
    DWORD style = WS_CHILD | ES_LEFT | ES_AUTOHSCROLL;
    _hwndSingle = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"", style, 0, 0, 0, 0, _hwnd, NULL, instance, NULL);
    style = WS_CHILD | ES_MULTILINE | ES_LEFT | ES_AUTOVSCROLL | ES_WANTRETURN | WS_VSCROLL;
    _hwndMulti = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"", style, 0, 0, 0, 0, _hwnd, NULL, instance, NULL);
}

PlayerEditBoxServiceWin::~PlayerEditBoxServiceWin()
{
    removeFont();
    DestroyWindow(_hwndSingle);
    DestroyWindow(_hwndMulti);
}

void PlayerEditBoxServiceWin::showSingleLineEditBox(const cocos2d::Rect &rect)
{
    MoveWindow(_hwndSingle, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, TRUE);
    ShowWindow(_hwndSingle, SW_SHOW);
    SetFocus(_hwndSingle);
}

void PlayerEditBoxServiceWin::showMultiLineEditBox(const cocos2d::Rect &rect)
{
    MoveWindow(_hwndMulti, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, TRUE);
    ShowWindow(_hwndMulti, SW_SHOW);
    SetFocus(_hwndMulti);
}

void PlayerEditBoxServiceWin::hide()
{
}

void PlayerEditBoxServiceWin::setText(const std::string &text)
{
}

void PlayerEditBoxServiceWin::setFont(const std::string &name, int size)
{
    removeFont();

    std::u16string u16name;
    cocos2d::StringUtils::UTF8ToUTF16(name, u16name);

    HDC hdc = GetDC(_hwnd);
    size = -MulDiv(size, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ReleaseDC(_hwnd, hdc);

    _hfont = CreateFont(size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        0, OUT_DEFAULT_PRECIS, FW_NORMAL, DEFAULT_QUALITY, DEFAULT_PITCH,
                        (LPCTSTR)u16name.c_str());
    if (!_hfont)
    {
        DWORD err = GetLastError();
        CCLOG("PlayerEditBoxServiceWin::setFont() - create HFONT for font \"%s\" failed, error code = 0x%08x",
              name.c_str(), err);
    }
    else
    {
        SendMessage(_hwndSingle, WM_SETFONT, (WPARAM)_hfont, NULL);
        SendMessage(_hwndMulti, WM_SETFONT, (WPARAM)_hfont, NULL);
    }
}

void PlayerEditBoxServiceWin::setFontColor(const cocos2d::Color3B &color)
{

}

void PlayerEditBoxServiceWin::removeFont()
{
    if (_hfont)
    {
        SendMessage(_hwndSingle, WM_SETFONT, NULL, NULL);
        SendMessage(_hwndMulti, WM_SETFONT, NULL, NULL);
        DeleteObject(_hfont);
    }
    _hfont = NULL;
}

void PlayerEditBoxServiceWin::setFormator(int /*formator*/ )
{

}

PLAYER_NS_END
