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
#include "AudioCache.h"
#include <thread>
#import <OpenAL/alc.h>
#import <AudioToolbox/ExtendedAudioFile.h>

#define PCMDATA_CACHEMAXSIZE 1048576

typedef ALvoid	AL_APIENTRY	(*alBufferDataStaticProcPtr) (const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq);
static ALvoid  alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq)
{
	static	alBufferDataStaticProcPtr	proc = NULL;
    
    if (proc == NULL){
        proc = (alBufferDataStaticProcPtr) alcGetProcAddress(NULL, (const ALCchar*) "alBufferDataStatic");
    }
    
    if (proc){
        proc(bid, format, data, size, freq);
    }
	
    return;
}
using namespace cocos2d;
using namespace cocos2d::experimental;

AudioCache::AudioCache()
: _pcmData(nullptr)
, _dataSize(0)
, _bytesOfRead(0)
, _exitReadDataTask(false)
, _queBufferFrames(0)
, _queBufferBytes(0)
, _alBufferReady(false)
{
    
}

AudioCache::~AudioCache()
{
    _exitReadDataTask = true;
    if(_pcmData){
        if (_alBufferReady){
            alDeleteBuffers(1, &_alBufferId);
        }
        //wait for the 'readDataTask' task to exit
        _readDataTaskMutex.lock();
        _readDataTaskMutex.unlock();
        
        free(_pcmData);
    }
    
    if (_queBufferFrames > 0) {
        for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
            free(_queBuffers[index]);
        }
    }
}

void AudioCache::readDataTask()
{
    _readDataTaskMutex.lock();
    
    AudioStreamBasicDescription		theFileFormat;
    UInt32 thePropertySize = sizeof(theFileFormat);
    
    SInt64 theFileLengthInFrames;
    SInt64 readInFrames;
    SInt64 dataSize;
    SInt64 frames;
    AudioBufferList theDataBuffer;
    ExtAudioFileRef extRef = nullptr;
    
    auto fileURL = (CFURLRef)[[NSURL fileURLWithPath:[NSString stringWithCString:_fileFullPath.c_str() encoding:[NSString defaultCStringEncoding]]] retain];
    
    auto error = ExtAudioFileOpenURL(fileURL, &extRef);
    if(error) {
        printf("%s: ExtAudioFileOpenURL FAILED, Error = %ld\n", __PRETTY_FUNCTION__, error);
        goto ExitThread;
    }
    
    // Get the audio data format
	error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileDataFormat, &thePropertySize, &theFileFormat);
	if(error) {
        printf("%s: ExtAudioFileGetProperty(kExtAudioFileProperty_FileDataFormat) FAILED, Error = %ld\n", __PRETTY_FUNCTION__, error);
        goto ExitThread;
    }
	if (theFileFormat.mChannelsPerFrame > 2)  {
        printf("%s: Unsupported Format, channel count is greater than stereo\n",__PRETTY_FUNCTION__);
        goto ExitThread;
    }
    
    // Set the client format to 16 bit signed integer (native-endian) data
	// Maintain the channel count and sample rate of the original source format
	outputFormat.mSampleRate = theFileFormat.mSampleRate;
	outputFormat.mChannelsPerFrame = theFileFormat.mChannelsPerFrame;
    
    _bytesPerFrame = 2 * outputFormat.mChannelsPerFrame;
	outputFormat.mFormatID = kAudioFormatLinearPCM;
	outputFormat.mBytesPerPacket = _bytesPerFrame;
	outputFormat.mFramesPerPacket = 1;
	outputFormat.mBytesPerFrame = _bytesPerFrame;
	outputFormat.mBitsPerChannel = 16;
	outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
    
    error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(outputFormat), &outputFormat);
    if(error) {
        printf("%s: ExtAudioFileSetProperty FAILED, Error = %ld\n", __PRETTY_FUNCTION__, error);
        goto ExitThread;
    }
    
    // Get the total frame count
	thePropertySize = sizeof(theFileLengthInFrames);
	error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileLengthFrames, &thePropertySize, &theFileLengthInFrames);
	if(error) {
        printf("%s: ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %ld\n", __PRETTY_FUNCTION__, error);
        goto ExitThread;
    }
	
	_dataSize = (ALsizei)(theFileLengthInFrames * outputFormat.mBytesPerFrame);
    _format = (outputFormat.mChannelsPerFrame > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    _sampleRate = (ALsizei)outputFormat.mSampleRate;
    _duration = 1.0f * theFileLengthInFrames / outputFormat.mSampleRate;
    
    if (_dataSize <= PCMDATA_CACHEMAXSIZE) {
        _pcmData = (char*)malloc(_dataSize);
        alGenBuffers(1, &_alBufferId);
        auto alError = alGetError();
        if (alError != AL_NO_ERROR) {
            printf("%s: attaching audio to buffer fail: %x\n", __PRETTY_FUNCTION__, alError);
            goto ExitThread;
        }
        alBufferDataStaticProc(_alBufferId, _format, _pcmData, _dataSize, _sampleRate);
        
        readInFrames = theFileFormat.mSampleRate * QUEUEBUFFER_TIME_STEP * QUEUEBUFFER_NUM;
        dataSize = outputFormat.mBytesPerFrame * readInFrames;
        if (dataSize > _dataSize) {
            dataSize = _dataSize;
            readInFrames = theFileLengthInFrames;
        }
        theDataBuffer.mNumberBuffers = 1;
        theDataBuffer.mBuffers[0].mDataByteSize = (UInt32)dataSize;
        theDataBuffer.mBuffers[0].mNumberChannels = outputFormat.mChannelsPerFrame;
        
        theDataBuffer.mBuffers[0].mData = _pcmData;
        frames = readInFrames;
        ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
        _alBufferReady = true;
        _bytesOfRead += dataSize;
        invokingCallbacks();
        
        while (!_exitReadDataTask && _bytesOfRead + dataSize < _dataSize) {
            theDataBuffer.mBuffers[0].mData = _pcmData + _bytesOfRead;
            frames = readInFrames;
            ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
            _bytesOfRead += dataSize;
        }
        
        dataSize = _dataSize - _bytesOfRead;
        if (!_exitReadDataTask && dataSize > 0) {
            theDataBuffer.mBuffers[0].mDataByteSize = (UInt32)dataSize;
            theDataBuffer.mBuffers[0].mData = _pcmData + _bytesOfRead;
            frames = readInFrames;
            ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
        }
        
        _bytesOfRead = _dataSize;
    }
    else{
        _queBufferFrames = theFileFormat.mSampleRate * QUEUEBUFFER_TIME_STEP;
        _queBufferBytes = _queBufferFrames * outputFormat.mBytesPerFrame;
        
		theDataBuffer.mNumberBuffers = QUEUEBUFFER_NUM;
        for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
            _queBuffers[index] = (char*)malloc(_queBufferBytes);
            
            theDataBuffer.mBuffers[index].mDataByteSize = _queBufferBytes;
            theDataBuffer.mBuffers[index].mNumberChannels = outputFormat.mChannelsPerFrame;
            theDataBuffer.mBuffers[index].mData = _queBuffers[index];
        }
		
        frames = _queBufferFrames * QUEUEBUFFER_NUM;
        ExtAudioFileRead(extRef, (UInt32*)&frames, &theDataBuffer);
    }
    
ExitThread:
    CFRelease(fileURL);
    if (extRef)
        ExtAudioFileDispose(extRef);
    
    _readDataTaskMutex.unlock();
    if (_queBufferFrames > 0)
        _alBufferReady = true;
    
    invokingCallbacks();
}

void AudioCache::invokingCallbacks()
{
    _callbackMutex.lock();
    auto count = _callbacks.size();
    for (size_t index = 0; index < count; ++index) {
        _callbacks[index]();
    }
    _callbacks.clear();
    _callbackMutex.unlock();
}

void AudioCache::addCallbacks(const std::function<void ()> &callback)
{
    _callbackMutex.lock();
    if (_alBufferReady) {
        callback();
    } else {
        _callbacks.push_back(callback);
    }
    _callbackMutex.unlock();
}
