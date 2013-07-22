#ifndef __CDDANDRIODANDROIDJAVAENGINE_H__
#define __CDDANDRIODANDROIDJAVAENGINE_H__

#include "SimpleAudioEngine.h"

namespace CocosDenshion {
    namespace android {
        class AndroidJavaEngine : public SimpleAudioEngine {
            ~AndroidJavaEngine();

            void preloadBackgroundMusic(const char* pszFilePath);
            void playBackgroundMusic(const char* pszFilePath, bool bLoop);
            void stopBackgroundMusic(bool bReleaseData);
            void pauseBackgroundMusic();
            void resumeBackgroundMusic();
            void rewindBackgroundMusic();
            bool willPlayBackgroundMusic();
            bool isBackgroundMusicPlaying();
            float getBackgroundMusicVolume();
            void setBackgroundMusicVolume(float volume);
            float getEffectsVolume();
            void setEffectsVolume(float volume);
            unsigned int playEffect(const char* pszFilePath, bool bLoop);
            void pauseEffect(unsigned int nSoundId);
            void pauseAllEffects();
            void resumeEffect(unsigned int nSoundId);
            void resumeAllEffects();
            void stopEffect(unsigned int nSoundId);
            void stopAllEffects();
            void preloadEffect(const char* pszFilePath);
            void unloadEffect(const char* pszFilePath);
        };
    }
}

#endif //__CDDANDRIODANDROIDJAVAENGINE_H__
