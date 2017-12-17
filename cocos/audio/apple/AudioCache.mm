/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "audio/apple/AudioCache.h"

#import <Foundation/Foundation.h>
#import <OpenAL/alc.h>
#include <thread>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "audio/apple/AudioDecoder.h"

#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

namespace {
unsigned int __idIndex = 0;
}

#define INVALID_AL_BUFFER_ID 0xFFFFFFFF
#define PCMDATA_CACHEMAXSIZE 1048576

typedef ALvoid	AL_APIENTRY	(*alBufferDataStaticProcPtr) (const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq);
static ALvoid  alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq)
{
    static alBufferDataStaticProcPtr proc = nullptr;

    if (proc == nullptr) {
        proc = (alBufferDataStaticProcPtr) alcGetProcAddress(nullptr, (const ALCchar*) "alBufferDataStatic");
    }

    if (proc){
        proc(bid, format, data, size, freq);
    }

    return;
}

@interface NSTimerWrapper : NSObject
{
    std::function<void()> _timeoutCallback;
}

@end

@implementation NSTimerWrapper

-(id) initWithTimeInterval:(double) seconds callback:(const std::function<void()>&) cb
{
    if (self = [super init])
    {
        _timeoutCallback = cb;
        NSTimer* timer = [NSTimer timerWithTimeInterval:seconds target: self selector:@selector(onTimeoutCallback:) userInfo:nil repeats:NO];
        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    }

    return self;
}

-(void) onTimeoutCallback: (NSTimer*) timer
{
    if (_timeoutCallback != nullptr)
    {
        _timeoutCallback();
        _timeoutCallback = nullptr;
    }
}

-(void) dealloc
{
    [super dealloc];
}

@end

static void setTimeout(double seconds, const std::function<void()>& cb)
{
    [[[NSTimerWrapper alloc] initWithTimeInterval:seconds callback:cb] autorelease];
}

using namespace cocos2d;
using namespace cocos2d::experimental;

AudioCache::AudioCache()
: _format(-1)
, _duration(0.0f)
, _totalFrames(0)
, _framesRead(0)
, _alBufferId(INVALID_AL_BUFFER_ID)
, _pcmData(nullptr)
, _queBufferFrames(0)
, _state(State::INITIAL)
, _isDestroyed(std::make_shared<bool>(false))
, _id(++__idIndex)
, _isLoadingFinished(false)
, _isSkipReadDataTask(false)
{
    ALOGVV("AudioCache() %p, id=%u", this, _id);
    for (int i = 0; i < QUEUEBUFFER_NUM; ++i)
    {
        _queBuffers[i] = nullptr;
        _queBufferSize[i] = 0;
    }
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
    _readDataTaskMutex.unlock();

    if (_pcmData)
    {
        if (_state == State::READY)
        {
            if (_alBufferId != INVALID_AL_BUFFER_ID && alIsBuffer(_alBufferId))
            {
                ALOGV("~AudioCache(id=%u), delete buffer: %u", _id, _alBufferId);
                alDeleteBuffers(1, &_alBufferId);
                _alBufferId = INVALID_AL_BUFFER_ID;
            }
        }
        else
        {
            ALOGW("AudioCache (%p), id=%u, buffer isn't ready, state=%d", this, _id, _state);
        }

        // fixed #17494: CrashIfClientProvidedBogusAudioBufferList
        // We're using 'alBufferDataStaticProc' for speeding up
        // the performance of playing audio without preload, but we need to manage the memory by ourself carefully.
        // It's probably that '_pcmData' is freed before OpenAL finishes the audio render task,
        // then 'CrashIfClientProvidedBogusAudioBufferList' may be triggered.
        // 'cpp-tests/NewAudioEngineTest/AudioSwitchStateTest' can reproduce this issue without the following fix.
        // The workaround is delaying 200ms to free pcm data.
        char* data = _pcmData;
        setTimeout(0.2, [data](){
            free(data);
        });
    }

    if (_queBufferFrames > 0)
    {
        for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
        {
            free(_queBuffers[index]);
        }
    }
    ALOGVV("~AudioCache() %p, id=%u, end", this, _id);
}

void AudioCache::readDataTask(unsigned int selfId)
{
    //Note: It's in sub thread
    ALOGVV("readDataTask, cache id=%u", selfId);

    _readDataTaskMutex.lock();
    _state = State::LOADING;

    AudioDecoder decoder;
    do
    {
        if (!decoder.open(_fileFullPath.c_str()))
            break;

        const uint32_t originalTotalFrames = decoder.getTotalFrames();
        const uint32_t bytesPerFrame = decoder.getBytesPerFrame();
        const uint32_t sampleRate = decoder.getSampleRate();
        const uint32_t channelCount = decoder.getChannelCount();

        uint32_t totalFrames = originalTotalFrames;
        uint32_t dataSize = totalFrames * bytesPerFrame;
        uint32_t remainingFrames = totalFrames;
        uint32_t adjustFrames = 0;

        _format = channelCount > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
        _sampleRate = (ALsizei)sampleRate;
        _duration = 1.0f * totalFrames / sampleRate;
        _totalFrames = totalFrames;

        if (dataSize <= PCMDATA_CACHEMAXSIZE)
        {
            uint32_t framesRead = 0;
            const uint32_t framesToReadOnce = std::min(totalFrames, static_cast<uint32_t>(sampleRate * QUEUEBUFFER_TIME_STEP * QUEUEBUFFER_NUM));

            BREAK_IF_ERR_LOG(!decoder.seek(totalFrames), "AudioDecoder::seek(%u) error", totalFrames);

            char* tmpBuf = (char*)malloc(framesToReadOnce * bytesPerFrame);
            std::vector<char> adjustFrameBuf;
            adjustFrameBuf.reserve(framesToReadOnce * bytesPerFrame);

            // Adjust total frames by setting position to the end of frames and try to read more data.
            // This is a workaround for https://github.com/cocos2d/cocos2d-x/issues/16938
            do
            {
                framesRead = decoder.read(framesToReadOnce, tmpBuf);
                if (framesRead > 0)
                {
                    adjustFrames += framesRead;
                    adjustFrameBuf.insert(adjustFrameBuf.end(), tmpBuf, tmpBuf + framesRead * bytesPerFrame);
                }

            } while (framesRead > 0);

            if (adjustFrames > 0)
            {
                ALOGV("Orignal total frames: %u, adjust frames: %u, current total frames: %u", totalFrames, adjustFrames, totalFrames + adjustFrames);
                totalFrames += adjustFrames;
                _totalFrames = remainingFrames = totalFrames;
            }

            // Reset dataSize
            dataSize = totalFrames * bytesPerFrame;

            free(tmpBuf);

            // Reset to frame 0
            BREAK_IF_ERR_LOG(!decoder.seek(0), "AudioDecoder::seek(0) failed!");

            _pcmData = (char*)malloc(dataSize);
            memset(_pcmData, 0x00, dataSize);

            if (adjustFrames > 0)
            {
                memcpy(_pcmData + (dataSize - adjustFrameBuf.size()), adjustFrameBuf.data(), adjustFrameBuf.size());
            }

            alGenBuffers(1, &_alBufferId);
            auto alError = alGetError();
            if (alError != AL_NO_ERROR) {
                ALOGE("%s: attaching audio to buffer fail: %x", __PRETTY_FUNCTION__, alError);
                break;
            }

            if (*_isDestroyed)
                break;

            alBufferDataStaticProc(_alBufferId, _format, _pcmData, (ALsizei)dataSize, (ALsizei)sampleRate);

            framesRead = decoder.readFixedFrames(std::min(framesToReadOnce, remainingFrames), _pcmData + _framesRead * bytesPerFrame);
            _framesRead += framesRead;
            remainingFrames -= framesRead;

            if (*_isDestroyed)
                break;

            _state = State::READY;

            invokingPlayCallbacks();

            uint32_t frames = 0;
            while (!*_isDestroyed && _framesRead < originalTotalFrames)
            {
                frames = std::min(framesToReadOnce, remainingFrames);
                if (_framesRead + frames > originalTotalFrames)
                {
                    frames = originalTotalFrames - _framesRead;
                }
                framesRead = decoder.read(frames, _pcmData + _framesRead * bytesPerFrame);
                if (framesRead == 0)
                    break;
                _framesRead += framesRead;
                remainingFrames -= framesRead;
            }

            if (_framesRead < originalTotalFrames)
            {
                memset(_pcmData + _framesRead * bytesPerFrame, 0x00, (totalFrames - _framesRead) * bytesPerFrame);
            }
            ALOGV("pcm buffer was loaded successfully, total frames: %u, total read frames: %u, adjust frames: %u, remainingFrames: %u", totalFrames, _framesRead, adjustFrames, remainingFrames);

            _framesRead += adjustFrames;
        }
        else
        {
            _queBufferFrames = sampleRate * QUEUEBUFFER_TIME_STEP;
            BREAK_IF_ERR_LOG(_queBufferFrames == 0, "_queBufferFrames == 0");

            const uint32_t queBufferBytes = _queBufferFrames * bytesPerFrame;

            for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
            {
                _queBuffers[index] = (char*)malloc(queBufferBytes);
                _queBufferSize[index] = queBufferBytes;

                decoder.readFixedFrames(_queBufferFrames, _queBuffers[index]);
            }

            _state = State::READY;
        }

    } while (false);

    decoder.close();

    //FIXME: Why to invoke play callback first? Should it be after 'load' callback?
    invokingPlayCallbacks();
    invokingLoadCallbacks();

    _isLoadingFinished = true;
    if (_state != State::READY)
    {
        _state = State::FAILED;
        if (_alBufferId != INVALID_AL_BUFFER_ID && alIsBuffer(_alBufferId))
        {
            ALOGV("readDataTask failed, delete buffer: %u", _alBufferId);
            alDeleteBuffers(1, &_alBufferId);
            _alBufferId = INVALID_AL_BUFFER_ID;
        }
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

#endif
