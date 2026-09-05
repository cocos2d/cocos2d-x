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

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include "platform/CCPlatformMacros.h"
#include "audio/apple/av/AudioMacros.h"

#ifdef __OBJC__
@class AVAudioFile;
@class AVAudioPCMBuffer;
@class AVAudioPlayerNode;
#else
typedef struct objc_object AVAudioFile;
typedef struct objc_object AVAudioPCMBuffer;
typedef struct objc_object AVAudioPlayerNode;
#endif

NS_CC_BEGIN

class AudioCache;
class AudioEngineImpl;

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void destroy();

    bool setTime(float time);
    float getTime();
    bool setLoop(bool loop);

protected:
    /* Scheduling state outlives the player: AVAudioEngine may invoke a completion handler
     * after the player is gone, so the handlers only touch this shared block.
     */
    struct ScheduleState
    {
        std::atomic_int generation;
        std::atomic_int passes;

        ScheduleState() : generation(0), passes(0) {}
    };

    void setCache(AudioCache* cache);
    bool play2d();
    void rescheduleFrom(float time);
    void topUpSchedule();
    bool isFinished() const;

    void schedulePass(int64_t startFrame, bool allowLoopOption);
    void makeBufferSlice(int64_t startFrame);

    AudioCache* _audioCache;

    float _volume;
    bool _loop;
    std::function<void (int, const std::string &)> _finishCallbak;

    bool _isDestroyed;
    bool _removeByAudioEngine;
    bool _ready;
    bool _paused;

    AVAudioPlayerNode* _node;
    int _nodeIndex;
    AVAudioFile* _file;
    AVAudioPCMBuffer* _sliceBuffer;

    std::shared_ptr<ScheduleState> _schedule;

    float _startTime;
    float _currTime;

    std::mutex _play2dMutex;

    unsigned int _id;

    friend class AudioEngineImpl;
};

NS_CC_END
