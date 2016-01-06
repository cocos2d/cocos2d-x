/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "MediaStreamer.h"

#include <Mfidl.h>
#include <Mfreadwrite.h>
#include <Mfapi.h>

#include <wrl\wrappers\corewrappers.h>
#include <ppltasks.h>

using namespace Microsoft::WRL;
using namespace Windows::Storage;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Concurrency;

#ifndef MAKEFOURCC
    #define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((uint32)(byte)(ch0) | ((uint32)(byte)(ch1) << 8) |       \
                ((uint32)(byte)(ch2) << 16) | ((uint32)(byte)(ch3) << 24 ))
#endif /* defined(MAKEFOURCC) */

const int FMT_CHUNK_MAX = 256;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        // Set a breakpoint on this line to catch DX API errors.
        throw Platform::Exception::CreateException(hr);
    }
}

MediaStreamer::MediaStreamer() :
    m_offset(0)
    , m_dataLen(0)
    , m_filename(nullptr)
{
    ZeroMemory(&m_waveFormat, sizeof(m_waveFormat));
    m_location = Package::Current->InstalledLocation;
    m_locationPath = Platform::String::Concat(m_location->Path, "\\Assets\\Resources\\");
}

MediaStreamer::~MediaStreamer()
{
}

Platform::Array<byte>^ MediaStreamer::ReadData(_In_ Platform::String^ filename)
{
    return ReadData(filename, 0, 0);
}

Platform::Array<byte>^ MediaStreamer::ReadData(_In_ Platform::String^ filename, uint32 from, uint32 length)
{
    CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {0};
    extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    extendedParams.dwFileFlags = from ? FILE_FLAG_RANDOM_ACCESS : FILE_FLAG_SEQUENTIAL_SCAN;
    extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
    extendedParams.lpSecurityAttributes = nullptr;
    extendedParams.hTemplateFile = nullptr;

    Wrappers::FileHandle file(
        CreateFile2(filename->Data(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams)
        );

    if (file.Get()==INVALID_HANDLE_VALUE)
    {
        throw ref new Platform::FailureException();
    }

    FILE_STANDARD_INFO fileInfo = { 0 };
    if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo, &fileInfo, sizeof(fileInfo)))
    {
        throw ref new Platform::FailureException();
    }

    if (fileInfo.EndOfFile.HighPart != 0)
    {
        throw ref new Platform::OutOfMemoryException();
    }

    from += m_offset;
    length = (length == 0 || from + length > fileInfo.EndOfFile.LowPart) ? fileInfo.EndOfFile.LowPart - from : length;
    Platform::Array<byte>^ fileData = ref new Platform::Array<byte>(length);

    if (from)
    {
        LARGE_INTEGER pos = { 0 };
        pos.QuadPart = from;
        if (!SetFilePointerEx(file.Get(), pos, nullptr, FILE_BEGIN))
        {
            throw ref new Platform::FailureException();
        }
    }

    if (!ReadFile(file.Get(), fileData->Data, fileData->Length, nullptr, nullptr))
    {
        throw ref new Platform::FailureException();
    }

    return fileData;
}

void MediaStreamer::Initialize(__in const WCHAR* url, bool lazy)
{
    m_filename = ref new Platform::String(url);
    WCHAR filePath[MAX_PATH] = {0};
	if ((wcslen(url) > 1 && url[1] == ':'))
	{
		// path start with "x:", is absolute path
		wcscat_s(filePath, url);
	}
	else if (wcslen(url) > 0 
		&& (L'/' == url[0] || L'\\' == url[0]))
	{
		// path start with '/' or '\', is absolute path without driver name
		wcscat_s(filePath, m_locationPath->Data());
		// remove '/' or '\\'
		wcscat_s(filePath, (const WCHAR*)url[1]);
	}else
	{
		wcscat_s(filePath, m_locationPath->Data());
		wcscat_s(filePath, url);
	}

    Platform::Array<byte>^ data = lazy ? ReadData(ref new Platform::String(filePath), 0, FMT_CHUNK_MAX) : ReadData(ref new Platform::String(filePath));
	UINT32 length = data->Length;
	const byte * dataPtr = data->Data;
	UINT32 offset = 0;

	DWORD riffDataSize = 0;

	auto ReadChunk = [&length, &offset, &dataPtr, &riffDataSize](DWORD fourcc, DWORD& outChunkSize, DWORD& outChunkPos) -> HRESULT
	{
		while (true)
		{
			if (offset + sizeof(DWORD) * 2 >= length)
			{
				return E_FAIL;
			}

			// Read two DWORDs.
			DWORD chunkType = *reinterpret_cast<const DWORD *>(&dataPtr[offset]);
			DWORD chunkSize = *reinterpret_cast<const DWORD *>(&dataPtr[offset + sizeof(DWORD)]);
			offset += sizeof(DWORD) * 2;

			if (chunkType == MAKEFOURCC('R', 'I', 'F', 'F'))
			{
				riffDataSize = chunkSize;
				chunkSize = sizeof(DWORD);
				outChunkSize = sizeof(DWORD);
				outChunkPos = offset;
			}
			else
			{
				outChunkSize = chunkSize;
				outChunkPos = offset;
			}

			offset += chunkSize;

			if (chunkType == fourcc)
			{
				return S_OK;
			}
		}
	};

	// Locate riff chunk, check the file type.
	DWORD chunkSize = 0;
	DWORD chunkPos = 0;

	ThrowIfFailed(ReadChunk(MAKEFOURCC('R', 'I', 'F', 'F'), chunkSize, chunkPos));
	if (*reinterpret_cast<const DWORD *>(&dataPtr[chunkPos]) != MAKEFOURCC('W', 'A', 'V', 'E')) ThrowIfFailed(E_FAIL);

	// Locate 'fmt ' chunk, copy to WAVEFORMATEXTENSIBLE.
	ThrowIfFailed(ReadChunk(MAKEFOURCC('f', 'm', 't', ' '), chunkSize, chunkPos));
	ThrowIfFailed((chunkSize <= sizeof(m_waveFormat)) ? S_OK : E_FAIL);
	CopyMemory(&m_waveFormat, &dataPtr[chunkPos], chunkSize);

	// Locate the 'data' chunk and copy its contents to a buffer.
	ThrowIfFailed(ReadChunk(MAKEFOURCC('d', 'a', 't', 'a'), chunkSize, chunkPos));
    m_dataLen = chunkSize;
    m_offset = chunkPos;

    if (!lazy)
    {
        m_data.resize(chunkSize);
        CopyMemory(m_data.data(), &dataPtr[chunkPos], chunkSize);
        m_offset = 0;
    }
}

void MediaStreamer::ReadAll(uint8* buffer, uint32 maxBufferSize, uint32* bufferLength)
{
    if (!m_data.size())
    {
        ReadChunk(buffer, 0, m_dataLen, bufferLength);
    }
    else
    {
        UINT32 toCopy = m_data.size() - m_offset;
        if (toCopy > maxBufferSize) toCopy = maxBufferSize;

        CopyMemory(buffer, m_data.data(), toCopy);
        *bufferLength = toCopy;

        m_offset += toCopy;
        if (m_offset > m_data.size()) m_offset = m_data.size();
    }
}

void MediaStreamer::ReadChunk(uint8* buffer, uint32 from, uint32 length, uint32* bytesRead)
{
    Platform::Array<byte>^ data = ReadData(m_filename, from, length);
    *bytesRead = data->Length;

    if (*bytesRead > 0)
    {
        CopyMemory(buffer, (byte*)data->Data, data->Length);
    }
}

void MediaStreamer::Restart()
{
	m_offset = 0;
}
