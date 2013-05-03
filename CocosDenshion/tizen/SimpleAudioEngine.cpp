/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "cocos2d.h"

USING_NS_CC;

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
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    if (!s_pEngine)
    {
        s_pEngine = new SimpleAudioEngine();
    }
    
    return s_pEngine;
}

void SimpleAudioEngine::end()
{
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
}

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
} 

void SimpleAudioEngine::rewindBackgroundMusic()
{
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return true;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return true;
}

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return true;
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
}

float SimpleAudioEngine::getEffectsVolume()
{
    return 0;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
}

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    return 1;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
}

void SimpleAudioEngine::pauseAllEffects()
{
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
}

void SimpleAudioEngine::resumeAllEffects()
{
}

void SimpleAudioEngine::stopAllEffects()
{
}

}
