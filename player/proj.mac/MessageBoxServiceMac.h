//
//  MessageBoxServiceMac.h
//  quick-x-player
//

#ifndef __PLAYER_MessageBoxServiceMac_h
#define __PLAYER_MessageBoxServiceMac_h

#include "PlayerMacros.h"
#include "PlayerMessageBoxServiceProtocol.h"

PLAYER_NS_BEGIN

class MessageBoxServiceMac : public PlayerMessageBoxServiceProtocol
{
public:
    virtual int showMessageBox(const char *title,
                               const char *message,
                               MessageBoxButtonsType buttons = MessageBoxOK);
    
    std::vector<std::string> getTitles(MessageBoxButtonsType buttons);
    
};

PLAYER_NS_END

#endif // __PLAYER_MessageBoxServiceMac_h
