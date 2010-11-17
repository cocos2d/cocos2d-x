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

/**
@struct T_SoundResInfo
@brief  The data type of resource name and resource ID
*/
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

    /**
    @brief Get the shared Engine object,it will new one when first time be called
    */
    static SimpleAudioEngine* sharedEngine();

    /**
    @brief Release the shared Engine object
    */
	static void release();

    /**
    @brief set the sound ResInfo,it's only used on platform-uphone now
    */
    void setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount);

    /**
    @brief Set the resource entry,it's only used on platform-uphone now
    */
    void setResourceEntry(const void* pResEntry);

    /**
    @brief Play background music
    @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
    @param bLoop Whether the background music loop or not
    */
    void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);

    /**
    @brief Stop playing background music
    */
    void stopBackgroundMusic();

    /**
    @brief Pause playing background music
    */
    void pauseBackgroundMusic();

    /**
    @brief Resume playing background music
    */
    void resumeBackgroundMusic();

    /**
    @brief Rewind playing background music
    */
    void rewindBackgroundMusic();

    bool willPlayBackgroundMusic();

    /**
    @brief Whether the background music is playing
    @return If is playing return true,or return false
    */
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
    /**
    @brief Play sound effect
    @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
    @return If play succeed return the effect sound ID,or return 0
    */
    int playEffect(const char* pszFilePath);

    /**
    @brief Stop playing sound effect
    @param nSoundId The return value of function playEffect or preloadEffect
    */
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
