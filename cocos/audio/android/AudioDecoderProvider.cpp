/****************************************************************************
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

#define LOG_TAG "AudioDecoderProvider"

#include "audio/android/AudioDecoderProvider.h"
#include "audio/android/AudioDecoderSLES.h"
#include "audio/android/AudioDecoderOgg.h"
#include "audio/android/AudioDecoderMp3.h"
#include "audio/android/AudioDecoderWav.h"
#include "platform/CCFileUtils.h"

namespace cocos2d {

AudioDecoder* AudioDecoderProvider::createAudioDecoder(SLEngineItf engineItf, const std::string &url, int bufferSizeInFrames, int sampleRate, const FdGetterCallback &fdGetterCallback)
{
    AudioDecoder* decoder = nullptr;
    std::string extension = FileUtils::getInstance()->getFileExtension(url);
    ALOGV("url:%s, extension:%s", url.c_str(), extension.c_str());
    if (extension == ".ogg")
    {
        decoder = new AudioDecoderOgg();
        if (!decoder->init(url, sampleRate))
        {
            delete decoder;
            decoder = nullptr;
        }
    }
    else if (extension == ".mp3")
    {
        decoder = new AudioDecoderMp3();
        if (!decoder->init(url, sampleRate))
        {
            delete decoder;
            decoder = nullptr;
        }
    }
    else if (extension == ".wav")
    {
        decoder = new AudioDecoderWav();
        if (!decoder->init(url, sampleRate))
        {
            delete decoder;
            decoder = nullptr;
        }
    }
    else
    {
        auto slesDecoder = new AudioDecoderSLES();
        if (slesDecoder->init(engineItf, url, bufferSizeInFrames, sampleRate, fdGetterCallback))
        {
            decoder = slesDecoder;
        }
        else
        {
            delete slesDecoder;
        }
    }

    return decoder;
}

void AudioDecoderProvider::destroyAudioDecoder(AudioDecoder** decoder)
{
    if (decoder != nullptr && *decoder != nullptr)
    {
        delete (*decoder);
        (*decoder) = nullptr;
    }
}

} // namespace cocos2d {