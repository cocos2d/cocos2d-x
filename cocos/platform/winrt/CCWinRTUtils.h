/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#ifndef __CCWINRT_UTILS_H__
#define __CCWINRT_UTILS_H__

#include "platform/CCPlatformMacros.h"

#include <wrl/client.h>
#include <ppl.h>
#include <ppltasks.h>

#include <string>

NS_CC_BEGIN



std::wstring CC_DLL CCUtf8ToUnicode(const char * pszUtf8Str, unsigned len = -1);
std::string CC_DLL CCUnicodeToUtf8(const wchar_t* pwszStr);
std::string PlatformStringToString(Platform::String^ s);

// Method to convert a length in device-independent pixels (DIPs) to a length in physical pixels.
float ConvertDipsToPixels(float dips);
float getScaledDPIValue(float v);

Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ path);

void CC_DLL CCLogIPAddresses();

std::string CC_DLL getDeviceIPAddresses();


NS_CC_END

#endif // __CCWINRT_UTILS_H__
