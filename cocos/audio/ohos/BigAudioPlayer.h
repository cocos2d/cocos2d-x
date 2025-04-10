#ifndef PROJ_OHOS_BIGAUDIOPLAYER_H
#define PROJ_OHOS_BIGAUDIOPLAYER_H

#pragma once
#include "IAudioPlayer.h"
#include "AssetFd.h"
#include "PcmData.h"
#include "Track.h"

namespace cocos2d { namespace experimental {

class BigAudioPlayer : public IAudioPlayer {
    
public:
    // Override Functions Begin
    virtual int getId() const override { return _id; };

    virtual void setId(int id) override { _id = id; };

    virtual std::string getUrl() const override { return _url; };

    virtual State getState() const override;

    virtual void play() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void stop() override;

    virtual void rewind() override;

    virtual void setVolume(float volume) override;

    virtual float getVolume() const override;

    virtual void setAudioFocus(bool isFocus) override;

    virtual void setLoop(bool isLoop) override;

    virtual bool isLoop() const override;

    virtual float getDuration() const override;

    virtual float getPosition() const override;

    virtual bool setPosition(float pos) override;

    virtual void setPlayEventCallback(const PlayEventCallback &playEventCallback) override;
    
    // Override Functions End
    
    bool prepare(const std::string &url, const PcmData &decResult);

    BigAudioPlayer();
    virtual ~BigAudioPlayer();
    
private:
    int _id;
    std::string _url;
    float _duration;
    Track *_track;
    PlayEventCallback _playEventCallback;
    BigAudioService *_service;

    friend class AudioPlayerProvider;
};
}} // namespace cocos2d { namespace experimental

#endif //PROJ_OHOS_BIGAUDIOPLAYER_H
