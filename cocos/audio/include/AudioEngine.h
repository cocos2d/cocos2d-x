/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#ifndef __AUDIO_ENGINE_H_
#define __AUDIO_ENGINE_H_

#include <string.h>
#include <unordered_map>

#include "2d/CCNode.h"
#include "Export.h"

#ifdef ERROR
#undef ERROR
#endif // ERROR

NS_CC_BEGIN

class AudioEngine;
class AudioEngineImpl;

class EXPORT_DLL AudioProfile
{
public:
    unsigned int maxInstances;
    
    /* minimum delay in between sounds */
    double minDelay;

    /*the following property only take effect on 3d audio */
    float minRange;
    float maxRange;
 
private:
    AudioProfile()
    : minDelay(0.0)
    , maxInstances(0)
    , lastPlayTime(0.0)
    {
        
    }
    
    std::list<int> audioIDs;
    
    double lastPlayTime;
    
    friend class AudioEngine;
    friend class AudioEngineImpl;
};

/**
  @class          AudioEngine
  @brief          
  @note           
 */

class EXPORT_DLL AudioEngine
{
public:
    enum class AudioState
    {
        INITIAL,
        PLAYING,
        PAUSED
    };
    
    static const int INVAILD_AUDIO_ID;

    static const float TIME_UNKNOWN;

    /** Returns a shared instance of the AudioEngine */
    static AudioEngine* getInstance();

    /**
     * Release the shared Audio Engine object
     @warning It must be called before the application exit
     */
    static void destroyInstance();
    
    /** Create an audio profile
     *
     */
    virtual AudioProfile* createProfile(const std::string& name,int maxInstance = 0,double minDelay = 0.0f,float minRange = 0.0f,float maxRange = 1.0f);
    
    /** Get an audio profile
     *
     */
    virtual AudioProfile* getProfile(const std::string& name);
    
    /**  Setup default profiles for audio instances
     * @param profile a profile return by createProfile/getProfile function
     */
    virtual void setDefaultProfile(AudioProfile* profile);
    
    /**  Gets the default profile of audio instances
     * @return the default profile of audio instances
     */
    virtual AudioProfile* getDefaultProfile() const;
    
    /** Play 2d sound
     * @param filePath The path of an audio file
     * @param loop Whether audio instance loop or not
     * @param volume volume value (range from 0.0 to 1.0)
     * @param profile a profile return by createProfile/getProfile function
     * @return an audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     */
    virtual int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, AudioProfile *profile = nullptr);
    
    /** Sets whether an audio instance loop or not. 
     @param audioID an audioID returned by the play2d function
     @param loop Whether audio instance loop or not
     */
    virtual void setLoop(int audioID, bool loop);

    /** Checks whether an audio instance is loop.
     * @param audioID an audioID returned by the play2d function
     * @return Whether or not an audio instance is loop.
     */
    virtual bool isLoop(int audioID) const;

    /** Sets volume for an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @param volume volume value (range from 0.0 to 1.0)
     */
    virtual void setVolume(int audioID, float volume);

    /** Gets the volume value of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return volume value (range from 0.0 to 1.0)
     */
    virtual float getVolume(int audioID) const;

    /** Pause an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    virtual void pause(int audioID);

    /** Pause all playing audio instances */
    virtual void pauseAll();

    /** Resume an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    virtual void resume(int audioID);

    /** Resume all suspended audio instances */
    virtual void resumeAll();

    /** Stop an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    virtual void stop(int audioID);

    /** Stop all audio instances */
    virtual void stopAll();

    /** Sets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return 
     */
    virtual bool setCurrentTime(int audioID, float time);

    /** Gets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the current playback position of an audio instance
     */
    virtual float getCurrentTime(int audioID);

    /** Gets the duration of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the duration of an audio instance
     */
    virtual float getDuration(int audioID);

    /** Returns the state of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the status of an audio instance
     */
    virtual AudioState getState(int audioID) const;

    /** Register a callback to be invoked when an audio instance has completed playing.
     * @param audioID an audioID returned by the play2d function
     * @param callback 
     */
    virtual void setFinishCallback(int audioID, const std::function<void(int,const std::string&)>& callback);
    
    virtual unsigned int getMaxAudioInstance();
    
    virtual bool setMaxAudioInstance(unsigned int maxInstances);
    
    /** Uncache the audio data from internal buffer.
     * AudioEngine cache audio data on ios platform
     * @warning This can lead to stop related audio first.
     * @param filePath The path of an audio file
     */
    void uncache(const std::string& filePath);
    
    /** Uncache all audio data from internal buffer.
     * @warning All audio will be stopped first.
     * @param
     */
    void uncacheAll();
    
    /**  Setup profiles for an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @param profile a profile for audio instance
     */
    virtual void setProfile(int audioID, AudioProfile* profile);
    
    /**  Gets the profiles of audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the profile of audio instance
     */
    virtual AudioProfile* getProfile(int audioID);

protected:
    AudioEngine();
    virtual ~AudioEngine();
    
    //
    void remove(int audioID);
    
    virtual bool init();
    
    class AudioInfo
    {
    public:
        AudioInfo()
        : profile(nullptr)
        , duration(TIME_UNKNOWN)
        , state(AudioState::INITIAL)
        {
            
        }
        
        const std::string* filePath;
        AudioProfile* profile;
        
        float volume;
        bool loop;
        float duration;
        AudioState state;
        
        bool is3dAudio;
    };
    
    //audioID,audioAttribute
    std::unordered_map<int, AudioInfo> _audioInfos;
    
    //audio file path,audio IDs
    std::unordered_map<std::string,std::list<int>> _audioIDs;
    
    //profileName,AudioProfile
    std::unordered_map<std::string, AudioProfile*> _audioProfiles;
    
    int _maxInstances;
    
    AudioProfile* _defaultProfile;
    
    AudioEngineImpl* _audioEngineImpl;
    
    friend class AudioEngineImpl;
};

NS_CC_END

#endif // __AUDIO_ENGINE_H_
#endif
