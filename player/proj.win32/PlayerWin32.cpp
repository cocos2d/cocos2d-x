
#include "stdafx.h"
#include "PlayerWin32.h"
#include "PlayerFileDialogServiceWin32.h"

PLAYER_NS_BEGIN

PlayerWin32::PlayerWin32()
{
    setInstance(this);
}


PlayerWin32::~PlayerWin32()
{
}

PlayerFileDialogServiceProtocol *PlayerWin32::getFileDialogService()
{
    if (!m_fileDialogService)
    {
        m_fileDialogService = new PlayerFileDialogServiceWin32();
    }
    return m_fileDialogService;
}

PLAYER_NS_END
