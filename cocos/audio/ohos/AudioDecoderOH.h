#ifndef PROJ_OHOS_AUDIODECODEROH_H
#define PROJ_OHOS_AUDIODECODEROH_H

#include "AudioDecoder.h"

#include <multimedia/player_framework/native_avcodec_audiocodec.h>
#include <multimedia/native_audio_channel_layout.h>
#include <multimedia/player_framework/native_avcapability.h>
#include <multimedia/player_framework/native_avcodec_base.h>
#include <multimedia/player_framework/native_avformat.h>
#include <multimedia/player_framework/native_avbuffer.h>
#include "BigAudioPlayer.h"
#include "platform/CCFileUtils.h"
#include <fstream>

#include <multimedia/player_framework/native_avdemuxer.h>
#include <multimedia/player_framework/native_avsource.h>

#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

namespace cocos2d { namespace experimental {

struct AudioSampleInfo {
    int32_t audioSampleRate = 0;
    int32_t audioChannelCount = 0;
    int64_t audioChannelLayout = 0;
    std::string audioCodecMime = "";
    uint8_t *extra_addr; 
    size_t extra_size;
    // microseconds
    int64_t duration = 0;
};

struct CodecBufferInfo {
    uint32_t bufferIndex = 0;
    uintptr_t *buffer = nullptr;
    uint8_t *bufferAddr = nullptr;
    OH_AVCodecBufferAttr attr = {0, 0, 0, AVCODEC_BUFFER_FLAGS_NONE};

    explicit CodecBufferInfo(uint8_t *addr) : bufferAddr(addr){};
    CodecBufferInfo(uint8_t *addr, int32_t bufferSize)
        : bufferAddr(addr), attr({0, bufferSize, 0, AVCODEC_BUFFER_FLAGS_NONE}){};
    CodecBufferInfo(uint32_t argBufferIndex, OH_AVBuffer *argBuffer)
        : bufferIndex(argBufferIndex), buffer(reinterpret_cast<uintptr_t *>(argBuffer))
    {
        OH_AVBuffer_GetBufferAttr(argBuffer, &attr);
    };
};

class ADecBufferSignal {
public:
    std::mutex inMutex_;
    std::mutex outMutex_;
    std::mutex startMutex_;
    std::condition_variable inCond_;
    std::condition_variable outCond_;
    std::condition_variable startCond_;
    std::queue<CodecBufferInfo> inBufferQueue_;
    std::queue<CodecBufferInfo> outBufferQueue_;
};

class AudioDecoderOH : public AudioDecoder {
public:
    bool demuxer();
    
protected:
    AudioDecoderOH();
    virtual ~AudioDecoderOH();

    virtual bool decodeToPcm() override;
    void getDemuxerResult();
    void Release();
    void InputFunc();
    void OutputFunc();

    friend class AudioDecoderProvider;
    
private:
    std::atomic<bool> isRunning_{false};
    std::unique_ptr<std::thread> inputLoop_;
    std::unique_ptr<std::thread> outputLoop_;
    OH_AVCodec *audioDec_;
    ADecBufferSignal *signal_;
    OH_AVSource *source_;
    OH_AVDemuxer *demuxer_;
    struct OH_AVCodecCallback cb_;
    uint32_t audioTrackIndex_ = 0;
    OH_AVFormat *trackFormat = nullptr;
    OH_AVFormat *decFormat = nullptr;
    AudioSampleInfo *info = nullptr;
};
}}
#endif //PROJ_OHOS_AUDIODECODEROH_H
