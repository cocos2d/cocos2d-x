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

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

namespace cocos2d { namespace experimental {

struct PcmData
{
    std::shared_ptr<std::vector<char>> pcmBuffer;
    int numChannels;
    int sampleRate;
    int bitsPerSample;
    int containerSize;
    int channelMask;
    int endianness;
    int numFrames;
    float duration; // in seconds

    PcmData();

    ~PcmData();

    PcmData(const PcmData &o);

    PcmData(PcmData &&o);

    PcmData &operator=(const PcmData &o);

    PcmData &operator=(PcmData &&o);

    void reset();

    bool isValid() const;

    std::string toString() const;
};

}} // namespace cocos2d { namespace experimental {
