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

#define LOG_TAG "AudioDecoderMp3"

#include "audio/android/AudioDecoderMp3.h"
#include "audio/android/mp3reader.h"
#include "platform/CCFileUtils.h"

namespace cocos2d {

AudioDecoderMp3::AudioDecoderMp3()
{
    ALOGV("Create AudioDecoderMp3");
}

AudioDecoderMp3::~AudioDecoderMp3()
{

}

bool AudioDecoderMp3::decodeToPcm()
{
    _fileData = FileUtils::getInstance()->getDataFromFile(_url);
    if (_fileData.isNull())
    {
        return false;
    }

    mp3_callbacks callbacks;
    callbacks.read = AudioDecoder::fileRead;
    callbacks.seek = AudioDecoder::fileSeek;
    callbacks.close = AudioDecoder::fileClose;
    callbacks.tell = AudioDecoder::fileTell;

    int numChannels = 0;
    int sampleRate = 0;
    int numFrames = 0;
    
    if (EXIT_SUCCESS == decodeMP3(&callbacks, this, *_result.pcmBuffer, &numChannels, &sampleRate, &numFrames)
        && numChannels > 0 && sampleRate > 0 && numFrames > 0)
    {
        _result.numChannels = numChannels;
        _result.sampleRate = sampleRate;
        _result.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
        _result.channelMask = numChannels == 1 ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);
        _result.endianness = SL_BYTEORDER_LITTLEENDIAN;
        _result.numFrames = numFrames;
        _result.duration = 1.0f * numFrames / sampleRate;

        std::string info = _result.toString();
        ALOGI("Original audio info: %s, total size: %d", info.c_str(), (int)_result.pcmBuffer->size());
        return true;
    }

    ALOGE("Decode MP3 (%s) failed, channels: %d, rate: %d, frames: %d", _url.c_str(), numChannels, sampleRate, numFrames);
    return false;
}

} // namespace cocos2d {