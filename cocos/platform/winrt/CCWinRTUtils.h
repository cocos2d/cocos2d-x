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
#include <ppltasks.h>

#include <string>

NS_CC_BEGIN

bool isWindowsPhone();

CC_DEPRECATED_ATTRIBUTE std::wstring CC_DLL CCUtf8ToUnicode(const char * pszUtf8Str, unsigned len = -1);
CC_DEPRECATED_ATTRIBUTE std::string CC_DLL CCUnicodeToUtf8(const wchar_t* pwszStr);

std::wstring CC_DLL StringUtf8ToWideChar(const std::string& strUtf8);
std::string CC_DLL StringWideCharToUtf8(const std::wstring& strWideChar);

Platform::Object^ findXamlElement(Platform::Object^ parent, Platform::String^ name);
bool removeXamlElement(Platform::Object^ parent, Platform::Object^ element);
bool replaceXamlElement(Platform::Object^ parent, Platform::Object^ add, Platform::Object^ remove);

std::string PlatformStringToString(Platform::String^ s);
Platform::String^ PlatformStringFromString(const std::string& s);

Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ path);

void CC_DLL CCLogIPAddresses();

std::string CC_DLL getDeviceIPAddresses();

std::string computeHashForFile(const std::string& filePath);

// creates a  cache file path corresponding to given source file.
// srcFilePath - source file.
// cacheFilePath - cache file path to be used to save cache.
// return true if file already exists
bool createMappedCacheFile(/*In*/ const std::string& srcFilePath, /*Out*/ std::string& cacheFilePath, /*Optional*/ std::string ext = "");
void destroyMappedCacheFile(const std::string& key);

NS_CC_END

#endif // __CCWINRT_UTILS_H__
