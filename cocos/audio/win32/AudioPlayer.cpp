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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "audio/win32/AudioPlayer.h"
#include "audio/win32/AudioCache.h"
#include "base/CCConsole.h"
#include "platform/CCFileUtils.h"
#include "mpg123.h"
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

using namespace cocos2d::experimental;

AudioPlayer::AudioPlayer()
    : _exitThread(false)
    , _timeDirty(false)
    , _streamingSource(false)
    , _currTime(0.0f)
    , _finishCallbak(nullptr)
    , _ready(false)
    , _audioCache(nullptr)
    , _readForRemove(false)
{

}

AudioPlayer::AudioPlayer(const AudioPlayer& player)
{
    _exitThread = player._exitThread;
    _timeDirty = player._timeDirty;
    _streamingSource = player._streamingSource;
    _currTime = player._currTime;
    _finishCallbak = player._finishCallbak;
    _ready = player._ready;
    _audioCache = player._audioCache;
    _readForRemove = player._readForRemove;
}

AudioPlayer::~AudioPlayer()
{
    if (_audioCache && _audioCache->_queBufferFrames > 0) {
        alDeleteBuffers(QUEUEBUFFER_NUM, _bufferIds);
    }
}

void AudioPlayer::notifyExitThread()
{
    if (_audioCache && _audioCache->_queBufferFrames > 0) {
        std::unique_lock<std::mutex> lk(_sleepMutex);
        _exitThread = true;
        _sleepCondition.notify_all();
    }
}

bool AudioPlayer::play2d(AudioCache* cache)
{
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
        _streamingSource = true;
        alSourcei(_alSource, AL_LOOPING, AL_FALSE);

        auto alError = alGetError();
        alGenBuffers(QUEUEBUFFER_NUM, _bufferIds);
        alError = alGetError();
        if (alError == AL_NO_ERROR) {
            for (int index = 0; index < QUEUEBUFFER_NUM; ++index) {
                alBufferData(_bufferIds[index], _audioCache->_alBufferFormat, _audioCache->_queBuffers[index], _audioCache->_queBufferSize[index], _audioCache->_sampleRate);
            }
            alSourceQueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
        }
        else {
            ALOGE("%s:alGenBuffers error code:%x", __FUNCTION__,alError);
            return false;
        }
    }

    if (_streamingSource)
    {
        _rotateBufferThread = std::thread(&AudioPlayer::rotateBufferThread, this, _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1);
        _rotateBufferThread.detach();
    }
    else
    {
        alSourcePlay(_alSource);

        auto alError = alGetError();
        if (alError != AL_NO_ERROR) {
            ALOGE("%s:alSourcePlay error code:%x\n", __FUNCTION__, alError);
            return false;
        }

        _ready = true;
    }

    return true;
}

int AudioPlayer::readPcmData(char* buffer, int bufferSize, const std::function<int/*readBytes*/(char* /*buf*/, int /*bytesToRead*/)>& fileReader)
{
    assert(buffer != nullptr && bufferSize > 0);

    int readBytes = 0;
    int readBytesOnce = 0;
    int remainBytes = bufferSize;
    do
    {
        readBytesOnce = fileReader(buffer + readBytes, remainBytes);
        if (readBytesOnce > 0)
        {
            readBytes += readBytesOnce;
            remainBytes -= readBytesOnce;
        }
    } while (readBytesOnce > 0 && readBytes < bufferSize);

    return readBytes;
}

void AudioPlayer::rotateBufferThread(int offsetFrame)
{
    ALint sourceState;
    ALint bufferProcessed = 0;
    mpg123_handle* mpg123handle = nullptr;
    OggVorbis_File* vorbisFile = nullptr;

    std::function<int(char*, int)> fileReader = nullptr;
    std::function<void(int)> fileSeeker = nullptr;

    auto audioFileFormat = _audioCache->_fileFormat;
    char* tmpBuffer = (char*)malloc(_audioCache->_queBufferBytes);

    switch (audioFileFormat)
    {
    case AudioCache::FileFormat::MP3:
        {
            int error = MPG123_OK;
            mpg123handle = mpg123_new(nullptr, &error);
            if (!mpg123handle){
                ALOGE("Basic setup goes wrong: %s", mpg123_plain_strerror(error));
                goto ExitBufferThread;
            }
            long rate = 0;
            int channels = 0;
            int mp3Encoding = 0;
            if (mpg123_open(mpg123handle,_audioCache->_fileFullPath.c_str()) != MPG123_OK
                || mpg123_getformat(mpg123handle, &rate, &channels, &mp3Encoding) != MPG123_OK){
                ALOGE("Trouble with mpg123: %s\n", mpg123_strerror(mpg123handle) );
                goto ExitBufferThread;
            }

            /* Ensure that this output format will not change (it could, when we allow it). */
            mpg123_format_none(mpg123handle);
            mpg123_format(mpg123handle, _audioCache->_sampleRate, _audioCache->_channels, _audioCache->_mp3Encoding);

            if (offsetFrame != 0) {
                mpg123_seek(mpg123handle,offsetFrame,SEEK_SET);
            }
            break;
        }
    case AudioCache::FileFormat::OGG:
        {
            vorbisFile = new OggVorbis_File;
            int openCode;
            if (openCode = ov_fopen(FileUtils::getInstance()->getSuitableFOpen(_audioCache->_fileFullPath).c_str(), vorbisFile)){
                ALOGE("Input does not appear to be an Ogg bitstream: %s. Code: 0x%x\n", _audioCache->_fileFullPath.c_str(), openCode);
                goto ExitBufferThread;
            }
            if (offsetFrame != 0) {
                ov_pcm_seek(vorbisFile,offsetFrame);
            }
            break;
        }
    default:
        break;
    }

    alSourcePlay(_alSource);

    if (audioFileFormat == AudioCache::FileFormat::MP3)
    {
        fileReader = [&](char* buffer, int bufferSize) -> int {
            size_t ret = 0;
            mpg123_read(mpg123handle, (unsigned char*)buffer, bufferSize, &ret);
            return ret;
        };

        fileSeeker = [&](int pos) {
            mpg123_seek(mpg123handle, pos, SEEK_SET);
        };
    }
    else if (audioFileFormat == AudioCache::FileFormat::OGG)
    {
        fileReader = [&](char* buffer, int bufferSize) -> int {
            int current_section = 0;
            return ov_read(vorbisFile, buffer, bufferSize, 0, 2, 1, &current_section);
        };

        fileSeeker = [&](int pos) {
            ov_pcm_seek(vorbisFile, pos);
        };
    }

    while (!_exitThread) {
        alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
        if (sourceState == AL_PLAYING) {
            _ready = true;

            alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
            while (bufferProcessed > 0) {
                bufferProcessed--;
                if (_timeDirty) {
                    _timeDirty = false;
                    offsetFrame = _currTime * _audioCache->_sampleRate;
                    fileSeeker(offsetFrame);
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

                int readRet = readPcmData(tmpBuffer, _audioCache->_queBufferBytes, fileReader);
                if (readRet <= 0) {
                    if (_loop) {
                        fileSeeker(0);
                        readRet = readPcmData(tmpBuffer, _audioCache->_queBufferBytes, fileReader);
                    }
                    else {
                        _exitThread = true;
                        break;
                    }
                }
                else
                {
                    _audioCache->_bytesOfRead += readRet;
                }

                //ALOGV("readRet: %d, queBufferBytes: %d", (int)readRet, _audioCache->_queBufferBytes);
                ALuint bid;
                alSourceUnqueueBuffers(_alSource, 1, &bid);
                CHECK_AL_ERROR_DEBUG();
                alBufferData(bid, _audioCache->_alBufferFormat, tmpBuffer, readRet, _audioCache->_sampleRate);
                CHECK_AL_ERROR_DEBUG();
                alSourceQueueBuffers(_alSource, 1, &bid);
                CHECK_AL_ERROR_DEBUG();
            }
        }

        std::unique_lock<std::mutex> lk(_sleepMutex);
        if (_exitThread)
        {
            ALOGV("thread exit...");
            break;
        }
        
        _sleepCondition.wait_for(lk,std::chrono::milliseconds(35));
    }
ExitBufferThread:
    switch (audioFileFormat)
    {
    case AudioCache::FileFormat::OGG:
        ov_clear(vorbisFile);
        delete vorbisFile;
        break;
    case AudioCache::FileFormat::MP3:
        mpg123_close(mpg123handle);
        mpg123_delete(mpg123handle);
        break;
    case AudioCache::FileFormat::UNKNOWN:
    default:
        break;
    }
    free(tmpBuffer);
    _readForRemove = true;
    ALOGV("%s exited.\n", __FUNCTION__);
}

bool AudioPlayer::setLoop(bool loop)
{
    if (!_exitThread ) {
        _loop = loop;
        return true;
    }

    return false;
}

bool AudioPlayer::setTime(float time)
{
    if (!_exitThread && time >= 0.0f && time < _audioCache->_duration) {
        _currTime = time;
        _timeDirty = true;
        return true;
    }
    return false;
}

#endif
