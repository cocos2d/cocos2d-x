/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#define LOG_TAG "AudioDecoderProvider"

#include "AudioDecoderProvider.h"
#include "AudioDecoderMp3.h"
#include "AudioDecoderOgg.h"
#include "AudioDecoderSLES.h"
#include "AudioDecoderWav.h"
#include "platform/CCFileUtils.h"

namespace cocos2d { namespace experimental {

cocos2d::experimental::AudioDecoder *AudioDecoderProvider::createAudioDecoder(SLEngineItf engineItf, const std::string &url, int bufferSizeInFrames, int sampleRate, const FdGetterCallback &fdGetterCallback) {
    AudioDecoder *decoder = nullptr;
    std::string extension = FileUtils::getInstance()->getFileExtension(url);
    ALOGE("url:%s, extension:%s, sampleRate:%d", url.c_str(), extension.c_str(), sampleRate);
    if (extension == ".ogg") {
        decoder = new AudioDecoderOgg();
        if (!decoder->init(url, sampleRate)) {
            delete decoder;
            decoder = nullptr;
        }
    } else if (extension == ".mp3") {
        decoder = new AudioDecoderMp3();
        if (!decoder->init(url, sampleRate)) {
            delete decoder;
            decoder = nullptr;
        }
    } else if (extension == ".wav") {
        decoder = new AudioDecoderWav();
        if (!decoder->init(url, sampleRate)) {
            delete decoder;
            decoder = nullptr;
        }
    } else {
        auto slesDecoder = new AudioDecoderSLES();
        if (slesDecoder->init(engineItf, url, bufferSizeInFrames, sampleRate, fdGetterCallback)) {
            decoder = slesDecoder;
        } else {
            delete slesDecoder;
        }
    }

    return decoder;
}

void AudioDecoderProvider::destroyAudioDecoder(AudioDecoder **decoder) {
    if (decoder != nullptr && *decoder != nullptr) {
        delete (*decoder);
        (*decoder) = nullptr;
    }
}

}} // namespace cocos2d { namespace experimental