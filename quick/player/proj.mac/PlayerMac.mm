

#include "PlayerMac.h"
#include "FileDialogServiceMac.h"
#include "MessageBoxServiceMac.h"
#include "MenuServiceMac.h"

PLAYER_NS_BEGIN

PlayerMac::PlayerMac()
{
    assert(!getInstance() && "just init once!");
    setInstance(this);
}


PlayerMac::~PlayerMac()
{
}

PlayerFileDialogServiceProtocol *PlayerMac::getFileDialogService()
{
    if (!m_fileDialogService)
    {
        m_fileDialogService = new FileDialogServiceMac();
    }
    return m_fileDialogService;
}

PlayerMessageBoxServiceProtocol *PlayerMac::getMessageBoxService()
{
    if (!m_messageBoxService)
    {
        m_messageBoxService = new MessageBoxServiceMac();
    }
    return m_messageBoxService;
}

PlayerMenuServiceProtocol *PlayerMac::getMenuService()
{
    if (!m_menuService)
    {
        m_menuService = new MenuServiceMac();
    }
    return m_menuService;
}

PLAYER_DECLARE_GLOBAL_INSTANCE(PlayerMac, __mac_player);

PLAYER_NS_END
