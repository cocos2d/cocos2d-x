#ifndef _MCI_PLAYER_WIN32_H_
#define _MCI_PLAYER_WIN32_H_

#include "CCStdC.h"
#include <mmsystem.h>
#include "oae.h"
#include <string>

namespace CocosDenshion {

class MciPlayer
{
public:
    MciPlayer();
    ~MciPlayer();

    void Close();

    void Open(const char* pFileName, UINT uId);

    void Play(UINT uTimes = 1);

    void Pause();

    void Resume();

    void Stop();

    void Rewind();

    bool IsPlaying();

    UINT GetSoundID();
public:
	static oae::Renderer* _device;
	static HMODULE _lib;

	std::string _fileName;
	oae::Screamer* _scr;

	UINT        _nSoundID;
    UINT        _uTimes;
};

} // end of namespace CocosDenshion

#endif
