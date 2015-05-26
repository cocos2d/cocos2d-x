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

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#include "AudioSourceReader.h"

using namespace cocos2d;
using namespace cocos2d::experimental;


// AudioFileReader
AudioSourceReader::AudioSourceReader() :
_isStreaming(false)
, _filePath("")
, _audioSize(0)
{
}

AudioSourceReader::~AudioSourceReader()
{
}


// WAVFileReader
WAVReader::WAVReader() :
_bytesRead(0)
, _isDirty(false)
, _streamer(nullptr)
{
}

WAVReader::~WAVReader()
{
    flushChunks();
}

bool WAVReader::initialize(const std::string& filePath)
{
    bool ret = false;
    _isStreaming = false;
    _filePath = filePath;

    do {
        auto fileSize = FileUtils::getInstance()->getFileSize(_filePath);

        if (fileSize <= 0)
            break;

        flushChunks();

        _rwMutex.lock();
        _streamer = ref new MediaStreamer;
        _streamer->Initialize(std::wstring(_filePath.begin(), _filePath.end()).c_str(), true);
        _rwMutex.unlock();
        _wfx = _streamer->GetOutputWaveFormatEx();
        UINT32 dataSize = _streamer->GetMaxStreamLengthInBytes();

        if (dataSize <= 0)
            break;

        _audioSize = dataSize;
        if (_audioSize <= PCMDATA_CACHEMAXSIZE) {
            produceChunk();
        }
        else {
            _isStreaming = true;
            for (int i = 0; i < QUEUEBUFFER_NUM; i++) {
                produceChunk();
            }
        }

        ret = true;
    } while (false);

    return ret;
}

bool WAVReader::consumeChunk(AudioDataChunk& chunk)
{
    bool ret = false;
    _isDirty = true;

    _rwMutex.lock();
    if (_chnkQ.size() > 0) {
        chunk = _chnkQ.front();
        if (_isStreaming) {
            _chnkQ.pop();
        }
        else{
            // copy for future requests
            auto cpy = new (std::nothrow) unsigned char[chunk._dataSize];
            memcpy(cpy, chunk._data, chunk._dataSize);
            _chnkQ.front()._data = cpy;
        }
        ret = true;
    }
    _rwMutex.unlock();

    return ret;
}

void WAVReader::produceChunk()
{
    _rwMutex.lock();
    int chunkSize = _audioSize;

    do {
        if (!_isStreaming && _chnkQ.size() || _chnkQ.size() >= QUEUEBUFFER_NUM) {
            break;
        }

        if (_isStreaming) {
            chunkSize = std::min(CHUNK_SIZE_MAX, _audioSize - _bytesRead);
        }

        if (!chunkSize && !_chnkQ.size()) {
            auto alignment = _wfx.nChannels * _wfx.nBlockAlign;
            _bytesRead -= alignment;
            chunkSize = alignment;
        }

        UINT retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = new (std::nothrow) unsigned char[chunkSize];
        _streamer->ReadChunk(chunk._data, _bytesRead, chunkSize, &retSize);

        if (retSize <= 0) {
            delete[] chunk._data;
            chunk._data = nullptr;
            break;
        }

        _bytesRead += retSize;
        chunk._dataSize = retSize;
        chunk._seqNo = ((float)_bytesRead / _audioSize) * ((float)_audioSize / CHUNK_SIZE_MAX);
        chunk._endOfStream = (_bytesRead >= _audioSize);
        _chnkQ.push(chunk);
    } while (false);
    _rwMutex.unlock();
}

void WAVReader::seekTo(const float ratio)
{
    if (_isStreaming) {
        _bytesRead = ratio * _audioSize;

        if (!_bytesRead && !_isDirty && _chnkQ.size())  // already in 0.0 position
            return;

        flushChunks();

        switch (_wfx.wFormatTag)
        {
        case WAVE_FORMAT_PCM:
        case WAVE_FORMAT_ADPCM: {
            auto alignment = _wfx.nChannels * _wfx.nBlockAlign;
            _bytesRead = _bytesRead >= _audioSize ? (_audioSize - alignment) : _bytesRead - (_bytesRead % alignment);
        } break;

        default:
            break;
        }

        for (int i = 0; i < QUEUEBUFFER_NUM; i++) {
            produceChunk();
        }
    }
}

void WAVReader::flushChunks()
{
    _rwMutex.lock();
    while (!_chnkQ.empty()) {
        delete[] _chnkQ.front()._data;
        _chnkQ.pop();
    }
    _rwMutex.unlock();
}

#endif
