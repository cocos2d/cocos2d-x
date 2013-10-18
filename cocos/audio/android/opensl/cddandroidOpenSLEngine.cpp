#include "cddandroidOpenSLEngine.h"

namespace CocosDenshion {
    namespace android {
        OpenSLEngine::~OpenSLEngine() {
        }

        void OpenSLEngine::preloadBackgroundMusic(const char* pszFilePath) { }
        void OpenSLEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop) { }
        void OpenSLEngine::stopBackgroundMusic(bool bReleaseData) { }
        void OpenSLEngine::pauseBackgroundMusic() { }
        void OpenSLEngine::resumeBackgroundMusic() { }
        void OpenSLEngine::rewindBackgroundMusic() { }
        bool OpenSLEngine::willPlayBackgroundMusic() { }
        bool OpenSLEngine::isBackgroundMusicPlaying() { }
        float OpenSLEngine::getBackgroundMusicVolume() { }
        void OpenSLEngine::setBackgroundMusicVolume(float volume) { }
        float OpenSLEngine::getEffectsVolume() { }
        void OpenSLEngine::setEffectsVolume(float volume) { }
        unsigned int OpenSLEngine::playEffect(const char* pszFilePath,
                                              bool bLoop,
                                              float pitch, float pan,
                                              float gain) {
        }
        void OpenSLEngine::pauseEffect(unsigned int nSoundId) { }
        void OpenSLEngine::pauseAllEffects() { }
        void OpenSLEngine::resumeEffect(unsigned int nSoundId) { }
        void OpenSLEngine::resumeAllEffects() { }
        void OpenSLEngine::stopEffect(unsigned int nSoundId) { }
        void OpenSLEngine::stopAllEffects() { }
        void OpenSLEngine::preloadEffect(const char* pszFilePath) { }
        void OpenSLEngine::unloadEffect(const char* pszFilePath) { }

    }
}
