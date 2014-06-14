
#ifndef __PLAYER_FILE_DIALOG_SERVICE_WIN32_H_
#define __PLAYER_FILE_DIALOG_SERVICE_WIN32_H_

#include "stdafx.h"

#include "PlayerMacros.h"
#include "PlayerFileDialogServiceProtocol.h"

#include "PlayerServiceProtocolWin32.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceWin32 : public PlayerFileDialogServiceProtocol, public PlayerServiceProtocolWin32
{
    virtual string openFile(const char *title,
        const char *directory = NULL,
        const char *extensions = NULL);

    virtual string openDirectory(const char *title,
        const char *directory = NULL);

    virtual vector<string> openMultiple(const char *title,
        const char *directory = NULL);

    virtual string saveFile(const char *title,
        const char *filename,
        const char *directory);

};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_WIN32_H_
