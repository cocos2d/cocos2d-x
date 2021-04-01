/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#define LOG_TAG "AudioDecoderOgg"

#include "audio/android/AudioDecoderOgg.h"
#include "platform/CCFileUtils.h"

namespace cocos2d {

AudioDecoderOgg::AudioDecoderOgg()
{
    ALOGV("Create AudioDecoderOgg");
}

AudioDecoderOgg::~AudioDecoderOgg()
{

}

int AudioDecoderOgg::fseek64Wrap(void* datasource, ogg_int64_t off, int whence)
{
    return AudioDecoder::fileSeek(datasource, (long)off, whence);
}

bool AudioDecoderOgg::decodeToPcm()
{
    _fileData = FileUtils::getInstance()->getDataFromFile(_url);
    if (_fileData.isNull())
    {
        return false;
    }

    ov_callbacks callbacks;
    callbacks.read_func = AudioDecoder::fileRead;
    callbacks.seek_func = AudioDecoderOgg::fseek64Wrap;
    callbacks.close_func = AudioDecoder::fileClose;
    callbacks.tell_func = AudioDecoder::fileTell;

    _fileCurrPos = 0;

    OggVorbis_File vf;
    int ret = ov_open_callbacks(this, &vf, NULL, 0, callbacks);
    if (ret != 0)
    {
        ALOGE("Open file error, file: %s, ov_open_callbacks return %d", _url.c_str(), ret);
        return false;
    }
    // header
    auto vi = ov_info(&vf, -1);

    uint32_t pcmSamples = (uint32_t) ov_pcm_total(&vf, -1);

    uint32_t bufferSize = pcmSamples * vi->channels * sizeof(short);
    char* pcmBuffer = (char*)malloc(bufferSize);
    memset(pcmBuffer, 0, bufferSize);

    int currentSection = 0;
    long curPos = 0;
    long readBytes = 0;

    do
    {
        readBytes = ov_read(&vf, pcmBuffer + curPos, 4096, &currentSection);
        curPos += readBytes;
    } while (readBytes > 0);

    if (curPos > 0)
    {
        _result.pcmBuffer->insert(_result.pcmBuffer->end(), pcmBuffer, pcmBuffer + bufferSize);
        _result.numChannels = vi->channels;
        _result.sampleRate = vi->rate;
        _result.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.channelMask = vi->channels == 1 ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);
        _result.endianness = SL_BYTEORDER_LITTLEENDIAN;
        _result.numFrames = pcmSamples;
        _result.duration = 1.0f * pcmSamples / vi->rate;
    }
    else
    {
        ALOGE("ov_read returns 0 byte!");
    }

    ov_clear(&vf);
    free(pcmBuffer);

    return (curPos > 0);
}

} // namespace cocos2d {