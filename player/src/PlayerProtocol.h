
#ifndef __PLAYER_PROTOCOL_H_
#define __PLAYER_PROTOCOL_H_

#include "PlayerMacros.h"
#include "PlayerFileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerProtocol
{
public:
    ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService() = 0; // impl in platform related source files

protected:
    PlayerProtocol(); // avoid create instance from outside
    static void setInstance(PlayerProtocol *instance); // call from platform related class constructor

    PlayerFileDialogServiceProtocol *m_fileDialogService;

private:
    static PlayerProtocol *s_instance;
};

PLAYER_NS_END

#endif // __PLAYER_PROTOCOL_H_
