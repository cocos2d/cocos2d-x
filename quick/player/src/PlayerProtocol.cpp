
#include "PlayerProtocol.h"

PLAYER_NS_BEGIN

PlayerProtocol *PlayerProtocol::s_instance = NULL;

PlayerProtocol::PlayerProtocol()
: m_fileDialogService(NULL)
, m_messageBoxService(NULL)
, m_menuService(NULL)
, m_editBoxService(NULL)
{
}

PlayerProtocol::~PlayerProtocol()
{
    PLAYER_SAFE_DELETE(m_fileDialogService);
    PLAYER_SAFE_DELETE(m_messageBoxService);
    PLAYER_SAFE_DELETE(m_menuService);
    PLAYER_SAFE_DELETE(m_editBoxService);
    
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

void PlayerProtocol::setPlayerSettings(PlayerSettings &settings)
{
    m_settings = settings;
}

PlayerSettings &PlayerProtocol::getPlayerSettings()
{
    return m_settings;
}

PLAYER_NS_END
