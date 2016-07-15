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

#include "audio/android/AudioBufferProvider.h"

#include <stddef.h>
#include <stdio.h>

namespace cocos2d { namespace experimental {

class PcmBufferProvider : public AudioBufferProvider
{
public:
    PcmBufferProvider();
    bool init(const void *addr, size_t frames, size_t frameSize);
    virtual status_t getNextBuffer(Buffer *buffer, int64_t pts = kInvalidPTS) override ;
    virtual void releaseBuffer(Buffer *buffer) override ;
    void reset();

protected:
    const void *_addr;      // base address
    size_t _numFrames; // total frames
    size_t _frameSize; // size of each frame in bytes
    size_t _nextFrame; // index of next frame to provide
    size_t _unrel;     // number of frames not yet released
};

}} // namespace cocos2d { namespace experimental {
