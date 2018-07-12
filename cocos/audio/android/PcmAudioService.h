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

#pragma once

#include "audio/android/IAudioPlayer.h"
#include "audio/android/OpenSLHelper.h"
#include "audio/android/PcmData.h"

#include <mutex>
#include <condition_variable>

namespace cocos2d { namespace experimental {

class AudioMixerController;

class PcmAudioService
{
public:
    inline int getChannelCount() const
    { return _numChannels; };

    inline int getSampleRate() const
    { return _sampleRate; };

private:
    PcmAudioService(SLEngineItf engineItf, SLObjectItf outputMixObject);

    virtual ~PcmAudioService();

    bool init(AudioMixerController* controller, int numChannels, int sampleRate, int bufferSizeInBytes);

    bool enqueue();

    void bqFetchBufferCallback(SLAndroidSimpleBufferQueueItf bq);

    void pause();
    void resume();

private:
    SLEngineItf _engineItf;
    SLObjectItf _outputMixObj;

    SLObjectItf _playObj;
    SLPlayItf _playItf;
    SLVolumeItf _volumeItf;
    SLAndroidSimpleBufferQueueItf _bufferQueueItf;

    int _numChannels;
    int _sampleRate;
    int _bufferSizeInBytes;
    bool _isInitialised;

    AudioMixerController* _controller;

    friend class SLPcmAudioPlayerCallbackProxy;
    friend class AudioPlayerProvider;
};

}} // namespace cocos2d { namespace experimental {
