//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once
#include "pch.h"

class MediaStreamer
{
private:
    WAVEFORMATEX                        m_waveFormat;
    uint32                              m_maxStreamLengthInBytes;
    Windows::Storage::StorageFolder^    m_installedLocation;
    Platform::String^                   m_installedLocationPath;

public:
    Microsoft::WRL::ComPtr<IMFSourceReader> m_reader;
    Microsoft::WRL::ComPtr<IMFMediaType> m_audioType;

public:
    MediaStreamer();
    ~MediaStreamer();

    WAVEFORMATEX& GetOutputWaveFormatEx()
    {
        return m_waveFormat;
    }

    UINT32 GetMaxStreamLengthInBytes()
    {
        return m_maxStreamLengthInBytes;
    }

    void Initialize(_In_ const WCHAR* url); 
    bool GetNextBuffer(uint8* buffer, uint32 maxBufferSize, uint32* bufferLength);
    void ReadAll(uint8* buffer, uint32 maxBufferSize, uint32* bufferLength); 
    void Restart();
};