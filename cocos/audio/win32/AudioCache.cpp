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

#include "AudioCache.h"
#include <thread>
#include <algorithm>
#include "base/CCConsole.h"
#include "mpg123.h"
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include "base/ccUtils.h"

#define PCMDATA_CACHEMAXSIZE 2621440

using namespace cocos2d::experimental;

AudioCache::AudioCache()
: _pcmData(nullptr)
, _pcmDataSize(0)
, _bytesOfRead(0)
, _alBufferReady(false)
, _fileFormat(FileFormat::UNKNOWN)
, _queBufferFrames(0)
, _queBufferBytes(0)
, _mp3Encoding(0)
{
    
}

AudioCache::AudioCache(AudioCache& cache)
{
    _pcmData = cache._pcmData;
    _pcmDataSize = cache._pcmDataSize;
    _bytesOfRead = cache._bytesOfRead;
    _alBufferReady = cache._alBufferReady;
    _fileFormat = cache._fileFormat;
    _queBufferFrames = cache._queBufferFrames;
    _queBufferBytes = cache._queBufferBytes;
    _mp3Encoding = cache._mp3Encoding;
}

AudioCache::~AudioCache()
{
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

     OggVorbis_File* vf = nullptr;
     mpg123_handle* mpg123handle = nullptr;
     long totalFrames = 0;

     switch (_fileFormat)
     {
     case FileFormat::OGG:
         {
             vf = new OggVorbis_File;
             if (ov_fopen(_fileFullPath.c_str(), vf)){
                 log("Input does not appear to be an Ogg bitstream.\n");
                 goto ExitThread;
             }

             auto vi = ov_info(vf,-1);
             totalFrames = (long)ov_pcm_total(vf,-1);
             _bytesPerFrame =  vi->channels * 2;
             _alBufferFormat = (vi->channels > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
             _sampleRate = vi->rate;
             _pcmDataSize = totalFrames * _bytesPerFrame;
             _duration = 1.0f * totalFrames / _sampleRate;
         }
         break;
     case FileFormat::MP3:
         {
             long rate = 0;
             int error = MPG123_OK;
             mpg123handle = mpg123_new(nullptr, &error);
             if (!mpg123handle){
                 log("Basic setup goes wrong: %s", mpg123_plain_strerror(error));
                 goto ExitThread;
             }

             if (mpg123_open(mpg123handle,_fileFullPath.c_str()) != MPG123_OK || 
                 mpg123_getformat(mpg123handle, &rate, &_channels, &_mp3Encoding) != MPG123_OK) {
                 log("Trouble with mpg123: %s\n", mpg123_strerror(mpg123handle) );
                 goto ExitThread;
             }

             if (_mp3Encoding == MPG123_ENC_SIGNED_16){
                 _bytesPerFrame = 2 * _channels;
             }
             else if (_mp3Encoding == MPG123_ENC_FLOAT_32){
                 _bytesPerFrame = 4 * _channels;
             }
             else{
                 log("Bad encoding: 0x%x!\n", _mp3Encoding);
                 goto ExitThread;
             }
             
             _alBufferFormat = (_channels > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
             _sampleRate = rate;
             
             /* Ensure that this output format will not change (it could, when we allow it). */
             mpg123_format_none(mpg123handle);
             mpg123_format(mpg123handle, rate, _channels, _mp3Encoding);
             /* Ensure that we can get accurate length by call mpg123_length */
             mpg123_scan(mpg123handle);

             auto framesLength = mpg123_length(mpg123handle);
             totalFrames = framesLength;
             _pcmDataSize = totalFrames * _bytesPerFrame;
             _duration = 1.0f * totalFrames / _sampleRate;
         }
         break;
     case FileFormat::UNKNOWN:
     default:
         break;
     }
    
    if (_pcmDataSize <= PCMDATA_CACHEMAXSIZE)
    {
        _pcmData = malloc(_pcmDataSize);
        auto alError = alGetError();
        alGenBuffers(1, &_alBufferId);
        alError = alGetError();
        if (alError != AL_NO_ERROR) {
            log("%s: attaching audio to buffer fail: %x\n", __FUNCTION__, alError);
            goto ExitThread;
        }

        switch (_fileFormat)
        {
        case FileFormat::OGG:
            {
                int current_section;
                unsigned int currPos = 0;
                long readRet = 0;
                do 
                {
                    readRet = ov_read(vf,(char*)_pcmData + _bytesOfRead,4096,0,2,1,&current_section);
                    if (readRet > 0){
                        _bytesOfRead += readRet;
                    }
                } while (_bytesOfRead < _pcmDataSize);

                _alBufferReady = true;
                _bytesOfRead = _pcmDataSize;
                break;
            }
        case FileFormat::MP3:
            {
                size_t done = 0;
                auto err = mpg123_read(mpg123handle,(unsigned char*)_pcmData, _pcmDataSize,&done);
                if (err == MPG123_ERR){
                    log("Trouble with mpg123: %s\n", mpg123_strerror(mpg123handle) );
                    goto ExitThread;
                }
                if (err == MPG123_DONE || err == MPG123_OK){
                    _alBufferReady = true;
                    _pcmDataSize = done;
                    _bytesOfRead = done;
                }
            }
            break;     
        case FileFormat::UNKNOWN:
        default:
            break;
        }
        alBufferData(_alBufferId,_alBufferFormat,_pcmData,_pcmDataSize,_sampleRate);
    } 
    else{
        _queBufferFrames = _sampleRate * QUEUEBUFFER_TIME_STEP;
        _queBufferBytes = _queBufferFrames * _bytesPerFrame;

        for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
            _queBuffers[index] = (char*)malloc(_queBufferBytes);
            
            switch (_fileFormat){
            case FileFormat::MP3:
                {
                    size_t done = 0;
                    mpg123_read(mpg123handle,(unsigned char*)_queBuffers[index], _queBufferBytes,&done);
                    _queBufferSize[index] = done;
                    _bytesOfRead += done;
                }
                break;
            case FileFormat::OGG:
                {
                    int current_section;
                    auto readRet = ov_read(vf,_queBuffers[index],_queBufferBytes,0,2,1,&current_section);
                    _queBufferSize[index] = readRet;
                }
                break;
            }
        }
    }
    
ExitThread:
    switch (_fileFormat)
    {
    case FileFormat::OGG:
        ov_clear(vf);
        delete vf;
        break;
    case FileFormat::MP3:
        mpg123_close(mpg123handle);
        mpg123_delete(mpg123handle);
        break;
    case FileFormat::UNKNOWN:
    default:
        break;
    }
    
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

#endif
