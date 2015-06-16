/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

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

/**
 * @addtogroup audio
 * @{
 */

NS_CC_BEGIN
    namespace experimental{

/**
 * @class @~english AudioProfile
 *
 * @brief
 * @~chinese AudioProfile
 * 
 * @brief
 * @js NA
 */
class EXPORT_DLL AudioProfile
{
public:
    //Profile name can't be empty.
    std::string name;
    //The maximum number of simultaneous audio instance.
    unsigned int maxInstances;
    
    /* @~english Minimum delay in between sounds  @~chinese 最小声音之间的延迟*/
    double minDelay;
    
    /**@~english
     * Defautl constructor
     *
     * @~chinese 
     * 默认构造函数
     * 
     * @lua new
     */
    AudioProfile()
    : maxInstances(0)
    , minDelay(0.0)
    {
        
    }
};

class AudioEngineImpl;

/**
 * @class @~english AudioEngine
 *
 * @~chinese )
 * 
 * @brief @~english Offers a interface to play audio.
 *
 * @~chinese 提供了一个音频播放接口。
 * 
 * @note @~english Make sure to call AudioEngine::end() when the audio engine is not needed anymore to release resources.
 * @~chinese 当音频引擎不再需要时确保调用AudioEngine::end()以释放资源。
 * @js NA
 */
class EXPORT_DLL AudioEngine
{
public:
    /** @~english AudioState enum,all possible states of an audio instance. @~chinese 音频状态枚举,音频的所有可能状态。*/
    enum class AudioState
    {
        ERROR  = -1,
        INITIALZING,
        PLAYING,
        PAUSED
    };
    
    static const int INVALID_AUDIO_ID;

    static const float TIME_UNKNOWN;

    static bool lazyInit();

    /**@~english
     * Release objects relating to AudioEngine.
     *
     * @~chinese 
     * 释放音频引擎的相关对象.
     * 
     * @warning @~english It must be called before the application exit.
     * @~chinese 在应用程序退出之前必须要调用它。
     */
    static void end();
    
    /**  @~english
     * Gets the default profile of audio instances.
     *
     * @~chinese 
     * 得到音频的默认的配置。
     * 
     * @return @~english The default profile of audio instances.
     * @~chinese 音频的默认的配置。
     */
    static AudioProfile* getDefaultProfile();
    
    /** @~english
     * Play 2d sound.
     *
     * @~chinese 
     * Play 2d sound.
     * 
     * @param filePath @~english The path of an audio file.
     * @~chinese 一个音频文件的路径。
     * @param loop @~english Whether audio instance loop or not.
     * @~chinese 音频是否循环播放。
     * @param volume @~english Volume value (range from 0.0 to 1.0).
     * @~chinese 音量值(范围从0.0到1.0)。
     * @param profile @~english A profile for audio instance. When profile is not specified, default profile will be used.
     * @~chinese 音频的一个配置文件。当没有指定配置文件,将使用默认的配置。
     * @return @~english An audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     *
     * @~chinese 一个音频ID。它允许您动态地改变一个音频实例的行为。
     * 
     * @see `AudioProfile`
     */
    static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);
    
    /** @~english
     * Sets whether an audio instance loop or not.
     *
     * @~chinese 
     * 设置一个音频实例是否循环播放。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @param loop @~english Whether audio instance loop or not.
     * @~chinese 是否循环播放。
     */
    static void setLoop(int audioID, bool loop);

    /** @~english
     * Checks whether an audio instance is loop.
     *
     * @~chinese 
     * 检查一个音频实例是否循环播放。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english Whether or not an audio instance is loop.
     * @~chinese 是否循环播放。
     */
    static bool isLoop(int audioID);

    /** @~english
     * Sets volume for an audio instance.
     *
     * @~chinese 
     * 设置一个音频实例的音量大小。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @param volume @~english Volume value (range from 0.0 to 1.0).
     * @~chinese 音量值(范围从0.0到1.0)。
     */
    static void setVolume(int audioID, float volume);

    /** @~english
     * Gets the volume value of an audio instance.
     *
     * @~chinese 
     * 返回一个音频实例的音量值。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english Volume value (range from 0.0 to 1.0).
     * @~chinese 音量值(范围从0.0到1.0)。
     */
    static float getVolume(int audioID);

    /** @~english
     * Pause an audio instance.
     *
     * @~chinese 
     * 暂停一个音频实例。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     */
    static void pause(int audioID);

    /** @~english Pause all playing audio instances.  @~chinese 暂停所有正在播放的音频实例。 */
    static void pauseAll();

    /** @~english
     * Resume an audio instance.
     *
     * @~chinese 
     * 恢复一个已暂停的音频实例。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     */
    static void resume(int audioID);

    /** @~english Resume all suspended audio instances.  @~chinese 恢复所有暂停音频实例。*/
    static void resumeAll();

    /** @~english
     * Stop an audio instance.
     *
     * @~chinese 
     * 停止一个音频实例。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     */
    static void stop(int audioID);

    /** @~english Stop all audio instances.  @~chinese 停止所有音频实例。*/
    static void stopAll();

    /**@~english
     * Sets the current playback position of an audio instance.
     *
     * @~chinese 
     * 设置一个音频实例的当前播放位置。
     * 
     * @param audioID   @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @param sec       @~english The offset in seconds from the start to seek to.
     * @~chinese 以秒为单位的相对于开始位置的偏移量。
     * @return 
     */
    static bool setCurrentTime(int audioID, float sec);

    /** @~english
     * Gets the current playback position of an audio instance.
     *
     * @~chinese 
     * 返回一个音频实例的当前播放位置。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english The current playback position of an audio instance.
     * @~chinese 音频实例的当前播放位置。
     */
    static float getCurrentTime(int audioID);

    /** @~english
     * Gets the duration of an audio instance.
     *
     * @~chinese 
     * 得到一个音频实例的持续时间。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english The duration of an audio instance.
     * @~chinese 一个音频的持续时间。
     */
    static float getDuration(int audioID);

    /** @~english
     * Returns the state of an audio instance.
     *
     * @~chinese 
     * 返回一个音频实例的状态。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english The status of an audio instance.
     * @~chinese 音频实例的状态。
     */
    static AudioState getState(int audioID);

    /** @~english
     * Register a callback to be invoked when an audio instance has completed playing.
     *
     * @~chinese 
     * 设置一个在音频实例播放完成时要进行的回调。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @param @~english callback
     * @~chinese 回调
     */
    static void setFinishCallback(int audioID, const std::function<void(int,const std::string&)>& callback);
    
    /**@~english
     * Gets the maximum number of simultaneous audio instance of AudioEngine.
     * @~chinese 
     * 返回音频引擎的最大并发数。
     */
    static int getMaxAudioInstance() {return _maxInstances;}
    
    /**@~english
     * Sets the maximum number of simultaneous audio instance for AudioEngine.
     *
     * @~chinese 
     * 设置音频引擎的最大并发数。
     * 
     * @param maxInstances @~english The maximum number of simultaneous audio instance.
     * @~chinese 同时可播放的音频实例最大数量。
     */
    static bool setMaxAudioInstance(int maxInstances);
    
    /** @~english
     * Uncache the audio data from internal buffer.
     * AudioEngine cache audio data on ios,mac, and win32 platform.
     *
     * @~chinese 
     * 从内部缓冲区取消一个音频数据的缓存。
     * 音频引擎会在ios、mac和win32平台上缓存音频数据。
     * 
     * @warning @~english This can lead to stop related audio first.
     * @~chinese 这可能导致停止相关的音频。
     * @param filePath @~english Audio file path.
     * @~chinese 音频文件路径。
     */
    static void uncache(const std::string& filePath);
    
    /** @~english
     * Uncache all audio data from internal buffer.
     *
     * @~chinese 
     * 从内部缓冲区取消所有音频缓存数据。
     * 
     * @warning @~english All audio will be stopped first.
     * @~chinese 所有音频将被停止。
     */
    static void uncacheAll();
    
    /**  @~english
     * Gets the audio profile by id of audio instance.
     *
     * @~chinese 
     * 通过音频ID返回它的配置。
     * 
     * @param audioID @~english An audioID returned by the play2d function.
     * @~chinese 一个play2d函数返回的音频ID。
     * @return @~english The audio profile.
     * @~chinese 音频配置。
     */
    static AudioProfile* getProfile(int audioID);

    /**  @~english
     * Gets an audio profile by name.
     *
     * @~chinese 
     * 通过音频配置文件返回一个音频配置。
     * 
     * @param profileName @~english A name of audio profile.
     * @~chinese 音频配置文件。
     * @return @~english The audio profile.
     * @~chinese 音频配置。
     */
    static AudioProfile* getProfile(const std::string &profileName);

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
    
    static unsigned int _maxInstances;
    
    static ProfileHelper* _defaultProfileHelper;
    
    static AudioEngineImpl* _audioEngineImpl;
    
    friend class AudioEngineImpl;
};

}
NS_CC_END

// end group
/// @}

#endif // __AUDIO_ENGINE_H_
#endif
