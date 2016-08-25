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

#define LOG_TAG "AudioCache"

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#include "audio/apple/AudioCache.h"

#import <Foundation/Foundation.h>
#import <OpenAL/alc.h>
#import <AudioToolbox/ExtendedAudioFile.h>
#include <thread>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#define VERY_VERY_VERBOSE_LOGGING
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
using namespace cocos2d;
using namespace cocos2d::experimental;

AudioCache::AudioCache()
: _dataSize(0)
, _format(-1)
, _duration(0.0f)
, _bytesPerFrame(0)
, _alBufferId(INVALID_AL_BUFFER_ID)
, _pcmData(nullptr)
, _bytesOfRead(0)
, _queBufferFrames(0)
, _queBufferBytes(0)
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
    
    memset(&_outputFormat, 0, sizeof(_outputFormat));
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
        
        free(_pcmData);
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
    
    CFURLRef fileURL = nil;
    ExtAudioFileRef extRef = nullptr;
    
    do
    {
        if (*_isDestroyed) break;
        
        AudioStreamBasicDescription		theFileFormat;
        UInt32 thePropertySize = sizeof(theFileFormat);
        
        SInt64 theFileLengthInFrames;
        SInt64 readInFrames;
        SInt64 dataSize;
        SInt64 frames;
        AudioBufferList theDataBuffer;
        
        NSString *fileFullPath = [[NSString alloc] initWithCString:_fileFullPath.c_str() encoding:NSUTF8StringEncoding];
        fileURL = (CFURLRef)[[NSURL alloc] initFileURLWithPath:fileFullPath];
        [fileFullPath release];
        
        if (*_isDestroyed) break;

        auto error = ExtAudioFileOpenURL(fileURL, &extRef);
        if (error) {
            ALOGE("%s: ExtAudioFileOpenURL FAILED, Error = %ld", __PRETTY_FUNCTION__, (long)error);
            break;
        }
        
        if (*_isDestroyed) break;
        
        // Get the audio data format
        error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileDataFormat, &thePropertySize, &theFileFormat);
        if(error)
        {
            ALOGE("%s: ExtAudioFileGetProperty(kExtAudioFileProperty_FileDataFormat) FAILED, Error = %ld", __PRETTY_FUNCTION__, (long)error);
            break;
        }
        
        if (theFileFormat.mChannelsPerFrame > 2)
        {
            ALOGE("%s: Unsupported Format, channel count is greater than stereo",__PRETTY_FUNCTION__);
            break;
        }
        
        if (*_isDestroyed) break;
        
        // Set the client format to 16 bit signed integer (native-endian) data
        // Maintain the channel count and sample rate of the original source format
        _outputFormat.mSampleRate = theFileFormat.mSampleRate;
        _outputFormat.mChannelsPerFrame = theFileFormat.mChannelsPerFrame;
        
        _bytesPerFrame = 2 * _outputFormat.mChannelsPerFrame;
        _outputFormat.mFormatID = kAudioFormatLinearPCM;
        _outputFormat.mBytesPerPacket = _bytesPerFrame;
        _outputFormat.mFramesPerPacket = 1;
        _outputFormat.mBytesPerFrame = _bytesPerFrame;
        _outputFormat.mBitsPerChannel = 16;
        _outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
        
        error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(_outputFormat), &_outputFormat);
        if(error)
        {
            ALOGE("%s: ExtAudioFileSetProperty FAILED, Error = %ld", __PRETTY_FUNCTION__, (long)error);
            break;
        }
        
        if (*_isDestroyed) break;
        
        // Get the total frame count
        thePropertySize = sizeof(theFileLengthInFrames);
        error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileLengthFrames, &thePropertySize, &theFileLengthInFrames);
        if(error)
        {
            ALOGE("%s: ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %ld", __PRETTY_FUNCTION__, (long)error);
            break;
        }
        
        if (*_isDestroyed) break;
        
        _dataSize = (ALsizei)(theFileLengthInFrames * _outputFormat.mBytesPerFrame);
        _format = (_outputFormat.mChannelsPerFrame > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
        _sampleRate = (ALsizei)_outputFormat.mSampleRate;
        _duration = 1.0f * theFileLengthInFrames / _outputFormat.mSampleRate;
        
        if (_dataSize <= PCMDATA_CACHEMAXSIZE)
        {
            _pcmData = (char*)malloc(_dataSize);
            alGenBuffers(1, &_alBufferId);
            auto alError = alGetError();
            if (alError != AL_NO_ERROR) {
                ALOGE("%s: attaching audio to buffer fail: %x", __PRETTY_FUNCTION__, alError);
                break;
            }
            
            if (*_isDestroyed) break;
            
            alBufferDataStaticProc(_alBufferId, _format, _pcmData, _dataSize, _sampleRate);
            
            readInFrames = theFileFormat.mSampleRate * QUEUEBUFFER_TIME_STEP * QUEUEBUFFER_NUM;
            dataSize = _outputFormat.mBytesPerFrame * readInFrames;
            if (dataSize > _dataSize) {
                dataSize = _dataSize;
                readInFrames = theFileLengthInFrames;
            }
            theDataBuffer.mNumberBuffers = 1;
            theDataBuffer.mBuffers[0].mDataByteSize = (UInt32)dataSize;
            theDataBuffer.mBuffers[0].mNumberChannels = _outputFormat.mChannelsPerFrame;
            
            theDataBuffer.mBuffers[0].mData = _pcmData;
            frames = readInFrames;
            ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
            
            if (*_isDestroyed) break;
            
            _state = State::READY;
            
            _bytesOfRead += dataSize;
            invokingPlayCallbacks();
            
            while (!*_isDestroyed && _bytesOfRead + dataSize < _dataSize) {
                theDataBuffer.mBuffers[0].mData = _pcmData + _bytesOfRead;
                frames = readInFrames;
                ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
                _bytesOfRead += dataSize; //FIXME: the buffer size of read frames may be fewer than dataSize.
            }
            
            dataSize = _dataSize - _bytesOfRead;
            if (!*_isDestroyed && dataSize > 0) {
                theDataBuffer.mBuffers[0].mDataByteSize = (UInt32)dataSize;
                theDataBuffer.mBuffers[0].mData = _pcmData + _bytesOfRead;
                frames = readInFrames;
                ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
            }
            
            _bytesOfRead = _dataSize;
        }
        else
        {
            _queBufferFrames = theFileFormat.mSampleRate * QUEUEBUFFER_TIME_STEP;
            if (_queBufferFrames == 0)
                break;
            
            _queBufferBytes = _queBufferFrames * _outputFormat.mBytesPerFrame;
            
            theDataBuffer.mNumberBuffers = 1;
            theDataBuffer.mBuffers[0].mNumberChannels = _outputFormat.mChannelsPerFrame;
            for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
                _queBuffers[index] = (char*)malloc(_queBufferBytes);
                
                theDataBuffer.mBuffers[0].mDataByteSize = _queBufferBytes;
                theDataBuffer.mBuffers[0].mData = _queBuffers[index];
                frames = _queBufferFrames;
                ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
                
                _queBufferSize[index] = theDataBuffer.mBuffers[0].mDataByteSize;
            }
            
            _state = State::READY;
        }
        
    } while (false);
    
    if (fileURL != nil)
        CFRelease(fileURL);
    
    if (extRef != nullptr)
        ExtAudioFileDispose(extRef);
    
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
