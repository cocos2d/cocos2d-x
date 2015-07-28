/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#ifndef __AUDIO_CACHE_H_
#define __AUDIO_CACHE_H_

#import <OpenAL/al.h>
#import <AudioToolbox/AudioToolbox.h>

#include <string>
#include <mutex>
#include <vector>

#include "CCPlatformMacros.h"

#define QUEUEBUFFER_NUM 3
#define QUEUEBUFFER_TIME_STEP 0.1

NS_CC_BEGIN
namespace experimental{

class AudioEngineImpl;
class AudioPlayer;

class AudioCache{
public:
    AudioCache();
    ~AudioCache();

    void addPlayCallback(const std::function<void()>& callback);

    void addLoadCallback(const std::function<void(bool)>& callback);
    
protected:
    void readDataTask();

    void invokingPlayCallbacks();

    void invokingLoadCallbacks();
    
    //pcm data related stuff
    ALsizei _dataSize;
    ALenum _format;
    ALsizei _sampleRate;
    float _duration;
    int _bytesPerFrame;
    AudioStreamBasicDescription outputFormat;
    
    /*Cache related stuff;
     * Cache pcm data when sizeInBytes less than PCMDATA_CACHEMAXSIZE
     */
    ALuint _alBufferId;
    char* _pcmData;
    SInt64 _bytesOfRead;

    /*Queue buffer related stuff
     *  Streaming in openal when sizeInBytes greater then PCMDATA_CACHEMAXSIZE
     */
    char* _queBuffers[QUEUEBUFFER_NUM];
    ALsizei _queBufferSize[QUEUEBUFFER_NUM];
    UInt32 _queBufferFrames;
    UInt32 _queBufferBytes;

    bool _alBufferReady;
    bool _loadFail;
    std::mutex _callbackMutex;
    
    std::vector< std::function<void()> > _callbacks;
    std::vector< std::function<void(bool)> > _loadCallbacks;
    std::mutex _readDataTaskMutex;
    
    bool _exitReadDataTask;
    std::string _fileFullPath;
    
    friend class AudioEngineImpl;
    friend class AudioPlayer;
} ;

}
NS_CC_END

#endif // __AUDIO_CACHE_H_
#endif

