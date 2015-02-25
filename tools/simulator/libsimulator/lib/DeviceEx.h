#pragma once

#include <string>
#include "PlayerMacros.h"

PLAYER_NS_BEGIN

class DeviceEx
{
public:
    static DeviceEx *getInstance();

    std::string getCurrentUILangName();
    std::string getUserGUID();

private:
    DeviceEx();
    void init();
    void makeUILangName();
    std::string makeUserGUID();

    std::string _uiLangName;
    std::string _userGUID;
};

PLAYER_NS_END