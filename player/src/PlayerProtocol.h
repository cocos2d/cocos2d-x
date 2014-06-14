
#include "PlayerMacros.h"
#include "FileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerProtocol
{
public:
    ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    virtual FileDialogServiceProtocol *getFileDialogService() = 0; // impl in platform related source files

protected:
    PlayerProtocol(); // avoid create instance from outside
    static void setInstance(PlayerProtocol *instance); // call from platform related source files

    FileDialogServiceProtocol *m_fileDialogService;

private:
    static PlayerProtocol *s_instance;
};

PLAYER_NS_END
