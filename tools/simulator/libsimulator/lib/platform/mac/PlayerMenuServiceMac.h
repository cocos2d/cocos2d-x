
#ifndef __PLAYER_MENU_SERVICE_MAC_H_
#define __PLAYER_MENU_SERVICE_MAC_H_

#include <unordered_map>

#include "cocos2d.h"
#include "PlayerMacros.h"
#include "PlayerMenuServiceProtocol.h"

//
// Menu item Helper
//

PLAYER_NS_BEGIN
class PlayerMenuItemMac;
PLAYER_NS_END

@interface NNMenuItem : NSMenuItem <NSMenuDelegate>
{
    int scriptHandler;
    player::PlayerMenuItemMac *macMenuItem;
}
@property (nonatomic) int scriptHandler;
@property (nonatomic) const player::PlayerMenuItemMac *macMenuItem;

+(id) createMenuItem:(const player::PlayerMenuItemMac *) macMenuItem;
@end


//
// PlayerMenuItemMac
//

PLAYER_NS_BEGIN

class PlayerMenuItemMac : public PlayerMenuItem
{
public:
    static PlayerMenuItemMac *create(const std::string &menuId, const std::string &title);
    virtual ~PlayerMenuItemMac();
    
    virtual void setTitle(const std::string &title);
    virtual void setEnabled(bool enabled);
    virtual void setChecked(bool checked);
    virtual void setShortcut(const std::string &shortcut);

protected:
    PlayerMenuItemMac();
    
    PlayerMenuItemMac *_parent;
    NNMenuItem *_menuItem;
    NSMenu     *_menu;
    cocos2d::Vector<PlayerMenuItemMac*> _children;

    friend class PlayerMenuServiceMac;
};

class PlayerMenuServiceMac : public PlayerMenuServiceProtocol
{
public:
    PlayerMenuServiceMac();
    virtual ~PlayerMenuServiceMac();

    virtual PlayerMenuItem *addItem(const std::string &menuId, const std::string &title, const std::string &parentId, int order = MAX_ORDER);
    virtual PlayerMenuItem *addItem(const std::string &menuId, const std::string &title);
    virtual PlayerMenuItem *getItem(const std::string &menuId);
    virtual bool removeItem(const std::string &menuId);
    virtual void setMenuBarEnabled(bool enabled);
    
private:
    bool removeItemInternal(const std::string &menuId, bool isUpdateChildrenOrder);
    void updateChildrenOrder(PlayerMenuItemMac *parent);
    
private:
    PlayerMenuItemMac _root;
    std::unordered_map<std::string, PlayerMenuItemMac*> _items;
};

PLAYER_NS_END

#endif // __PLAYER_MENU_SERVICE_MAC_H_
