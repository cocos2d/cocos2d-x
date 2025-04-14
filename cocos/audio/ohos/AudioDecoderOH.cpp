#include "AudioDecoderOH.h"

namespace cocos2d { namespace experimental {

static void OnError(OH_AVCodec *codec, int32_t errorCode, void *userData) {
    ALOGV("AudioDecoderOH OH_AVCodecOnError errorCode=%{public}d", errorCode);
}

static void OnOutputFormatChanged(OH_AVCodec *codec, OH_AVFormat *format, void *userData) {
}

static void OnInputBufferAvailable(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData) {
    if (userData == nullptr) {
        return;
    }
    ADecBufferSignal *signal = static_cast<ADecBufferSignal *>(userData);
    unique_lock<mutex> lock(signal->inMutex_);
    signal->inBufferQueue_.emplace(index, buffer);
    signal->inCond_.notify_all();
}

static void OnOutputBufferAvailable(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData) {
    if (userData == nullptr) {
        return;
    }
    ADecBufferSignal *signal = static_cast<ADecBufferSignal *>(userData);
    unique_lock<mutex> lock(signal->outMutex_);
    signal->outBufferQueue_.emplace(index, buffer);
    signal->outCond_.notify_all();
}

AudioDecoderOH::AudioDecoderOH(): demuxer_(nullptr), audioDec_(nullptr), signal_(nullptr) {
}

AudioDecoderOH::~AudioDecoderOH() {
    Release();
}

bool AudioDecoderOH::decodeToPcm() {
    
    if (!demuxer()) {
        return false;
    }
    
    if (info->audioCodecMime == "audio/raw") {
        while (true) {
            size_t bufSize = 4096;
            OH_AVBuffer * buffer = OH_AVBuffer_Create(bufSize);
            int32_t ret = OH_AVDemuxer_ReadSampleBuffer(demuxer_, audioTrackIndex_, buffer);
            if (ret != AV_ERR_OK) {
                break;
            }
            OH_AVCodecBufferAttr attr = {0, 0, 0, AVCODEC_BUFFER_FLAGS_NONE};
            ret = OH_AVBuffer_GetBufferAttr(buffer, &attr);
            char* source = (char*)OH_AVBuffer_GetAddr(buffer);
            _result.pcmBuffer->insert(_result.pcmBuffer->end(), source, source + attr.size);
            if (attr.flags & AVCODEC_BUFFER_FLAGS_EOS) {
                break;
            }
        }
        return true;
    }
    
    audioDec_ = OH_AudioCodec_CreateByMime(info->audioCodecMime.c_str(), false);
    if (audioDec_ == nullptr) {
        ALOGE("AudioDecoderOH Create AudioCodec Failed");
        return false;
    }
    
    decFormat = OH_AVFormat_Create();
    OH_AVFormat_SetIntValue(decFormat, OH_MD_KEY_AUDIO_SAMPLE_FORMAT, SAMPLE_S16LE);
    OH_AVFormat_SetIntValue(decFormat, OH_MD_KEY_AUD_CHANNEL_COUNT, info->audioChannelCount);
    OH_AVFormat_SetIntValue(decFormat, OH_MD_KEY_AUD_SAMPLE_RATE, info->audioSampleRate);
    OH_AVFormat_SetLongValue(decFormat, OH_MD_KEY_CHANNEL_LAYOUT, info->audioChannelLayout);
    if (info->audioCodecMime == OH_AVCODEC_MIMETYPE_AUDIO_VORBIS) {
        OH_AVFormat_SetBuffer(decFormat, OH_MD_KEY_CODEC_CONFIG, info->extra_addr, info->extra_size);
    }

    int32_t ret = OH_AudioCodec_Configure(audioDec_, decFormat);
    if (ret != AV_ERR_OK) {
        ALOGE("AudioDecoderOH Configure AudioCodec Failed");
        return false;
    }
    
    signal_ = new ADecBufferSignal();
    OH_AVCodecCallback cb_ = {&OnError, &OnOutputFormatChanged, &OnInputBufferAvailable, &OnOutputBufferAvailable};
    OH_AudioCodec_RegisterCallback(audioDec_, cb_, signal_);

    {
        int ret = OH_AudioCodec_Prepare(audioDec_);
        if (ret != AV_ERR_OK) {
            ALOGE("AudioDecoderOH Prepare AudioCodec Failed");
            return false;
        }
    }
    
    ret = OH_AudioCodec_Start(audioDec_);
    if (ret != AV_ERR_OK) {
        ALOGE("AudioDecoderOH Start AudioCodec Failed");
        return false;
    }
    
    isRunning_.store(true);
    inputLoop_ = make_unique<thread>(&AudioDecoderOH::InputFunc, this);
    outputLoop_ = make_unique<thread>(&AudioDecoderOH::OutputFunc, this);
    
    unique_lock<mutex> lock(signal_->startMutex_);
    signal_->startCond_.wait(lock, [this]() { return (!(isRunning_.load())); });
    
    return true;
}

void AudioDecoderOH::getDemuxerResult() {
    if (info == nullptr) {
        return;
    }
    _result.numChannels = info->audioChannelCount;
    _result.sampleRate = info->audioSampleRate;
    _result.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    _result.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    _result.channelMask = info->audioChannelCount == 1 ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);
    _result.endianness = SL_BYTEORDER_LITTLEENDIAN;
    _result.duration = info->duration / 1000000.0f;
    _result.numFrames = _result.duration * info->audioSampleRate;
}

bool AudioDecoderOH::demuxer() {
    
    if (info != nullptr) {
        return true;
    }
    
    info = new AudioSampleInfo();
    
    int64_t offset = _fileInfo.start;
    int fd = _fileInfo.assetFd->getFd();
    if (fd < 0) {
        ALOGE("AudioDecoderOH Failed to open file descriptor for '%{public}s'", _url.c_str());
        return false;
    }
    long fileSize = _fileInfo.length;
    source_ = OH_AVSource_CreateWithFD(fd, offset, fileSize);
    if (source_ == nullptr) {
        ALOGE("AudioDecoderOH demuxer create source failed");
        return false;
    }
    demuxer_ = OH_AVDemuxer_CreateWithSource(source_);
    if (demuxer_ == nullptr) {
        ALOGE("AudioDecoderOH demuxer create demuxer failed");
        return false;
    }
    
    OH_AVFormat *sourceFormat = OH_AVSource_GetSourceFormat(source_);
    if (sourceFormat == nullptr) {
        ALOGE("AudioDecoderOH demuxer get source format failed");
       return false;
    }
    int32_t trackCount = 0;
    OH_AVFormat_GetIntValue(sourceFormat, OH_MD_KEY_TRACK_COUNT, &trackCount);
    OH_AVFormat_GetLongValue(sourceFormat, OH_MD_KEY_DURATION, &info->duration);
    OH_AVFormat_Destroy(sourceFormat);
    
    for (uint32_t index = 0; index < (static_cast<uint32_t>(trackCount)); index++) {
        trackFormat = OH_AVSource_GetTrackFormat(source_, index);
        if (trackFormat == nullptr) {
            ALOGE("AudioDecoderOH demuxer get track format failed");
            return false;
        }
        audioTrackIndex_ = index;
        if(OH_AVDemuxer_SelectTrackByID(demuxer_, audioTrackIndex_) != AV_ERR_OK){
           ALOGE("AudioDecoderOH select audio track failed: %d", audioTrackIndex_);
           return false;
        }
        OH_AVFormat_GetIntValue(trackFormat, OH_MD_KEY_AUD_CHANNEL_COUNT, &info->audioChannelCount);
        OH_AVFormat_GetLongValue(trackFormat, OH_MD_KEY_CHANNEL_LAYOUT, &info->audioChannelLayout);
        OH_AVFormat_GetIntValue(trackFormat, OH_MD_KEY_AUD_SAMPLE_RATE, &info->audioSampleRate);
        char *audioCodecMime;
        OH_AVFormat_GetStringValue(trackFormat,
            OH_MD_KEY_CODEC_MIME, const_cast<char const **>(&audioCodecMime));
        info->audioCodecMime = audioCodecMime;
        if (info->audioCodecMime == OH_AVCODEC_MIMETYPE_AUDIO_VORBIS) {
            OH_AVFormat_GetBuffer(trackFormat, OH_MD_KEY_CODEC_CONFIG, &info->extra_addr, &info->extra_size);
        }
    }
    
    getDemuxerResult();    
    return true;
}

void AudioDecoderOH::InputFunc() {
    
    while (isRunning_.load()) {
        if (!isRunning_.load()) {
            break;
        }
        std::unique_lock<std::mutex> lock(signal_->inMutex_);
        bool condRet = signal_->inCond_.wait_for(
            lock, 5s, [this]() { return (!signal_->inBufferQueue_.empty() || !isRunning_.load());  });
        if (!isRunning_.load()) {
            break;
        }
        if (signal_->inBufferQueue_.empty()) {
            continue;
        }
        auto bufferInfo = signal_->inBufferQueue_.front();
        signal_->inBufferQueue_.pop();
        lock.unlock();
        auto buffer = reinterpret_cast<OH_AVBuffer *>(bufferInfo.buffer);
        
        int32_t ret = OH_AVDemuxer_ReadSampleBuffer(demuxer_, audioTrackIndex_, buffer);
        ret = OH_AVBuffer_GetBufferAttr(buffer, &bufferInfo.attr);
        ret = OH_AVBuffer_SetBufferAttr(buffer, &bufferInfo.attr);
        ret = OH_AudioCodec_PushInputBuffer(audioDec_, bufferInfo.bufferIndex);
        if (ret != AV_ERR_OK) {
            ALOGV("InputFunc Fatal error, exit! ret=%{public}d", ret);
            break;
        }
        if (bufferInfo.attr.flags & AVCODEC_BUFFER_FLAGS_EOS) {
            break;
        }
    }
    ALOGV("InputFunc stop, exit");
}

void AudioDecoderOH::OutputFunc() {
    while (isRunning_.load()) {
        if (!isRunning_.load()) {
            break;
        }
        std::unique_lock<std::mutex> lock(signal_->outMutex_);
        bool condRet = signal_->outCond_.wait_for(
            lock, 5s, [this]() { return (!signal_->outBufferQueue_.empty() || !isRunning_.load());  });
        if (!isRunning_.load()) {
            break;
        }
        if (signal_->outBufferQueue_.empty()) {
            continue;
        }
        auto bufferInfo = signal_->outBufferQueue_.front();
        signal_->outBufferQueue_.pop();
        char* source = (char*)OH_AVBuffer_GetAddr(reinterpret_cast<OH_AVBuffer *>(bufferInfo.buffer));
        _result.pcmBuffer->insert(_result.pcmBuffer->end(), source, source + bufferInfo.attr.size);
        
        int32_t ret = OH_AudioCodec_FreeOutputBuffer(audioDec_, bufferInfo.bufferIndex);
        if (ret != AV_ERR_OK) {
            ALOGV("InputFunc Fatal error, exit! ret=%{public}d", ret);
            break;
        }
        
        if (bufferInfo.attr.flags & AVCODEC_BUFFER_FLAGS_EOS) {
            break;
        }
        
        lock.unlock();
    }
    isRunning_.store(false);
    signal_->startCond_.notify_all();
    ALOGV("OutputFunc stop, exit");
}

void AudioDecoderOH::Release() {
    isRunning_.store(false);
    if (inputLoop_ != nullptr && inputLoop_->joinable()) {
        {
            unique_lock<mutex> lock(signal_->inMutex_);
            signal_->inCond_.notify_all();
        }
        inputLoop_->join();
        inputLoop_ = nullptr;
    }

    if (outputLoop_ != nullptr && outputLoop_->joinable()) {
        {
            unique_lock<mutex> lock(signal_->outMutex_);
            signal_->outCond_.notify_all();
        }
        outputLoop_->join();
        outputLoop_ = nullptr;
        while (!signal_->outBufferQueue_.empty()) {
            signal_->outBufferQueue_.pop();
        }
    }
    if (audioDec_ != nullptr) {
        OH_AudioCodec_Flush(audioDec_);
        OH_AudioCodec_Stop(audioDec_);
        OH_AudioCodec_Destroy(audioDec_);
        audioDec_ = nullptr;   
    }
    
    if (demuxer_ != nullptr) {
        OH_AVDemuxer_Destroy(demuxer_);
        demuxer_ = nullptr;
    }
    if (source_ != nullptr) {
        OH_AVSource_Destroy(source_);
        source_ = nullptr;
    }
    
    if (trackFormat != nullptr) {
        OH_AVFormat_Destroy(trackFormat);
        trackFormat = nullptr;
    }
    if (decFormat != nullptr) {
        OH_AVFormat_Destroy(decFormat);
        decFormat = nullptr;
    }
    if (signal_) {
        delete signal_;
        signal_ = nullptr;
    }
    if (info != nullptr) {
        delete info;
        info = nullptr;
    }
}
}}