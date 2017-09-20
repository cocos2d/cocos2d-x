/****************************************************************************
Copyright (c) 2017 Chukong Technologies Inc.

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

#define LOG_TAG "AudioDecoderWav"

#include "audio/android/AudioDecoderWav.h"
#include "audio/android/tinysndfile.h"
#include "platform/CCFileUtils.h"

namespace cocos2d { namespace experimental {

AudioDecoderWav::AudioDecoderWav()
{
    ALOGV("Create AudioDecoderWav");
}

AudioDecoderWav::~AudioDecoderWav()
{

}

void* AudioDecoderWav::onWavOpen(const char* path, void* user)
{
    return user;
}

int AudioDecoderWav::onWavSeek(void* datasource, long offset, int whence)
{
    return AudioDecoder::fileSeek(datasource, (int64_t) offset, whence);
}

int AudioDecoderWav::onWavClose(void* datasource)
{
}

bool AudioDecoderWav::decodeToPcm()
{
    _fileData = FileUtils::getInstance()->getDataFromFile(_url);
    if (_fileData.isNull())
    {
        return false;
    }

    SF_INFO info;

    snd_callbacks cb;
    cb.open = onWavOpen;
    cb.read = AudioDecoder::fileRead;
    cb.seek = onWavSeek;
    cb.close = onWavClose;
    cb.tell = AudioDecoder::fileTell;

    SNDFILE* handle = NULL;
    bool ret = false;
    do
    {
        handle = sf_open_read(_url.c_str(), &info, &cb, this);
        if (handle == nullptr)
            break;

        if (info.frames == 0)
            break;

        ALOGD("wav info: frames: %d, samplerate: %d, channels: %d, format: %d", info.frames, info.samplerate, info.channels, info.format);
        size_t bufSize = sizeof(short) * info.frames * info.channels;
        unsigned char* buf = (unsigned char*)malloc(bufSize);
        sf_count_t readFrames = sf_readf_short(handle, (short*)buf, info.frames);
        assert(readFrames == info.frames);

        _result.pcmBuffer->insert(_result.pcmBuffer->end(), buf, buf + bufSize);
        _result.numChannels = info.channels;
        _result.sampleRate = info.samplerate;
        _result.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.channelMask = _result.numChannels == 1 ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);
        _result.endianness = SL_BYTEORDER_LITTLEENDIAN;
        _result.numFrames = info.frames;
        _result.duration = 1.0f * info.frames / _result.sampleRate;

        free(buf);
        ret = true;
    } while (false);

    if (handle != NULL)
        sf_close(handle);

    return ret;
}

}} // namespace cocos2d { namespace experimental {