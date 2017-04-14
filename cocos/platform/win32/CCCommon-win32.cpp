/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "platform/CCCommon.h"
#include "platform/CCStdC.h"
#include "platform/win32/CCUtils-win32.h"

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void MessageBox(const char * pszMsg, const char * pszTitle)
{
    std::wstring wsMsg = cocos2d::StringUtf8ToWideChar(pszMsg);
    std::wstring wsTitle = cocos2d::StringUtf8ToWideChar(pszTitle);
    MessageBoxW(nullptr, wsMsg.c_str(), wsTitle.c_str(), MB_OK);
}

void LuaLog(const char *pszMsg)
{
    OutputDebugStringW(cocos2d::StringUtf8ToWideChar(pszMsg).c_str());
    OutputDebugStringA("\n");

    puts(UTF8StringToMultiByte(pszMsg).c_str());
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
