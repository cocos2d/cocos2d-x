
#include "PlayerMacros.h"
#include "FileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class FileDialogServiceWin32 : public FileDialogServiceProtocol
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
