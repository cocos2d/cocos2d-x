/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include "../Export.h"

typedef struct _tResourceInfo
{
    const char* FileName;
    int         nResID;
} T_SoundResInfo;

/*!***************************************************************************
@class          SimpleAudioEngine
@brief  		offer a VERY simple interface to play background music & sound effect
*****************************************************************************/
class EXPORT_DLL SimpleAudioEngine
{
public:
    SimpleAudioEngine();
    ~SimpleAudioEngine();

    // get the Engine object
    static SimpleAudioEngine* getSharedEngine();

    // set the sound ResInfo
    void setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount);

    // set the resource entry
    void setResourceEntry(const void* pResEntry);

    // for background music
    void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    void rewindBackgroundMusic();

    bool willPlayBackgroundMusic();
    bool isBackgroundMusicPlaying();

    // properties
    /**
    @brief The volume of the background music max value is 100,the min value is 0
    */
    int GetBackgroundMusicVolume();
    void SetBackgroundMusicVolume(int volume);

    /**
    @brief The volume of the effects max value is 100,the min value is 0
    */
    int GetEffectsVolume();
    void SetEffectsVolume(int volume);

    // for sound effects
    int playEffect(const char* pszFilePath);
    void stopEffect(int nSoundId);

    /*!***************************************************************************
    @brief  		preload a compressed audio file
    @details	    the compressed audio will be decode to wave, then write into an 
    internal buffer in SimpleaudioEngine
    @param[in]		pszFilePath		the relative path to currently executing program
    @return         >0              preload success, return the SoundId
    @return         ==0             can't read the file, or unsupported audio format
    *****************************************************************************/
    int preloadEffect(const char* pszFilePath);


    /*!***************************************************************************
    @brief  		unload the preloaded effect from internal buffer
    @param[in]		nSoundId		the sound id returned from preloadEffect
    *****************************************************************************/
    void unloadEffect(int nSoundId);


	/*!***************************************************************************
	@brief          unload all preloaded effect from internal buffer
	*****************************************************************************/
	void unloadEffectAll();


    /*!***************************************************************************
    @brief          play the preloaded effect
    @param[in]		nSoundId		the sound id returned from preloadEffect
    *****************************************************************************/
    void playPreloadedEffect(int nSoundId);
};

#endif // _SIMPLE_AUDIO_ENGINE_H_
