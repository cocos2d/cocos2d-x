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
#include "AudioPlayer.h"
#include "AudioCache.h"
#include "platform/CCFileUtils.h"
#import <AudioToolbox/ExtendedAudioFile.h>

using namespace cocos2d;

AudioPlayer::AudioPlayer()
: _release(false)
, _largeFile(false)
, _currTime(0.0f)
, _finishCallbak(nullptr)
, _ready(false)
, _audioCache(nullptr)
{
    
}

AudioPlayer::~AudioPlayer()
{
    _release = true;
    if (_audioCache && _audioCache->_queBufferFrames > 0) {
        _timeMtx.unlock();
        _rotateBufferMtx.lock();
        _rotateBufferMtx.unlock();
        alDeleteBuffers(3, _bufferIds);
    }
}

bool AudioPlayer::play2d(AudioCache* cache)
{
    bool ret = true;
    if (!cache->_alBufferReady) {
        return false;
    }
    _audioCache = cache;
    
    alSourcei(_alSource, AL_BUFFER, NULL);
    alSourcef(_alSource, AL_PITCH, 1.0f);
    alSourcef(_alSource, AL_GAIN, _volume);
    
    if (_audioCache->_queBufferFrames == 0) {
        if (_loop) {
            alSourcei(_alSource, AL_LOOPING, AL_TRUE);
        }
        else {
            alSourcei(_alSource, AL_LOOPING, AL_FALSE);
        }
        alSourcei(_alSource, AL_BUFFER, _audioCache->_alBufferId);
        
    } else {
        _largeFile = true;
        
        auto alError = alGetError();
        alGenBuffers(3, _bufferIds);
        alError = alGetError();
        if (alError == AL_NO_ERROR) {
            for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
                alBufferData(_bufferIds[index], _audioCache->_format, _audioCache->_queBuffers[index], _audioCache->_queBufferBytes, _audioCache->_sampleRate);
            }
            alSourcei(_alSource, AL_BUFFER, NULL);
            alSourceQueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
            
            _timeMtx.lock();
            auto rotateThread = std::thread(&AudioPlayer::rotateBufferThread,this, _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1);
            rotateThread.detach();
        }
        else {
            printf("error:%s, error code:%x", __PRETTY_FUNCTION__,alError);
            ret = false;
        }
    }
    
    alSourcePlay(_alSource);
    _ready = true;
    auto alError = alGetError();
    
    if (alError != AL_NO_ERROR) {
        ret = false;
        printf("error:%s, error code:%x\n", __PRETTY_FUNCTION__,alError);
    }
    
    return ret;
}

void AudioPlayer::rotateBufferThread(int offsetFrame)
{
    _rotateBufferMtx.lock();
    printf("%s start\n",__func__);
    
    ALint sourceState;
    ALint bufferProcessed = 0;
    ExtAudioFileRef extRef = nullptr;
    
    auto fileURL = (CFURLRef)[[NSURL fileURLWithPath:[NSString stringWithCString:_audioCache->_fileFullPath.c_str() encoding:[NSString defaultCStringEncoding]]] retain];
    char* tmpBuffer = (char*)malloc(_audioCache->_queBufferBytes);
    auto frames = _audioCache->_queBufferFrames;
    
    auto error = ExtAudioFileOpenURL(fileURL, &extRef);
    if(error) {
        printf("rotateBufferThread: ExtAudioFileOpenURL FAILED, Error = %d\n", error);
        goto ExitBufferThread;
    }
    
    error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(_audioCache->outputFormat), &_audioCache->outputFormat);
    AudioBufferList		theDataBuffer;
    theDataBuffer.mNumberBuffers = 1;
    theDataBuffer.mBuffers[0].mData = tmpBuffer;
    theDataBuffer.mBuffers[0].mDataByteSize = _audioCache->_queBufferBytes;
    theDataBuffer.mBuffers[0].mNumberChannels = _audioCache->outputFormat.mChannelsPerFrame;
    
    if (offsetFrame != 0) {
        ExtAudioFileSeek(extRef, offsetFrame);
    }
    
    while (!_release) {
        alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
        if (sourceState == AL_PLAYING) {
            alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
            while (bufferProcessed > 0) {
                bufferProcessed--;
                
                _currTime += 0.2f;
                if (_currTime > _audioCache->_duration) {
                    if (_loop) {
                        _currTime = 0.0f;
                    } else {
                        _currTime = _audioCache->_duration;
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
                        break;
                    }
                }
                
                ALuint bid;
                alSourceUnqueueBuffers(_alSource, 1, &bid);
                alBufferData(bid, _audioCache->_format, tmpBuffer, frames * _audioCache->outputFormat.mBytesPerFrame, _audioCache->_sampleRate);
                alSourceQueueBuffers(_alSource, 1, &bid);
            }
        }
        
        _timeMtx.try_lock_for(std::chrono::milliseconds(100));
    }
    
ExitBufferThread:
    CFRelease(fileURL);
	// Dispose the ExtAudioFileRef, it is no longer needed
	if (extRef){
        ExtAudioFileDispose(extRef);
    }
    free(tmpBuffer);
    _rotateBufferMtx.unlock();
    printf("%s end\n",__func__);
}

bool AudioPlayer::setLoop(bool loop)
{
    if (!_release ) {
        _loop = loop;
        if (_rotateBufferMtx.try_lock() && loop) {
            _rotateBufferMtx.unlock();
            
            auto rotateThread = std::thread(&AudioPlayer::rotateBufferThread,this, 0);
            rotateThread.detach();
        }
        
        return true;
    }
    
    return false;
}

bool AudioPlayer::setTime(float time)
{
    return  false;
    
    if (!_release && time >= 0.0f && time < _audioCache->_duration) {
        _release = true;
        _timeMtx.unlock();
        _rotateBufferMtx.lock();
        _rotateBufferMtx.unlock();
        
        _currTime = time;
        alSourcei(_alSource, AL_BUFFER, NULL);
        
        ExtAudioFileRef extRef = nullptr;
        AudioBufferList		theDataBuffer;
        char* bufferData[QUEUEBUFFER_NUM];
        
        auto fileURL = (CFURLRef)[[NSURL fileURLWithPath:[NSString stringWithCString:_audioCache->_fileFullPath.c_str() encoding:[NSString defaultCStringEncoding]]] retain];
        auto error = ExtAudioFileOpenURL(fileURL, &extRef);
        error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(_audioCache->outputFormat), &_audioCache->outputFormat);
        
		theDataBuffer.mNumberBuffers = QUEUEBUFFER_NUM;
        for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
            bufferData[index] = (char*)malloc(_audioCache->_queBufferBytes);
            
            theDataBuffer.mBuffers[index].mDataByteSize = _audioCache->_queBufferBytes;
            theDataBuffer.mBuffers[index].mNumberChannels = _audioCache->outputFormat.mChannelsPerFrame;
            theDataBuffer.mBuffers[index].mData = bufferData[index];
        }
		
        int offsetFrames = time * _audioCache->outputFormat.mSampleRate;
        if (offsetFrames != 0) {
            error = ExtAudioFileSeek(extRef, offsetFrames);
        }
        
        UInt32 frames = _audioCache->_queBufferFrames * QUEUEBUFFER_NUM;
        ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
        
        for (int index = 0; index < theDataBuffer.mNumberBuffers; ++index) {
            alBufferData(_bufferIds[index], _audioCache->_format, bufferData[index], theDataBuffer.mBuffers[index].mDataByteSize, _audioCache->_sampleRate);
            free(bufferData[index]);
        }
        alSourceQueueBuffers(_alSource, theDataBuffer.mNumberBuffers, _bufferIds);
        
    ExitSetTime:
        CFRelease(fileURL);
        // Dispose the ExtAudioFileRef, it is no longer needed
        if (extRef){
            ExtAudioFileDispose(extRef);
        }
        
        auto rotateThread = std::thread(&AudioPlayer::rotateBufferThread,this, offsetFrames + QUEUEBUFFER_NUM * _audioCache->_queBufferFrames+ 1);
        rotateThread.detach();
        
        return true;
    }
    return false;
}
