#ifndef _DIRECT_SOUND_PLAYER_WIN32_H_
#define _DIRECT_SOUND_PLAYER_WIN32_H_

#include <windows.h>
#include <dsound.h>
#include "SimpleAudioEngine.h"

namespace CocosDenshion {

class DSPlayer
{
public:
    DSPlayer();
    ~DSPlayer();

    void Close();

    /**
    @brief ІҐ·ЕЙщТфОДјю
    @param pFileName ІҐ·ЕµДЙщТфОДјюГыіЖЈ¬РиТЄ°ьє¬ОДјюµДВ·ѕ¶
    @param nTimes    ІҐ·ЕЙщТфОДјюµДС­»·ґОКэЈ¬Д¬ИПЦµОЄ 1Ј¬јґІҐ·ЕТ»ґО
    */
    void Open(const char* pFileName, UINT uId);

    void Play(UINT uTimes = 1);

    /**
    @brief ФЭНЈІҐ·ЕЙщТф
    */
    void Pause();

    /**
    @brief јМРшІҐ·ЕЙщТф
    */
    void Resume();

    /**
    @brief НЈЦ№ІҐ·ЕЙщТф
    */
    void Stop();

  LONG GetVolume();
	void SetVolume(int vol);

    /**
    @brief ЦШРВІҐ·Е
    */
    void Rewind();

    /**
    @brief »сИЎІҐ·ЕЖчµ±З°КЗ·сХэФЪІҐ·ЕЦР
    */
    bool IsPlaying();

    /**
    @brief »сИЎµ±З°ІҐ·ЕµДТфР§ ID
    @return µ±З°ІҐ·ЕµДТфР§ID
    */
    UINT GetSoundID();

private:
    UINT        m_nSoundID;
    UINT        m_uTimes;
    bool        m_bPlaying;
	IDirectSoundBuffer8 *g_pDSBuffer; // Глобальный объект 8 версии
};

} // end of namespace CocosDenshion

#endif
