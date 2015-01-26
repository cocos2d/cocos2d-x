/****************************************************************************
Copyright (c) 2010      Steve Oldmeadow
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include "Export.h"

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define CC_DEPRECATED_ATTRIBUTE
#endif

namespace CocosDenshion {

/**
  @class          SimpleAudioEngine
  @brief          Offers a VERY simple interface to play background music & sound effects.
  @note           Make sure to call SimpleAudioEngine::end() when the sound engine is not needed anymore
                  to release allocated resources.
 */

class EXPORT_DLL SimpleAudioEngine
{
public:
    /**
     @brief Get the shared Engine object,it will new one when first time be called
     */
    static SimpleAudioEngine* getInstance();
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static SimpleAudioEngine* sharedEngine() { return SimpleAudioEngine::getInstance(); }

    /**
     @brief Release the shared Engine object
     @warning It must be called before the application exit, or a memory leak will be casued.
     */
    static void end();

protected:
    SimpleAudioEngine();
    virtual ~SimpleAudioEngine();

public:

    /**
     @brief Preload background music
     @param pszFilePath The path of the background music file.
     * @js preloadMusic
     * @lua preloadMusic
     */
    virtual void preloadBackgroundMusic(const char* pszFilePath);
    
    /**
     @brief Play background music
     @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
     @param bLoop Whether the background music loop or not
     * @js playMusic
     * @lua playMusic
     */
    virtual void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);

    /**
     @brief Stop playing background music
     @param bReleaseData If release the background music data or not.As default value is false
     * @js stopMusic
     * @lua stopMusic
     */
    virtual void stopBackgroundMusic(bool bReleaseData = false);

    /**
     @brief Pause playing background music
     * @js pauseMusic
     * @lua pauseMusic
     */
    virtual void pauseBackgroundMusic();

    /**
     @brief Resume playing background music
     * @js resumeMusic
     * @lua resumeMusic
     */
    virtual void resumeBackgroundMusic();

    /**
     @brief Rewind playing background music
     * @js rewindMusic
     * @lua rewindMusic
     */
    virtual void rewindBackgroundMusic();

    /**
     @brief Indicates whether any background music can be played or not.
     @return <i>true</i> if background music can be played, otherwise <i>false</i>.
     * @js willPlayMusic
     * @lua willPlayMusic
     */
    virtual bool willPlayBackgroundMusic();

    /**
     @brief Indicates whether the background music is playing
     @return <i>true</i> if the background music is playing, otherwise <i>false</i>
     * @js isMusicPlaying
     * @lua isMusicPlaying
     */
    virtual bool isBackgroundMusicPlaying();

    // 
    // properties
    //

    /**
     @brief The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @js getMusicVolume
     * @lua getMusicVolume
     */
    virtual float getBackgroundMusicVolume();

    /**
     @brief Set the volume of background music
     @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
     * @js setMusicVolume
     * @lua setMusicVolume
     */
    virtual void setBackgroundMusicVolume(float volume);

    /**
    @brief The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
    */
    virtual float getEffectsVolume();

    /**
    @brief Set the volume of sound effects
    @param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
    */
    virtual void setEffectsVolume(float volume);

    // 
    // for sound effects

    /**
    @brief Play sound effect with a file path, pitch, pan and gain
    @param pszFilePath The path of the effect file.
    @param bLoop Determines whether to loop the effect playing or not. The default value is false.
    @param pitch Frequency, normal value is 1.0. Will also change effect play time.
    @param pan   Stereo effect, in the range of [-1..1] where -1 enables only left channel.
    @param gain  Volume, in the range of [0..1]. The normal value is 1.
    @return the OpenAL source id

    @note Full support is under development, now there are limitations:
        - no pitch effect on Samsung Galaxy S2 with OpenSL backend enabled;
        - no pitch/pan/gain on emscrippten, win32, marmalade.
    */
    virtual unsigned int playEffect(const char* pszFilePath, bool bLoop = false,
                                    float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);

    /**
    @brief Pause playing sound effect
    @param nSoundId The return value of function playEffect
    */
    virtual void pauseEffect(unsigned int nSoundId);

    /**
    @brief Pause all playing sound effect
    */
    virtual void pauseAllEffects();

    /**
    @brief Resume playing sound effect
    @param nSoundId The return value of function playEffect
    */
    virtual void resumeEffect(unsigned int nSoundId);

    /**
    @brief Resume all playing sound effect
    */
    virtual void resumeAllEffects();

    /**
    @brief Stop playing sound effect
    @param nSoundId The return value of function playEffect
    */
    virtual void stopEffect(unsigned int nSoundId);

    /**
    @brief Stop all playing sound effects
    */
    virtual void stopAllEffects();

    /**
    @brief          preload a compressed audio file
    @details        the compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine
    @param pszFilePath The path of the effect file
    */
    virtual void preloadEffect(const char* pszFilePath);

    /**
    @brief          unload the preloaded effect from internal buffer
    @param pszFilePath        The path of the effect file
    */
    virtual void unloadEffect(const char* pszFilePath);
};

} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_
