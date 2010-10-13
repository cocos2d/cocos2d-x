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

#include "../Platform/platform.h"
#include "uthash.h"
#include <vector>
#include "../Export.h"

typedef struct
{
    std::string FileName;
    int         nResID;
} T_SoundResInfo;

struct AppResourceEntry;
class  TResourceLib;

class SoundResHandle
{
public:
    SoundResHandle();
    ~SoundResHandle();

    void setResourceEntry(const AppResourceEntry* pResEntry);
    void release();
    const void* LoadConstRawData(int nResID, unsigned int* nLen);

private:
    TResourceLib* m_pResLib;
};

/*!***************************************************************************
@class          SimpleAudioEngine
@brief  		offer a VERY simple interface to play background music & sound effect
*****************************************************************************/
class EXPORT_DLL SimpleAudioEngine
{
public:
    typedef std::vector<SoundPlayer*> PlayerArray;
    typedef PlayerArray::iterator     PlayerArrayIterator;

public:
    SimpleAudioEngine();
    ~SimpleAudioEngine();

    // get the Engine object
    static SimpleAudioEngine* getSharedSimpleAudioEngine();

    // set the sound ResInfo
    static void setSoundResInfo(const T_SoundResInfo ResInfo[], int nCount);

    // set the resource entry
    static void setResourceEntry(const AppResourceEntry* pResEntry);

    // for background music
    void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    void rewindBackgroundMusic();

    bool willPlayBackgroundMusic();
    bool isBackgroundMusicPlaying();

    // properties
    int GetBackgroundMusicVolume();
    void SetBackgroundMusicVolume(int volume);

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
    @brief          play the preloaded effect
    @param[in]		nSoundId		the sound id returned from preloadEffect
    *****************************************************************************/
    void playPreloadedEffect(int nSoundId);

    void removeAllEffectPlayers();
    void removeAllEffects();

private:
    int  loadFromResourceInfo(const char* pFileKey);
    int  loadFromFile(const char* pFilePath);

protected:
    int     m_nBackgroundMusicVolume;
    int     m_nEffectsVolume;
    bool    m_bWillPlayBackgroundMusic;

    SoundPlayer m_obBackPlayer;
    PlayerArray* m_pEffectPlayers;

    // use hash map to save the effects loaded
    typedef struct _hashElement
    {
        int                 nSoundID;
        unsigned char*      pDataBuffer;
        std::string         FileName;
        int                 nDataSize;
        UT_hash_handle		hh;
    } tHashElement;
    struct _hashElement	*   m_pEffects;
};

#endif // _SIMPLE_AUDIO_ENGINE_H_
