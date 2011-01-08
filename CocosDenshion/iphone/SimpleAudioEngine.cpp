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
#include "SimpleAudioEngine_objc.h"


namespace CocosDenshion
{
	static SimpleAudioEngine *s_pEngine;

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

	void SimpleAudioEngine::release()
	{
        [[SimpleAudioEngine sharedEngine] end];

		if (s_pEngine)
		{
			delete s_pEngine;
			s_pEngine = NULL;
		}
	}

	void SimpleAudioEngine::setResourcePath(const char *pszResourcePath)
	{

	}

	void SimpleAudioEngine::setResourceZipFile(const char* pszZipPath)
	{

	}

	void SimpleAudioEngine::setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount)
	{

	}


	void SimpleAudioEngine::setResourceEntry(const void* pResEntry)
	{

	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop = false)
	{
		[[SimpleAudioEngine sharedEngine] playBackgroundMusic: [NSString stringWithUTF8String: pszFilePath] loop: bLoop];
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData = false)
	{
        [[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
        [[SimpleAudioEngine sharedEngine] pauseBackgroundMusic];
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
        [[SimpleAudioEngine sharedEngine] resumeBackgroundMusic];
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
        [[SimpleAudioEngine sharedEngine] rewindBackgroundMusic];
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
        return [[SimpleAudioEngine sharedEngine] willPlayBackgroundMusic];
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
        return [[SimpleAudioEngine sharedEngine] isBackgroundMusicPlaying];
	}

	int SimpleAudioEngine::GetBackgroundMusicVolume()
	{
         return (int)[[SimpleAudioEngine sharedEngine] backgroundMusicVolume];
	}

	void SimpleAudioEngine::SetBackgroundMusicVolume(int volume)
	{
        [[SimpleAudioEngine sharedEngine].backgroundMusicVolume = volume;
	}

	int SimpleAudioEngine::GetEffectsVolume()
	{
         return (int)[[SimpleAudioEngine sharedEngine] effectsVolume]
	}

	void SimpleAudioEngine::SetEffectsVolume(int volume)
	{
        [SimpleAudioEngine sharedEngine].effectsVolume = volume;
	}

	int SimpleAudioEngine::playEffect(const char* pszFilePath)
	{
		return [[SimpleAudioEngine sharedEngine] playEffect:[NSString stringWithUTF8String: pszFilePath]]; 
	}

	void SimpleAudioEngine::stopEffect(int nSoundId)
	{
		[[SimpleAudioEngine sharedEngine] stopEffect: nSoundId];
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
        [[SimpleAudioEngine sharedEngine] preloadEffect: [NSString stringWithUTF8String: pszFilePath]];
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
         [[SimpleAudioEngine sharedEngine] unloadEffect: [NSString stringWithUTF8String: pszFilePath]];
	}

	void SimpleAudioEngine::unloadEffectAll()
	{

	}
}