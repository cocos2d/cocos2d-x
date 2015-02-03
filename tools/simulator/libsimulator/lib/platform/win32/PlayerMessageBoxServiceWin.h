
#ifndef __PLAYER_MESSAGEBOX_SERVICE_WIN_H_
#define __PLAYER_MESSAGEBOX_SERVICE_WIN_H_

#include <string>

#include "stdafx.h"
#include "cocos2d.h"
#include "PlayerMessageBoxServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMessageBoxServiceWin : public PlayerMessageBoxServiceProtocol
{
public:
    PlayerMessageBoxServiceWin(HWND hwnd);

    virtual int showMessageBox(const std::string &title,
                               const std::string &message,
                               int buttonsType = BUTTONS_OK);

protected:
    HWND _hwnd;
};

PLAYER_NS_END

#endif // __PLAYER_MESSAGEBOX_SERVICE_WIN_H_
