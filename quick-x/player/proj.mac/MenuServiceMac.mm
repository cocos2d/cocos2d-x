//
//  MenuServiceMac.mm
//  quick-x-player
//

#include "MenuServiceMac.h"

#include "CCLuaEngine.h"

///////////////////////////////////////  splite helper  ////////////////////////////////////////////

#include <sstream>
#include <string>

struct split
{
    enum empties_t { empties_ok, no_empties };
};

template <typename Container>
static Container& split(
                        Container&                                 result,
                        const typename Container::value_type&      s,
                        typename Container::value_type::value_type delimiter,
                        split::empties_t                           empties = split::empties_ok )
{
    result.clear();
    std::istringstream ss( s );
    while (!ss.eof())
    {
        typename Container::value_type field;
        getline( ss, field, delimiter );
        if ((empties == split::no_empties) && field.empty()) continue;
        result.push_back( field );
    }
    return result;
}


///////////////////////////////////////  menu helper  //////////////////////////////////////////////


@interface NNMenuItem : NSMenuItem
@property (nonatomic) int scriptHandler;
@end

@implementation NNMenuItem


-(id) initWithData:(const player::MenuItem &) itemData
{
    NSString *title = [NSString stringWithUTF8String:itemData.title.c_str()];
    if ([super initWithTitle:title action:@selector(onClicked:) keyEquivalent:@""])
    {
        self.scriptHandler = itemData.scriptHandlerId;
        self.target = self;
    }
    return self;
}

-(void) setShortcut:(std::string) shortcut
{
    std::vector <std::string> fields;
    split(fields, shortcut, '+');
    
    NSUInteger mask = [self keyEquivalentModifierMask];
    for (auto cut : fields)
    {
        if (cut == kPlayerSuperModifyKey)
        {
            mask |= NSCommandKeyMask;
        }
        else if (cut == kPlayerShiftModifyKey)
        {
            mask |= NSShiftKeyMask;
        }
        else if (cut == kPlayerCtrlModifyKey)
        {
            mask |= NSControlKeyMask;
        }
        else if (cut == kPlayerAltModifyKey)
        {
            mask |= NSAlternateKeyMask;
        }
        else
        {
            if (cut.length() == 1)
            {
                [self setKeyEquivalent:[NSString stringWithUTF8String:cut.c_str()]];
            }
            else
            {
                CCLOG("[modifyItem] shortcut (%s) is invalid.", shortcut.c_str());
            }
        }
    }
    
    if (mask != 0)
    {
        [self setKeyEquivalentModifierMask:mask];
    }
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
//    m_id2Menu = [[NSMutableDictionary alloc] init];
}

MenuServiceMac::~MenuServiceMac()
{
//    [m_id2Menu release];
    m_menu2Id.clear();
    m_id2Menu.clear();
}

void MenuServiceMac::addItem( const MenuItem &item,
                              std::string    parentId,
                              int index)
{
    NSMenu *menu             = NULL;

    std::unordered_map<std::string, id>::iterator it = m_id2Menu.find(item.itemId);
    if (it != m_id2Menu.end())
    {
        CCLOG("[add menuItem] item (%s) has been exist.", item.itemId.c_str());
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
            menu = [(it->second) submenu];
        }
        
        if (!menu)
        {
            CCLOG("[add menuItem] parent (%s) menu is not exist.", parentId.c_str());
            return ;
        }
        

        if (index < 0 || index > [menu itemArray].count) {
            index = (int)[menu itemArray].count;
        }
        
        
        NSString *title        = [NSString stringWithUTF8String:item.title.c_str()];
        NSMenu *nsmenu         = [[NSMenu alloc] initWithTitle:title];
        NSMenuItem *nsMenuItem = [[NSMenuItem alloc] initWithTitle:title action:nil keyEquivalent:@""];
        

        [menu insertItem:nsMenuItem atIndex:index];
        [menu setSubmenu:nsmenu forItem:nsMenuItem];
        
        addId(item.itemId, nsMenuItem);
    }
    else
    {
        std::unordered_map<std::string, id>::iterator it = m_id2Menu.find(parentId);
        if (it != m_id2Menu.end())
        {
            menu = [it->second submenu];
            if (index < 0 || index > [menu itemArray].count) {
                index = (int)[menu itemArray].count;
            }
            
            NNMenuItem *newItem = [[[NNMenuItem alloc] initWithData:item] autorelease];
            [menu insertItem:newItem atIndex:index];
            
            addId(item.itemId, newItem);
            
        }
        else
        {
            CCLOG("[add menuItem] parent (%s) menu is not exist.", parentId.c_str());
        }
    }
    
    modifyItem(item);
}

void MenuServiceMac::modifyItem(const MenuItem &item)
{
    std::unordered_map<std::string, id>::iterator it = m_id2Menu.find(item.itemId);
    if (it != m_id2Menu.end())
    {
        NNMenuItem *menuObj = it->second;
        NSString *title     = [NSString stringWithUTF8String:item.title.c_str()];
        if (item.isGroup)
        {
            [[menuObj submenu] setTitle:title];
        }
        else
        {
            [menuObj setTitle:title];
            
            menuObj.scriptHandler = item.scriptHandlerId;
            [menuObj setState:item.isChecked ? NSOnState : NSOffState];
            [menuObj setShortcut:item.shortcut];
            
            if (item.isEnabled)
            {
                [menuObj setAction:@selector(onClicked:)];
            }
            else
            {
                [menuObj setAction:nil];
            }
        }
        
        [menuObj setEnabled:item.isEnabled ? YES : NO];

        // more date update
    }
    else
    {
        CCLOG("[modifyItem] item (%s) is not exist.", item.itemId.c_str());
    }
}

void MenuServiceMac::deleteItem(const MenuItem &item)
{
    std::unordered_map<std::string, id>::iterator it = m_id2Menu.find(item.itemId);
    if (it != m_id2Menu.end())
    {
        NNMenuItem *menuObj = it->second;
        
        removeIdRecursion(menuObj);
        [[menuObj menu] removeItem:menuObj];
    }
}

#pragma mark - private -

void MenuServiceMac::removeIdRecursion(NSMenuItem *menuItem)
{
    NSMenu *menu = [menuItem submenu];
    if (menu)
    {
        for (NSMenuItem *oneItem in [menu itemArray]) {
            removeIdRecursion(oneItem);
        }
    }
    
    removeId(menuItem);
}

void MenuServiceMac::removeId(NSMenuItem *menuItem)
{
    std::string itemId = m_menu2Id[menuItem];
    m_id2Menu.erase(itemId);
    m_menu2Id.erase(menuItem);
}

void MenuServiceMac::addId(const std::string &menuIt, NSMenuItem *menuItem)
{
    m_id2Menu[menuIt]   = menuItem;
    m_menu2Id[menuItem] = menuIt;
}

PLAYER_NS_END