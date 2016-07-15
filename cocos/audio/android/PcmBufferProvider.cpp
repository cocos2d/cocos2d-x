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

#define LOG_TAG "PcmBufferProvider"

#include "audio/android/cutils/log.h"
#include "audio/android/PcmBufferProvider.h"

//#define VERY_VERY_VERBOSE_LOGGING
#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(a...) do { } while (0)
#endif

namespace cocos2d { namespace experimental {

PcmBufferProvider::PcmBufferProvider()
        : _addr(nullptr)
        , _numFrames(0)
        , _frameSize(0)
        , _nextFrame(0)
        , _unrel(0)
{
    
}

bool PcmBufferProvider::init(const void *addr, size_t frames, size_t frameSize)
{
    _addr = addr;
    _numFrames = frames;
    _frameSize = frameSize;
    _nextFrame = 0;
    _unrel = 0;
    return true;
}

status_t PcmBufferProvider::getNextBuffer(Buffer *buffer,
                                          int64_t pts/* = kInvalidPTS*/) {
    (void) pts; // suppress warning
    size_t requestedFrames = buffer->frameCount;
    if (requestedFrames > _numFrames - _nextFrame) {
        buffer->frameCount = _numFrames - _nextFrame;
    }

    ALOGVV("getNextBuffer() requested %zu frames out of %zu frames available,"
                  " and returned %zu frames",
              requestedFrames, (size_t) (_numFrames - _nextFrame), buffer->frameCount);

    _unrel = buffer->frameCount;
    if (buffer->frameCount > 0) {
        buffer->raw = (char *) _addr + _frameSize * _nextFrame;
        return NO_ERROR;
    } else {
        buffer->raw = NULL;
        return NOT_ENOUGH_DATA;
    }
}

void PcmBufferProvider::releaseBuffer(Buffer *buffer) {
    if (buffer->frameCount > _unrel) {
        ALOGVV("ERROR releaseBuffer() released %zu frames but only %zu available "
                "to release", buffer->frameCount, _unrel);
        _nextFrame += _unrel;
        _unrel = 0;
    } else {
        ALOGVV("releaseBuffer() released %zu frames out of %zu frames available "
                           "to release", buffer->frameCount, _unrel);
        _nextFrame += buffer->frameCount;
        _unrel -= buffer->frameCount;
    }
    buffer->frameCount = 0;
    buffer->raw = NULL;
}

void PcmBufferProvider::reset() {
    _nextFrame = 0;
}

}} // namespace cocos2d { namespace experimental {
