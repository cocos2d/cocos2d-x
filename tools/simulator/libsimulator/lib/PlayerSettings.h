
#ifndef __PLAYER_SETTINGS_H_
#define __PLAYER_SETTINGS_H_

#include "PlayerMacros.h"

PLAYER_NS_BEGIN

class PlayerSettings
{
public:
    PlayerSettings()
        : openLastProject(false)
        , offsetX(0)
        , offsetY(0)
    {}

    bool openLastProject;
    int offsetX;
    int offsetY;
};

PLAYER_NS_END

#endif // __PLAYER_SETTINGS_H_
