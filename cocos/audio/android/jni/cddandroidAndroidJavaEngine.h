/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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
#ifndef __CDDANDRIODANDROIDJAVAENGINE_H__
#define __CDDANDRIODANDROIDJAVAENGINE_H__

#include "audio/include/SimpleAudioEngine.h"
#include "platform/android/jni/JniHelper.h"
#include <list>

namespace CocosDenshion {
    namespace android {
        class AndroidJavaEngine : public SimpleAudioEngine {
        public:
            AndroidJavaEngine();
            ~AndroidJavaEngine();

            virtual void preloadBackgroundMusic(const char* filePath);
            virtual void playBackgroundMusic(const char* filePath, bool loop);
            virtual void stopBackgroundMusic(bool releaseData);
            virtual void pauseBackgroundMusic();
            virtual void resumeBackgroundMusic();
            virtual void rewindBackgroundMusic();
            virtual bool willPlayBackgroundMusic();
            virtual bool isBackgroundMusicPlaying();
            virtual float getBackgroundMusicVolume();
            virtual void setBackgroundMusicVolume(float volume);
            virtual float getEffectsVolume();
            virtual void setEffectsVolume(float volume);
            virtual unsigned int playEffect(const char* filePath, bool loop = false,
                                    float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
            virtual void pauseEffect(unsigned int soundId);
            virtual void pauseAllEffects();
            virtual void resumeEffect(unsigned int soundId);
            virtual void resumeAllEffects();
            virtual void stopEffect(unsigned int soundId);
            virtual void stopAllEffects();
            virtual void preloadEffect(const char* filePath);
            virtual void unloadEffect(const char* filePath);

        private :
            bool _implementBaseOnAudioEngine;
            float _effectVolume;
            std::list<int> _soundIDs;
        };
    }
}

#endif //__CDDANDRIODANDROIDJAVAENGINE_H__
