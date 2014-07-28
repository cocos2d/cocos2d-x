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

#ifndef __AUDIO_ENGINE_H_
#define __AUDIO_ENGINE_H_

#include <string.h>

#include "2d/CCNode.h"

NS_CC_BEGIN
namespace experimental {

/**
  @class          AudioEngine
  @brief          
  @note           
 */

class EXPORT_DLL AudioEngine
{
public:
    enum class SoundState
    {
        ERROR = -1,
        IDLE,
        PLAYING,
        LOOPING,
        PAUSED,
        COMPLETED
    };

    /** Returns a shared instance of the AudioEngine */
    static AudioEngine* getInstance();

    /**
     * Release the shared Audio Engine object
     @warning It must be called before the application exit
     */
    static void destroyInstance();

    /** Play 2d sound
     * @param filePath The path of an audio file
     * @param loop Whether audio instance loop or not
     * @param volume volume value (range from 0.0 to 1.0)
     * @return an audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     */
    int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f);

    /** Sets whether an audio instance loop or not. 
     @param audioID an audioID returned by the play2d/play3d function
     @param loop Whether audio instance loop or not
     */
    void setLoop(int audioID, bool loop);

    /** Checks whether an audio instance is loop.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return 
     */
    bool isLoop(int audioID) const;

    /** Sets volume for an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @param volume volume value (range from 0.0 to 1.0)
     */
    void setVolume(int audioID, float volume);

    /** Gets the volume value of an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return volume value (range from 0.0 to 1.0)
     */
    float getVolume(int audioID) const;

    /** Pause an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     */
    void pause(int audioID);

    /** Resume an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     */
    void resume(int audioID);

    /** Stop an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     */
    void stop(int audioID);

    /** Sets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return 
     */
    void setCurrentTime(int audioID, float time);

    /** Gets the current playback position of an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return the current playback position of an audio instance
     */
    float getCurrentTime(int audioID);

    /** Gets the duration of an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return the duration of an audio instance
     */
    float getDuration(int audioID);

    /** Returns the state of an audio instance.
     * @param audioID an audioID returned by the play2d/play3d function
     * @return the status of an audio instance
     */
    SoundState getState(int audioID) const;

    /** Register a callback to be invoked when an audio instance has completed playing.
     * @param audioID an audioID returned by the play2d/play3d function
     * @param callback 
     */
    void setFinishCallback(int audioID, const std::function<void(int,const std::string&)>& callback);

    /** Place listener
     * In case a Vec2 position is passed in, the z value will always be 0.
     * @param position a Vec2 position
     */
    void setEar(const Vec2& position);

    /** Place listener 
     * @param position a Vec3 position
     */
    void setEar(const Vec3& position);

    /** Place listener 
     * It would be very convenient if you need to place listener at camera.
     * @param node
     */
    void setEar(cocos2d::Node* node);

    /** Sets the position (x,y) of a 3d audio instance.
     * The z value will always be 0.
     * @param audioID an audioID returned by the play3d function
     * @param position a Vec2 position
     */
    void setPosition(int audioID, const Vec2& position);

    /** Sets the position (x,y,z) of a 3d audio instance.
     * @param audioID an audioID returned by the play3d function
     * @param position a Vec3 position
     */
    void setPosition(int audioID, const Vec3& position);

    /** Gets the position (x,y,z) of a 3d audio instance.
     * @param audioID an audioID returned by the play3d function
     * @return  a Vec3 position
     */
    const Vec3& getPosition(int audioID);

    typedef struct _audioProfile
    {
        float miniRange;
        float maxRange;
        float dopplerFactor;
        /* minimum delay in between sounds*/
        float minDelay;
    }AudioProfile;

    /**  Setup profiles for an audio instance.
     * @param audioID an audioID returned by the play3d function
     * @param profile a profile for audio instance
     */
    void setProfile(int audioID, const AudioProfile& profile);

    /**  Gets the profiles of audio instance.
     * @param audioID an audioID returned by the play3d function
     * @return the profile of audio instance
     */
    const AudioProfile* getProfile(int audioID);

    /** Play 3d sound
     * @param filePath The path of an audio file
     * @param position 
     * @param loop Whether the audio instance loop or not
     * @param volume audio volume value (range from 0.0 to 1.0)
     * @param profile a profile of audio instance.When profile is not specified, default profile will be used.
     *
     * @return an audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     */
    int play3d(const std::string& filePath, const Vec2& position, bool loop = false, float volume = 1.0, AudioProfile *profile = nullptr);

    int play3d(const std::string& filePath, const Vec3& position, bool loop = false, float volume = 1.0, AudioProfile *profile = nullptr);

    /** Play 3d sound
     * @param filePath The path of an audio file
     * @param node 
     * @param loop Whether the audio instance loop or not
     * @param volume audio volume value (range from 0.0 to 1.0)
     * @param profile a profile of audio instance.When profile is not specified, default profile will be used.
     *
     * @return a audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
     */
    int play3d(const std::string& filePath, cocos2d::Node* node, bool loop = false, float volume = 1.0, AudioProfile *profile = nullptr);

protected:
    AudioEngine();
    virtual ~AudioEngine();
};

} // end of namespace experimental
NS_CC_END

#endif // __AUDIO_ENGINE_H_
