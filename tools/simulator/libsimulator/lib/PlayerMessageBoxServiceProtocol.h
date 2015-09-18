
#ifndef __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H
#define __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H

#include <string>

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerMessageBoxServiceProtocol : public PlayerServiceProtocol
{
public:
    static const int BUTTONS_OK = 0;
    static const int BUTTONS_OK_CANCEL = 1;
    static const int BUTTONS_YES_NO = 2;
    static const int BUTTONS_YES_NO_CANCEL = 3;

    static const int BUTTON_OK = 0;
    static const int BUTTON_CANCEL = 1;
    static const int BUTTON_YES = 2;
    static const int BUTTON_NO = 3;

    // Show a message box, return index of user clicked button
    //
    // @return int first button index is 0
    virtual int showMessageBox(const std::string &title,
                               const std::string &message,
                               int buttonsType = BUTTONS_OK) = 0;
};

PLAYER_NS_END

#endif // __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H
