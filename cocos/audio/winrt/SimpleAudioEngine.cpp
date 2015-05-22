/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "SimpleAudioEngine.h"
#include "Audio.h"
#include "cocos2d.h"

#include <map>
//#include "CCCommon.h"
using namespace std;
USING_NS_CC;

namespace CocosDenshion {

Audio* s_audioController = NULL;
bool s_initialized = false;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}


static Audio* sharedAudioController()
{
    if (! s_audioController || !s_initialized)
    {
        if(s_audioController == NULL)
        {
            s_audioController = new Audio;
        }
        s_audioController->Initialize();
        s_audioController->CreateResources();
        s_initialized = true;
    }

    return s_audioController;
}

SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}


void SimpleAudioEngine::end()
{
    sharedAudioController()->StopBackgroundMusic(true);
    sharedAudioController()->StopAllSoundEffects(true);
    sharedAudioController()->ReleaseResources();
    s_initialized = false;
}



//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    if (! pszFilePath)
    {
        return;
    }

    string fullPath = CCFileUtils::getInstance()->fullPathForFilename(pszFilePath);
    sharedAudioController()->PlayBackgroundMusic(fullPath.c_str(), bLoop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    sharedAudioController()->StopBackgroundMusic(bReleaseData);
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    sharedAudioController()->PauseBackgroundMusic();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    sharedAudioController()->ResumeBackgroundMusic();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    sharedAudioController()->RewindBackgroundMusic();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return sharedAudioController()->IsBackgroundMusicPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,float pitch, float pan, float gain)
{
    unsigned int sound;
    string fullPath = CCFileUtils::getInstance()->fullPathForFilename(pszFilePath);
    sharedAudioController()->PlaySoundEffect(fullPath.c_str(), bLoop, sound);    // TODO: need to support playEffect parameters
    return sound;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    sharedAudioController()->StopSoundEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    string fullPath = CCFileUtils::getInstance()->fullPathForFilename(pszFilePath);
    sharedAudioController()->PreloadSoundEffect(fullPath.c_str());
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    sharedAudioController()->PauseSoundEffect(nSoundId);
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    sharedAudioController()->ResumeSoundEffect(nSoundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    sharedAudioController()->PauseAllSoundEffects();
}

void SimpleAudioEngine::resumeAllEffects()
{
    sharedAudioController()->ResumeAllSoundEffects();
}

void SimpleAudioEngine::stopAllEffects()
{
    sharedAudioController()->StopAllSoundEffects(false);
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    UNUSED_PARAM(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    string fullPath = CCFileUtils::getInstance()->fullPathForFilename(pszFilePath);
    sharedAudioController()->UnloadSoundEffect(fullPath.c_str());
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return sharedAudioController()->GetBackgroundVolume();
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
	sharedAudioController()->SetBackgroundVolume((volume<=0.0f)? 0.0f : volume);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return sharedAudioController()->GetSoundEffectVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    sharedAudioController()->SetSoundEffectVolume((volume<=0.0f)? 0.0f : volume);
}

} // end of namespace CocosDenshion
