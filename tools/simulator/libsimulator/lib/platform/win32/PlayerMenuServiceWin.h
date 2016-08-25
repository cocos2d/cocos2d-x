
#ifndef __PLAYER_MENU_SERVICE_WIN_H_
#define __PLAYER_MENU_SERVICE_WIN_H_

#include <string>
#include <unordered_map>

#include "cocos2d.h"
#include "stdafx.h"
#include "PlayerMenuServiceProtocol.h"
#include "SimulatorExport.h"

PLAYER_NS_BEGIN

class CC_LIBSIM_DLL PlayerMenuItemWin : public PlayerMenuItem
{
public:
    static PlayerMenuItemWin *create(const std::string &menuId, const std::string &title);
    virtual ~PlayerMenuItemWin();

    virtual void setTitle(const std::string &title);
    virtual void setEnabled(bool enabled);
    virtual void setChecked(bool checked);
    virtual void setShortcut(const std::string &shortcut);

protected:
    PlayerMenuItemWin();

    PlayerMenuItemWin *_parent;
    UINT _commandId;
    HMENU _hmenu;
    bool _menubarEnabled;
    cocos2d::Vector<PlayerMenuItemWin*> _children;

    friend class PlayerMenuServiceWin;
};

class CC_LIBSIM_DLL PlayerMenuServiceWin : public PlayerMenuServiceProtocol
{
public:
    PlayerMenuServiceWin(HWND hwnd);
    virtual ~PlayerMenuServiceWin();

    virtual PlayerMenuItem *addItem(const std::string &menuId,
                                    const std::string &title,
                                    const std::string &parentId,
                                    int order = MAX_ORDER);
    virtual PlayerMenuItem *addItem(const std::string &menuId,
                                    const std::string &title);
    virtual PlayerMenuItem *getItem(const std::string &menuId);
    virtual bool removeItem(const std::string &menuId);
    virtual void setMenuBarEnabled(bool enabled);

    PlayerMenuItemWin *getItemByCommandId(WORD commandId);

private:
    static WORD _newCommandId;

    HWND _hwnd;
    bool _menubarEnabled;
    PlayerMenuItemWin _root;
    std::unordered_map<std::string, PlayerMenuItemWin*> _items;
    std::unordered_map<WORD, std::string> _commandId2menuId;

    bool removeItemInternal(const std::string &menuId, bool isUpdateChildrenOrder);
    void updateChildrenOrder(PlayerMenuItemWin *parent);
};

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_WIN_H_
