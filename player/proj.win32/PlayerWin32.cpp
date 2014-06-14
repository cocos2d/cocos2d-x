
#include "stdafx.h"
#include "PlayerWin32.h"
#include "FileDialogServiceWin32.h"

PLAYER_NS_BEGIN

PlayerWin32::PlayerWin32()
{
    setInstance(this);
}


PlayerWin32::~PlayerWin32()
{
}

FileDialogServiceProtocol *PlayerWin32::getFileDialogService()
{
    if (!m_fileDialogService)
    {
        m_fileDialogService = new FileDialogServiceWin32();
    }
    return m_fileDialogService;
}

PLAYER_NS_END
