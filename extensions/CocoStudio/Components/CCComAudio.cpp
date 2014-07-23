/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "cocos-ext.h"
#include "CCComAudio.h"
#include "SimpleAudioEngine.h"

NS_CC_EXT_BEGIN

IMPLEMENT_CLASS_COMPONENT_INFO(CCComAudio)
CCComAudio::CCComAudio(void)
: m_strFilePath("")
, m_bLoop(false)
{
    m_strName = "CCComAudio";
}

CCComAudio::~CCComAudio(void)
{
    
}

bool CCComAudio::init()
{
    return true;
}

void CCComAudio::onEnter()
{
}

void CCComAudio::onExit()
{
    stopBackgroundMusic(true);
    stopAllEffects();
}

bool CCComAudio::isEnabled() const
{
    return m_bEnabled;
}

void CCComAudio::setEnabled(bool b)
{
    m_bEnabled = b;
}

bool CCComAudio::serialize(void* r)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(r == NULL);
		SerData *pSerData = (SerData *)(r);
		const rapidjson::Value *v = pSerData->prData;
		stExpCocoNode *pCocoNode = pSerData->pCocoNode;
		CocoLoader *pCocoLoader = pSerData->pCocoLoader;
		const char *pClassName = NULL;
		const char *pComName = NULL;
		const char *pFile = NULL;
		std::string strFilePath;
		int nResType = 0;
		bool bLoop = false;
		if (v != NULL)
		{
			pClassName = DICTOOL->getStringValue_json(*v, "classname");
			CC_BREAK_IF(pClassName == NULL);
			pComName = DICTOOL->getStringValue_json(*v, "name");
			const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
			CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
			pFile = DICTOOL->getStringValue_json(fileData, "path");
			CC_BREAK_IF(pFile == NULL);
			nResType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
			CC_BREAK_IF(nResType != 0);
			bLoop = DICTOOL->getIntValue_json(*v, "loop") != 0? true:false;
		}
		else if (pCocoNode != NULL)
		{
			pClassName = pCocoNode[1].GetValue(pCocoLoader);
			CC_BREAK_IF(pClassName == NULL);
			pComName = pCocoNode[2].GetValue(pCocoLoader);
			stExpCocoNode *pfileData = pCocoNode[4].GetChildArray(pCocoLoader);
			CC_BREAK_IF(!pfileData);
			pFile = pfileData[0].GetValue(pCocoLoader);
			CC_BREAK_IF(pFile == NULL);
			nResType = atoi(pfileData[2].GetValue(pCocoLoader));
			CC_BREAK_IF(nResType != 0);
			bLoop = atoi(pCocoNode[5].GetValue(pCocoLoader)) != 0? true:false;
			bRet = true;
		}
		if (pComName != NULL)
		{
			setName(pComName);
		}
		else
		{
			setName(pClassName);
		}
		if (pFile != NULL)
		{
            if (strcmp(pFile, "") == 0)
            {
                continue;
            }
			strFilePath.assign(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFile));
		}
		if (strcmp(pClassName, "CCBackgroundAudio") == 0)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
			// no MP3 support for CC_PLATFORM_WP8
			std::string::size_type pos = strFilePath.find(".mp3");
			if (pos  == strFilePath.npos)
			{
				continue;
			}
			strFilePath.replace(pos, strFilePath.length(), ".wav");
#endif
			preloadBackgroundMusic(strFilePath.c_str());
			setLoop(bLoop);
			playBackgroundMusic(strFilePath.c_str(), bLoop);
		}
		else if(strcmp(pClassName, "CCComAudio") == 0)
		{
			preloadEffect(strFilePath.c_str());
		}
		else
		{
			CC_BREAK_IF(true);
		}
		bRet = true;
	}while (0);
	return bRet;
}

CCComAudio* CCComAudio::create(void)
{
    CCComAudio * pRet = new CCComAudio();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void CCComAudio::end()
{
   CocosDenshion::SimpleAudioEngine::end();
}

void CCComAudio::preloadBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(pszFilePath);
    setFile(pszFilePath);
	setLoop(false);
}

void CCComAudio::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath, bLoop);
}

void CCComAudio::playBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pszFilePath);
}

void CCComAudio::playBackgroundMusic()
{
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_strFilePath.c_str(), m_bLoop);
}

void CCComAudio::stopBackgroundMusic(bool bReleaseData)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
}

void CCComAudio::stopBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void CCComAudio::pauseBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void CCComAudio::resumeBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void CCComAudio::rewindBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

bool CCComAudio::willPlayBackgroundMusic()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->willPlayBackgroundMusic();
}

bool CCComAudio::isBackgroundMusicPlaying()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

float CCComAudio::getBackgroundMusicVolume()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void CCComAudio::setBackgroundMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

float CCComAudio::getEffectsVolume()
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}

void CCComAudio::setEffectsVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

unsigned int CCComAudio::playEffect(const char* pszFilePath, bool bLoop)
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath, bLoop);
}

unsigned int CCComAudio::playEffect(const char* pszFilePath)
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath);
}

unsigned int CCComAudio::playEffect()
{
	return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m_strFilePath.c_str(), m_bLoop);
}

void CCComAudio::pauseEffect(unsigned int nSoundId)
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseEffect(nSoundId);
}

void CCComAudio::pauseAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void CCComAudio::resumeEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeEffect(nSoundId);
}

void CCComAudio::resumeAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void CCComAudio::stopEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(nSoundId);
}

void CCComAudio::stopAllEffects()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void CCComAudio::preloadEffect(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(pszFilePath);
    setFile(pszFilePath);
    setLoop(false);
}

void CCComAudio::unloadEffect(const char *pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect(pszFilePath);
}

void CCComAudio::setFile(const char* pszFilePath)
{
	m_strFilePath.assign(pszFilePath);
}

void CCComAudio::setLoop(bool bLoop)
{
	m_bLoop = bLoop;
}

const char* CCComAudio::getFile()
{
	return m_strFilePath.c_str();
}

bool CCComAudio::isLoop()
{
	return m_bLoop;
}

NS_CC_EXT_END
