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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#ifndef __AUDIO_ENGINE_H_
#define __AUDIO_ENGINE_H_

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "Export.h"

#ifdef ERROR
#undef ERROR
#endif // ERROR

NS_CC_BEGIN
    namespace experimental{

class EXPORT_DLL AudioProfile
{
public:
    //name can't be empty
    std::string name;
    
    unsigned int maxInstances;
    
    /* minimum delay in between sounds */
    double minDelay;
 
    AudioProfile()
    : maxInstances(0)
    , minDelay(0.0)
    {
        
    }
};

class AudioEngineImpl;

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
        ERROR  = -1,
        INITIALZING,
        PLAYING,
        PAUSED
    };
    
    static const int INVAILD_AUDIO_ID;

    static const float TIME_UNKNOWN;

    static bool lazyInit();
    /**
     * Release related objects
     @warning It must be called before the application exit
     */
    static void end();
    
    /**  Gets the default profile of audio instances
     * @return the default profile of audio instances
     */
    static AudioProfile* getDefaultProfile();
    
    /** Play 2d sound
     * @param filePath The path of an audio file
     * @param loop Whether audio instance loop or not
     * @param volume volume value (range from 0.0 to 1.0)
     * @param profile a profile for audio instance
     * @return an audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     */
    static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);
    
    /** Sets whether an audio instance loop or not. 
     @param audioID an audioID returned by the play2d function
     @param loop Whether audio instance loop or not
     */
    static void setLoop(int audioID, bool loop);

    /** Checks whether an audio instance is loop.
     * @param audioID an audioID returned by the play2d function
     * @return Whether or not an audio instance is loop.
     */
    static bool isLoop(int audioID);

    /** Sets volume for an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @param volume volume value (range from 0.0 to 1.0)
     */
    static void setVolume(int audioID, float volume);

    /** Gets the volume value of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return volume value (range from 0.0 to 1.0)
     */
    static float getVolume(int audioID);

    /** Pause an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    static void pause(int audioID);

    /** Pause all playing audio instances */
    static void pauseAll();

    /** Resume an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    static void resume(int audioID);

    /** Resume all suspended audio instances */
    static void resumeAll();

    /** Stop an audio instance.
     * @param audioID an audioID returned by the play2d function
     */
    static void stop(int audioID);

    /** Stop all audio instances */
    static void stopAll();

    /** Sets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return 
     */
    static bool setCurrentTime(int audioID, float time);

    /** Gets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the current playback position of an audio instance
     */
    static float getCurrentTime(int audioID);

    /** Gets the duration of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the duration of an audio instance
     */
    static float getDuration(int audioID);

    /** Returns the state of an audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the status of an audio instance
     */
    static AudioState getState(int audioID);

    /** Register a callback to be invoked when an audio instance has completed playing.
     * @param audioID an audioID returned by the play2d function
     * @param callback 
     */
    static void setFinishCallback(int audioID, const std::function<void(int,const std::string&)>& callback);
    
    static int getMaxAudioInstance() {return _maxInstances;}
    
    static bool setMaxAudioInstance(int maxInstances);
    
    /** Uncache the audio data from internal buffer.
     * AudioEngine cache audio data on ios platform
     * @warning This can lead to stop related audio first.
     * @param filePath The path of an audio file
     */
    static void uncache(const std::string& filePath);
    
    /** Uncache all audio data from internal buffer.
     * @warning All audio will be stopped first.
     * @param
     */
    static void uncacheAll();
    
    /**  Gets the audio profile by id of audio instance.
     * @param audioID an audioID returned by the play2d function
     * @return the audio profile
     */
    static AudioProfile* getProfile(int audioID);

    /**  Gets the audio profile by name.
     * @param name name of audio profile
     * @return the audio profile
     */
    static AudioProfile* getProfile(const std::string &name);

protected:
    
    static void remove(int audioID);
    
    struct ProfileHelper
    {
        AudioProfile profile;

        std::list<int> audioIDs;

        double lastPlayTime;

        ProfileHelper()
            : lastPlayTime(0.0)
        {

        }
    };
    
    struct AudioInfo
    {
        const std::string* filePath;
        ProfileHelper* profileHelper;
        
        float volume;
        bool loop;
        float duration;
        AudioState state;
        
        bool is3dAudio;

        AudioInfo()
            : profileHelper(nullptr)
            , duration(TIME_UNKNOWN)
            , state(AudioState::INITIALZING)
        {

        }
    };

    //audioID,audioAttribute
    static std::unordered_map<int, AudioInfo> _audioIDInfoMap;
    
    //audio file path,audio IDs
    static std::unordered_map<std::string,std::list<int>> _audioPathIDMap;
    
    //profileName,ProfileHelper
    static std::unordered_map<std::string, ProfileHelper> _audioPathProfileHelperMap;
    
    static int _maxInstances;
    
    static ProfileHelper* _defaultProfileHelper;
    
    static AudioEngineImpl* _audioEngineImpl;
    
    friend class AudioEngineImpl;
};

}
NS_CC_END

#endif // __AUDIO_ENGINE_H_
#endif
