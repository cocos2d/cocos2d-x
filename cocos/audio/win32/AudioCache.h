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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#ifndef __AUDIO_CACHE_H_
#define __AUDIO_CACHE_H_

#include <string>
#include <mutex>
#include <vector>
#ifdef OPENAL_PLAIN_INCLUDES
#include <al.h>
#else
#include <AL/al.h>
#endif
#include "platform/CCPlatformMacros.h"

#define QUEUEBUFFER_NUM 5
#define QUEUEBUFFER_TIME_STEP 0.1f

// log, CCLOG aren't threadsafe, since we uses sub threads for parsing pcm data, threadsafe log output
// is needed. Define the following macros (ALOGV, ALOGD, ALOGI, ALOGW, ALOGE) for threadsafe log output.

//FIXME:Move the definition of the following macros to a separated file.

void audioLog(const char * format, ...);

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define ALOGV(fmt, ...) audioLog("V/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
#else
#define ALOGV(fmt, ...) do {} while(false)
#endif
#define ALOGD(fmt, ...) audioLog("D/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
#define ALOGI(fmt, ...) audioLog("I/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
#define ALOGW(fmt, ...) audioLog("W/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)
#define ALOGE(fmt, ...) audioLog("E/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "", ##__VA_ARGS__)

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

class CC_DLL AudioCache{
public:
    enum class FileFormat
    {
        UNKNOWN,
        OGG,
        MP3
    };

    AudioCache();
    AudioCache(const AudioCache&);
    ~AudioCache();

    void addPlayCallback(const std::function<void()>& callback);

    void addLoadCallback(const std::function<void(bool)>& callback);

protected:
    void readDataTask();  
    void invokingPlayCallbacks();
    void invokingLoadCallbacks();

    std::string _fileFullPath;
    FileFormat _fileFormat;
    //pcm data related stuff
    size_t _pcmDataSize;
    ALenum _alBufferFormat;

    int _channels;
    ALuint _sampleRate;
    size_t _bytesPerFrame;
    float _duration;
    
    /*Cache related stuff;
     * Cache pcm data when sizeInBytes less than PCMDATA_CACHEMAXSIZE
     */
    ALuint _alBufferId;
    void* _pcmData;
    size_t _bytesOfRead;

    /*Queue buffer related stuff
     *  Streaming in OpenAL when sizeInBytes greater then PCMDATA_CACHEMAXSIZE
     */
    char* _queBuffers[QUEUEBUFFER_NUM];
    ALsizei _queBufferSize[QUEUEBUFFER_NUM];
    int _queBufferFrames;
    int _queBufferBytes;

    bool _alBufferReady;
    bool _loadFail;
    std::mutex _callbackMutex; 
    std::vector< std::function<void()> > _callbacks;
    std::vector< std::function<void(bool)> > _loadCallbacks;

    std::mutex _readDataTaskMutex;    

    int _mp3Encoding;
    
    friend class AudioEngineImpl;
    friend class AudioPlayer;
} ;

}
NS_CC_END

#endif // __AUDIO_CACHE_H_
#endif

