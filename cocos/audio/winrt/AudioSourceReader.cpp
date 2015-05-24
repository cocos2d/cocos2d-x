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
        delete[] _chnkQ.front()._data;
        _chnkQ.pop();
    }
    _rwMutex.unlock();
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
            if (cpy) {
                memcpy(cpy, chunk._data, chunk._dataSize);
                _chnkQ.front()._data = cpy;
            }
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

        if (!chunkSize) {
            break;
        }

        UINT retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = new (std::nothrow) unsigned char[chunkSize];

        if (!chunk._data) {
            break;
        }

        _streamer->ReadChunk(chunk._data, _bytesRead, chunkSize, &retSize);
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
        auto newPos = ratio * _audioSize;

        if (!newPos && !_isDirty && _chnkQ.size())  // already in 0.0 position
            return;

        _bytesRead = newPos;
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


// MP3Reader
MP3Reader::MP3Reader() :
_mappedWavFile("")
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

        if (FAILED(hr = MFCreateSourceReaderFromURL(std::wstring(_filePath.begin(), _filePath.end()).c_str(), NULL, &pReader))) {
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

        memcpy(&_wfx, pWav, sizeof(WAVEFORMATEX));
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
        else{
            // copy for future requests
            auto cpy = new (std::nothrow) unsigned char[chunk._dataSize];
            if (cpy) {
                memcpy(cpy, chunk._data, chunk._dataSize);
                _chnkQ.front()._data = cpy;
            }
        }
        ret = true;
    }
    _rwMutex.unlock();

    return ret;
}

void MP3Reader::produceChunk()
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

        if (!chunkSize) {
            break;
        }

        UINT retSize = 0;
        AudioDataChunk chunk = { 0 };
        chunk._data = new (std::nothrow) unsigned char[chunkSize];

        if (!chunk._data) {
            break;
        }

        readFromMappedWavFile(chunk._data, _bytesRead, chunkSize, &retSize);
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
        size_t bytesProcessed = 0;
        std::vector<BYTE> buffer;
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

            if (_audioSize + cbSize > PCMDATA_CACHEMAXSIZE) {

                if (!_isStreaming) {
                    _isStreaming = true;
                    if (!createMappedWavFile()) {
                        break;
                    }
                    chunkify(buffer);
                    appendToMappedWavFile(buffer);
                    buffer.clear();
                }

                buffer.resize(cbSize);
                memcpy(buffer.data(), pAudioData, cbSize);
                appendToMappedWavFile(buffer);
                buffer.clear();
            }
            else {
                buffer.resize(_audioSize + cbSize);
                memcpy(&buffer[_audioSize], pAudioData, cbSize);
            }

            _audioSize += cbSize;
            hr = pBuffer->Unlock();
            pAudioData = NULL;
        }

        if (FAILED(hr)) {
            break;
        }

        chunkify(buffer);
    } while (false);

    return hr;
}

bool MP3Reader::createMappedWavFile()
{
    bool ret = true;
    auto folderPath = FileUtils::getInstance()->getWritablePath(); 
    _mappedWavFile = folderPath + computeHashForFile() + ".dat";
    std::string prevFile = UserDefault::getInstance()->getStringForKey(_filePath.c_str());

    if (prevFile == _mappedWavFile) {
        if (FileUtils::getInstance()->isFileExist(_mappedWavFile)) {
            _audioSize = FileUtils::getInstance()->getFileSize(_mappedWavFile);
            ret = false;
        }
    }
    else {
        if (FileUtils::getInstance()->isFileExist(prevFile)) {
            FileUtils::getInstance()->removeFile(prevFile);
        }
    }

    UserDefault::getInstance()->setStringForKey(_filePath.c_str(), _mappedWavFile);
    return ret;
}

void MP3Reader::chunkify(std::vector<BYTE> &buffer)
{
    _rwMutex.lock();
    size_t offset = 0;

    while (offset < buffer.size() && _chnkQ.size() < QUEUEBUFFER_NUM)
    {
        AudioDataChunk chunk = { 0 };
        int chunkSize = !_isStreaming ? buffer.size() : std::min(CHUNK_SIZE_MAX, buffer.size() - _bytesRead);
        chunk._data = new (std::nothrow) unsigned char[chunkSize];

        if (!chunk._data) {
            break;
        }

        _bytesRead += chunkSize;
        chunk._dataSize = chunkSize;
        memcpy(chunk._data, &buffer[offset], chunkSize);
        chunk._endOfStream = (!_isStreaming && _bytesRead >= _audioSize);
        chunk._seqNo = ((float)_bytesRead / _audioSize) * ((float)_audioSize / CHUNK_SIZE_MAX);
        _chnkQ.push(chunk);
        offset += chunkSize;
    }
    _rwMutex.unlock();
}

bool MP3Reader::appendToMappedWavFile(std::vector<BYTE> &buffer)
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

        ret = (TRUE == WriteFile(file.Get(), buffer.data(), buffer.size(), nullptr, nullptr));
    } while (false);
    _rwMutex.unlock();

    return ret;
}

void MP3Reader::readFromMappedWavFile(BYTE *data, size_t offset, int size, UINT *pRetSize)
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

        ReadFile(file.Get(), data, size, (LPDWORD)pRetSize, nullptr);
    } while (false);
}

std::string MP3Reader::computeHashForFile()
{
    std::string ret = _filePath;
    int pos = std::string::npos;
    pos = ret.find_last_of('/');

    if (pos != std::string::npos) {
        ret = ret.substr(pos);
    }

    pos = ret.find_last_of('.');

    if (pos != std::string::npos) {
        ret = ret.substr(0, pos);
    }

    auto file = openFile(_filePath);
    
    if (file.Get() != INVALID_HANDLE_VALUE) {
        FILE_BASIC_INFO  fInfo = { 0 };
        if (GetFileInformationByHandleEx(file.Get(), FileBasicInfo, &fInfo, sizeof(FILE_BASIC_INFO))) {
            std::stringstream ss;
            ss << ret << "_";
            ss << fInfo.CreationTime.QuadPart;
            ss << fInfo.ChangeTime.QuadPart;
            ret = ss.str();
        }
    }
    
    return ret;
}

Wrappers::FileHandle MP3Reader::openFile(const std::string& path, bool append)
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
    return Microsoft::WRL::Wrappers::FileHandle(CreateFile2(std::wstring(path.begin(), path.end()).c_str(), access, FILE_SHARE_READ, creation, &extParams));
}

#endif
