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

#define LOG_TAG "AudioPlayer"

#include "audio/apple/av/AudioPlayer.h"

#import <AVFoundation/AVFoundation.h>
#include <cmath>
#include <thread>

#include "audio/apple/av/AudioCache.h"

#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

using namespace cocos2d;

namespace {
unsigned int __idIndex = 0;
}

AudioPlayer::AudioPlayer()
: _audioCache(nullptr)
, _volume(1.0f)
, _loop(false)
, _finishCallbak(nullptr)
, _isDestroyed(false)
, _removeByAudioEngine(false)
, _ready(false)
, _paused(false)
, _node(nil)
, _nodeIndex(-1)
, _file(nil)
, _sliceBuffer(nil)
, _schedule(std::make_shared<ScheduleState>())
, _startTime(0.0f)
, _currTime(0.0f)
, _id(++__idIndex)
{
}

AudioPlayer::~AudioPlayer()
{
    ALOGVV("~AudioPlayer() (%p), id=%u", this, _id);
    destroy();

    [_sliceBuffer release];
    _sliceBuffer = nil;
    [_file release];
    _file = nil;
}

void AudioPlayer::destroy()
{
    if (_isDestroyed)
        return;

    ALOGVV("AudioPlayer::destroy begin, id=%u", _id);

    _isDestroyed = true;

    if (_audioCache != nullptr && _audioCache->_state != AudioCache::State::INITIAL)
    {
        while (!_audioCache->_isLoadingFinished)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    // Wait for play2d to be finished.
    _play2dMutex.lock();
    _play2dMutex.unlock();

    ++_schedule->generation;
    _schedule->passes = 0;

    if (_node != nil)
    {
        [_node stop];
    }

    _removeByAudioEngine = true;
    _ready = false;
    ALOGVV("AudioPlayer::destroy end, id=%u", _id);
}

void AudioPlayer::setCache(AudioCache* cache)
{
    _audioCache = cache;
}

bool AudioPlayer::play2d()
{
    _play2dMutex.lock();
    ALOGVV("AudioPlayer::play2d, id=%u", _id);

    bool ret = false;
    do
    {
        if (_audioCache->_state != AudioCache::State::READY)
        {
            ALOGE("The audio cache isn't ready for play!");
            break;
        }

        if (_isDestroyed)
            break;

        if (_audioCache->_streaming && _file == nil)
        {
            NSError* error = nil;
            NSURL* url = [NSURL fileURLWithPath:[NSString stringWithUTF8String:_audioCache->_fileFullPath.c_str()]];
            _file = [[AVAudioFile alloc] initForReading:url error:&error];
            if (_file == nil)
            {
                ALOGE("Failed to open %s, %s", _audioCache->_fileFullPath.c_str(),
                      [[error localizedDescription] UTF8String]);
                break;
            }
        }

        _node.volume = _volume;
        _startTime = 0.0f;
        _currTime = 0.0f;

        schedulePass(0, true);
        if (_audioCache->_streaming && _loop)
        {
            schedulePass(0, true);
        }

        if (_schedule->passes.load() == 0)
            break;

        [_node play];

        _ready = true;
        ret = true;

    } while (false);

    _play2dMutex.unlock();
    return ret;
}

void AudioPlayer::schedulePass(int64_t startFrame, bool allowLoopOption)
{
    if (_node == nil || _audioCache == nullptr)
        return;

    const int64_t totalFrames = _audioCache->_totalFrames;
    if (startFrame < 0 || startFrame >= totalFrames)
        return;

    if (_audioCache->_streaming && _file == nil)
        return;

    auto schedule = _schedule;
    const int generation = schedule->generation.load();
    ++schedule->passes;

    void (^onDone)(AVAudioPlayerNodeCompletionCallbackType) = ^(AVAudioPlayerNodeCompletionCallbackType) {
        if (schedule->generation.load() == generation)
        {
            --schedule->passes;
        }
    };

    if (_audioCache->_streaming)
    {
        [_node scheduleSegment:_file
                 startingFrame:startFrame
                    frameCount:(AVAudioFrameCount)(totalFrames - startFrame)
                        atTime:nil
        completionCallbackType:AVAudioPlayerNodeCompletionDataPlayedBack
             completionHandler:onDone];
        return;
    }

    AVAudioPCMBuffer* buffer = _audioCache->_pcmBuffer;
    AVAudioPlayerNodeBufferOptions options = 0;

    if (startFrame > 0)
    {
        makeBufferSlice(startFrame);
        buffer = _sliceBuffer;
    }
    else if (_loop && allowLoopOption)
    {
        options = AVAudioPlayerNodeBufferLoops;
    }

    if (buffer == nil)
    {
        --schedule->passes;
        return;
    }

    [_node scheduleBuffer:buffer
                   atTime:nil
                  options:options
   completionCallbackType:AVAudioPlayerNodeCompletionDataPlayedBack
        completionHandler:onDone];
}

void AudioPlayer::makeBufferSlice(int64_t startFrame)
{
    [_sliceBuffer release];
    _sliceBuffer = nil;

    AVAudioPCMBuffer* source = _audioCache->_pcmBuffer;
    if (source == nil || source.floatChannelData == NULL)
        return;

    const AVAudioFrameCount frames = (AVAudioFrameCount)(source.frameLength - startFrame);
    AVAudioPCMBuffer* slice = [[AVAudioPCMBuffer alloc] initWithPCMFormat:source.format frameCapacity:frames];
    if (slice == nil)
        return;

    const AVAudioChannelCount channels = source.format.channelCount;
    for (AVAudioChannelCount i = 0; i < channels; ++i)
    {
        memcpy(slice.floatChannelData[i], source.floatChannelData[i] + startFrame, frames * sizeof(float));
    }
    slice.frameLength = frames;

    _sliceBuffer = slice;
}

void AudioPlayer::rescheduleFrom(float time)
{
    if (_node == nil || _audioCache == nullptr)
        return;

    ++_schedule->generation;
    [_node stop];
    _schedule->passes = 0;

    _startTime = time;
    _currTime = time;

    const int64_t startFrame = (int64_t)(time * _audioCache->_sampleRate);
    schedulePass(startFrame, true);

    if (_loop && startFrame > 0)
    {
        schedulePass(0, true);
    }
    else if (_loop && _audioCache->_streaming)
    {
        schedulePass(0, true);
    }

    if (!_paused)
    {
        [_node play];
    }
}

void AudioPlayer::topUpSchedule()
{
    if (!_ready || _isDestroyed || !_loop || _audioCache == nullptr || !_audioCache->_streaming)
        return;

    while (_schedule->passes.load() < 2)
    {
        schedulePass(0, false);
    }
}

bool AudioPlayer::isFinished() const
{
    return _schedule->passes.load() <= 0;
}

float AudioPlayer::getTime()
{
    if (_ready && _node != nil && _audioCache != nullptr)
    {
        AVAudioTime* nodeTime = _node.lastRenderTime;
        if (nodeTime != nil && nodeTime.isSampleTimeValid)
        {
            AVAudioTime* playerTime = [_node playerTimeForNodeTime:nodeTime];
            if (playerTime != nil && playerTime.sampleRate > 0.0)
            {
                double time = _startTime + playerTime.sampleTime / playerTime.sampleRate;
                if (_loop && _audioCache->_duration > 0.0f)
                {
                    time = fmod(time, _audioCache->_duration);
                }
                _currTime = (float)time;
            }
        }
    }

    return _currTime;
}

bool AudioPlayer::setTime(float time)
{
    if (_isDestroyed || _audioCache == nullptr)
        return false;

    if (time < 0.0f || time >= _audioCache->_duration)
        return false;

    if (!_ready)
    {
        _startTime = _currTime = time;
        return true;
    }

    rescheduleFrom(time);
    return true;
}

bool AudioPlayer::setLoop(bool loop)
{
    if (_isDestroyed)
        return false;

    if (_loop == loop)
        return true;

    _loop = loop;

    if (_ready && _audioCache != nullptr && !_audioCache->_streaming)
    {
        rescheduleFrom(getTime());
    }

    return true;
}
