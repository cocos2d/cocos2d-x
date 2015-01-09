

#include "PlayerMac.h"


PLAYER_NS_BEGIN
using namespace cocos2d;

PlayerMac* PlayerMac::create()
{
    return new PlayerMac();
}


PlayerMac::PlayerMac()
: PlayerProtocol()
, _fileDialogService(nullptr)
, _messageBoxService(nullptr)
, _menuService(nullptr)
, _editBoxService(nullptr)
, _appController(nullptr)
, _taskService(nullptr)
{
}


PlayerMac::~PlayerMac()
{
    CC_SAFE_DELETE(_fileDialogService);
    CC_SAFE_DELETE(_fileDialogService);
    CC_SAFE_DELETE(_messageBoxService);
    CC_SAFE_DELETE(_menuService);
    CC_SAFE_DELETE(_editBoxService);
    CC_SAFE_DELETE(_taskService);
}

PlayerFileDialogServiceProtocol *PlayerMac::getFileDialogService()
{
    if (!_fileDialogService)
    {
        _fileDialogService = new PlayerFileDialogServiceMac();
    }
    return _fileDialogService;
}

PlayerMessageBoxServiceProtocol *PlayerMac::getMessageBoxService()
{
    if (!_messageBoxService)
    {
        _messageBoxService = new PlayerMessageBoxServiceMac();
    }
    return _messageBoxService;
}

PlayerMenuServiceProtocol *PlayerMac::getMenuService()
{
    if (!_menuService)
    {
        _menuService = new PlayerMenuServiceMac();
    }
    return _menuService;
}

PlayerEditBoxServiceProtocol *PlayerMac::getEditBoxService()
{
    if (!_editBoxService)
    {
        _editBoxService = new PlayerEditBoxServiceMac();
    }
    return _editBoxService;
}

PlayerTaskServiceProtocol *PlayerMac::getTaskService()
{
    if (!_taskService)
    {
        _taskService = new PlayerTaskServiceMac();
    }
    return _taskService;
}

PLAYER_NS_END
