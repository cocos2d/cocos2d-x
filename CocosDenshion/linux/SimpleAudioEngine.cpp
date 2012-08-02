#include "SimpleAudioEngine.h"
#include "FmodAudioPlayer.h"

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

//    sharedMusic().Close();
//
//	EffectList::iterator p = sharedList().begin();
//	while (p != sharedList().end())
//	{
//		delete p->second;
//		p->second = NULL;
//		p++;
//	}
//    sharedList().clear();
//    return;
}

//void SimpleAudioEngine::setResource(const char* pszZipFileName) {
//}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
		bool bLoop) {
	oAudioPlayer->playBackgroundMusic(pszFilePath, bLoop);
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
	return oAudioPlayer->preloadBackgroundMusic(pszFilePath);
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath,
		bool bLoop) {
	return oAudioPlayer->playEffect(pszFilePath, bLoop);
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId) {
	return oAudioPlayer->stopEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath) {
	return oAudioPlayer->preloadEffect(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath) {
	return oAudioPlayer->unloadEffect(pszFilePath);
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
	return oAudioPlayer->getBackgroundMusicVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume) {
	return oAudioPlayer->setEffectsVolume(volume);
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

const char * _FullPath(const char * szPath) {
}

unsigned int _Hash(const char *key) {
//    unsigned int len = strlen(key);
//    const char *end=key+len;
//    unsigned int hash;
//
//    for (hash = 0; key < end; key++)
//    {
//        hash *= 16777619;
//        hash ^= (unsigned int) (unsigned char) toupper(*key);
//    }
//    return (hash);
}

} // end of namespace CocosDenshion
