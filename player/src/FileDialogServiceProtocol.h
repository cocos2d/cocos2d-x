
#include "PlayerMacros.h"

#include <string>
#include <vector>

using namespace std;

PLAYER_NS_BEGIN

class FileDialogServiceProtocol
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
