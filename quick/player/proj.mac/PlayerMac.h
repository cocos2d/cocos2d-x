
#ifndef __PLAYER_MAC_H_
#define __PLAYER_MAC_H_

#include "PlayerProtocol.h"

PLAYER_NS_BEGIN

class PlayerMac : public PlayerProtocol
{
public:
    PlayerMac();
    virtual ~PlayerMac();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();

    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    
    virtual PlayerMenuServiceProtocol       *getMenuService();
    
    virtual PlayerEditBoxServiceProtocol    *getEditBoxService();
protected:
    
};

PLAYER_NS_END

#endif // __PLAYER_MAC_H_
