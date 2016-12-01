/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

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

#pragma once

#include <stdint.h>
#import <AudioToolbox/ExtendedAudioFile.h>

namespace cocos2d { namespace experimental {

class AudioDecoder
{
public:
    static const uint32_t INVALID_FRAME_INDEX = UINT32_MAX;

    AudioDecoder();
    ~AudioDecoder();

    bool open(const char* path);
    bool isOpened();
    void close();

    uint32_t read(uint32_t framesToRead, char* pcmBuf);
    bool seek(uint32_t frameIndex);
    uint32_t tell();

    uint32_t getTotalFrames();
    uint32_t getBytesPerFrame();
    uint32_t getSampleRate();
    uint32_t getChannelCount();

private:
    bool _isOpened;
    ExtAudioFileRef _extRef;
    uint32_t _totalFrames;
    uint32_t _bytesPerFrame;
    uint32_t _sampleRate;
    uint32_t _channelCount;

    AudioStreamBasicDescription _outputFormat;
};

}} // namespace cocos2d { namespace experimental {
