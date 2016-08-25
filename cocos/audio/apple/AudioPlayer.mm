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

#define LOG_TAG "AudioPlayer"

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#import <Foundation/Foundation.h>

#include "audio/apple/AudioPlayer.h"
#include "audio/apple/AudioCache.h"
#include "platform/CCFileUtils.h"
#import <AudioToolbox/ExtendedAudioFile.h>

#define VERY_VERY_VERBOSE_LOGGING
#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(...) do{} while(false)
#endif

using namespace cocos2d;
using namespace cocos2d::experimental;

namespace {
unsigned int __idIndex = 0;
}

AudioPlayer::AudioPlayer()
: _audioCache(nullptr)
, _finishCallbak(nullptr)
, _isDestroyed(false)
, _removeByAudioEngine(false)
, _ready(false)
, _currTime(0.0f)
, _streamingSource(false)
, _rotateBufferThread(nullptr)
, _timeDirty(false)
, _isRotateThreadExited(false)
, _id(++__idIndex)
{
    memset(_bufferIds, 0, sizeof(_bufferIds));
}

AudioPlayer::~AudioPlayer()
{
    ALOGVV("~AudioPlayer() (%p), id=%u", this, _id);
    destroy();
    
    if (_streamingSource)
    {
        alDeleteBuffers(3, _bufferIds);
    }
}

void AudioPlayer::destroy()
{
    if (_isDestroyed)
        return;
    
    ALOGVV("AudioPlayer::destroy begin, id=%u", _id);

    _isDestroyed = true;
    
    do
    {
        if (_audioCache != nullptr)
        {
            if (_audioCache->_state == AudioCache::State::INITIAL)
            {
                ALOGV("AudioPlayer::destroy, id=%u, cache isn't ready!", _id);
                break;
            }
            
            while (!_audioCache->_isLoadingFinished)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        }
        
        // Wait for play2d to be finished.
        _play2dMutex.lock();
        _play2dMutex.unlock();
        
        if (_streamingSource)
        {
            if (_rotateBufferThread != nullptr)
            {
                while (!_isRotateThreadExited)
                {
                    _sleepCondition.notify_one();
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
                
                if (_rotateBufferThread->joinable()) {
                    _rotateBufferThread->join();
                }
                
                delete _rotateBufferThread;
                _rotateBufferThread = nullptr;
                ALOGVV("rotateBufferThread exited!");
            }
        }
    } while(false);
    
    ALOGVV("Before alSourceStop");
    alSourceStop(_alSource); CHECK_AL_ERROR_DEBUG();
    ALOGVV("Before alSourcei");
    alSourcei(_alSource, AL_BUFFER, NULL); CHECK_AL_ERROR_DEBUG();
    
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
    ALOGV("AudioPlayer::play2d, _alSource: %u", _alSource);

    /*********************************************************************/
    /*       Note that it may be in sub thread or in main thread.       **/
    /*********************************************************************/
    bool ret = false;
    do
    {
        if (_audioCache->_state != AudioCache::State::READY)
        {
            ALOGE("alBuffer isn't ready for play!");
            break;
        }
        
        alSourcei(_alSource, AL_BUFFER, 0);CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_PITCH, 1.0f);CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_GAIN, _volume);CHECK_AL_ERROR_DEBUG();
        alSourcei(_alSource, AL_LOOPING, AL_FALSE);CHECK_AL_ERROR_DEBUG();
        
        if (_audioCache->_queBufferFrames == 0)
        {
            if (_loop) {
                alSourcei(_alSource, AL_LOOPING, AL_TRUE);
                CHECK_AL_ERROR_DEBUG();
            }
        }
        else
        {
            alGenBuffers(3, _bufferIds);
            
            auto alError = alGetError();
            if (alError == AL_NO_ERROR)
            {
                for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
                {
                    alBufferData(_bufferIds[index], _audioCache->_format, _audioCache->_queBuffers[index], _audioCache->_queBufferSize[index], _audioCache->_sampleRate);
                }
                CHECK_AL_ERROR_DEBUG();
            }
            else
            {
                ALOGE("%s:alGenBuffers error code:%x", __PRETTY_FUNCTION__,alError);
                break;
            }
            _streamingSource = true;
        }
        
        {
            std::unique_lock<std::mutex> lk(_sleepMutex);
            if (_isDestroyed)
                break;
            
            if (_streamingSource)
            {
                alSourceQueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
                CHECK_AL_ERROR_DEBUG();
                _rotateBufferThread = new std::thread(&AudioPlayer::rotateBufferThread, this, _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1);
            }
            else
            {
                alSourcei(_alSource, AL_BUFFER, _audioCache->_alBufferId);
                CHECK_AL_ERROR_DEBUG();
            }

            alSourcePlay(_alSource);
        }
        
        auto alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            ALOGE("%s:alSourcePlay error code:%x", __PRETTY_FUNCTION__,alError);
            break;
        }

        ALint state;
        alGetSourcei(_alSource, AL_SOURCE_STATE, &state);
        assert(state == AL_PLAYING);
        _ready = true;
        ret = true;
    } while (false);
    
    if (!ret)
    {
        _removeByAudioEngine = true;
    }
    
    _play2dMutex.unlock();
    return ret;
}

void AudioPlayer::rotateBufferThread(int offsetFrame)
{
    ALint sourceState;
    ALint bufferProcessed = 0;
    ExtAudioFileRef extRef = nullptr;
    
    NSString *fileFullPath = [[NSString alloc] initWithCString:_audioCache->_fileFullPath.c_str() encoding:NSUTF8StringEncoding];
    auto fileURL = (CFURLRef)[[NSURL alloc] initFileURLWithPath:fileFullPath];
    [fileFullPath release];
    char* tmpBuffer = (char*)malloc(_audioCache->_queBufferBytes);
    auto frames = _audioCache->_queBufferFrames;
    
    auto error = ExtAudioFileOpenURL(fileURL, &extRef);
    if(error) {
        ALOGE("%s: ExtAudioFileOpenURL FAILED, Error = %ld", __PRETTY_FUNCTION__,(long) error);
        goto ExitBufferThread;
    }
    
    error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(_audioCache->_outputFormat), &_audioCache->_outputFormat);
    AudioBufferList		theDataBuffer;
    theDataBuffer.mNumberBuffers = 1;
    theDataBuffer.mBuffers[0].mData = tmpBuffer;
    theDataBuffer.mBuffers[0].mDataByteSize = _audioCache->_queBufferBytes;
    theDataBuffer.mBuffers[0].mNumberChannels = _audioCache->_outputFormat.mChannelsPerFrame;
    
    if (offsetFrame != 0) {
        ExtAudioFileSeek(extRef, offsetFrame);
    }
    
    while (!_isDestroyed) {
        alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
        if (sourceState == AL_PLAYING) {
            alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
            while (bufferProcessed > 0) {
                bufferProcessed--;
                if (_timeDirty) {
                    _timeDirty = false;
                    offsetFrame = _currTime * _audioCache->_outputFormat.mSampleRate;
                    ExtAudioFileSeek(extRef, offsetFrame);
                }
                else {
                    _currTime += QUEUEBUFFER_TIME_STEP;
                    if (_currTime > _audioCache->_duration) {
                        if (_loop) {
                            _currTime = 0.0f;
                        } else {
                            _currTime = _audioCache->_duration;
                        }
                    }
                }
                
                frames = _audioCache->_queBufferFrames;
                ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
                if (frames <= 0) {
                    if (_loop) {
                        ExtAudioFileSeek(extRef, 0);
                        frames = _audioCache->_queBufferFrames;
                        theDataBuffer.mBuffers[0].mDataByteSize = _audioCache->_queBufferBytes;
                        ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
                    } else {
                        _isDestroyed = true;
                        break;
                    }
                }
                
                ALuint bid;
                alSourceUnqueueBuffers(_alSource, 1, &bid);
                alBufferData(bid, _audioCache->_format, tmpBuffer, frames * _audioCache->_outputFormat.mBytesPerFrame, _audioCache->_sampleRate);
                alSourceQueueBuffers(_alSource, 1, &bid);
            }
        }
        
        std::unique_lock<std::mutex> lk(_sleepMutex);
        if (_isDestroyed) {
            break;
        }
        
        _sleepCondition.wait_for(lk,std::chrono::milliseconds(75));
    }
    
ExitBufferThread:
    ALOGV("Exit rotate buffer thread ...");
    CFRelease(fileURL);
	// Dispose the ExtAudioFileRef, it is no longer needed
	if (extRef){
        ExtAudioFileDispose(extRef);
    }
    free(tmpBuffer);
    _isRotateThreadExited = true;
}

bool AudioPlayer::setLoop(bool loop)
{
    if (!_isDestroyed ) {
        _loop = loop;
        return true;
    }
    
    return false;
}

bool AudioPlayer::setTime(float time)
{
    if (!_isDestroyed && time >= 0.0f && time < _audioCache->_duration) {
        
        _currTime = time;
        _timeDirty = true;
        
        return true;
    }
    return false;
}

#endif
