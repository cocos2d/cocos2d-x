#include "SimpleAudioEngine.h"
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

SimpleAudioEngine* SimpleAudioEngine::sharedEngine() {
	static SimpleAudioEngine s_SharedEngine;
	return &s_SharedEngine;
}

void SimpleAudioEngine::end() {
	oAudioPlayer->close();
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
		bool bLoop) {
	// Changing file path to full path
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
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
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->preloadBackgroundMusic(fullPath.c_str());
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath,
		bool bLoop) {
	// Changing file path to full path
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->playEffect(fullPath.c_str(), bLoop);
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
	return oAudioPlayer->stopEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
	// Changing file path to full path
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
	return oAudioPlayer->preloadEffect(fullPath.c_str());
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
	// Changing file path to full path
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFilePath);
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
