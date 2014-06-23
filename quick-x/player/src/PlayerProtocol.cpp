
#include "PlayerProtocol.h"

PLAYER_NS_BEGIN

PlayerProtocol *PlayerProtocol::s_instance = NULL;

PlayerProtocol::PlayerProtocol()
: m_fileDialogService(NULL)
{
}

PlayerProtocol::~PlayerProtocol()
{
    PLAYER_SAFE_DELETE(m_fileDialogService);
    s_instance = NULL;
}

PlayerProtocol *PlayerProtocol::getInstance()
{
    return s_instance;
}

void PlayerProtocol::setInstance(PlayerProtocol *instance)
{
    s_instance = instance;
}

void PlayerProtocol::purgeInstance()
{
    PLAYER_SAFE_DELETE(s_instance);
}

PLAYER_NS_END
