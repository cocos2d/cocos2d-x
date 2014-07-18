
#ifndef __PLAYER_PROTOCOL_H_
#define __PLAYER_PROTOCOL_H_

#include "PlayerMacros.h"
#include "PlayerFileDialogServiceProtocol.h"
#include "PlayerMessageBoxServiceProtocol.h"
#include "PlayerMenuServiceProtocol.h"
#include "PlayerEditBoxServiceProtocol.h"

#include "PlayerUtils.h"

PLAYER_NS_BEGIN

struct PlayerSettings
{
public:
    PlayerSettings()
    : openLastProject(false), offsetX(0), offsetY(0), windowWidth(960), windowHeight(640)
    {}
    
    bool openLastProject;
    long offsetX;
    long offsetY;
    long windowWidth;
    long windowHeight;
};

class PlayerProtocol
{
public:
    virtual ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    void setPlayerSettings(PlayerSettings &settings);
    PlayerSettings &getPlayerSettings() ;
    
    virtual PlayerFileDialogServiceProtocol *getFileDialogService() = 0; // impl in platform related source files
    
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService() = 0;
    
    virtual PlayerMenuServiceProtocol       *getMenuService() = 0;
    
    virtual PlayerEditBoxServiceProtocol    *getEditBoxService() = 0;

protected:
    PlayerProtocol(); // avoid create instance from outside
    static void setInstance(PlayerProtocol *instance); // call from platform related class constructor

    PlayerFileDialogServiceProtocol *m_fileDialogService;
    PlayerMessageBoxServiceProtocol *m_messageBoxService;
    PlayerMenuServiceProtocol       *m_menuService;
    PlayerEditBoxServiceProtocol    *m_editBoxService;

private:
    static PlayerProtocol *s_instance;
    
    PlayerSettings m_settings;
};

PLAYER_NS_END

#endif // __PLAYER_PROTOCOL_H_
