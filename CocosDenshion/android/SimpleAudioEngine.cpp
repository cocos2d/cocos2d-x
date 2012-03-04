/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "SimpleAudioEngine.h"
#include "jni/SimpleAudioEngineJni.h"

namespace CocosDenshion
{
	static SimpleAudioEngine *s_pEngine = 0;

	SimpleAudioEngine::SimpleAudioEngine()
	{

	}

	SimpleAudioEngine::~SimpleAudioEngine()
	{

	}

	SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
	{
		if (! s_pEngine)
		{
			s_pEngine = new SimpleAudioEngine();
		}
        
		return s_pEngine;
	}

	void SimpleAudioEngine::end()
	{
		endJNI();
	}

	void SimpleAudioEngine::setResource(const char* pszZipFileName)
	{

	}

    void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
        preloadBackgroundMusicJNI(pszFilePath);
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
        playBackgroundMusicJNI(pszFilePath, bLoop);
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
		stopBackgroundMusicJNI();
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
		pauseBackgroundMusicJNI();
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
		resumeBackgroundMusicJNI();
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
		rewindBackgroundMusicJNI();
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
		return true;
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
		return isBackgroundMusicPlayingJNI();
	}

	float SimpleAudioEngine::getBackgroundMusicVolume()
	{
		return getBackgroundMusicVolumeJNI();
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
	{
		setBackgroundMusicVolumeJNI(volume);
	}

	float SimpleAudioEngine::getEffectsVolume()
	{
		return getEffectsVolumeJNI();
	}

	void SimpleAudioEngine::setEffectsVolume(float volume)
	{
		setEffectsVolumeJNI(volume);
	}

	unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
	{
		return playEffectJNI(pszFilePath, bLoop);
	}

	void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
	{
		stopEffectJNI(nSoundId);
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
		preloadEffectJNI(pszFilePath);
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
		unloadEffectJNI(pszFilePath);
	}

	void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
	{
		pauseEffectJNI(nSoundId);
	}

	void SimpleAudioEngine::pauseAllEffects()
	{
		pauseAllEffectsJNI();
	}

	void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
	{
		resumeEffectJNI(nSoundId);
	}

	void SimpleAudioEngine::resumeAllEffects()
	{
		resumeAllEffectsJNI();
	}

	void SimpleAudioEngine::stopAllEffects()
	{
		stopAllEffectsJNI();
	}
}
