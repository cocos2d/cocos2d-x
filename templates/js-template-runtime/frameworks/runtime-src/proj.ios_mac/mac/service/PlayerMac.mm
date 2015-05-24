

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

void PlayerMac::quit()
{
    cocos2d::Director::getInstance()->end();
}

void PlayerMac::relaunch()
{
    if (_appController && [_appController respondsToSelector:NSSelectorFromString(@"relaunch")])
    {
        [_appController performSelector:NSSelectorFromString(@"relaunch")];
    }
}

void PlayerMac::openNewPlayer()
{
}

void PlayerMac::openNewPlayerWithProjectConfig(const ProjectConfig& config)
{
    if (_appController && [_appController respondsToSelector:NSSelectorFromString(@"launch:")])
    {
        NSString *commandLine = [NSString stringWithCString:config.makeCommandLine().c_str()
                                                   encoding:NSUTF8StringEncoding];
        NSArray *arguments = [NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]];
        
        [_appController performSelector:NSSelectorFromString(@"launch:") withObject:arguments];
    }
}

void PlayerMac::openProjectWithProjectConfig(const ProjectConfig& config)
{
    this->openNewPlayerWithProjectConfig(config);
    this->quit();
}

void PlayerMac::setController(id controller)
{
    _appController = controller;
}

int PlayerMac::getPositionX()
{
    NSWindow *window = dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->getCocoaWindow();
    return window.frame.origin.x;
}

int PlayerMac::getPositionY()
{
    NSWindow *window = dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->getCocoaWindow();
    return window.frame.origin.y;
}

PLAYER_NS_END
