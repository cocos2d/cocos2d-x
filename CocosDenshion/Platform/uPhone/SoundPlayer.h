#ifndef _SOUNDPLAYER_UPHONE_H_
#define _SOUNDPLAYER_UPHONE_H_

#include "TG3.h"
#include "TCOM_MediaPlayer_Method.h"
#include "TCOM_Generic_DataType.h"
#include "../../Export.h"

class EXPORT_DLL SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();

    void Release();

    /**
    @brief 播放声音文件
    @param pFileName 播放的声音文件名称，需要包含文件的路径
    @param nTimes    播放声音文件的循环次数，默认值为 1，即播放一次
    */
    void PlaySoundFile(const char* pFileName, Int32 nTimes = 1);

    /**
    @brief 播放内存中的声音数据
    @param 
    */
    void PlaySoundFromMem(UInt8* pData, Int32 nSize, Int32 nTimes = 1);

    /**
    @brief 设置播放器的音量
    @oaram nValue 音量值，应处于 0~100 之间
    */
    void SetVolumeValue(Int32 nValue);

    /**
    @brief 暂停播放声音
    */
    void Pause();

    /**
    @brief 继续播放声音
    */
    void Resume();

    /**
    @brief 停止播放声音
    */
    void Stop();

    /**
    @brief 重新播放
    */
    void Rewind();

    /**
    @brief 静音
    @param bMute 是否静音，TRUE表示设置为静音
    */
    void Mute(bool bMute);

    /**
    @brief 获取播放器当前是否正在播放中
    */
    bool IsPlaying();

    /**
    @brief 将文件数据解码到 buffer 中
    @param buffer [out] 解码后的数据
    @param pszFilePath 要解码的文件路径
    @return 返回值 >= 0 表示成功，否则表示失败
    */
    Int32 DecodeFile(void* buffer, Int32 bufferLen, const char* pszFilePath);

    /**
    @brief 获取音频文件的数据大小
    @param 音频文件名
    @return 返回需要的buffer大小，如果打开失败的话，返回 -1
    */
    Int32 GetFileBufferSize(const char* pszFilePath);

private:
    Boolean OpenAudioFile(const char* pszFilePath);

private:
    // 播放声音所需变量
    TCOM_MediaPlayer_Method_Play *m_pPlayer;
    TCOM_DataType_SysFile *m_pMediaFile;

    Boolean m_bPaused;
    TCOM_MethodEmun m_MethodEmun; // 查找方法

    TUChar m_fileName[MAX_PATH];
};

#endif
