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

#ifndef FMODAUDIOPLAYER_H_
#define FMODAUDIOPLAYER_H_

#include "fmod.hpp"
#include "fmod_errors.h"
#include "AudioPlayer.h"
#include "string"
#include <map>


using namespace std;

namespace CocosDenshion {

class FmodAudioPlayer : public AudioPlayer{
public:
	FmodAudioPlayer();
	virtual ~FmodAudioPlayer();

	static FmodAudioPlayer* sharedPlayer();

	virtual void close();



	/**
	 @brief Preload background music
	 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
	 */
	virtual void preloadBackgroundMusic(const char* pszFilePath);

	/**
	 @brief Play background music
	 @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
	 @param bLoop Whether the background music loop or not
	 */
	virtual void playBackgroundMusic(const char* pszFilePath, bool bLoop);

	/**
	 @brief Stop playing background music
	 @param bReleaseData If release the background music data or not.As default value is false
	 */
	virtual void stopBackgroundMusic(bool bReleaseData);

	/**
	 @brief Pause playing background music
	 */
	virtual void pauseBackgroundMusic();

	/**
	 @brief Resume playing background music
	 */
	virtual void resumeBackgroundMusic();

	/**
	 @brief Rewind playing background music
	 */
	virtual void rewindBackgroundMusic();

	virtual bool willPlayBackgroundMusic();

	/**
	 @brief Whether the background music is playing
	 @return If is playing return true,or return false
	 */
	virtual bool isBackgroundMusicPlaying();

	// properties
	/**
	 @brief The volume of the background music max value is 1.0,the min value is 0.0
	 */
	virtual float getBackgroundMusicVolume();

	/**
	 @brief set the volume of background music
	 @param volume must be in 0.0~1.0
	 */
	virtual void setBackgroundMusicVolume(float volume);

	/**
	 @brief The volume of the effects max value is 1.0,the min value is 0.0
	 */
	virtual float getEffectsVolume();

	/**
	 @brief set the volume of sound effecs
	 @param volume must be in 0.0~1.0
	 */
	virtual void setEffectsVolume(float volume);

	// for sound effects
	/**
	 @brief Play sound effect
	 @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
	 @bLoop Whether to loop the effect playing, default value is false
	 */
	virtual unsigned int playEffect(const char* pszFilePath, bool bLoop,
                                    float pitch, float pan, float gain);

	/**
	 @brief Stop playing sound effect
	 @param nSoundId The return value of function playEffect
	 */
	virtual void stopEffect(unsigned int nSoundId);

	/**
	 @brief  		preload a compressed audio file
	 @details	    the compressed audio will be decode to wave, then write into an
	 internal buffer in SimpleaudioEngine
	 */
	virtual void preloadEffect(const char* pszFilePath);

	/**
	 @brief  		unload the preloaded effect from internal buffer
	 @param[in]		pszFilePath		The path of the effect file,or the FileName of T_SoundResInfo
	 */
	virtual void unloadEffect(const char* pszFilePath);

	/**
	 @brief  		pause an effect identified by sound id
	 @param[in]		uSoundId 	sound id
	 */
	virtual void pauseEffect(unsigned int uSoundId);

	/**
	 @brief  		pause all playing effects
	 */
	virtual void pauseAllEffects();

	/**
	 @brief  		resume an effect identified by sound id
	 @param[in]		uSoundId 	sound id
	 */
	virtual void resumeEffect(unsigned int uSoundId);

	/**
	 @brief  		resume a effect identified by sound id
	 */
	virtual void resumeAllEffects();

	/**
	 @brief  		stop all playing effects
	 */
	virtual void stopAllEffects();

private:

	void init();
	map<string, FMOD::Sound*> mapEffectSound;
	map<unsigned int, FMOD::Channel*> mapEffectSoundChannel;

	FMOD::System* 	pSystem;
	FMOD::Sound* 	pMusic;   //BGM
	FMOD::Channel* 	pBGMChannel;

	FMOD::ChannelGroup* pChannelGroup;

	unsigned int iSoundChannelCount;

	string sMusicPath;

};

} /* namespace CocosDenshion */
#endif /* FMODAUDIOPLAYER_H_ */
