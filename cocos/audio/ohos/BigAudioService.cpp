#include "BigAudioService.h"

namespace cocos2d { namespace experimental {

BigAudioService::BigAudioService(): _audioRenderer(nullptr), _builder(nullptr)
{
}

BigAudioService::~BigAudioService() {
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Release(_audioRenderer);
        _audioRenderer = nullptr;
    }

    if (_builder != nullptr) {
        OH_AudioStreamBuilder_Destroy(_builder);
        _builder = nullptr;
    }
}

int32_t BigAudioService::AudioRendererOnWriteData(OH_AudioRenderer* renderer,
    void* userData,
    void* buffer,
    int32_t bufferLen)
{
    auto *thiz = reinterpret_cast<BigAudioService *>(userData);
    if (thiz->getNextTrackBuff(buffer, bufferLen)) {
        return AUDIO_DATA_CALLBACK_RESULT_VALID;
    } else {
        return AUDIO_DATA_CALLBACK_RESULT_INVALID;
    }
}


int32_t BigAudioService::AudioRendererOnInterrupt(OH_AudioRenderer* renderer,
    void* userData,
    OH_AudioInterrupt_ForceType type,
    OH_AudioInterrupt_Hint hint)
{
    auto *thiz = reinterpret_cast<BigAudioService *>(userData);
    if (thiz->_audioRenderer != nullptr) {
        if (hint == AUDIOSTREAM_INTERRUPT_HINT_RESUME) {
            OH_AudioRenderer_Start(thiz->_audioRenderer);
        } else if (hint == AUDIOSTREAM_INTERRUPT_HINT_PAUSE) {
            OH_AudioRenderer_Pause(thiz->_audioRenderer);
        }
    }
    return 0;
}

bool BigAudioService::init(PcmData decResult) {

    _decResult = decResult;
    OH_AudioStream_Result ret;
    ret = OH_AudioStreamBuilder_Create(&_builder, AUDIOSTREAM_TYPE_RENDERER);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    OH_AudioStreamBuilder_SetSamplingRate(_builder, decResult.sampleRate);
    OH_AudioStreamBuilder_SetChannelCount(_builder, decResult.numChannels);
    OH_AudioStreamBuilder_SetLatencyMode(_builder, AUDIOSTREAM_LATENCY_MODE_FAST);
    OH_AudioStreamBuilder_SetRendererInfo(_builder, AUDIOSTREAM_USAGE_GAME);

    OH_AudioRenderer_Callbacks callbacks;
    callbacks.OH_AudioRenderer_OnWriteData = AudioRendererOnWriteData;
    callbacks.OH_AudioRenderer_OnInterruptEvent = AudioRendererOnInterrupt;
    callbacks.OH_AudioRenderer_OnError = nullptr;
    callbacks.OH_AudioRenderer_OnStreamEvent = nullptr;
    ret = OH_AudioStreamBuilder_SetRendererCallback(_builder, callbacks, this);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    ret = OH_AudioStreamBuilder_GenerateRenderer(_builder, &_audioRenderer);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    int32_t buffer_size;
    OH_AudioRenderer_GetFrameSizeInCallback(_audioRenderer, &buffer_size);
    _bufferSizeInBytes = buffer_size * decResult.numChannels * 2;
    
    ret = OH_AudioRenderer_Start(_audioRenderer);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    return true;
}

void BigAudioService::setTrack(Track *track) {
    _track = track;
}

bool BigAudioService::getNextTrackBuff(void * buffer, int32_t bufferLen) {
    if (_track == nullptr) {
        return false;
    }
    bool validData = false;
    bool need_destroy = false;
    Track::State state = _track->getState();
    if (state == Track::State::PLAYING) {
        std::lock_guard<std::mutex> lk(_track->_volumeDirtyMutex);
        if (_track->isVolumeDirty()) {
            OH_AudioRenderer_SetVolume(_audioRenderer, _track->getVolume());
            _track->setVolumeDirty(false);
        }
        if (_decResult.pcmBuffer->size() >= bufferLen) {
            int frameCount = _bufferSizeInBytes / _decResult.numChannels / 2;
            memcpy(buffer, _decResult.pcmBuffer->data() + _track->_nextFrame * _track->_frameSize, bufferLen);
            _track->_nextFrame += frameCount;
            validData = true;
        }
    } else if (state == Track::State::RESUMED) {
        _track->setState(Track::State::PLAYING);
    } else if (state == Track::State::STOPPED) {
        need_destroy = true;
    }
        
    if (_track->isPlayOver()) {
        if (_track->isLoop()) {
            _track->reset();
        } else {
            ALOGV("Play over ...");
            _track->setState(Track::State::OVER);
            need_destroy = true;
        }
    }
    
    if (need_destroy) {
        delete &_decResult.pcmBuffer;
        _track->onStateChanged(Track::State::DESTROYED);
    }
    
    return validData;
}

void BigAudioService::pause() {
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Pause(_audioRenderer);
    }
}

void BigAudioService::resume() {
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Flush(_audioRenderer);// clear pop sound
        OH_AudioRenderer_Start(_audioRenderer);
    }
}

}} // namespace cocos2d { namespace experimental
