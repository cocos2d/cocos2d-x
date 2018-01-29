/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#ifndef __AUDIO_ENGINE_INL_H_
#define __AUDIO_ENGINE_INL_H_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include <unordered_map>
#include "base/CCRef.h"
#include "base/ccUtils.h"

#define MAX_AUDIOINSTANCES 24

#define ERRORLOG(msg) log("fun:%s,line:%d,msg:%s",__func__,__LINE__,#msg)

NS_CC_BEGIN

class EventCustom;
class EventListener;

namespace experimental {

class IAudioPlayer;
class AudioPlayerProvider;

class AudioEngineImpl;

class AudioEngineImpl : public cocos2d::Ref
{
public:
    AudioEngineImpl();
    ~AudioEngineImpl();

    bool init();
    int play2d(const std::string &fileFullPath ,bool loop ,float volume);
    void setVolume(int audioID,float volume);
    void setLoop(int audioID, bool loop);
    void pause(int audioID);
    void resume(int audioID);
    void stop(int audioID);
    void stopAll();
    float getDuration(int audioID);
    float getCurrentTime(int audioID);
    bool setCurrentTime(int audioID, float time);
    void setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback);

    void uncache(const std::string& filePath);
    void uncacheAll();
    void preload(const std::string& filePath, const std::function<void(bool)>& callback);

    void setAudioFocusForAllPlayers(bool isFocus);
private:

    void onEnterBackground(EventCustom* event);
    void onEnterForeground(EventCustom* event);

    // engine interfaces
    SLObjectItf _engineObject;
    SLEngineItf _engineEngine;

    // output mix interfaces
    SLObjectItf _outputMixObject;

    //audioID,AudioInfo
    std::unordered_map<int, IAudioPlayer*>  _audioPlayers;
    std::unordered_map<int, std::function<void (int, const std::string &)>> _callbackMap;

    // UrlAudioPlayers which need to resumed while entering foreground
    std::unordered_map<int, IAudioPlayer*> _urlAudioPlayersNeedResume;

    AudioPlayerProvider* _audioPlayerProvider;
    EventListener* _onPauseListener;
    EventListener* _onResumeListener;

    int _audioIDIndex;
    
    bool _lazyInitLoop;
};

#endif // __AUDIO_ENGINE_INL_H_
 }
NS_CC_END

#endif
