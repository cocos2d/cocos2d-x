/*
 * FmodAudioPlayer.cpp
 *
 *  Created on: Aug 18, 2011
 *      Author: laschweinski
 */

#include "FmodAudioPlayer.h"
#include <stdio.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#define szMusicSuffix "|"

namespace CocosDenshion {

FmodAudioPlayer* FmodAudioPlayer::sharedPlayer() {
	static FmodAudioPlayer s_SharedPlayer;
	return &s_SharedPlayer;
}

void ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

FmodAudioPlayer::FmodAudioPlayer() :
		pMusic(0), pBGMChannel(0), iSoundChannelCount(0) {
	init();
}

void FmodAudioPlayer::init(){
	//init
	FMOD_RESULT result;
	FMOD::ChannelGroup *masterChannelGroup;

	unsigned int version;
	/*
	 Create a System object and initialize.
	 */
	result = FMOD::System_Create(&pSystem);
	ERRCHECK(result);

	result = pSystem->setOutput(FMOD_OUTPUTTYPE_ALSA);
	ERRCHECK(result);

	result = pSystem->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	result = pSystem->createChannelGroup("Channel Group", &pChannelGroup);
	ERRCHECK(result);

	result = pSystem->getMasterChannelGroup(&masterChannelGroup);
	ERRCHECK(result);

	result = masterChannelGroup->addGroup(pChannelGroup);
	ERRCHECK(result);

	mapEffectSound.clear();

}

void FmodAudioPlayer::close() {
	FMOD_RESULT result;
	//BGM
	if (pBGMChannel != NULL) {
		result = pBGMChannel->stop();
		ERRCHECK(result);
		pBGMChannel = 0;
	}

	if (pMusic != NULL) {
		result = pMusic->release();
		ERRCHECK(result);
		pMusic = 0;
	}

	result = pChannelGroup->release();
	ERRCHECK(result);
	sMusicPath.clear();

	result = pSystem->close();
	ERRCHECK(result);
	result = pSystem->release();
	ERRCHECK(result);

	init();
}

FmodAudioPlayer::~FmodAudioPlayer() {
	FMOD_RESULT result;
	//BGM
	if (pBGMChannel != NULL) {
		result = pBGMChannel->stop();
		ERRCHECK(result);
	}

	if (pMusic != NULL) {
		result = pMusic->release();
		ERRCHECK(result);
	}

	result = pChannelGroup->release();
	ERRCHECK(result);

	result = pSystem->close();
	ERRCHECK(result);
	result = pSystem->release();
	ERRCHECK(result);
}

// BGM
void FmodAudioPlayer::preloadBackgroundMusic(const char* pszFilePath) {
	FMOD_RESULT result;
	pSystem->update();
	string sNewMusicPath = string(pszFilePath) + szMusicSuffix;
	if (pMusic && sNewMusicPath != sMusicPath) {
		//release old
		result = pMusic->release();
		ERRCHECK(result);

		sMusicPath = sNewMusicPath;

	}

	result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL, 0, &pMusic);
	ERRCHECK(result);
}

void FmodAudioPlayer::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
	pSystem->update();
	if (pMusic == NULL) {
		//did not load it
		//load the new music
		FMOD_RESULT result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL,
				0, &pMusic);
		ERRCHECK(result);
		sMusicPath = string(pszFilePath) + szMusicSuffix;
	} else {
		string sNewMusicPath = string(pszFilePath) + szMusicSuffix;
		if (pBGMChannel) {
			pBGMChannel->stop();
			pBGMChannel = 0;
		}

		if (sNewMusicPath != sMusicPath) {

			pMusic->release();
			//load the new music
			FMOD_RESULT result = pSystem->createSound(pszFilePath,
					FMOD_LOOP_NORMAL, 0, &pMusic);
			sMusicPath = sNewMusicPath;
			ERRCHECK(result);
		}

	}

	FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, pMusic, true,
			&pBGMChannel);
	ERRCHECK(result);

	pBGMChannel->setLoopCount((bLoop) ? -1 : 1);
	result = pBGMChannel->setPaused(false);
	ERRCHECK(result);
}

void FmodAudioPlayer::stopBackgroundMusic(bool bReleaseData) {
	FMOD_RESULT result;
	pSystem->update();

	if (pBGMChannel == NULL || pMusic == NULL) {
		return;
	}
	if (bReleaseData) {
		result = pBGMChannel->stop();
		ERRCHECK(result);
		result = pMusic->release();
		ERRCHECK(result);
		pBGMChannel = 0;
	} else {
		result = pBGMChannel->stop();
		ERRCHECK(result);
		pBGMChannel = 0;
	}
	sMusicPath.clear();

}

void FmodAudioPlayer::pauseBackgroundMusic() {
	if (pBGMChannel == NULL) {
		return;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->setPaused(true);
	ERRCHECK(result);

}

void FmodAudioPlayer::resumeBackgroundMusic() {
	if (pBGMChannel == NULL) {
		return;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->setPaused(false);
	ERRCHECK(result);
}

void FmodAudioPlayer::rewindBackgroundMusic() {
	if (pBGMChannel == NULL) {
		return;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->setPosition(0, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);
}

bool FmodAudioPlayer::willPlayBackgroundMusic() {
	pSystem->update();
	return false; //do it according to win
}

bool FmodAudioPlayer::isBackgroundMusicPlaying() {
	bool bPlaying;
	if (pBGMChannel == NULL) {
		return false;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->isPlaying(&bPlaying);
	ERRCHECK(result);
	return bPlaying;

}

float FmodAudioPlayer::getBackgroundMusicVolume() {
	float fVolumn;
	if (pBGMChannel == NULL) {
		return 0;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->getVolume(&fVolumn);
	ERRCHECK(result);
	return fVolumn;
}

void FmodAudioPlayer::setBackgroundMusicVolume(float volume) {
	if (pBGMChannel == NULL) {
		return;
	}
	pSystem->update();
	FMOD_RESULT result = pBGMChannel->setVolume(volume);
	ERRCHECK(result);

}
//~BGM

// for sound effects
float FmodAudioPlayer::getEffectsVolume() {
	float fVolumn;
	pSystem->update();
	FMOD_RESULT result = pChannelGroup->getVolume(&fVolumn);
	ERRCHECK(result);
}

void FmodAudioPlayer::setEffectsVolume(float volume) {
	pSystem->update();
	FMOD_RESULT result = pChannelGroup->setVolume(volume);
	ERRCHECK(result);

}

unsigned int FmodAudioPlayer::playEffect(const char* pszFilePath, bool bLoop) {
	FMOD::Channel* pChannel;
	FMOD::Sound* pSound = NULL;

	pSystem->update();

	map<string, FMOD::Sound*>::iterator l_it = mapEffectSound.find(
			string(pszFilePath));
	if (l_it == mapEffectSound.end()) {
		//no load it yet
		preloadEffect(pszFilePath);
		l_it = mapEffectSound.find(string(pszFilePath));
	}
	pSound = l_it->second;
	assert(pSound);

	FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, pSound, true,
			&pChannel);
	ERRCHECK(result);

	pChannel->setChannelGroup(pChannelGroup);

	//set its loop
	pChannel->setLoopCount((bLoop) ? -1 : 1);
	result = pChannel->setPaused(false);

	mapEffectSoundChannel[iSoundChannelCount] = pChannel;

	return iSoundChannelCount++;
}

void FmodAudioPlayer::stopEffect(unsigned int nSoundId) {
	FMOD::Channel* pChannel;
	pSystem->update();

	map<unsigned int, FMOD::Channel*>::iterator l_it =
			mapEffectSoundChannel.find(nSoundId);
	if (l_it == mapEffectSoundChannel.end()) {
		//no play  yet
		return;
	}
	pChannel = l_it->second;
	//stop the channel;
	pChannel->stop();

	//delete from the map;
	mapEffectSoundChannel.erase(nSoundId);
}

void FmodAudioPlayer::preloadEffect(const char* pszFilePath) {
	FMOD::Sound* pLoadSound;

	pSystem->update();
	FMOD_RESULT result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL, 0,
			&pLoadSound);
	ERRCHECK(result);

	mapEffectSound[string(pszFilePath)] = pLoadSound;

}

void FmodAudioPlayer::unloadEffect(const char* pszFilePath) {
	FMOD::Sound* pSound;
	pSystem->update();

	map<string, FMOD::Sound*>::iterator l_it = mapEffectSound.find(
			string(pszFilePath));
	if (l_it == mapEffectSound.end()) {
		//no load  yet
		return;
	}
	pSound = l_it->second;

	//release the sound;
	pSound->release();

	//delete from the map
	mapEffectSound.erase(string(pszFilePath));
}

//~for sound effects

} /* namespace CocosDenshion */
