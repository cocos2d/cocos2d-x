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
#include "opensl/SimpleAudioEngineOpenSL.h"

#include "cocos2d.h"
#include <cstring>
#include <android/log.h>
#include <jni/JniHelper.h>
#include <jni.h>

#define  I9100_MODEL "GT-I9100"
#define  LOG_TAG     "Device Model"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

static bool s_bI9100 = false;

USING_NS_CC;
/**********************************************************************************
 *   jni
 **********************************************************************************/
#define  CLASS_NAME   "org/cocos2dx/lib/Cocos2dxHelper"
#define  METHOD_NAME  "getDeviceModel"

namespace CocosDenshion {

static std::string getFullPathWithoutAssetsPrefix(const char* pszFilename)
{
	// Changing file path to full path
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilename);
    // Removing `assets` since it isn't needed for the API of playing sound.
    size_t pos = fullPath.find("assets/");
    if (pos == 0)
    {
    	fullPath = fullPath.substr(strlen("assets/"));
    }
    return fullPath;
}

static SimpleAudioEngine *s_pEngine = 0;

SimpleAudioEngine::SimpleAudioEngine()
{
	JniMethodInfo methodInfo;
	jstring jstr;
	if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, METHOD_NAME, "()Ljava/lang/String;"))
	{
		jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	}
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	
	const char* deviceModel = methodInfo.env->GetStringUTFChars(jstr, NULL);
    
	LOGD("%s", deviceModel);
    
	if (strcmp(I9100_MODEL, deviceModel) == 0)
	{
		LOGD("i9100 model\nSwitch to OpenSLES");
		s_bI9100 = true;
	}
    
	methodInfo.env->ReleaseStringUTFChars(jstr, deviceModel);
	methodInfo.env->DeleteLocalRef(jstr);
}

SimpleAudioEngine::~SimpleAudioEngine()
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->end();
	}
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
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->end();
	}
	else
	{
		endJNI();
	}
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    std::string fullPath = getFullPathWithoutAssetsPrefix(pszFilePath);
    preloadBackgroundMusicJNI(fullPath.c_str());
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	std::string fullPath = getFullPathWithoutAssetsPrefix(pszFilePath);
    playBackgroundMusicJNI(fullPath.c_str(), bLoop);
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
	if (s_bI9100)
	{
		return SimpleAudioEngineOpenSL::sharedEngine()->getEffectsVolume();
	}
	else
	{
		return getEffectsVolumeJNI();
	}
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->setEffectsVolume(volume);
	}
	else
	{
		setEffectsVolumeJNI(volume);
	}
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
	std::string fullPath = getFullPathWithoutAssetsPrefix(pszFilePath);
	if (s_bI9100)
	{
		return SimpleAudioEngineOpenSL::sharedEngine()->playEffect(fullPath.c_str(), bLoop);
	}
	else 
	{
		return playEffectJNI(fullPath.c_str(), bLoop);
	}
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->stopEffect(nSoundId);
	}
	else
	{
		stopEffectJNI(nSoundId);
	}
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	std::string fullPath = getFullPathWithoutAssetsPrefix(pszFilePath);

	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->preloadEffect(fullPath.c_str());
	}
	else
	{
		preloadEffectJNI(fullPath.c_str());
	}
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	std::string fullPath = getFullPathWithoutAssetsPrefix(pszFilePath);

	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->unloadEffect(fullPath.c_str());
	}
	else
	{
		unloadEffectJNI(fullPath.c_str());
	}
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->pauseEffect(nSoundId);
	}
	else
	{
		pauseEffectJNI(nSoundId);
	}
}

void SimpleAudioEngine::pauseAllEffects()
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->pauseAllEffects();
	}
	else
	{
		pauseAllEffectsJNI();
	}
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->resumeEffect(nSoundId);
	}
	else
	{
		resumeEffectJNI(nSoundId);
	}
}

void SimpleAudioEngine::resumeAllEffects()
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->resumeAllEffects();
	}
	else
	{
		resumeAllEffectsJNI();
	}
}

void SimpleAudioEngine::stopAllEffects()
{
	if (s_bI9100)
	{
		SimpleAudioEngineOpenSL::sharedEngine()->stopAllEffects();
	}
	else
	{
		stopAllEffectsJNI();
	}
}

}
