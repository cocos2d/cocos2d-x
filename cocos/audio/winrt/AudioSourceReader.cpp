/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "base/ccMacros.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCFileUtils.h"


#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#include "platform/winrt/CCWinRTUtils.h"
#include "audio/winrt/AudioSourceReader.h"

using namespace cocos2d;
using namespace cocos2d::experimental;
using namespace Microsoft::WRL;


// AudioFileReader
AudioSourceReader::AudioSourceReader() :
_isStreaming(false)
, _filePath("")
, _audioSize(0)
, _bytesRead(0)
, _isDirty(false)
{
    memset(&_wfx, 0, sizeof(_wfx));
}

AudioSourceReader::~AudioSourceReader()
{
    flushChunks();
}

void AudioSourceReader::flushChunks()
{
    _rwMutex.lock();
    while (!_chnkQ.empty()) {
        _chnkQ.pop();
    }
    _rwMutex.unlock();
}

void AudioSourceReader::seekTo(const float ratio)
{
    if (_isStreaming) {
        auto newPos = ratio * _audioSize;

        if (!newPos && !_isDirty && _chnkQ.size())  // already in 0.0 position
            return;

        _bytesRead = newPos;
        flushChunks();
        auto alignment = _wfx.nChannels * _wfx.nBlockAlign;
        _bytesRead = _bytesRead >= _audioSize ? (_audioSize - alignment) : _bytesRead - (_bytesRead % alignment);

        for (int i = 0; i < QUEUEBUFFER_NUM; i++) {
            produceChunk();
        }
    }
}

// WAVFileReader
WAVReader::WAVReader() :
_streamer(nullptr)
{
}

WAVReader::~WAVReader()
{
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

        _streamer = ref new MediaStreamer;

        _streamer->Initialize(StringUtf8ToWideChar(_filePath).c_str(), true);
        _wfx = _streamer->GetOutputWaveFormatEx();
        size_t dataSize = _streamer->GetMaxStreamLengthInBytes();

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
        ret = true;
    }
    _rwMutex.unlock();

    return ret;
}

void WAVReader::produceChunk()
{
    _rwMutex.lock();
    size_t chunkSize = _audioSize;

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

        if (!chunkSize) {
            break;
        }

        unsigned int retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = std::make_shared<PCMBuffer>(chunkSize);
        _streamer->ReadChunk(chunk._data->data(), static_cast<unsigned int>(_bytesRead), static_cast<unsigned int>(chunkSize), &retSize);
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
    AudioSourceReader::seekTo(ratio);
}


// MP3Reader
MP3Reader::MP3Reader() :
_mappedWavFile("")
, _largeFileSupport(true)
{
}

MP3Reader::~MP3Reader()
{
}

bool MP3Reader::initialize(const std::string& filePath)
{
    bool ret = false;
    _filePath = filePath;
    HRESULT hr = S_OK;
    MFStartup(MF_VERSION);

    do {
        ComPtr<IMFSourceReader> pReader;
        ComPtr<IMFMediaType> ppDecomprsdAudioType;

        if (FAILED(hr = MFCreateSourceReaderFromURL(StringUtf8ToWideChar(_filePath).c_str(), NULL, &pReader))) {
            break;
        }
        
        hr = configureSourceReader(pReader.Get(), &ppDecomprsdAudioType);

        if (FAILED(hr)) {
            break;
        }

        UINT32 cbFormat = 0;
        WAVEFORMATEX *pWav = nullptr;
        if (FAILED(hr = MFCreateWaveFormatExFromMFMediaType(ppDecomprsdAudioType.Get(), &pWav, &cbFormat))) {
            break;
        }

        CopyMemory(&_wfx, pWav, sizeof(WAVEFORMATEX));
        CoTaskMemFree(pWav);

        if (FAILED(hr = readAudioData(pReader.Get()))) {
            break;
        }

        ret = SUCCEEDED(hr);
    } while (false);

    MFShutdown();
    return ret;
}

bool MP3Reader::consumeChunk(AudioDataChunk& chunk)
{
    bool ret = false;
    _isDirty = true;

    _rwMutex.lock();
    if (_chnkQ.size() > 0) {
        chunk = _chnkQ.front();
        if (_isStreaming) {
            _chnkQ.pop();
        }
        ret = true;
    }
    _rwMutex.unlock();

    return ret;
}

void MP3Reader::produceChunk()
{
    _rwMutex.lock();
    size_t chunkSize = _audioSize;

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

        if (!chunkSize) {
            break;
        }

        UINT retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = std::make_shared<PCMBuffer>(chunkSize);
        readFromMappedWavFile(chunk._data->data(), _bytesRead, chunkSize, &retSize);
        _bytesRead += retSize;
        chunk._dataSize = retSize;
        chunk._seqNo = ((float)_bytesRead / _audioSize) * ((float)_audioSize / CHUNK_SIZE_MAX);
        chunk._endOfStream = (_bytesRead >= _audioSize);
        _chnkQ.push(chunk);
    } while (false);
    _rwMutex.unlock();
}

void MP3Reader::seekTo(const float ratio)
{
    AudioSourceReader::seekTo(ratio);
}

HRESULT MP3Reader::configureSourceReader(IMFSourceReader* pReader, IMFMediaType** ppDecomprsdAudioType)
{
    HRESULT hr = S_OK;

    do {
        ComPtr<IMFMediaType> pTmpMediaType;
        ComPtr<IMFMediaType> pRetMediaType;
        pReader->SetStreamSelection(MF_SOURCE_READER_ALL_STREAMS, FALSE);
        pReader->SetStreamSelection(MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE);

        if (FAILED(hr = MFCreateMediaType(&pTmpMediaType))) {
            break;
        }

        if (FAILED(hr = pTmpMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio))) {
            break;
        }

        if (FAILED(hr = pTmpMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM))) {
            break;
        }

        if (FAILED(hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, NULL, pTmpMediaType.Get()))) {
            break;
        }

        if (FAILED(hr = pReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pRetMediaType))) {
            break;
        }

        if (FAILED(hr = pReader->SetStreamSelection(MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE))) {
            break;
        }

        *ppDecomprsdAudioType = pRetMediaType.Get();
        (*ppDecomprsdAudioType)->AddRef();
    } while (false);

    return hr;
}

HRESULT MP3Reader::readAudioData(IMFSourceReader* pReader)
{
    HRESULT hr = S_OK;

    do {
        PCMBuffer buffer;

        if (createMappedCacheFile(_filePath, _mappedWavFile, ".dat")) {
            _isStreaming = _largeFileSupport;
            _audioSize = FileUtils::getInstance()->getFileSize(_mappedWavFile);
            if (!_largeFileSupport) {
                buffer.resize(_audioSize);
                readFromMappedWavFile(buffer.data(), 0, _audioSize, nullptr);
                chunkify(buffer);
            }
            break;
        }

        buffer.reserve(PCMDATA_CACHEMAXSIZE);

        while (SUCCEEDED(hr))
        {
            DWORD flags = 0;
            DWORD cbSize = 0;
            BYTE* pAudioData = nullptr;
            ComPtr<IMFSample> pSample;
            ComPtr<IMFMediaBuffer> pBuffer;

            if (FAILED(hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, NULL, &flags, NULL, &pSample))) {
                break;
            }

            if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
                break;
            }

            if (FAILED(hr = pSample->ConvertToContiguousBuffer(&pBuffer))) {
                break;
            }

            if (FAILED(hr = pBuffer->Lock(&pAudioData, NULL, &cbSize))) {
                break;
            }

            if (_largeFileSupport && _audioSize + cbSize > PCMDATA_CACHEMAXSIZE) {

                if (!_isStreaming) {
                    _isStreaming = true;
                    chunkify(buffer);
                    appendToMappedWavFile(buffer);
                    buffer.clear();
                }

                buffer.resize(cbSize);
                CopyMemory(buffer.data(), pAudioData, cbSize);
                appendToMappedWavFile(buffer);
                buffer.clear();
            }
            else {
                buffer.resize(_audioSize + cbSize);
                CopyMemory(&buffer[_audioSize], pAudioData, cbSize);
            }

            _audioSize += cbSize;
            hr = pBuffer->Unlock();
            pAudioData = nullptr;
        }

        if (FAILED(hr)) {
            break;
        }

        if (!_isStreaming) {
            chunkify(buffer);
            _audioSize > PCMDATA_CACHEMAXSIZE ?
                appendToMappedWavFile(buffer) :
            destroyMappedCacheFile(_filePath);
        }
    } while (false);

    return hr;
}

void MP3Reader::chunkify(PCMBuffer& buffer)
{
    _rwMutex.lock();
    size_t offset = 0;

    if (buffer.size() && _chnkQ.size() < QUEUEBUFFER_NUM)
    {
        AudioDataChunk chunk = { 0 };
        size_t chunkSize = buffer.size();
        chunk._data = std::make_shared<PCMBuffer>(buffer);
        _bytesRead += chunkSize;
        chunk._dataSize = chunkSize;
        chunk._endOfStream = (!_isStreaming && _bytesRead >= _audioSize);
        chunk._seqNo = ((float)_bytesRead / _audioSize) * ((float)_audioSize / CHUNK_SIZE_MAX);
        _chnkQ.push(chunk);
        offset += chunkSize;
    }
    _rwMutex.unlock();
}

bool MP3Reader::appendToMappedWavFile(PCMBuffer& buffer)
{
    bool ret = false;

    _rwMutex.lock();
    do {
        auto file = openFile(_mappedWavFile, true);

        if (file.Get() == INVALID_HANDLE_VALUE) {
            break;
        }

        LARGE_INTEGER li = { 0 };
        if (!SetFilePointerEx(file.Get(), li, nullptr, FILE_END)) {
            break;
        }

        ret = (TRUE == WriteFile(file.Get(), buffer.data(), static_cast<DWORD>(buffer.size()), nullptr, nullptr));
    } while (false);
    _rwMutex.unlock();

    return ret;
}

void MP3Reader::readFromMappedWavFile(BYTE *data, size_t offset, size_t size, UINT *pRetSize)
{
    do {
        auto file = openFile(_mappedWavFile);

        if (file.Get() == INVALID_HANDLE_VALUE) {
            break;
        }

        if (offset) {
            LARGE_INTEGER li = { 0 };
            li.QuadPart = offset;
            if (!SetFilePointerEx(file.Get(), li, nullptr, FILE_BEGIN)) {
                break;
            }
        }

        ReadFile(file.Get(), data, static_cast<DWORD>(size), (LPDWORD)pRetSize, nullptr);
    } while (false);
}

Wrappers::FileHandle MP3Reader::openFile(const std::string& filePath, bool append)
{
    CREATEFILE2_EXTENDED_PARAMETERS extParams = { 0 };
    extParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    extParams.dwFileFlags = FILE_FLAG_RANDOM_ACCESS;
    extParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
    extParams.dwSize = sizeof(extParams);
    extParams.hTemplateFile = nullptr;
    extParams.lpSecurityAttributes = nullptr;

    DWORD access = append ? GENERIC_WRITE : GENERIC_READ;
    DWORD creation = append ? OPEN_ALWAYS : OPEN_EXISTING;
    return Microsoft::WRL::Wrappers::FileHandle(CreateFile2(StringUtf8ToWideChar(filePath).c_str(), access, FILE_SHARE_READ, creation, &extParams));
}


// OGGReader
OGGReader::OGGReader()
{
}

OGGReader::~OGGReader()
{
    if (_vorbisFd) {
        ov_clear(_vorbisFd.get());
    }
}

bool OGGReader::initialize(const std::string& filePath)
{
    bool ret = false;
    _filePath = filePath;

    do {
        _vorbisFd = std::make_unique<OggVorbis_File>();
        if (ov_fopen(FileUtils::getInstance()->getSuitableFOpen(_filePath).c_str(), _vorbisFd.get())){
            break;
        }

        auto  vi = ov_info(_vorbisFd.get(), -1);

        if (!vi) {
            break;
        }

        auto totalFrames = ov_pcm_total(_vorbisFd.get(), -1);
        auto bytesPerFrame = vi->channels * 2;
        _audioSize = totalFrames * bytesPerFrame;

        _wfx.wFormatTag = WAVE_FORMAT_PCM;
        _wfx.nChannels = vi->channels;
        _wfx.nSamplesPerSec = vi->rate;
        _wfx.nAvgBytesPerSec = vi->rate * bytesPerFrame;
        _wfx.nBlockAlign = bytesPerFrame;
        _wfx.wBitsPerSample = (bytesPerFrame / vi->channels) * 8;
        _wfx.cbSize = 0;

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

bool OGGReader::consumeChunk(AudioDataChunk& chunk)
{
    bool ret = false;
    _isDirty = true;

    _rwMutex.lock();
    if (_chnkQ.size() > 0) {
        chunk = _chnkQ.front();
        if (_isStreaming) {
            _chnkQ.pop();
        }
        ret = true;
    }
    _rwMutex.unlock();

    return ret;
}

void OGGReader::produceChunk()
{
    _rwMutex.lock();
    size_t chunkSize = _audioSize;

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

        if (!chunkSize) {
            break;
        }

        int retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = std::make_shared<PCMBuffer>(chunkSize);
        
        auto newPos = (1.0f * _bytesRead / _audioSize) * ov_time_total(_vorbisFd.get(), -1);
        if (ov_time_seek(_vorbisFd.get(), newPos)){
            break;
        }

        do
        {
            long br = 0;
            int current_section = 0;
            if ((br = ov_read(_vorbisFd.get(), (char*)chunk._data->data() + retSize, static_cast<int>(chunkSize) - retSize, 0, 2, 1, &current_section)) == 0) {
                break;
            }
            retSize += br;
        } while (retSize < chunkSize);

        _bytesRead += retSize;
        chunk._dataSize = retSize;
        chunk._seqNo = ((float)_bytesRead / _audioSize) * ((float)_audioSize / CHUNK_SIZE_MAX);
        chunk._endOfStream = (_bytesRead >= _audioSize);
        _chnkQ.push(chunk);
    } while (false);
    _rwMutex.unlock();
}

void OGGReader::seekTo(const float ratio)
{
    AudioSourceReader::seekTo(ratio);
}

#endif
