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
