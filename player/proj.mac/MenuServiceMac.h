//
//  PlayerMenuServiceMac.h
//  quick-x-player
//
//

#ifndef __PLAYER_MenuServiceMac_h
#define __PLAYER_MenuServiceMac_h

#include "PlayerMacros.h"
#include "PlayerMenuServiceProtocol.h"

PLAYER_NS_BEGIN

class MenuServiceMac : public PlayerMenuServiceProtocol
{
public:
    MenuServiceMac();
    ~MenuServiceMac();
    
    virtual void addItem(const MenuItem &item,
                         std::string parentId = std::string(),
                         int index = MAX_INT);
    
    virtual void modifyItem(const MenuItem &item);
    
    virtual void deleteItem(const MenuItem &item);
    
private:
    NSMutableDictionary *m_id2Menu;
};

PLAYER_NS_END

#endif // __PLAYER_MenuServiceMac_h
