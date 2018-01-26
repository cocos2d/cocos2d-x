
#include "PlayerWin.h"

USING_NS_CC;
PLAYER_NS_BEGIN

PlayerWin::PlayerWin()
    : PlayerProtocol()
    , _menuService(nullptr)
    , _messageBoxService(nullptr)
    , _editboxService(nullptr)
    , _taskService(nullptr)
    , _hwnd(NULL)
{
}

PlayerWin::~PlayerWin()
{
    CC_SAFE_DELETE(_menuService);
    CC_SAFE_DELETE(_messageBoxService);
    CC_SAFE_DELETE(_fileDialogService);
}

PlayerWin *PlayerWin::createWithHwnd(HWND hWnd)
{
    auto instance = new PlayerWin();
    instance->_hwnd = hWnd;
    instance->initServices();
    return instance;
}

PlayerFileDialogServiceProtocol *PlayerWin::getFileDialogService()
{
    return _fileDialogService;
}

PlayerMessageBoxServiceProtocol *PlayerWin::getMessageBoxService()
{
    return _messageBoxService;
}

PlayerMenuServiceProtocol *PlayerWin::getMenuService()
{
    return _menuService;
}

PlayerEditBoxServiceProtocol *PlayerWin::getEditBoxService()
{
    return _editboxService;
}

PlayerTaskServiceProtocol *PlayerWin::getTaskService()
{
    return _taskService;
}

// services
void PlayerWin::initServices()
{
    CCASSERT(_menuService == nullptr, "CAN'T INITIALIZATION SERVICES MORE THAN ONCE");
    _menuService = new PlayerMenuServiceWin(_hwnd);
    _messageBoxService = new PlayerMessageBoxServiceWin(_hwnd);
    _fileDialogService = new PlayerFileDialogServiceWin(_hwnd);
    _editboxService = new PlayerEditBoxServiceWin(_hwnd);
    _taskService = new PlayerTaskServiceWin(_hwnd);
}

PLAYER_NS_END
