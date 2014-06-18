
#ifndef __PLAYER_WIN32_H_
#define __PLAYER_WIN32_H_

#include "PlayerProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceProtocol;

class PlayerWin32 : public PlayerProtocol
{
public:
    virtual ~PlayerWin32();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();

    HWND getWindowHandle();

protected:
    PlayerWin32();


};

PLAYER_NS_END

#endif // __PLAYER_WIN32_H_
