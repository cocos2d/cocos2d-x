
#ifndef __PLAYER_MAC_H_
#define __PLAYER_MAC_H_

#include "PlayerProtocol.h"

#include "PlayerEditBoxServiceMac.h"
#include "PlayerFileDialogServiceMac.h"
#include "PlayerMenuServiceMac.h"
#include "PlayerMessageBoxServiceMac.h"
#include "PlayerTaskServiceMac.h"

#include "PlayerUtils.h"

#include "ProjectConfig/ProjectConfig.h"
PLAYER_NS_BEGIN

class PlayerMac : public PlayerProtocol
{
public:
    static PlayerMac *create();
    virtual ~PlayerMac();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    virtual PlayerMenuServiceProtocol *getMenuService();
    virtual PlayerEditBoxServiceProtocol *getEditBoxService();
    virtual PlayerTaskServiceProtocol *getTaskService();

protected:
    PlayerMac();

    PlayerMenuServiceMac       *_menuService;
    PlayerMessageBoxServiceMac *_messageBoxService;
    PlayerFileDialogServiceMac *_fileDialogService;
    PlayerEditBoxServiceMac    *_editBoxService;
    PlayerTaskServiceMac       *_taskService;
    id _appController;
};

PLAYER_NS_END

#endif // __PLAYER_MAC_H_
