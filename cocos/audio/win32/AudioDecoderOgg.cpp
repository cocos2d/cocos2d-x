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

#include "audio/win32/AudioDecoderOgg.h"
#include "audio/win32/AudioMacros.h"
#include "platform/CCFileUtils.h"

#define LOG_TAG "AudioDecoderOgg"

namespace cocos2d {

    AudioDecoderOgg::AudioDecoderOgg()
    {
    }

    AudioDecoderOgg::~AudioDecoderOgg()
    {
        close();
    }

    bool AudioDecoderOgg::open(const char* path)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
        if (0 == ov_fopen(FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), &_vf))
        {
            // header
            vorbis_info* vi = ov_info(&_vf, -1);
            _sampleRate = static_cast<uint32_t>(vi->rate);
            _channelCount = vi->channels;
            _bytesPerFrame = vi->channels * sizeof(short);
            _totalFrames = static_cast<uint32_t>(ov_pcm_total(&_vf, -1));
            _isOpened = true;
            return true;
        }
        return false;
    }

    void AudioDecoderOgg::close()
    {
        if (isOpened())
        {
            ov_clear(&_vf);
            _isOpened = false;
        }
    }

    uint32_t AudioDecoderOgg::read(uint32_t framesToRead, char* pcmBuf)
    {
        int currentSection = 0;
        int bytesToRead = framesToRead * _bytesPerFrame;
        long bytesRead = ov_read(&_vf, pcmBuf, bytesToRead, 0, 2, 1, &currentSection);
        return static_cast<uint32_t>(bytesRead / _bytesPerFrame);
    }

    bool AudioDecoderOgg::seek(uint32_t frameOffset)
    {
        return 0 == ov_pcm_seek(&_vf, frameOffset);
    }

    uint32_t AudioDecoderOgg::tell() const
    {
        return static_cast<uint32_t>(ov_pcm_tell(const_cast<OggVorbis_File*>(&_vf)));
    }

} // namespace cocos2d {
