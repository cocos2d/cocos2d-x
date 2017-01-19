/****************************************************************************
Copyright (c) 2016-2017 Chukong Technologies Inc.

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

#define LOG_TAG "AudioDecoder"

#include "audio/android/AudioDecoder.h"
#include "audio/android/AudioResampler.h"
#include "audio/android/PcmBufferProvider.h"
#include "audio/android/AudioResampler.h"

#include <thread>
#include <chrono>

namespace cocos2d { namespace experimental {

size_t AudioDecoder::fileRead(void* ptr, size_t size, size_t nmemb, void* datasource)
{
    AudioDecoder* thiz = (AudioDecoder*)datasource;
    ssize_t toReadBytes = std::min((ssize_t)(thiz->_fileData.getSize() - thiz->_fileCurrPos), (ssize_t)(nmemb * size));
    if (toReadBytes > 0)
    {
        memcpy(ptr, (unsigned char*) thiz->_fileData.getBytes() + thiz->_fileCurrPos, toReadBytes);
        thiz->_fileCurrPos += toReadBytes;
    }
    // ALOGD("File size: %d, After fileRead _fileCurrPos %d", (int)thiz->_fileData.getSize(), thiz->_fileCurrPos);
    return toReadBytes;
}

int AudioDecoder::fileSeek(void* datasource, int64_t offset, int whence)
{
    AudioDecoder* thiz = (AudioDecoder*)datasource;
    if (whence == SEEK_SET)
        thiz->_fileCurrPos = offset;
    else if (whence == SEEK_CUR)
        thiz->_fileCurrPos = thiz->_fileCurrPos + offset;
    else if (whence == SEEK_END)
        thiz->_fileCurrPos = thiz->_fileData.getSize();
    return 0;
}

int AudioDecoder::fileClose(void* datasource)
{
    return 0;
}

long AudioDecoder::fileTell(void* datasource)
{
    AudioDecoder* thiz = (AudioDecoder*)datasource;
    return (long) thiz->_fileCurrPos;
}

AudioDecoder::AudioDecoder()
        : _fileCurrPos(0), _sampleRate(-1)
{
    auto pcmBuffer = std::make_shared<std::vector<char>>();
    pcmBuffer->reserve(4096);
    _result.pcmBuffer = pcmBuffer;
}

AudioDecoder::~AudioDecoder()
{
    ALOGV("~AudioDecoder() %p", this);
}

bool AudioDecoder::init(const std::string &url, int sampleRate)
{
    _url = url;
    _sampleRate = sampleRate;
    return true;
}

bool AudioDecoder::start()
{
    auto oldTime = clockNow();
    auto nowTime = oldTime;
    bool ret;
    do
    {
        ret = decodeToPcm();
        if (!ret) 
        {
            ALOGE("decodeToPcm (%s) failed!", _url.c_str());
            break;
        }

        nowTime = clockNow();
        ALOGD("Decoding (%s) to pcm data wasted %fms", _url.c_str(), intervalInMS(oldTime, nowTime));
        oldTime = nowTime;

        ret = resample();
        if (!ret) 
        {
            ALOGE("resample (%s) failed!", _url.c_str());
            break;
        }

        nowTime = clockNow();
        ALOGD("Resampling (%s) wasted %fms", _url.c_str(), intervalInMS(oldTime, nowTime));
        oldTime = nowTime;

        ret = interleave();
        if (!ret) 
        {
            ALOGE("interleave (%s) failed!", _url.c_str());
            break;
        }
        
        nowTime = clockNow();
        ALOGD("Interleave (%s) wasted %fms", _url.c_str(), intervalInMS(oldTime, nowTime));

    } while(false);

    ALOGV_IF(!ret, "%s returns false, decode (%s)", __FUNCTION__, _url.c_str());
    return ret;
}

bool AudioDecoder::resample()
{
    if (_result.sampleRate == _sampleRate)
    {
        ALOGI("No need to resample since the sample rate (%d) of the decoded pcm data is the same as the device output sample rate",
              _sampleRate);
        return true;
    }

    ALOGV("Resample: %d --> %d", _result.sampleRate, _sampleRate);

    auto r = _result;
    PcmBufferProvider provider;
    provider.init(r.pcmBuffer->data(), r.numFrames, r.pcmBuffer->size() / r.numFrames);

    const int outFrameRate = _sampleRate;
    int outputChannels = 2;
    size_t outputFrameSize = outputChannels * sizeof(int32_t);
    size_t outputFrames = ((int64_t) r.numFrames * outFrameRate) / r.sampleRate;
    size_t outputSize = outputFrames * outputFrameSize;
    void *outputVAddr = malloc(outputSize);

    auto resampler = AudioResampler::create(AUDIO_FORMAT_PCM_16_BIT, r.numChannels, outFrameRate,
                                            AudioResampler::MED_QUALITY);
    resampler->setSampleRate(r.sampleRate);
    resampler->setVolume(AudioResampler::UNITY_GAIN_FLOAT, AudioResampler::UNITY_GAIN_FLOAT);

    memset(outputVAddr, 0, outputSize);

    ALOGV("resample() %zu output frames", outputFrames);

    std::vector<int> Ovalues;

    if (Ovalues.empty())
    {
        Ovalues.push_back(outputFrames);
    }
    for (size_t i = 0, j = 0; i < outputFrames;)
    {
        size_t thisFrames = Ovalues[j++];
        if (j >= Ovalues.size())
        {
            j = 0;
        }
        if (thisFrames == 0 || thisFrames > outputFrames - i)
        {
            thisFrames = outputFrames - i;
        }
        int outFrames = resampler->resample((int *) outputVAddr + outputChannels * i, thisFrames,
                                            &provider);
        ALOGV("outFrames: %d", outFrames);
        i += thisFrames;
    }

    ALOGV("resample() complete");

    resampler->reset();

    ALOGV("reset() complete");

    delete resampler;
    resampler = nullptr;

    // mono takes left channel only (out of stereo output pair)
    // stereo and multichannel preserve all channels.

    int channels = r.numChannels;
    int32_t *out = (int32_t *) outputVAddr;
    int16_t *convert = (int16_t *) malloc(outputFrames * channels * sizeof(int16_t));

    const int volumeShift = 12; // shift requirement for Q4.27 to Q.15
    // round to half towards zero and saturate at int16 (non-dithered)
    const int roundVal = (1 << (volumeShift - 1)) - 1; // volumePrecision > 0

    for (size_t i = 0; i < outputFrames; i++)
    {
        for (int j = 0; j < channels; j++)
        {
            int32_t s = out[i * outputChannels + j] + roundVal; // add offset here
            if (s < 0)
            {
                s = (s + 1) >> volumeShift; // round to 0
                if (s < -32768)
                {
                    s = -32768;
                }
            } else
            {
                s = s >> volumeShift;
                if (s > 32767)
                {
                    s = 32767;
                }
            }
            convert[i * channels + j] = int16_t(s);
        }
    }

    // Reset result
    _result.numFrames = outputFrames;
    _result.sampleRate = outFrameRate;

    auto buffer = std::make_shared<std::vector<char>>();
    buffer->reserve(_result.numFrames * _result.bitsPerSample / 8);
    buffer->insert(buffer->end(), (char *) convert,
                   (char *) convert + outputFrames * channels * sizeof(int16_t));
    _result.pcmBuffer = buffer;

    ALOGV("pcm buffer size: %d", (int)_result.pcmBuffer->size());

    free(convert);
    free(outputVAddr);
    return true;
}

//-----------------------------------------------------------------
bool AudioDecoder::interleave()
{
    if (_result.numChannels == 2)
    {
        ALOGI("Audio channel count is 2, no need to interleave");
        return true;
    }
    else if (_result.numChannels == 1)
    {
        // If it's a mono audio, try to compose a fake stereo buffer
        size_t newBufferSize = _result.pcmBuffer->size() * 2;
        auto newBuffer = std::make_shared<std::vector<char>>();
        newBuffer->reserve(newBufferSize);
        size_t totalFrameSizeInBytes = (size_t) (_result.numFrames * _result.bitsPerSample / 8);

        for (size_t i = 0; i < totalFrameSizeInBytes; i += 2)
        {
            // get one short value
            char byte1 = _result.pcmBuffer->at(i);
            char byte2 = _result.pcmBuffer->at(i + 1);

            // push two short value
            for (int j = 0; j < 2; ++j)
            {
                newBuffer->push_back(byte1);
                newBuffer->push_back(byte2);
            }
        }
        _result.numChannels = 2;
        _result.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
        _result.pcmBuffer = newBuffer;
        return true;
    }

    ALOGE("Audio channel count (%d) is wrong, interleave only supports converting mono to stereo!", _result.numChannels);
    return false;
}

}} // namespace cocos2d { namespace experimental {
