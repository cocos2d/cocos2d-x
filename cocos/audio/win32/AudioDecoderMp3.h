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

#include "audio/win32/AudioDecoder.h"

struct mpg123_handle_struct;

namespace cocos2d {

/**
 * @brief The class for decoding compressed audio file to PCM buffer.
 */
class AudioDecoderMp3 : public AudioDecoder
{
public:
    /**
     * @brief Opens an audio file specified by a file path.
     * @return true if succeed, otherwise false.
     */
    virtual bool open(const char* path) override;

    /**
     * @brief Closes opened audio file.
     * @note The method will also be automatically invoked in the destructor.
     */
    virtual void close() override;

    /**
     * @brief Reads audio frames of PCM format.
     * @param framesToRead The number of frames excepted to be read.
     * @param pcmBuf The buffer to hold the frames to be read, its size should be >= |framesToRead| * _bytesPerFrame.
     * @return The number of frames actually read, it's probably less than 'framesToRead'. Returns 0 means reach the end of file.
     */
    virtual uint32_t read(uint32_t framesToRead, char* pcmBuf) override;

    /**
     * @brief Sets frame offest to be read.
     * @param frameOffset The frame offest to be set.
     * @return true if succeed, otherwise false
     */
    virtual bool seek(uint32_t frameOffset) override;

    /**
     * @brief Tells the current frame offset.
     * @return The current frame offset.
     */
    virtual uint32_t tell() const override;

protected:

    AudioDecoderMp3();
    ~AudioDecoderMp3();

    static bool lazyInit();
    static void destroy();

    struct mpg123_handle_struct* _mpg123handle;

    friend class AudioDecoderManager;
};

} // namespace cocos2d {
