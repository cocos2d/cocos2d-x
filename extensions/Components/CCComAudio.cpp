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

#include "CCComAudio.h"
#include "SimpleAudioEngine.h"

NS_CC_EXT_BEGIN

ComAudio::ComAudio(void)
{
    _name = "Audio";
}

ComAudio::~ComAudio(void)
{
    
}

bool ComAudio::init()
{
    return true;
}

void ComAudio::onEnter()
{
}

void ComAudio::onExit()
{
    stopBackgroundMusic(true);
    stopAllEffects();
}

bool ComAudio::isEnabled() const
{
    return _enabled;
}

void ComAudio::setEnabled(bool b)
{
    _enabled = b;
}

ComAudio* ComAudio::create(void)
{
    ComAudio * pRet = new ComAudio();
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

void ComAudio::end()
{
   CocosDenshion::SimpleAudioEngine::end();
}

void ComAudio::preloadBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(pszFilePath);
}

void ComAudio::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, bLoop);
}

void ComAudio::playBackgroundMusic(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath);
}

void ComAudio::stopBackgroundMusic(bool bReleaseData)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(bReleaseData);
}

void ComAudio::stopBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void ComAudio::pauseBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void ComAudio::resumeBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void ComAudio::rewindBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
}

bool ComAudio::willPlayBackgroundMusic()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->willPlayBackgroundMusic();
}

bool ComAudio::isBackgroundMusicPlaying()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

float ComAudio::getBackgroundMusicVolume()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

void ComAudio::setBackgroundMusicVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

float ComAudio::getEffectsVolume()
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void ComAudio::setEffectsVolume(float volume)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

unsigned int ComAudio::playEffect(const char* pszFilePath, bool bLoop)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, bLoop);
}

unsigned int ComAudio::playEffect(const char* pszFilePath)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath);
}

void ComAudio::pauseEffect(unsigned int nSoundId)
{
    return CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(nSoundId);
}

void ComAudio::pauseAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void ComAudio::resumeEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(nSoundId);
}

void ComAudio::resumeAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void ComAudio::stopEffect(unsigned int nSoundId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(nSoundId);
}

void ComAudio::stopAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void ComAudio::preloadEffect(const char* pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(pszFilePath);
}

void ComAudio::unloadEffect(const char *pszFilePath)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(pszFilePath);
}


NS_CC_EXT_END
