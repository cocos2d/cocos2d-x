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

#include <memory>
#include <mutex>
#include <thread>
#include <map>
#include "AssetFd.h"
#include "IAudioPlayer.h"
#include "cutils/log.h"
#include "multimedia/player_framework/avplayer.h"

namespace cocos2d { namespace experimental {

class ICallerThreadUtils;
class AssetFd;

class UrlAudioPlayer : public IAudioPlayer {
public:
    // Override Functions Begin
    virtual int getId() const override { return _id; };

    virtual void setId(int id) override { _id = id; };

    virtual std::string getUrl() const override { return _url; };

    virtual State getState() const override { return _state; };

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

    UrlAudioPlayer(ICallerThreadUtils *callerThreadUtils);

    virtual ~UrlAudioPlayer();

    bool prepare(const std::string &url, std::shared_ptr<AssetFd> assetFd, int32_t start, int32_t length);

    static void onInfo(OH_AVPlayer *player, AVPlayerOnInfoType type, int32_t extra);

    static void onError(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg);
    
    static void stopAll();

    void destroy();

    inline void setState(State state) { _state = state; };

    void playEventCallback();

    void setVolumeToAVPlayer(float volume);

private:
    ICallerThreadUtils *_callerThreadUtils;

    int _id;
    std::string _url;

    std::shared_ptr<AssetFd> _assetFd;

    OH_AVPlayer *_playObj;

    float _volume;
    float _duration;
    bool _isLoop;
    bool _isAudioFocus;
    State _state;

    PlayEventCallback _playEventCallback;

    std::thread::id _callerThreadId;
    std::shared_ptr<bool> _isDestroyed;

    friend class AudioPlayerProvider;
};

}} // namespace cocos2d { namespace experimental
