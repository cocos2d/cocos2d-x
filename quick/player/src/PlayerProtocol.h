
#ifndef __PLAYER_PROTOCOL_H_
#define __PLAYER_PROTOCOL_H_

#include "PlayerMacros.h"
#include "PlayerFileDialogServiceProtocol.h"
#include "PlayerMessageBoxServiceProtocol.h"
#include "PlayerMenuServiceProtocol.h"

#include "PlayerUtils.h"

PLAYER_NS_BEGIN

class PlayerProtocol
{
public:
    virtual ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService() = 0; // impl in platform related source files
    
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService() = 0;
    
    virtual PlayerMenuServiceProtocol       *getMenuService() = 0;

protected:
    PlayerProtocol(); // avoid create instance from outside
    static void setInstance(PlayerProtocol *instance); // call from platform related class constructor

    PlayerFileDialogServiceProtocol *m_fileDialogService;
    PlayerMessageBoxServiceProtocol *m_messageBoxService;
    PlayerMenuServiceProtocol       *m_menuService;

private:
    static PlayerProtocol *s_instance;
};

PLAYER_NS_END

#endif // __PLAYER_PROTOCOL_H_
