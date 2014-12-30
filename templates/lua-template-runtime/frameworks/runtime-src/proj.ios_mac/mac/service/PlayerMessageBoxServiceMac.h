
#ifndef __PLAYER_MessageBoxServiceMac_h
#define __PLAYER_MessageBoxServiceMac_h

#include <vector>

#include "PlayerMacros.h"
#include "PlayerMessageBoxServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMessageBoxServiceMac : public PlayerMessageBoxServiceProtocol
{
public:
    virtual int showMessageBox(const std::string &title,
                               const std::string &message,
                               int buttonsType = BUTTONS_OK);
protected:
    struct MessageBoxInfo
    {
        std::string title;
        const int   buttonId;
    };
    std::vector<MessageBoxInfo> getTitles(int buttons);
};

PLAYER_NS_END

#endif // __PLAYER_MessageBoxServiceMac_h
