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

namespace cocos2d { namespace experimental {

static int gVerbose = 0;

PcmBufferProvider::PcmBufferProvider()
        : mAddr(nullptr)
        , mNumFrames(0)
        , mFrameSize(0)
        , mNextFrame(0)
        , mUnrel(0)
{
    
}

bool PcmBufferProvider::init(const void *addr, size_t frames, size_t frameSize)
{
    mAddr = addr;
    mNumFrames = frames;
    mFrameSize = frameSize;
    mNextFrame = 0;
    mUnrel = 0;
    return true;
}

status_t PcmBufferProvider::getNextBuffer(Buffer *buffer,
                                          int64_t pts/* = kInvalidPTS*/) {
    (void) pts; // suppress warning
    size_t requestedFrames = buffer->frameCount;
    if (requestedFrames > mNumFrames - mNextFrame) {
        buffer->frameCount = mNumFrames - mNextFrame;
    }

    if (gVerbose) {
        ALOGV("getNextBuffer() requested %zu frames out of %zu frames available,"
                       " and returned %zu frames\n",
               requestedFrames, (size_t) (mNumFrames - mNextFrame), buffer->frameCount);
    }
    mUnrel = buffer->frameCount;
    if (buffer->frameCount > 0) {
        buffer->raw = (char *) mAddr + mFrameSize * mNextFrame;
        return NO_ERROR;
    } else {
        buffer->raw = NULL;
        return NOT_ENOUGH_DATA;
    }
}

void PcmBufferProvider::releaseBuffer(Buffer *buffer) {
    if (buffer->frameCount > mUnrel) {
        ALOGV("ERROR releaseBuffer() released %zu frames but only %zu available "
                "to release\n", buffer->frameCount, mUnrel);
        mNextFrame += mUnrel;
        mUnrel = 0;
    } else {
        if (gVerbose) {
            ALOGV("releaseBuffer() released %zu frames out of %zu frames available "
                           "to release\n", buffer->frameCount, mUnrel);
        }
        mNextFrame += buffer->frameCount;
        mUnrel -= buffer->frameCount;
    }
    buffer->frameCount = 0;
    buffer->raw = NULL;
}

void PcmBufferProvider::reset() {
    mNextFrame = 0;
}

}} // namespace cocos2d { namespace experimental {
