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

#include "audio/winrt/AudioCachePlayer.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr)) {
        // Set a breakpoint on this line to catch XAudio2 API errors.
        throw Platform::Exception::CreateException(hr);
    }
}


// AudioCache
AudioCache::AudioCache()
    : _isReady(false)
    , _retry(false)
    , _fileFullPath("")
    , _srcReader(nullptr)
    , _fileFormat(FileFormat::UNKNOWN)
{
    _callbacks.clear();
    memset(&_audInfo, 0, sizeof(AudioInfo));
}

AudioCache::~AudioCache()
{
    _callbacks.clear();

    if (nullptr != _srcReader) {
        delete _srcReader;
        _srcReader = nullptr;
    }
}

void AudioCache::readDataTask()
{
    if (_isReady) {
        return;
    }

    if (nullptr != _srcReader) {
        delete _srcReader;
        _srcReader = nullptr;
    }

    switch (_fileFormat)
    {
    case FileFormat::WAV:
        _srcReader = new (std::nothrow) WAVReader();
        break;

    case FileFormat::OGG:
        _srcReader = new (std::nothrow) OGGReader();
        break;

    case FileFormat::MP3:
        _srcReader = new (std::nothrow) MP3Reader();

        break;

    case FileFormat::UNKNOWN:
    default:
        break;
    }

    if (_srcReader && _srcReader->initialize(_fileFullPath)) {
        _audInfo._totalAudioBytes = _srcReader->getTotalAudioBytes();
        _audInfo._wfx = _srcReader->getWaveFormatInfo();
        _isReady = true;
        _retry = false;
        invokePlayCallbacks();
    }

    if (!_isReady) {
        _retry = true;
        log("Failed to read input file: %s.\n", _fileFullPath.c_str());
    }

    invokeLoadCallbacks();
}

void AudioCache::addPlayCallback(const std::function<void()> &callback)
{
    _cbMutex.lock();
    if (_isReady) {
        callback();
    }
    else {
        _callbacks.push_back(callback);
    }
    _cbMutex.unlock();

    if (_retry) {
        readDataTask();
    }
}

void AudioCache::addLoadCallback(const std::function<void(bool)> &callback)
{
    if (_isReady) {
        callback(true);
    }
    else {
        _loadCallbacks.push_back(callback);
    }

    if (_retry) {
        readDataTask();
    }
}

void AudioCache::invokePlayCallbacks()
{
    _cbMutex.lock();
    auto cnt = _callbacks.size();
    for (size_t ind = 0; ind < cnt; ind++)
    {
        _callbacks[ind]();
    }
    _callbacks.clear();
    _cbMutex.unlock();
}

void AudioCache::invokeLoadCallbacks()
{
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread([&](){
        auto cnt = _loadCallbacks.size();
        for (size_t ind = 0; ind < cnt; ind++)
        {
            _loadCallbacks[ind](_isReady);
        }
        _loadCallbacks.clear();
    });
}

bool AudioCache::getChunk(AudioDataChunk& chunk)
{
    bool ret = false;

    if (nullptr != _srcReader) {
        ret = _srcReader->consumeChunk(chunk);
    }

    return ret;
}

void AudioCache::doBuffering()
{
    if (isStreamingSource()){
        _srcReader->produceChunk();
    }
}

bool AudioCache::isStreamingSource()
{
    if (nullptr != _srcReader) {
        return _srcReader->isStreamingSource();
    }

    return false;
}

void AudioCache::seek(const float ratio)
{
    if (nullptr != _srcReader){
        _srcReader->seekTo(ratio);
    }
}


// AudioPlayer
AudioPlayer::AudioPlayer()
    : _loop(false)
    , _ready(false)
    , _current(0.0)
    , _volume(0.0)
    , _duration(0.0)
    , _cache(nullptr)
    , _totalSamples(0)
    , _samplesOffset(0)
    , _criticalError(false)
    , _isStreaming(false)
    , _finishCallback(nullptr)
    , _xaMasterVoice(nullptr)
    , _xaSourceVoice(nullptr)
    , _state(AudioPlayerState::INITIALIZING)
{
    init();
}

AudioPlayer::~AudioPlayer()
{
    free();
}

void AudioPlayer::stop()
{
    _stop();
}

void AudioPlayer::pause()
{
    _stop(true);
}

bool AudioPlayer::update()
{
    if (_criticalError){
        free();
        init();
    }

    if (_cache != nullptr) {
        _cache->doBuffering();
    }

    //log("bufferQueued: %d, _current: %f", _cachedBufferQ.size(), _current);
    return _criticalError;
}

void AudioPlayer::resume()
{
    _play(true);
}

bool AudioPlayer::isInError()
{
    return _criticalError;
}

float AudioPlayer::getDuration()
{
    if (nullptr == _cache) {
        return _duration;
    }

    auto fmt = _cache->_audInfo._wfx;

    if (!fmt.nChannels) {
        return _duration;
    }

    if ((int)_duration <= 0)
    {
        switch (fmt.wFormatTag)
        {
        case WAVE_FORMAT_PCM:
        case WAVE_FORMAT_ADPCM:
            _duration = (float(_cache->_audInfo._totalAudioBytes / ((fmt.wBitsPerSample / 8) * fmt.nChannels)) / fmt.nSamplesPerSec) * 1000;
            _totalSamples = fmt.nSamplesPerSec * _duration / 1000;
            break;

        default:
            break;
        }
    }

    return _duration;
}

float AudioPlayer::getCurrentTime()
{
    _stMutex.lock();
    auto samplesPlayed = getSourceVoiceState().SamplesPlayed;
    //log("_samplesOffset: %lu, samplesPlayed: %lu, _current: %f", (UINT32)_samplesOffset, (UINT32)samplesPlayed, _current);
    _current += ((samplesPlayed - _samplesOffset) / (float)_totalSamples) * _duration;
    _current = _current > _duration ? 0.0 : _current;
    _samplesOffset = samplesPlayed;
    _stMutex.unlock();
    return _current;
}

bool AudioPlayer::setTime(float time)
{
    bool ret = true;
    _stop();

    if (!_isStreaming) {
        auto fmt = _cache->_audInfo._wfx;
        int seek = (time / _duration) * _totalSamples;
        seek -= (seek % (fmt.nChannels * fmt.nBlockAlign));

        _xaBuffer.LoopCount = 0;
        _xaBuffer.PlayBegin = seek;
        _xaBuffer.PlayLength = _totalSamples - seek;

        if (_xaBuffer.PlayBegin >= _totalSamples) {
            _xaBuffer.PlayBegin = _totalSamples - (fmt.nChannels * fmt.nBlockAlign);
            _xaBuffer.PlayLength = (fmt.nChannels * fmt.nBlockAlign);
        }
    }

    _stMutex.lock();
    _samplesOffset = getSourceVoiceState().SamplesPlayed;
    _current = time;
    _stMutex.unlock();
    _play();
    return ret;
}

void AudioPlayer::setVolume(float volume)
{
    if (_xaMasterVoice != nullptr){
        if (FAILED(_xaMasterVoice->SetVolume(volume))) {
            error();
        }
        else {
            _volume = volume;
        }
    }
}

bool AudioPlayer::play2d(AudioCache* cache)
{
    bool ret = false;
    HRESULT hr = S_OK;

    if (cache != nullptr)
    {
        _cache = cache;
        if (nullptr == _xaSourceVoice && _ready)  {

            XAUDIO2_SEND_DESCRIPTOR descriptors[1];
            descriptors[0].pOutputVoice = _xaMasterVoice;
            descriptors[0].Flags = 0;
            XAUDIO2_VOICE_SENDS sends = { 0 };
            sends.SendCount = 1;
            sends.pSends = descriptors;
            hr = _xaEngine->CreateSourceVoice(&_xaSourceVoice, &cache->_audInfo._wfx, 0, 1.0, this, &sends);
        }

        if (SUCCEEDED(hr)) {
            _isStreaming = _cache->isStreamingSource();
            _duration = getDuration();
            ret = _play();
        }
        else {
            error();
        }
    }

    return ret;
}

void AudioPlayer::init()
{
    do {
        memset(&_xaBuffer, 0, sizeof(_xaBuffer));
        if (FAILED(XAudio2Create(_xaEngine.ReleaseAndGetAddressOf()))) {
            error();
            break;
        }

#if defined(_DEBUG)
        XAUDIO2_DEBUG_CONFIGURATION debugConfig = { 0 };
        debugConfig.BreakMask = XAUDIO2_LOG_ERRORS;
        debugConfig.TraceMask = XAUDIO2_LOG_ERRORS;
        _xaEngine->SetDebugConfiguration(&debugConfig);
#endif

        _xaEngine->RegisterForCallbacks(this);
        if (FAILED(_xaEngine->CreateMasteringVoice(&_xaMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameMedia))) {
            error();
            break;
        }

        _ready = true;
        _state = AudioPlayerState::READY;
    } while (false);
}

void AudioPlayer::free()
{
    _ready = false;
    _stop();
    memset(&_xaBuffer, 0, sizeof(_xaBuffer));

    if (_xaEngine) {
        _xaEngine->UnregisterForCallbacks(this);
        _xaEngine->StopEngine();
    }

    if (_xaSourceVoice != nullptr) {
        _xaSourceVoice->DestroyVoice();
        _xaSourceVoice = nullptr;
    }

    if (_xaMasterVoice != nullptr) {
        _xaMasterVoice->DestroyVoice();
        _xaMasterVoice = nullptr;
    }

    while (!_cachedBufferQ.empty()) {
        popBuffer();
    }
}

bool AudioPlayer::_play(bool resume)
{
    do {
        if (!resume) {
            _cache->seek(_current / _duration);
            submitBuffers();
        }

        if (_state == AudioPlayerState::PAUSED && !resume || nullptr == _xaSourceVoice) break;

        if (FAILED(_xaMasterVoice->SetVolume(_volume)) || FAILED(_xaSourceVoice->Start())) {
            error();
        }
        else {
            _state = AudioPlayerState::PLAYING;
        }
    } while (false);

    return !_criticalError;
}

void AudioPlayer::_stop(bool pause)
{
    if (_xaSourceVoice != nullptr) {

        if (FAILED(_xaSourceVoice->Stop())) {
            error();
        }
        else {
            if (!pause) {
                _xaSourceVoice->FlushSourceBuffers();
                if (_state != AudioPlayerState::PAUSED) _state = AudioPlayerState::STOPPED;
            }
            else {
                _state = AudioPlayerState::PAUSED;
            }
        }
    }
}

void AudioPlayer::error()
{
    _criticalError = true;
    _ready = false;
    _state = AudioPlayerState::ERRORED;
    CCLOG("Audio system encountered error.");
}

void AudioPlayer::popBuffer()
{
    _bqMutex.lock();
    if (!_cachedBufferQ.empty()) {
        _cachedBufferQ.pop();
    }
    _bqMutex.unlock();
}

bool AudioPlayer::submitBuffers()
{
    bool  ret = false;

    _bqMutex.lock();
    do {
        if (nullptr == _xaSourceVoice) break;
        if (!_cachedBufferQ.size() || (_isStreaming && _cachedBufferQ.size() < QUEUEBUFFER_NUM)) {
            AudioDataChunk chunk;
            if (_cache->getChunk(chunk) && chunk._dataSize) {
                _xaBuffer.AudioBytes = static_cast<UINT32>(chunk._dataSize);
                _xaBuffer.pAudioData = chunk._data->data();
                _xaBuffer.Flags = chunk._endOfStream ? XAUDIO2_END_OF_STREAM : 0;
                _cachedBufferQ.push(chunk);
                ret = SUCCEEDED(_xaSourceVoice->SubmitSourceBuffer(&_xaBuffer));
                if (!_isStreaming) break;
            }
            else {
                break;
            }
        }
        else if (!_isStreaming) {
            ret = SUCCEEDED(_xaSourceVoice->SubmitSourceBuffer(&_xaBuffer));
            break;
        }
        else {
            break;
        }
    } while (ret);
    _bqMutex.unlock();

    return ret;
}

void AudioPlayer::updateState()
{
    if (!_isStreaming) {
        _stMutex.lock();
        _samplesOffset = getSourceVoiceState().SamplesPlayed;
        _stMutex.unlock();
    }
    else {
        if (_cachedBufferQ.size() > getSourceVoiceState(true).BuffersQueued) {
            popBuffer();
        }
    }
}

void AudioPlayer::onBufferRunOut()
{
    _stMutex.lock();
    _samplesOffset = 0;
    _current = 0.0;
    _xaBuffer.PlayBegin = _xaBuffer.PlayLength = 0;
    _stMutex.unlock();

    if (!_loop) {
        _stop();
        //invokeFinishCallback();
    }
    else {
        _play();
    }
}

void AudioPlayer::invokeFinishCallback()
{
    if (_finishCallback) {
        _finishCallback(0, "");
    }
}

XAUDIO2_VOICE_STATE AudioPlayer::getSourceVoiceState(bool fast)
{
    XAUDIO2_VOICE_STATE state;
    memset(&state, 0, sizeof(XAUDIO2_VOICE_STATE));

    if (_xaSourceVoice != nullptr) {
        _xaSourceVoice->GetState(&state, fast ? XAUDIO2_VOICE_NOSAMPLESPLAYED : 0);
    }

    return state;
}

// IXAudio2EngineCallback
void AudioPlayer::OnProcessingPassStart()
{
}

void AudioPlayer::OnProcessingPassEnd()
{
}

void AudioPlayer::OnCriticalError(HRESULT err)
{
    UNREFERENCED_PARAMETER(err);
    if (_ready) {
        error();
    }
}

// IXAudio2VoiceCallback
void AudioPlayer::OnVoiceProcessingPassStart(UINT32 uBytesRequired)
{
    if (_ready && uBytesRequired && _isStreaming){
        submitBuffers();
    }
}

void AudioPlayer::OnVoiceProcessingPassEnd()
{
}

void AudioPlayer::OnStreamEnd()
{
    if (_ready) {
        onBufferRunOut();
    }
}

void AudioPlayer::OnBufferStart(void* pBufferContext)
{
    UNREFERENCED_PARAMETER(pBufferContext);
}

void AudioPlayer::OnBufferEnd(void* pBufferContext)
{
    UNREFERENCED_PARAMETER(pBufferContext);
    if (_ready) {
        updateState();
    }
}

void AudioPlayer::OnLoopEnd(void* pBufferContext)
{
    UNREFERENCED_PARAMETER(pBufferContext);

    if (_ready && !_loop) {
        _stop();
    }
}

void AudioPlayer::OnVoiceError(void* pBufferContext, HRESULT err)
{
    UNREFERENCED_PARAMETER(pBufferContext);
    UNREFERENCED_PARAMETER(err);
    if (_ready) {
        error();
    }
}

#endif
