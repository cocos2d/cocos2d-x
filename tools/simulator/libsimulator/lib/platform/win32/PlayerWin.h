#pragma once

#include "cocos2d.h"

#include "PlayerMacros.h"
#include "PlayerProtocol.h"
#include "PlayerMenuServiceWin.h"
#include "PlayerMessageBoxServiceWin.h"
#include "PlayerFileDialogServiceWin.h"
#include "PlayerEditBoxServiceWin.h"
#include "PlayerTaskServiceWin.h"

PLAYER_NS_BEGIN

class PlayerWin : public PlayerProtocol, public cocos2d::Ref
{
public:
    static PlayerWin *createWithHwnd(HWND hWnd);
    virtual ~PlayerWin();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    virtual PlayerMenuServiceProtocol *getMenuService();
    virtual PlayerEditBoxServiceProtocol *getEditBoxService();
    virtual PlayerTaskServiceProtocol *getTaskService();

protected:
    PlayerWin();
    
    // services
    void initServices();

    PlayerMenuServiceWin *_menuService;
    PlayerMessageBoxServiceWin *_messageBoxService;
    PlayerFileDialogServiceWin *_fileDialogService;
    PlayerEditBoxServiceWin *_editboxService;
    PlayerTaskServiceWin *_taskService;

    HWND _hwnd;
};


PLAYER_NS_END
