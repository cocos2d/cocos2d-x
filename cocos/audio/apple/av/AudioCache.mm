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

#define LOG_TAG "AudioCache"

#include "audio/apple/av/AudioCache.h"

#import <AVFoundation/AVFoundation.h>
#include <thread>

#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

namespace {
unsigned int __idIndex = 0;
}

#define PCMDATA_CACHEMAXSIZE 1048576

using namespace cocos2d;

AudioCache::AudioCache()
: _format(nil)
, _sampleRate(0.0)
, _duration(0.0f)
, _totalFrames(0)
, _streaming(false)
, _pcmBuffer(nil)
, _state(State::INITIAL)
, _isDestroyed(std::make_shared<bool>(false))
, _id(++__idIndex)
, _isLoadingFinished(false)
, _isSkipReadDataTask(false)
{
    ALOGVV("AudioCache() %p, id=%u", this, _id);
}

AudioCache::~AudioCache()
{
    ALOGVV("~AudioCache() %p, id=%u, begin", this, _id);
    *_isDestroyed = true;
    while (!_isLoadingFinished)
    {
        if (_isSkipReadDataTask)
        {
            ALOGV("id=%u, Skip read data task, don't continue to wait!", _id);
            break;
        }
        ALOGVV("id=%u, waiting readData thread to finish ...", _id);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    //wait for the 'readDataTask' task to exit
    _readDataTaskMutex.lock();

    [_pcmBuffer release];
    _pcmBuffer = nil;
    [_format release];
    _format = nil;

    ALOGVV("~AudioCache() %p, id=%u, end", this, _id);
    _readDataTaskMutex.unlock();
}

void AudioCache::readDataTask(unsigned int selfId)
{
    //Note: It's in sub thread
    ALOGVV("readDataTask, cache id=%u", selfId);

    _readDataTaskMutex.lock();
    _state = State::LOADING;

    @autoreleasepool
    {
        AVAudioFile* file = nil;
        do
        {
            NSError* error = nil;
            NSURL* url = [NSURL fileURLWithPath:[NSString stringWithUTF8String:_fileFullPath.c_str()]];
            file = [[AVAudioFile alloc] initForReading:url error:&error];
            BREAK_IF_ERR_LOG(file == nil, "Failed to open %s, %s", _fileFullPath.c_str(),
                             [[error localizedDescription] UTF8String]);

            AVAudioFormat* format = file.processingFormat;
            BREAK_IF_ERR_LOG(format.sampleRate <= 0.0, "Invalid sample rate in %s", _fileFullPath.c_str());

            _format = [format retain];
            _sampleRate = format.sampleRate;
            _totalFrames = file.length;
            _duration = (float)(_totalFrames / _sampleRate);

            const int64_t dataSize = _totalFrames * format.channelCount * (int64_t)sizeof(float);
            if (dataSize > PCMDATA_CACHEMAXSIZE)
            {
                _streaming = true;
                _state = State::READY;
                break;
            }

            if (*_isDestroyed)
                break;

            AVAudioPCMBuffer* buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:format
                                                                     frameCapacity:(AVAudioFrameCount)_totalFrames];
            BREAK_IF_ERR_LOG(buffer == nil, "Failed to allocate a buffer of %lld frames", (long long)_totalFrames);

            if (![file readIntoBuffer:buffer error:&error])
            {
                ALOGE("Failed to read %s, %s", _fileFullPath.c_str(), [[error localizedDescription] UTF8String]);
                [buffer release];
                break;
            }

            _pcmBuffer = buffer;
            _totalFrames = buffer.frameLength;
            _duration = (float)(_totalFrames / _sampleRate);
            _state = State::READY;

        } while (false);

        [file release];
    }

    invokingPlayCallbacks();
    invokingLoadCallbacks();

    _isLoadingFinished = true;
    if (_state != State::READY)
    {
        _state = State::FAILED;
    }

    _readDataTaskMutex.unlock();
}

void AudioCache::addPlayCallback(const std::function<void()>& callback)
{
    std::lock_guard<std::mutex> lk(_playCallbackMutex);
    switch (_state)
    {
        case State::INITIAL:
        case State::LOADING:
            _playCallbacks.push_back(callback);
            break;

        case State::READY:
        // If state is failure, we still need to invoke the callback
        // since the callback will set the 'AudioPlayer::_removeByAudioEngine' flag to true.
        case State::FAILED:
            callback();
            break;

        default:
            ALOGE("Invalid state: %d", _state);
            break;
    }
}

void AudioCache::invokingPlayCallbacks()
{
    std::lock_guard<std::mutex> lk(_playCallbackMutex);

    for (auto&& cb : _playCallbacks)
    {
        cb();
    }

    _playCallbacks.clear();
}

void AudioCache::addLoadCallback(const std::function<void(bool)>& callback)
{
    switch (_state)
    {
        case State::INITIAL:
        case State::LOADING:
            _loadCallbacks.push_back(callback);
            break;

        case State::READY:
            callback(true);
            break;
        case State::FAILED:
            callback(false);
            break;

        default:
            ALOGE("Invalid state: %d", _state);
            break;
    }
}

void AudioCache::invokingLoadCallbacks()
{
    if (*_isDestroyed)
    {
        ALOGV("AudioCache (%p) was destroyed, don't invoke preload callback ...", this);
        return;
    }

    auto isDestroyed = _isDestroyed;
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread([&, isDestroyed](){
        if (*isDestroyed)
        {
            ALOGV("invokingLoadCallbacks perform in cocos thread, AudioCache (%p) was destroyed!", this);
            return;
        }

        for (auto&& cb : _loadCallbacks)
        {
            cb(_state == State::READY);
        }

        _loadCallbacks.clear();
    });
}
