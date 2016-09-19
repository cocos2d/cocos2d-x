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

#pragma once

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#import <OpenAL/al.h>
#import <AudioToolbox/AudioToolbox.h>

#include <string>
#include <mutex>
#include <vector>

#include "platform/CCPlatformMacros.h"

#define QUEUEBUFFER_NUM 3
#define QUEUEBUFFER_TIME_STEP 0.1

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define ALOGV(fmt, ...) printf("V/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#else
#define ALOGV(fmt, ...) do {} while(false)
#endif
#define ALOGD(fmt, ...) printf("D/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGI(fmt, ...) printf("I/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGW(fmt, ...) printf("W/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGE(fmt, ...) printf("E/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define CHECK_AL_ERROR_DEBUG() \
do { \
    GLenum __error = alGetError(); \
    if (__error) { \
        ALOGE("OpenAL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
    } \
} while (false)
#else
#define CHECK_AL_ERROR_DEBUG() 
#endif

NS_CC_BEGIN
namespace experimental{

class AudioEngineImpl;
class AudioPlayer;

class AudioCache
{
public:
    
    enum class State
    {
        INITIAL,
        LOADING,
        READY,
        FAILED
    };
    
    AudioCache();
    ~AudioCache();

    void addPlayCallback(const std::function<void()>& callback);

    void addLoadCallback(const std::function<void(bool)>& callback);
    
protected:
    void setSkipReadDataTask(bool isSkip) { _isSkipReadDataTask = isSkip; };
    void readDataTask(unsigned int selfId);

    void invokingPlayCallbacks();

    void invokingLoadCallbacks();
    
    //pcm data related stuff
    ALsizei _dataSize;
    ALenum _format;
    ALsizei _sampleRate;
    float _duration;
    int _bytesPerFrame;
    AudioStreamBasicDescription _outputFormat;
    
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

    std::mutex _playCallbackMutex;
    std::vector< std::function<void()> > _playCallbacks;
    
    // loadCallbacks doesn't need mutex since it's invoked only in Cocos thread.
    std::vector< std::function<void(bool)> > _loadCallbacks;
    
    std::mutex _readDataTaskMutex;
    
    State _state;
    
    std::shared_ptr<bool> _isDestroyed;
    std::string _fileFullPath;
    unsigned int _id;
    bool _isLoadingFinished;
    bool _isSkipReadDataTask;
    
    friend class AudioEngineImpl;
    friend class AudioPlayer;
} ;

}
NS_CC_END

#endif

