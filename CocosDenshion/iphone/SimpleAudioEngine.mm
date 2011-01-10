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

static void static_release()
{
    [SimpleAudioEngine  end];
}

static void static_preloadBackgroundMusic(const char* pszFilePath)
{
    [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic: [NSString stringWithUTF8String: pszFilePath]];
}

static void static_playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    [[SimpleAudioEngine sharedEngine] playBackgroundMusic: [NSString stringWithUTF8String: pszFilePath] loop: bLoop];
}

static void static_stopBackgroundMusic()
{
    [[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
}

static void static_pauseBackgroundMusic()
{
     [[SimpleAudioEngine sharedEngine] pauseBackgroundMusic];
}

static void static_resumeBackgroundMusic()
{
    [[SimpleAudioEngine sharedEngine] resumeBackgroundMusic];
} 

static void static_rewindBackgroundMusic()
{
    [[SimpleAudioEngine sharedEngine] rewindBackgroundMusic];
}

static bool static_willPlayBackgroundMusic()
{
    return [[SimpleAudioEngine sharedEngine] willPlayBackgroundMusic];
}

static bool static_isBackgroundMusicPlaying()
{
    return [[SimpleAudioEngine sharedEngine] isBackgroundMusicPlaying];
}

static int static_getBackgroundMusicVolume()
{
    return (int)[[SimpleAudioEngine sharedEngine] backgroundMusicVolume];
}

static void static_setBackgroundMusicVolume(int volume)
{
    [SimpleAudioEngine sharedEngine].backgroundMusicVolume = volume;
}
     
static int static_getEffectsVolume()
{
    return (int)[[SimpleAudioEngine sharedEngine] effectsVolume];
}
     
static void static_setEffectsVolume(int volume)
{
    [SimpleAudioEngine sharedEngine].effectsVolume = volume;
}
     
static int static_playEffect(const char* pszFilePath)
{
    return [[SimpleAudioEngine sharedEngine] playEffect:[NSString stringWithUTF8String: pszFilePath]]; 
}
     
static void static_stopEffect(int nSoundId)
{
    [[SimpleAudioEngine sharedEngine] stopEffect: nSoundId];
}
     
static void static_preloadEffect(const char* pszFilePath)
{
    [[SimpleAudioEngine sharedEngine] preloadEffect: [NSString stringWithUTF8String: pszFilePath]];
}
     
static void static_unloadEffect(const char* pszFilePath)
{
    [[SimpleAudioEngine sharedEngine] unloadEffect: [NSString stringWithUTF8String: pszFilePath]];
}

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
		if (s_pEngine)
		{
			delete s_pEngine;
			s_pEngine = NULL;
		}
        
                static_release();
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
    
        void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
	{
		static_preloadBackgroundMusic(pszFilePath);
	}

	void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
	{
		static_playBackgroundMusic(pszFilePath, bLoop);
	}

	void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
	{
                static_stopBackgroundMusic();
	}

	void SimpleAudioEngine::pauseBackgroundMusic()
	{
                static_pauseBackgroundMusic();
	}

	void SimpleAudioEngine::resumeBackgroundMusic()
	{
                static_resumeBackgroundMusic();
	} 

	void SimpleAudioEngine::rewindBackgroundMusic()
	{
                static_rewindBackgroundMusic();
	}

	bool SimpleAudioEngine::willPlayBackgroundMusic()
	{
                return static_willPlayBackgroundMusic();
	}

	bool SimpleAudioEngine::isBackgroundMusicPlaying()
	{
                return static_isBackgroundMusicPlaying();
	}

	int SimpleAudioEngine::getBackgroundMusicVolume()
	{
                return (int)static_getBackgroundMusicVolume();
	}

	void SimpleAudioEngine::setBackgroundMusicVolume(int volume)
	{
                 static_setBackgroundMusicVolume(volume);
	}

	int SimpleAudioEngine::getEffectsVolume()
	{
                return (int)static_getEffectsVolume();
	}

	void SimpleAudioEngine::setEffectsVolume(int volume)
	{
                static_setEffectsVolume(volume);
	}

	int SimpleAudioEngine::playEffect(const char* pszFilePath)
	{
                return static_playEffect(pszFilePath);
	}

	void SimpleAudioEngine::stopEffect(int nSoundId)
	{
                static_stopEffect(nSoundId);
	}

	void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
	{
                static_preloadEffect(pszFilePath);
	}

	void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
	{
                static_unloadEffect(pszFilePath);
	}

	void SimpleAudioEngine::unloadEffectAll()
	{

	}
}