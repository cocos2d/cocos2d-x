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

#pragma once


#include <vector>

ref class MediaStreamer
{
private:
    WAVEFORMATEX      m_waveFormat;
    uint32            m_maxStreamLengthInBytes;
    std::vector<byte> m_data;
    UINT32            m_offset;
	Platform::Array<byte>^ ReadData(
    _In_ Platform::String^ filename
    );
internal:
    Windows::Storage::StorageFolder^ m_location;
    Platform::String^ m_locationPath;

public:
    virtual ~MediaStreamer();

internal:
    MediaStreamer();

    WAVEFORMATEX& GetOutputWaveFormatEx()
    {
        return m_waveFormat;
    }

    UINT32 GetMaxStreamLengthInBytes()
    {
		return m_data.size();
    }

    void Initialize(_In_ const WCHAR* url); 
    void ReadAll(uint8* buffer, uint32 maxBufferSize, uint32* bufferLength); 
    void Restart();
};