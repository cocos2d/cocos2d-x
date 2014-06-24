
#ifndef __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
#define __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_

#include <string>
#include <vector>

using namespace std;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceProtocol : public PlayerServiceProtocol
{
public:
    virtual string openFile(const char *title,
        const char *directory = NULL,
        const char *extensions = NULL) = 0;

    virtual string openDirectory(const char *title,
        const char *directory = NULL) = 0;

    virtual vector<string> openMultiple(const char *title,
        const char *directory = NULL) = 0;

    virtual string saveFile(const char *title,
        const char *filename,
        const char *directory) = 0;
};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
