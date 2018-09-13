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

#include "audio/android/PcmAudioService.h"
#include "audio/android/AudioMixerController.h"

namespace cocos2d { namespace experimental {

static std::vector<char> __silenceData;

#define AUDIO_PLAYER_BUFFER_COUNT (2)

class SLPcmAudioPlayerCallbackProxy
{
public:
    static void samplePlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
    {
        PcmAudioService *thiz = reinterpret_cast<PcmAudioService *>(context);
        thiz->bqFetchBufferCallback(bq);
    }
};

PcmAudioService::PcmAudioService(SLEngineItf engineItf, SLObjectItf outputMixObject)
        : _engineItf(engineItf), _outputMixObj(outputMixObject), _playObj(nullptr),
          _playItf(nullptr), _volumeItf(nullptr), _bufferQueueItf(nullptr), _numChannels(-1),
          _sampleRate(-1), _bufferSizeInBytes(0), _controller(nullptr), _isInitialised(false)
{
}

PcmAudioService::~PcmAudioService()
{
    ALOGV("PcmAudioServicee() (%p), before destroy play object", this);
    SL_DESTROY_OBJ(_playObj);
    ALOGV("PcmAudioServicee() end");
}

bool PcmAudioService::enqueue()
{
    if (_controller->hasPlayingTacks())
    {
        if (_controller->isPaused())
        {
            SLresult r = (*_bufferQueueItf)->Enqueue(_bufferQueueItf, __silenceData.data(), __silenceData.size());
            SL_RETURN_VAL_IF_FAILED(r, false, "enqueue silent data failed!");
        }
        else
        {
            _controller->mixOneFrame();

            auto current = _controller->current();
            ALOG_ASSERT(current != nullptr, "current buffer is nullptr ...");
            SLresult r = (*_bufferQueueItf)->Enqueue(_bufferQueueItf, current->buf, current->size);
            SL_RETURN_VAL_IF_FAILED(r, false, "enqueue failed!");
        }
    }
    else
    {
        SLresult r = (*_bufferQueueItf)->Enqueue(_bufferQueueItf, __silenceData.data(), __silenceData.size());
        SL_RETURN_VAL_IF_FAILED(r, false, "enqueue silent data failed!");
    }

    return true;
}

void PcmAudioService::bqFetchBufferCallback(SLAndroidSimpleBufferQueueItf bq)
{
    // FIXME: PcmAudioService instance may be destroyed, we need to find a way to wait...
    // It's in sub thread
    enqueue();
}

bool PcmAudioService::init(AudioMixerController* controller, int numChannels, int sampleRate, int bufferSizeInBytes)
{
    _controller = controller;
    _numChannels = numChannels;
    _sampleRate = sampleRate;
    _bufferSizeInBytes = bufferSizeInBytes;

    SLuint32 channelMask = SL_SPEAKER_FRONT_CENTER;

    if (numChannels > 1)
    {
        channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    }

    SLDataFormat_PCM formatPcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32) numChannels,
            (SLuint32) sampleRate * 1000,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            channelMask,
            SL_BYTEORDER_LITTLEENDIAN
    };

    SLDataLocator_AndroidSimpleBufferQueue locBufQueue = {
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,
            AUDIO_PLAYER_BUFFER_COUNT
    };
    SLDataSource source = {&locBufQueue, &formatPcm};

    SLDataLocator_OutputMix locOutmix = {
            SL_DATALOCATOR_OUTPUTMIX,
            _outputMixObj
    };
    SLDataSink sink = {&locOutmix, nullptr};

    const SLInterfaceID ids[] = {
            SL_IID_PLAY,
            SL_IID_VOLUME,
            SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
    };

    const SLboolean req[] = {
            SL_BOOLEAN_TRUE,
            SL_BOOLEAN_TRUE,
            SL_BOOLEAN_TRUE,
    };

    SLresult r;

    r = (*_engineItf)->CreateAudioPlayer(_engineItf, &_playObj, &source, &sink,
                                         sizeof(ids) / sizeof(ids[0]), ids, req);
    SL_RETURN_VAL_IF_FAILED(r, false, "CreateAudioPlayer failed");

    r = (*_playObj)->Realize(_playObj, SL_BOOLEAN_FALSE);
    SL_RETURN_VAL_IF_FAILED(r, false, "Realize failed");

    r = (*_playObj)->GetInterface(_playObj, SL_IID_PLAY, &_playItf);
    SL_RETURN_VAL_IF_FAILED(r, false, "GetInterface SL_IID_PLAY failed");

    r = (*_playObj)->GetInterface(_playObj, SL_IID_VOLUME, &_volumeItf);
    SL_RETURN_VAL_IF_FAILED(r, false, "GetInterface SL_IID_VOLUME failed");

    r = (*_playObj)->GetInterface(_playObj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &_bufferQueueItf);
    SL_RETURN_VAL_IF_FAILED(r, false, "GetInterface SL_IID_ANDROIDSIMPLEBUFFERQUEUE failed");

    r = (*_bufferQueueItf)->RegisterCallback(_bufferQueueItf,
                                             SLPcmAudioPlayerCallbackProxy::samplePlayerCallback,
                                             this);
    SL_RETURN_VAL_IF_FAILED(r, false, "_bufferQueueItf RegisterCallback failed");

    if (__silenceData.empty())
    {
        __silenceData.resize(_numChannels * _bufferSizeInBytes, 0x00);
    }

    r = (*_bufferQueueItf)->Enqueue(_bufferQueueItf, __silenceData.data(), __silenceData.size());
    SL_RETURN_VAL_IF_FAILED(r, false, "_bufferQueueItf Enqueue failed");

    r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PLAYING);
    SL_RETURN_VAL_IF_FAILED(r, false, "SetPlayState failed");

    _isInitialised = true;
    return true;
}

void PcmAudioService::pause()
{
    if (_isInitialised)
    {
        SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PAUSED);
        SL_RETURN_IF_FAILED(r, "PcmAudioService::pause failed");
    }
}

void PcmAudioService::resume()
{
    if (_isInitialised)
    {
        SLresult r = (*_playItf)->SetPlayState(_playItf, SL_PLAYSTATE_PLAYING);
        SL_RETURN_IF_FAILED(r, "PcmAudioService::resume failed");
    }
}

}} // namespace cocos2d { namespace experimental {
