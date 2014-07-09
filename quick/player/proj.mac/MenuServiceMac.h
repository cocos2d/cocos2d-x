//
//  PlayerMenuServiceMac.h
//  quick-x-player
//
//

#ifndef __PLAYER_MenuServiceMac_h
#define __PLAYER_MenuServiceMac_h

#include <unordered_map>
#include "PlayerMacros.h"
#include "PlayerMenuServiceProtocol.h"

PLAYER_NS_BEGIN

class MenuServiceMac : public PlayerMenuServiceProtocol
{
public:
    MenuServiceMac();
    ~MenuServiceMac();
    
    virtual void addItem(const PlayerMenuItem &item,
                         std::string parentId = std::string(),
                         int index = MAX_INT);
    
    virtual void modifyItem(const PlayerMenuItem &item);
    
    virtual void deleteItem(const PlayerMenuItem &item);
    
private:
    void removeIdRecursion(NSMenuItem *menuItem);
    void removeId(NSMenuItem *menuItem);
    void addId(const std::string &menuIt, NSMenuItem *menuItem);
    
private:
    std::unordered_map<std::string, id> m_id2Menu;
    std::unordered_map<id, std::string> m_menu2Id;
};

PLAYER_NS_END

#endif // __PLAYER_MenuServiceMac_h
