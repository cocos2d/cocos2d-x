//
//  MenuServiceMac.mm
//  quick-x-player
//

#include "MenuServiceMac.h"

#include "CCLuaEngine.h"

@interface NNMenuItem : NSMenuItem
@property (nonatomic) int scriptHandler;
@end

@implementation NNMenuItem


-(id) initWithData:(const player::MenuItem &) itemData
{
    NSString *title = [NSString stringWithUTF8String:itemData.title.c_str()];
    if ([super initWithTitle:title action:@selector(onClicked:) keyEquivalent:@"0"])
    {
        self.scriptHandler = itemData.scriptHandlerId;
        self.target = self;
    }
    return self;
}

-(void) onClicked:(id)sender
{
    if (self.scriptHandler != 0)
    {
        cocos2d::LuaEngine::getInstance()->getLuaStack()->pushString("{}");
        cocos2d::LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(self.scriptHandler, 1);
    }
}

@end


PLAYER_NS_BEGIN


////////////////////////////////////////////////////////////////////////////////////////////////////

MenuServiceMac::MenuServiceMac()
{
    m_id2Menu = [[NSMutableDictionary alloc] init];
}

MenuServiceMac::~MenuServiceMac()
{
    [m_id2Menu release];
}

void MenuServiceMac::addItem( const MenuItem &item,
                              std::string    parentId,
                              int index)
{
    NSMenu *menu             = NULL;
    NSString *itemIdString   = [NSString stringWithUTF8String:item.itemId.c_str()];
    NSString *parentIdString = [NSString stringWithUTF8String:parentId.c_str()];

    if ([m_id2Menu objectForKey:itemIdString])
    {
        cocos2d::log("[add menuItem] item (%s) has been exist.", item.itemId.c_str());
        return ;
    }
    
    if (item.isGroup)
    {
        if (parentId.length() <= 0)
        {
            NSApplication *thisApp = [NSApplication sharedApplication];
            menu = [thisApp mainMenu];
        }
        else
        {
            menu = [[m_id2Menu objectForKey:parentIdString] submenu];
        }
        
        if (!menu)
        {
            cocos2d::log("[add menuItem] parent (%s) menu is not exist.", parentId.c_str());
            return ;
        }
        

        if (index < 0 || index > [menu itemArray].count) {
            index = (int)[menu itemArray].count;
        }
        
        
        NSString *title = [NSString stringWithUTF8String:item.title.c_str()];
        NSMenu *nsmenu         = [[NSMenu alloc] initWithTitle:title];
        NSMenuItem *nsMenuItem = [[NSMenuItem alloc] initWithTitle:title action:nil keyEquivalent:@""];
        

        [menu insertItem:nsMenuItem atIndex:index];
        [menu setSubmenu:nsmenu forItem:nsMenuItem];
        
        [m_id2Menu setObject:nsMenuItem forKey:[NSString stringWithUTF8String:item.itemId.c_str()]];

    }
    else
    {
        menu = [[m_id2Menu objectForKey:[NSString stringWithUTF8String:parentId.c_str()]] submenu] ;
        if (!menu)
        {
            cocos2d::log("[add menuItem] parent (%s) menu is not exist.", parentId.c_str());
            return ;
        }
        
        if (index < 0 || index > [menu itemArray].count) {
            index = (int)[menu itemArray].count;
        }
        
        NNMenuItem *newItem = [[[NNMenuItem alloc] initWithData:item] autorelease];
        
        [menu insertItem:newItem atIndex:index];
        
        [m_id2Menu setObject:newItem forKey:[NSString stringWithUTF8String:item.itemId.c_str()]];
    }
}


void MenuServiceMac::modifyItem(const MenuItem &item)
{
    NNMenuItem *menuObj = (NNMenuItem*) [m_id2Menu objectForKey:[NSString stringWithUTF8String:item.itemId.c_str()]];
    
    if (menuObj)
    {
        NSString *title = [NSString stringWithUTF8String:item.title.c_str()];
        if (item.isGroup)
        {
            [[menuObj submenu] setTitle:title];
        }
        else
        {
            [menuObj setTitle:title];
        }
    }
}

void MenuServiceMac::deleteItem(const MenuItem &item)
{
    id menuObj = [m_id2Menu objectForKey:[NSString stringWithUTF8String:item.itemId.c_str()]];
    
    if (menuObj)
    {
        NNMenuItem *menuItem = (NNMenuItem *) (menuObj);
        
        [[menuItem menu] removeItem:menuItem];
        
        [m_id2Menu removeObjectForKey:[NSString stringWithUTF8String:item.itemId.c_str()]];
        // 递归删除这些 id
    }
}

PLAYER_NS_END