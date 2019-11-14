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

#pragma once

#include "audio/android/OpenSLHelper.h"
#include "audio/android/PcmData.h"
#include "base/CCData.h"

namespace cocos2d {

class AudioDecoder
{
public:
    AudioDecoder();
    virtual ~AudioDecoder();

    virtual bool init(const std::string &url, int sampleRate);

    bool start();

    inline PcmData getResult()
    { return _result; };

protected:
    virtual bool decodeToPcm() = 0;
    bool resample();
    bool interleave();

    static size_t fileRead(void* ptr, size_t size, size_t nmemb, void* datasource);
    static int fileSeek(void* datasource, int64_t offset, int whence);
    static int fileClose(void* datasource);
    static long fileTell(void* datasource);

    std::string _url;
    PcmData _result;
    int _sampleRate;
    Data _fileData;
    size_t _fileCurrPos;
};

} // namespace cocos2d {
