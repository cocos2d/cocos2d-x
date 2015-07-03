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
#ifndef OPENAL

#include "audio/include/SimpleAudioEngine.h"
#include "FmodAudioPlayer.h"
#include "cocos2d.h"
USING_NS_CC;

namespace CocosDenshion {

static AudioPlayer* oAudioPlayer;

SimpleAudioEngine::SimpleAudioEngine() {
	oAudioPlayer = FmodAudioPlayer::sharedPlayer();
}

SimpleAudioEngine::~SimpleAudioEngine() {
}

SimpleAudioEngine* SimpleAudioEngine::getInstance() {
	static SimpleAudioEngine s_SharedEngine;
	return &s_SharedEngine;
}

void SimpleAudioEngine::end() {
    if(oAudioPlayer)
    {
        oAudioPlayer->close();
    }
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
		bool bLoop) {
	// Changing file path to full path
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
	oAudioPlayer->playBackgroundMusic(fullPath.c_str(), bLoop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData) {
	oAudioPlayer->stopBackgroundMusic(bReleaseData);
}

void SimpleAudioEngine::pauseBackgroundMusic() {
	oAudioPlayer->pauseBackgroundMusic();
}

void SimpleAudioEngine::resumeBackgroundMusic() {
	oAudioPlayer->resumeBackgroundMusic();
}

void SimpleAudioEngine::rewindBackgroundMusic() {
	oAudioPlayer->rewindBackgroundMusic();
}

bool SimpleAudioEngine::willPlayBackgroundMusic() {
	return oAudioPlayer->willPlayBackgroundMusic();
}

bool SimpleAudioEngine::isBackgroundMusicPlaying() {
	return oAudioPlayer->isBackgroundMusicPlaying();
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath) {
	// Changing file path to full path
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->preloadBackgroundMusic(fullPath.c_str());
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
                                           float pitch, float pan, float gain) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    return oAudioPlayer->playEffect(fullPath.c_str(), bLoop, pitch, pan, gain);
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
	return oAudioPlayer->stopEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
	// Changing file path to full path
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->preloadEffect(fullPath.c_str());
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
	// Changing file path to full path
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->unloadEffect(fullPath.c_str());
}

void SimpleAudioEngine::pauseEffect(unsigned int uSoundId) {
	oAudioPlayer->pauseEffect(uSoundId);
}

void SimpleAudioEngine::pauseAllEffects() {
	oAudioPlayer->pauseAllEffects();
}

void SimpleAudioEngine::resumeEffect(unsigned int uSoundId) {
	oAudioPlayer->resumeEffect(uSoundId);
}

void SimpleAudioEngine::resumeAllEffects() {
	oAudioPlayer->resumeAllEffects();
}

void SimpleAudioEngine::stopAllEffects() {
	oAudioPlayer->stopAllEffects();
}



//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume() {
	return oAudioPlayer->getBackgroundMusicVolume();
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume) {
	return oAudioPlayer->setBackgroundMusicVolume(volume);
}

float SimpleAudioEngine::getEffectsVolume() {
	return oAudioPlayer->getEffectsVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume) {
	return oAudioPlayer->setEffectsVolume(volume);
}


} // end of namespace CocosDenshion

#endif
