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

#include "audio/apple/AudioDecoder.h"
#include "audio/apple/AudioMacros.h"

#import <Foundation/Foundation.h>

#define LOG_TAG "AudioDecoder"

namespace cocos2d { namespace experimental {

    AudioDecoder::AudioDecoder()
    : _isOpened(false)
    , _extRef(nullptr)
    , _totalFrames(0)
    , _bytesPerFrame(0)
    , _sampleRate(0)
    , _channelCount(0)
    {
        memset(&_outputFormat, 0, sizeof(_outputFormat));
    }

    AudioDecoder::~AudioDecoder()
    {
        close();
    }

    bool AudioDecoder::open(const char* path)
    {
        bool ret = false;
        CFURLRef fileURL = nil;
        do
        {
            BREAK_IF_ERR_LOG(path == nullptr || strlen(path) == 0, "Invalid path!");

            NSString *fileFullPath = [[NSString alloc] initWithCString:path encoding:NSUTF8StringEncoding];
            fileURL = (CFURLRef)[[NSURL alloc] initFileURLWithPath:fileFullPath];
            [fileFullPath release];
            BREAK_IF_ERR_LOG(fileURL == nil, "Converting path to CFURLRef failed!");

            OSStatus status = ExtAudioFileOpenURL(fileURL, &_extRef);
            BREAK_IF_ERR_LOG(status != noErr, "ExtAudioFileOpenURL FAILED, Error = %d", status);

            AudioStreamBasicDescription	fileFormat;
            UInt32 propertySize = sizeof(fileFormat);

            // Get the audio data format
            status = ExtAudioFileGetProperty(_extRef, kExtAudioFileProperty_FileDataFormat, &propertySize, &fileFormat);
            BREAK_IF_ERR_LOG(status != noErr, "ExtAudioFileGetProperty(kExtAudioFileProperty_FileDataFormat) FAILED, Error = %d", status);
            BREAK_IF_ERR_LOG(fileFormat.mChannelsPerFrame > 2, "Unsupported Format, channel count is greater than stereo!");

            // Set the client format to 16 bit signed integer (native-endian) data
            // Maintain the channel count and sample rate of the original source format
            _outputFormat.mSampleRate = fileFormat.mSampleRate;
            _outputFormat.mChannelsPerFrame = fileFormat.mChannelsPerFrame;
            _outputFormat.mFormatID = kAudioFormatLinearPCM;
            _outputFormat.mFramesPerPacket = 1;
            _outputFormat.mBitsPerChannel = 16;
            _outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;

            _sampleRate = _outputFormat.mSampleRate;
            _channelCount = _outputFormat.mChannelsPerFrame;
            _bytesPerFrame = 2 * _outputFormat.mChannelsPerFrame;

            _outputFormat.mBytesPerPacket = _bytesPerFrame;
            _outputFormat.mBytesPerFrame = _bytesPerFrame;

            status = ExtAudioFileSetProperty(_extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(_outputFormat), &_outputFormat);
            BREAK_IF_ERR_LOG(status != noErr, "ExtAudioFileSetProperty FAILED, Error = %d", status);

            // Get the total frame count
            SInt64 totalFrames = 0;
            propertySize = sizeof(totalFrames);
            status = ExtAudioFileGetProperty(_extRef, kExtAudioFileProperty_FileLengthFrames, &propertySize, &totalFrames);
            BREAK_IF_ERR_LOG(status != noErr, "ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %d", status);
            BREAK_IF_ERR_LOG(totalFrames <= 0, "Total frames is 0, it's an invalid audio file: %s", path);
            _totalFrames = static_cast<uint32_t>(totalFrames);
            _isOpened = true;

            ret = true;
        } while (false);

        if (fileURL != nil)
            CFRelease(fileURL);

        if (!ret)
        {
            close();
        }

        return ret;
    }

    void AudioDecoder::close()
    {
        if (_extRef != nullptr)
        {
            ExtAudioFileDispose(_extRef);
            _extRef = nullptr;

            _totalFrames = 0;
            _bytesPerFrame = 0;
            _sampleRate = 0;
            _channelCount = 0;
        }
    }

    uint32_t AudioDecoder::read(uint32_t framesToRead, char* pcmBuf)
    {
        uint32_t ret = 0;
        do
        {
            BREAK_IF_ERR_LOG(!isOpened(), "decoder isn't openned");
            BREAK_IF_ERR_LOG(framesToRead == INVALID_FRAME_INDEX, "frameToRead is INVALID_FRAME_INDEX");
            BREAK_IF_ERR_LOG(framesToRead == 0, "frameToRead is 0");
            BREAK_IF_ERR_LOG(pcmBuf == nullptr, "pcmBuf is nullptr");

            AudioBufferList bufferList;
            bufferList.mNumberBuffers = 1;
            bufferList.mBuffers[0].mDataByteSize = framesToRead * _bytesPerFrame;
            bufferList.mBuffers[0].mNumberChannels = _outputFormat.mChannelsPerFrame;
            bufferList.mBuffers[0].mData = pcmBuf;

            UInt32 frames = framesToRead;
            OSStatus status = ExtAudioFileRead(_extRef, &frames, &bufferList);
            BREAK_IF(status != noErr);
            ret = frames;
        } while (false);

        return ret;
    }

    uint32_t AudioDecoder::readFixedFrames(uint32_t framesToRead, char* pcmBuf)
    {
        uint32_t framesRead = 0;
        uint32_t framesReadOnce = 0;
        do
        {
            framesReadOnce = read(framesToRead - framesRead, pcmBuf + framesRead * _bytesPerFrame);
            framesRead += framesReadOnce;
        } while (framesReadOnce != 0 && framesRead < framesToRead);

        if (framesRead < framesToRead)
        {
            memset(pcmBuf + framesRead * _bytesPerFrame, 0x00, (framesToRead - framesRead) * _bytesPerFrame);
        }

        return framesRead;
    }

    bool AudioDecoder::seek(uint32_t frameOffset)
    {
        bool ret = false;
        do
        {
            BREAK_IF_ERR_LOG(!isOpened(), "decoder isn't openned");
            BREAK_IF_ERR_LOG(frameOffset == INVALID_FRAME_INDEX, "frameIndex is INVALID_FRAME_INDEX");

            OSStatus status = ExtAudioFileSeek(_extRef, frameOffset);
            BREAK_IF(status != noErr);
            ret = true;
        } while(false);
        return ret;
    }

    uint32_t AudioDecoder::tell() const
    {
        uint32_t ret = INVALID_FRAME_INDEX;
        do
        {
            BREAK_IF_ERR_LOG(!isOpened(), "decoder isn't openned");
            SInt64 frameIndex = INVALID_FRAME_INDEX;
            OSStatus status = ExtAudioFileTell(_extRef, &frameIndex);
            BREAK_IF(status != noErr);
            ret = static_cast<uint32_t>(frameIndex);
        } while(false);

        return ret;
    }

    uint32_t AudioDecoder::getTotalFrames() const
    {
        return _totalFrames;
    }

    uint32_t AudioDecoder::getBytesPerFrame() const
    {
        return _bytesPerFrame;
    }

    uint32_t AudioDecoder::getSampleRate() const
    {
        return _sampleRate;
    }

    uint32_t AudioDecoder::getChannelCount() const
    {
        return _channelCount;
    }

    bool AudioDecoder::isOpened() const
    {
        return _isOpened;
    }

}} // namespace cocos2d { namespace experimental {
