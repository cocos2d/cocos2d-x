#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "cocos2d.h"
#include "AppDelegate.h"
#include "ProjectConfig/ProjectConfig.h"
#include "ProjectConfig/SimulatorConfig.h"

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
    static PlayerWin *getInstance();
    virtual ~PlayerWin();
    int run();

    virtual PlayerFileDialogServiceProtocol *getFileDialogService();
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService();
    virtual PlayerMenuServiceProtocol *getMenuService();
    virtual PlayerEditBoxServiceProtocol *getEditBoxService();
    virtual PlayerTaskServiceProtocol *getTaskService();

    virtual void quit();
    virtual void relaunch();
    virtual void openNewPlayer();
    virtual void openNewPlayerWithProjectConfig(const ProjectConfig &config);
    virtual void openProjectWithProjectConfig(const ProjectConfig &config);

    virtual int getPositionX();
    virtual int getPositionY();
protected:
    PlayerWin();

    static PlayerWin *_instance;
    ProjectConfig _project;
    HWND _hwnd;
    HWND _hwndConsole;
    AppDelegate *_app;
    FILE *_writeDebugLogFile;

    PlayerMenuServiceWin *_menuService;
    PlayerMessageBoxServiceWin *_messageBoxService;
    PlayerFileDialogServiceWin *_fileDialogService;
    PlayerEditBoxServiceWin *_editboxService;
    PlayerTaskServiceWin *_taskService;

    // services
    void initServices();

    // event handlers
    void onWindowClose(cocos2d::EventCustom* event);
    void onWindowResize(cocos2d::EventCustom* event);
    void onWindowScale(cocos2d::EventCustom* event);

    // 
    void loadLuaConfig();
    void registerKeyboardEvent();
    void setZoom(float frameScale);

    // debug log
    void writeDebugLog(const char *log);

    // helper
    std::string convertPathFormatToUnixStyle(const std::string& path);
    std::string getUserDocumentPath();
    std::string getApplicationExePath();
    std::string getUserGUID();
    char*	    convertTCharToUtf8(const TCHAR* src);

    std::string _userGUID;
    static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


PLAYER_NS_END
