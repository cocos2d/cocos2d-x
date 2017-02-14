/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.

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

/**
 * @brief The class for decoding compressed audio file to PCM buffer.
 */
class AudioDecoder
{
public:
    static const uint32_t INVALID_FRAME_INDEX = UINT32_MAX;

    AudioDecoder();
    ~AudioDecoder();

    /**
     * @brief Opens an audio file specified by a file path.
     * @return true if succeed, otherwise false.
     */
    bool open(const char* path);

    /**
     * @brief Checks whether decoder has opened file successfully.
     * @return true if succeed, otherwise false.
     */
    bool isOpened() const;

    /**
     * @brief Closes opened audio file.
     * @note The method will also be automatically invoked in the destructor.
     */
    void close();

    /**
     * @brief Reads audio frames of PCM format.
     * @param framesToRead The number of frames excepted to be read.
     * @param pcmBuf The buffer to hold the frames to be read, its size should be >= |framesToRead| * _bytesPerFrame.
     * @return The number of frames actually read, it's probably less than 'framesToRead'. Returns 0 means reach the end of file.
     */
    uint32_t read(uint32_t framesToRead, char* pcmBuf);

    /**
     * @brief Reads fixed audio frames of PCM format.
     * @param framesToRead The number of frames excepted to be read.
     * @param pcmBuf The buffer to hold the frames to be read, its size should be >= |framesToRead| * _bytesPerFrame.
     * @return The number of frames actually read, it's probably less than |framesToRead|. Returns 0 means reach the end of file.
     * @note The different between |read| and |readFixedFrames| is |readFixedFrames| will do multiple reading operations if |framesToRead| frames
     *       isn't filled entirely, while |read| just does reading operation once whatever |framesToRead| is or isn't filled entirely.
     *       If current position reaches the end of frames, the return value may smaller than |framesToRead| and the remaining
     *       buffer in |pcmBuf| will be set with silence data (0x00).
     */
    uint32_t readFixedFrames(uint32_t framesToRead, char* pcmBuf);

    /**
     * @brief Sets frame offest to be read.
     * @param frameOffset The frame offest to be set.
     * @return true if succeed, otherwise false
     */
    bool seek(uint32_t frameOffset);

    /**
     * @brief Tells the current frame offset.
     * @return The current frame offset.
     */
    uint32_t tell() const;

    /** Gets total frames of current audio.*/
    uint32_t getTotalFrames() const;

    /** Gets bytes per frame of current audio.*/
    uint32_t getBytesPerFrame() const;

    /** Gets sample rate of current audio.*/
    uint32_t getSampleRate() const;

    /** Gets the channel count of current audio.
     * @note Currently we only support 1 or 2 channels.
     */
    uint32_t getChannelCount() const;

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
