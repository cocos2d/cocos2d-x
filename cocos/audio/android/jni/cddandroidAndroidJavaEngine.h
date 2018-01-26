/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#ifndef __CDDANDROIDANDROIDJAVAENGINE_H__
#define __CDDANDROIDANDROIDJAVAENGINE_H__

#include "audio/include/SimpleAudioEngine.h"
#include "platform/android/jni/JniHelper.h"
#include <list>

namespace CocosDenshion {
    namespace android {
        class AndroidJavaEngine : public SimpleAudioEngine {
        public:
            AndroidJavaEngine();
            ~AndroidJavaEngine();

            /*
             * @brief Preload background music.
             * @param filePath The path of the background music file.
             */
            virtual void preloadBackgroundMusic(const char* filePath);
            
            /*
             * @brief Play background music.
             * @param filePath The path of the background music file,or the FileName of T_SoundResInfo.
             * @param loop Whether the background music loop or not.
             */
            virtual void playBackgroundMusic(const char* filePath, bool loop);
            
            /*
             * @brief Stop playing background music.
             * @param releaseData If release the background music data or not.As default value is false.
             */
            virtual void stopBackgroundMusic(bool releaseData);
            
            /*
             * @brief Pause playing background music.
             */
            virtual void pauseBackgroundMusic();
            
            /*
             * @brief Resume playing background music.
             */
            virtual void resumeBackgroundMusic();
            
            /*
             * @brief Rewind playing background music
             */
            virtual void rewindBackgroundMusic();
            
            /*
             * @brief Indicates whether any background music can be played or not.
             * @return true if background music can be played; otherwise false.
             */
            virtual bool willPlayBackgroundMusic();
            
            /*
             * @brief Indicates whether the background music is playing.
             * @return true if the background music is playing; otherwise false.
             */
            virtual bool isBackgroundMusicPlaying();
            
            /*
             * @brief Get the volume of the background music.
             * @return the range of 0.0 as the minimum and 1.0 as the maximum.
             */
            virtual float getBackgroundMusicVolume();
            
            /*
             * @brief Set the volume of the background music.
             * @param volume must be range of 0.0 as the minimum and 1.0 as the maximum.
             */
            virtual void setBackgroundMusicVolume(float volume);
            
            /*
             * @brief Get the volume of the effects.
             * @return the range of 0.0 as the minimum and 1.0 as the maximum.
             */
            virtual float getEffectsVolume();
            
            /*
             * @brief Set the volume of sound effects.
             * @param volume must be range of 0.0 as the minimum and 1.0 as the maximum.
             */
            virtual void setEffectsVolume(float volume);
            
            /*
             * @brief Play sound effect with a file path, pitch, pan, and gain.
             * @param filePath The path of the effect file.
             * @param loop Determines whether to loop the effect playing or not. The default value is false.
             * @param pitch Fequency, normal value is 1.0. will also change effect play time.
             * @param pan Stereo effect, in the range of [-1..1] where -1 enables only left channel.
             * @param gain Volume, in the range of [0..1]. The normal value is 1.
             * @return The sound id.
             */
            virtual unsigned int playEffect(const char* filePath, bool loop = false,
                                    float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
            
            /*
             * @brief Pause playing sound effect.
             * @param soundId The return value of function playEffect.
             */
            virtual void pauseEffect(unsigned int soundId);
            
            /*
             * @brief Pause all playing sound effect.
             */
            virtual void pauseAllEffects();
            
            /*
             * @brief Resume playing sound effect.
             * @param soundId The return value of function playEffect.
             */
            virtual void resumeEffect(unsigned int soundId);
            
            /*
             * @brief Resume all playing sound effects.
             */
            virtual void resumeAllEffects();
            
            /*
             * @brief Stop playing sound effect.
             * @param soundId The return value of function playEffect.
             */
            virtual void stopEffect(unsigned int soundId);
            
            /*
             * @brief Stop all playing sound effects.
             */
            virtual void stopAllEffects();
            
            /*
             * @brief Preload a compressed audio file.
             * @param filePath The path of the effect file.
             */
            virtual void preloadEffect(const char* filePath);
            
            /*
             * @brief Unload the preloaded effect from internal buffer.
             * @param filePath The path of the effect file.
             */
            virtual void unloadEffect(const char* filePath);

        private :
            bool _implementBaseOnAudioEngine;
            float _effectVolume;
            std::list<int> _soundIDs;
        };
    }
}

#endif //__CDDANDROIDANDROIDJAVAENGINE_H__
