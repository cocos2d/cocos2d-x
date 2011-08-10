#ifndef _SOUNDPLAYER_WOPHONE_H_
#define _SOUNDPLAYER_WOPHONE_H_

#include "TG3.h"
#include "TCOM_MediaPlayer_Method.h"
#include "TCOM_Generic_DataType.h"
#include <string>

namespace CocosDenshion {

class SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();

    void Release();

    /**
    @brief Play sound file on the hard disk
    @param pFileName The absolute path of the file
    @param nTimes    The loop times of playing,If the value is -1,it will loop forever
    */
    void PlaySoundFile(const char* pFileName, Int32 nTimes = 1);

    /**
    @brief Play sound data in memory
    @param pData  The pointer of sound data
    @param nSize  The size of sound data
    @param nTimes Loop times,default value is 1.
    @param pFileName  The file name of sound data,default value is empty string
    @warning The file name must have extension,the extension affect the decode mode of the playing.
             So the extension must as same as the original file.
             If keep it empty string,the sound data will be decode as wav file.
    */
    void PlaySoundFromMem(UInt8* pData, Int32 nSize, const char* pFileName = "", Int32 nTimes = 1);

    /**
    @brief Set the player volume
    @param nValue The volume value,must between 0 and 100
    */
    void SetVolumeValue(Int32 nValue);

    /**
    @brief Pause playing
    */
    void Pause();

    /**
    @brief Resume Playing
    */
    void Resume();

    /**
    @brief Stop Playing
    */
    void Stop();

    /**
    @brief Rewind Playing
    */
    void Rewind();

    /**
    @brief Set the player mute or not
    @param bMute Whether mute or not
    */
    void Mute(bool bMute);

    /**
    @brief Whether the player is playing or not
    */
    bool IsPlaying();

    /**
    @brief Decode the file data
    @param buffer [out] The data after decode
    @param pszFilePath The absolute path of sound file
    @return If success return value >= 0,or return value < 0
    */
    Int32 DecodeFile(void* buffer, Int32 bufferLen, const char* pszFilePath);

    /**
    @brief Get the size of file buffer
    @param pszFilePath The absolute path of sound file
    @return If file existed return the data size,or return -1
    */
    Int32 GetFileBufferSize(const char* pszFilePath);

private:
    Boolean OpenAudioFile(const char* pszFilePath);

private:
    TCOM_MediaPlayer_Method_Play *m_pPlayer;
    TCOM_DataType_SysFile *m_pMediaFile;

    TCOM_MethodEmun m_MethodEmun;

    TUChar m_fileName[MAX_PATH];
};

} // end of namespace CocosDenshion

#endif
