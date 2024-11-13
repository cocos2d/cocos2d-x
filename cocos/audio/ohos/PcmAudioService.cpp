/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#define LOG_TAG "PcmAudioService"

#include "Macros.h"
#include "PcmAudioService.h"
#include "AudioMixerController.h"
#include "utils/Compat.h"

namespace cocos2d {


static std::vector<char> __silenceData;//NOLINT(bugprone-reserved-identifier, readability-identifier-naming)

PcmAudioService::PcmAudioService()
: _controller(nullptr) {
}

PcmAudioService::~PcmAudioService() {
    ALOGV("PcmAudioService() (%p), before destroy play object", this);
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Stop(_audioRenderer);
        OH_AudioRenderer_Release(_audioRenderer);
    }

    if (_builder != nullptr) {
        OH_AudioStreamBuilder_Destroy(_builder);
    }
      ALOGV("PcmAudioService() end");
}

int32_t PcmAudioService::AudioRendererOnWriteData(OH_AudioRenderer* renderer,
    void* userData,
    void* buffer,
    int32_t bufferLen)
{
    auto *thiz = reinterpret_cast<PcmAudioService *>(userData);
    if (bufferLen != thiz->_bufferSizeInBytes) {
        __silenceData.resize(bufferLen, 0x00);
        thiz->_bufferSizeInBytes = bufferLen;
        thiz->_controller->updateBufferSize(thiz->_bufferSizeInBytes);
     }

    if (thiz->_controller->hasPlayingTacks()) {
        if (thiz->_controller->isPaused()) {
            memcpy(buffer, __silenceData.data(), bufferLen);
        } else {
         
            thiz->_controller->mixOneFrame();
            auto *current = thiz->_controller->current();
            ALOG_ASSERT(current != nullptr, "current buffer is nullptr ...");
            memcpy(buffer, current->buf, current->size < bufferLen ? current->size : bufferLen);
        }
    } else {
        memcpy(buffer, __silenceData.data(), bufferLen);
    }

    return 0;
}

int32_t PcmAudioService::AudioRendererOnInterrupt(OH_AudioRenderer* renderer,
    void* userData,
    OH_AudioInterrupt_ForceType type,
    OH_AudioInterrupt_Hint hint)
{
    auto *thiz = reinterpret_cast<PcmAudioService *>(userData);
    if (thiz->_audioRenderer != nullptr) {
        if (hint == AUDIOSTREAM_INTERRUPT_HINT_RESUME) {
            OH_AudioRenderer_Start(thiz->_audioRenderer);
        } else if (hint == AUDIOSTREAM_INTERRUPT_HINT_PAUSE) {
            OH_AudioRenderer_Pause(thiz->_audioRenderer);
        }
    }
    return 0;
}

bool PcmAudioService::init(AudioMixerController *controller, int numChannels, int sampleRate, int *bufferSizeInBytes) {
    _controller = controller;

    OH_AudioStream_Result ret;
    OH_AudioStream_Type type = AUDIOSTREAM_TYPE_RENDERER;
    ret = OH_AudioStreamBuilder_Create(&_builder, type);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    OH_AudioStreamBuilder_SetSamplingRate(_builder, sampleRate);
    OH_AudioStreamBuilder_SetChannelCount(_builder, numChannels);
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
    _bufferSizeInBytes = buffer_size * numChannels * 2;
    *bufferSizeInBytes = buffer_size;

    if (__silenceData.empty()) {
        __silenceData.resize(_bufferSizeInBytes, 0x00);
    }

    ret = OH_AudioRenderer_Start(_audioRenderer);
    if (ret != AUDIOSTREAM_SUCCESS) {
        return false;
    }

    return true;
}

void PcmAudioService::pause() {
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Pause(_audioRenderer);
    }
}

void PcmAudioService::resume() {
    if (_audioRenderer != nullptr) {
        OH_AudioRenderer_Start(_audioRenderer);
    }
}

} 
