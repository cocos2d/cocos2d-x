/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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
#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#ifndef __AUDIO_ENGINE_LINUX_H_
#define __AUDIO_ENGINE_LINUX_H_

#include <functional>
#include <iostream>
#include <map>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "audio/include/AudioEngine.h"

#include "base/CCRef.h"

NS_CC_BEGIN
    namespace experimental{
#define MAX_AUDIOINSTANCES 32

class CC_DLL AudioEngineImpl : public cocos2d::Ref
{
public:
    AudioEngineImpl();
    ~AudioEngineImpl();
    
    bool init();
    int play2d(const std::string &fileFullPath ,bool loop ,float volume);
    void setVolume(int audioID,float volume);
    void setLoop(int audioID, bool loop);
    bool pause(int audioID);
    bool resume(int audioID);
    bool stop(int audioID);
    void stopAll();
    float getDuration(int audioID);
    float getCurrentTime(int audioID);
    bool setCurrentTime(int audioID, float time);
    void setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback);
    
    void uncache(const std::string& filePath);
    void uncacheAll();
    

    int preload(const std::string& filePath, std::function<void(bool isSuccess)> callback);
    
    void update(float dt);
    
    /**
     * used internally by ffmod callback 
     */ 
    void onSoundFinished(FMOD::Channel * channel); 
    
private:
  
    /**
    * returns null if a sound with the given path is not found
    */
    FMOD::Sound * findSound(const std::string &path);
  
    FMOD::Channel * getChannel(FMOD::Sound *);
  
    struct ChannelInfo{
        size_t id; 
        std::string path; 
        FMOD::Sound * sound;
        FMOD::Channel * channel; 
        bool loop; 
        float volume; 
        std::function<void (int, const std::string &)> callback;
    };
    
    std::map<int, ChannelInfo> mapChannelInfo;
    
    std::map<std::string, FMOD::Sound *> mapSound;  
    
    FMOD::System* pSystem;
    
};
}
NS_CC_END
#endif // __AUDIO_ENGINE_LINUX_H_
#endif

