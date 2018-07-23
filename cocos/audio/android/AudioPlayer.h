/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2018 x-studio365 @HALX99.

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

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <string>
#include <condition_variable>
#include <mutex>
#include <thread>
#ifdef OPENAL_PLAIN_INCLUDES
#include <al.h>
#else
#include <AL/al.h>
#endif
#include "platform/CCPlatformMacros.h"
// #include "object_pool.h"

NS_CC_BEGIN
namespace experimental{

class AudioCache;
class AudioEngineImpl;

class CC_DLL AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void destroy();

    //queue buffer related stuff
    bool setTime(float time);
    float getTime() { return _currTime;}
    bool setLoop(bool loop);

    // DEFINE_OBJECT_POOL_ALLOCATION(AudioPlayer, 128)

    bool isFinished() const;
protected:
    void setCache(AudioCache* cache);
    void rotateBufferThread(int offsetFrame);
    bool play2d();

    AudioCache* _audioCache;

    float _volume;
    bool _loop;
    std::function<void (uintptr_t, const std::string &)> _finishCallbak;

    bool _isDestroyed;
    bool _removeByAudioEngine;
    bool _ready;
    ALuint _alSource;

    //play by circular buffer
    float _currTime;
    bool _streamingSource;
    ALuint _bufferIds[3];
    std::thread* _rotateBufferThread;
    std::condition_variable _sleepCondition;
    std::mutex _sleepMutex;
    bool _timeDirty;
    bool _isRotateThreadExited;

    std::mutex _play2dMutex;

    uintptr_t _id;
    friend class AudioEngineImpl;
};

}
NS_CC_END

#endif //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

