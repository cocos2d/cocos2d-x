#ifndef PROJ_OHOS_BIGAUDIOSERVICE_H
#define PROJ_OHOS_BIGAUDIOSERVICE_H

#pragma once

#include "cutils/log.h"
#include <ohaudio/native_audiostreambuilder.h>
#include <ohaudio/native_audiorenderer.h>
#include "Track.h"

namespace cocos2d { namespace experimental {

class Track;

class BigAudioService {
public:
    
    BigAudioService();

    virtual ~BigAudioService();

    bool init(PcmData decResult);
    void setTrack(Track *track);
    bool getNextTrackBuff(void* buffer, int32_t bufferLen);
    static int32_t AudioRendererOnWriteData(OH_AudioRenderer* renderer, void* userData, void* buffer, int32_t bufferLen);
    static int32_t AudioRendererOnInterrupt(OH_AudioRenderer* renderer, void* userData, OH_AudioInterrupt_ForceType type, OH_AudioInterrupt_Hint hint);
    
    void pause();
    void resume();

    int _numChannels;
    int _sampleRate;
    int _bufferSizeInBytes;
    
    OH_AudioRenderer *_audioRenderer;
    OH_AudioStreamBuilder *_builder;
    
private:
    Track *_track = nullptr;
    PcmData _decResult;
};

}} // namespace cocos2d { namespace experimental

#endif //PROJ_OHOS_BIGAUDIOSERVICE_H
