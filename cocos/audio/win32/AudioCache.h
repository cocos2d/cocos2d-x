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
#include "CCPlatformMacros.h"

#define QUEUEBUFFER_NUM 3
#define QUEUEBUFFER_TIME_STEP 0.1f

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

    void addCallbacks(const std::function<void()> &callback);

protected:
    void readDataTask();  
    void invokingCallbacks();

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
    std::mutex _callbackMutex; 
    std::vector< std::function<void()> > _callbacks;

    std::mutex _readDataTaskMutex;    

    int _mp3Encoding;
    
    friend class AudioEngineImpl;
    friend class AudioPlayer;
} ;

}
NS_CC_END

#endif // __AUDIO_CACHE_H_
#endif

