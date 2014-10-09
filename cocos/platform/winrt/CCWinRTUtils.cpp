/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
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
#include "CCWinRTUtils.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <Windows.h>
#include <wrl/client.h>
#include <ppl.h>
#include <ppltasks.h>
#include <sstream>

NS_CC_BEGIN

using namespace Windows::Graphics::Display;
using namespace Windows::Storage;
using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking::Connectivity;

std::wstring CCUtf8ToUnicode(const char * pszUtf8Str, unsigned len/* = -1*/)
{
    std::wstring ret;
    do
    {
        if (! pszUtf8Str) break;
		// get UTF8 string length
		if (-1 == len)
		{
			len = strlen(pszUtf8Str);
		}
        if (len <= 0) break;

		// get UTF16 string length
		int wLen = MultiByteToWideChar(CP_UTF8, 0, pszUtf8Str, len, 0, 0);
		if (0 == wLen || 0xFFFD == wLen) break;
		
		// convert string  
        wchar_t * pwszStr = new wchar_t[wLen + 1];
        if (! pwszStr) break;
        pwszStr[wLen] = 0;
        MultiByteToWideChar(CP_UTF8, 0, pszUtf8Str, len, pwszStr, wLen + 1);
        ret = pwszStr;
        CC_SAFE_DELETE_ARRAY(pwszStr);
    } while (0);
    return ret;
}

std::string CCUnicodeToUtf8(const wchar_t* pwszStr)
{
	std::string ret;
	do
	{
		if(! pwszStr) break;
		size_t len = wcslen(pwszStr);
		if (len <= 0) break;
		
		size_t convertedChars = 0;
		char * pszUtf8Str = new char[len*3 + 1];
		WideCharToMultiByte(CP_UTF8, 0, pwszStr, len+1, pszUtf8Str, len*3 + 1, 0, 0);
		ret = pszUtf8Str;
		CC_SAFE_DELETE_ARRAY(pszUtf8Str);
	}while(0);

	return ret;
}

std::string PlatformStringToString(Platform::String^ s) {
	std::wstring t = std::wstring(s->Data());
	return std::string(t.begin(),t.end());
}

Platform::String^ PlatformStringFromString(const std::string& s)
{
    std::wstring ws(CCUtf8ToUnicode(s.c_str()));
    return ref new Platform::String(ws.data(), ws.length());
}

// Method to convert a length in device-independent pixels (DIPs) to a length in physical pixels.
float ConvertDipsToPixels(float dips)
{
   static const float dipsPerInch = 96.0f;
   return floor(dips * DisplayProperties::LogicalDpi / dipsPerInch + 0.5f); // Round to nearest integer.
}

float getScaledDPIValue(float v) {
	auto dipFactor = DisplayProperties::LogicalDpi / 96.0f;
	return v * dipFactor;
}

void CC_DLL CCLogIPAddresses()
{
    auto hostnames = NetworkInformation::GetHostNames();
    int length = hostnames->Size;

    for(int i = 0; i < length; i++)
    {
        auto hn = hostnames->GetAt(i);
        if (hn->IPInformation != nullptr)
        {
            std::string s = PlatformStringToString(hn->DisplayName);
            CCLog("IP Address: %s:", s.c_str());
        }
    }
}

std::string CC_DLL getDeviceIPAddresses()
{
    std::stringstream result;

    auto hostnames = NetworkInformation::GetHostNames();
    int length = hostnames->Size;

    for(int i = 0; i < length; i++)
    {
        auto hn = hostnames->GetAt(i);
        if (hn->IPInformation != nullptr)
        {
            result << PlatformStringToString(hn->DisplayName) << std::endl;
        }
    }

    return result.str();
}








#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

// Function that reads from a binary file asynchronously.
Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ filename)
{
	using namespace Windows::Storage;
	using namespace Concurrency;
		
	auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
		
	return create_task(folder->GetFileAsync(filename)).then([] (StorageFile^ file) 
	{
		return file->OpenReadAsync();
	}).then([] (Streams::IRandomAccessStreamWithContentType^ stream)
	{
		unsigned int bufferSize = static_cast<unsigned int>(stream->Size);
		auto fileBuffer = ref new Streams::Buffer(bufferSize);
		return stream->ReadAsync(fileBuffer, bufferSize, Streams::InputStreamOptions::None);
	}).then([] (Streams::IBuffer^ fileBuffer) -> Platform::Array<byte>^ 
	{
		auto fileData = ref new Platform::Array<byte>(fileBuffer->Length);
		Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(fileData);
		return fileData;
	});
}
#else



// Function that reads from a binary file asynchronously.
Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ path)
{
	using namespace Windows::Storage;
	using namespace Concurrency;
		
	return create_task(StorageFile::GetFileFromPathAsync(path)).then([&](StorageFile^ f)
	{
		return FileIO::ReadBufferAsync(f);

	}).then([] (Streams::IBuffer^ fileBuffer) -> Platform::Array<byte>^ 
	{
		auto fileData = ref new Platform::Array<byte>(fileBuffer->Length);
		Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(fileData);
		return fileData;
	});
}



#endif


NS_CC_END
