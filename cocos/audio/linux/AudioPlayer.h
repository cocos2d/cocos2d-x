/****************************************************************************
Copyright (c) 2011      Laschweinski
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

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

namespace CocosDenshion {

class AudioPlayer {
public:
	virtual void close() = 0;

	/**
	 @brief Preload background music
	 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
	 */
	virtual void preloadBackgroundMusic(const char* pszFilePath) = 0;

	/**
	 @brief Play background music
	 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
	 @param bLoop Whether the background music loop or not
	 */
	virtual void playBackgroundMusic(const char* pszFilePath, bool bLoop = false) = 0;

	/**
	 @brief Stop playing background music
	 @param bReleaseData If release the background music data or not.As default value is false
	 */
	virtual void stopBackgroundMusic(bool bReleaseData = false) = 0;

	/**
	 @brief Pause playing background music
	 */
	virtual void pauseBackgroundMusic() = 0;

	/**
	 @brief Resume playing background music
	 */
	virtual void resumeBackgroundMusic() = 0;

	/**
	 @brief Rewind playing background music
	 */
	virtual void rewindBackgroundMusic() = 0;

	virtual bool willPlayBackgroundMusic() = 0;

	/**
	 @brief Whether the background music is playing
	 @return If is playing return true,or return false
	 */
	virtual bool isBackgroundMusicPlaying() = 0;

	// properties
	/**
	 @brief The volume of the background music max value is 1.0,the min value is 0.0
	 */
	virtual float getBackgroundMusicVolume() = 0;

	/**
	 @brief set the volume of background music
	 @param volume must be in 0.0~1.0
	 */
	virtual void setBackgroundMusicVolume(float volume) = 0;

	/**
	 @brief The volume of the effects max value is 1.0,the min value is 0.0
	 */
	virtual float getEffectsVolume() = 0;

	/**
	 @brief set the volume of sound effecs
	 @param volume must be in 0.0~1.0
	 */
	virtual void setEffectsVolume(float volume) = 0;

	// for sound effects
	/**
	 @brief Play sound effect
	 @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
	 @bLoop Whether to loop the effect playing, default value is false
	 */
	virtual unsigned int playEffect(const char* pszFilePath, bool bLoop,
                                    float pitch, float pan, float gain) = 0;

	/**
	 @brief Stop playing sound effect
	 @param nSoundId The return value of function playEffect
	 */
	virtual void stopEffect(unsigned int nSoundId) = 0;

	/**
	 @brief  		preload a compressed audio file
	 @details	    the compressed audio will be decode to wave, then write into an
	 internal buffer in SimpleaudioEngine
	 */
	virtual void preloadEffect(const char* pszFilePath) = 0;

	/**
	 @brief  		unload the preloaded effect from internal buffer
	 @param[in]		pszFilePath		The path of the effect file,or the FileName of T_SoundResInfo
	 */
	virtual void unloadEffect(const char* pszFilePath) = 0;

	/**
	 @brief  		pause an effect identified by sound id
	 @param[in]		uSoundId 	sound id
	 */
	virtual void pauseEffect(unsigned int uSoundId) = 0;

	/**
	 @brief  		pause all playing effects
	 */
	virtual void pauseAllEffects() = 0;

	/**
	 @brief  		resume an effect identified by sound id
	 @param[in]		uSoundId 	sound id
	 */
	virtual void resumeEffect(unsigned int uSoundId) = 0;

	/**
	 @brief  		resume a effect identified by sound id
	 */
	virtual void resumeAllEffects() = 0;

	/**
	 @brief  		stop all playing effects
	 */
	virtual void stopAllEffects() = 0;
};
}


#endif /* AUDIOPLAYER_H_ */
