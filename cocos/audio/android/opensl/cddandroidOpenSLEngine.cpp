/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
