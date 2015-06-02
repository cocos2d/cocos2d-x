
#include "PlayerMenuServiceMac.h"
#include "PlayerUtils.h"

#include "cocos2d.h"
#include "AppEvent.h"

USING_NS_CC;

///////////////////////////////////////  menu helper  //////////////////////////////////////////////
static bool __G_IS_MENUBAR_ENABLED__ = true;    // WTF

@implementation NNMenuItem
@synthesize scriptHandler;
@synthesize macMenuItem;

+(id) createMenuItem:(const player::PlayerMenuItemMac *) macMenuItem
{
    if (macMenuItem->getTitle().compare("-") == 0)
    {
        return [NSMenuItem separatorItem];
    }
    else
    {
        return [[[NNMenuItem alloc] initWithMenuItem:macMenuItem] autorelease];
    }
    
    return NULL;
}

-(id) initWithMenuItem:(const player::PlayerMenuItemMac *) menuItem
{
    NSString *title = [NSString stringWithUTF8String:menuItem->getTitle().c_str()];
    title = [title stringByReplacingOccurrencesOfString:@"&" withString:@""];
    if ([super initWithTitle:title action:@selector(onClicked:) keyEquivalent:@""])
    {
        self.target = self;
    }
    
    self.macMenuItem = menuItem;
    
    return self;
}

-(void) setShortcut:(std::string) shortcut
{
    std::vector <std::string> fields = player::splitString(shortcut, std::string("+"));
    
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
    AppEvent event(kAppEventName, APP_EVENT_MENU);
    
    std::stringstream buf;
    buf << "{\"data\":\"" << self.macMenuItem->getMenuId().c_str() << "\"";
    buf << ",\"name\":" << "\"menuClicked\"" << "}";
    event.setDataString(buf.str());
    event.setUserData((void*)self.macMenuItem);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

-(BOOL) validateMenuItem:(NSMenuItem *)menuItem
{
    return __G_IS_MENUBAR_ENABLED__;
}

@end



PLAYER_NS_BEGIN

//

PlayerMenuItemMac *PlayerMenuItemMac::create(const std::string &menuId, const std::string &title)
{
    PlayerMenuItemMac *item = new PlayerMenuItemMac();
    item->_menuId = menuId;
    item->_title = title;
    item->autorelease();
    return item;
}

PlayerMenuItemMac::PlayerMenuItemMac()
    : _parent(nullptr)
    , _menuItem(nullptr)
    , _menu(nullptr)
{
}

PlayerMenuItemMac::~PlayerMenuItemMac()
{
    CC_SAFE_RELEASE(_parent);
    if (_menuItem)
    {
        [_parent->_menu removeItem:_menuItem];
    }
    
    CCLOG("PlayerMenuItemWin::~PlayerMenuItemWin() - %s", _menuId.c_str());
}

void PlayerMenuItemMac::setTitle(const std::string &title)
{
    if (title.length() == 0)
    {
        CCLOG("MenuServiceWin::setTitle() - can not set menu title to empty, menu id (%s)", _menuId.c_str());
        return;
    }
    
    _menuItem.title = [NSString stringWithUTF8String:title.c_str()];
    if (_menu)
    {
        _menu.title = _menuItem.title;
    }
    
    _title = title;
}

void PlayerMenuItemMac::setEnabled(bool enabled)
{
    _isEnabled = enabled;
    
    if (enabled)
    {
        [_menuItem setAction:@selector(onClicked:)];
    }
    else
    {
        [_menuItem setAction:nil];
    }
}

void PlayerMenuItemMac::setChecked(bool checked)
{
    _isChecked = checked;
    [_menuItem setState:checked ? NSOnState : NSOffState];
}

void PlayerMenuItemMac::setShortcut(const std::string &shortcut)
{
    _shortcut = shortcut;
    [_menuItem setShortcut:shortcut];
}



////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerMenuServiceMac::PlayerMenuServiceMac()
{
    // @TODO: build menu with **EDIT** menu
    
    NSApplication *thisApp = [NSApplication sharedApplication];
    _root._menu = [thisApp mainMenu];
}

PlayerMenuServiceMac::~PlayerMenuServiceMac()
{
    log("~PlayerMenuServiceMac");
    _items.clear();
}

PlayerMenuItem* PlayerMenuServiceMac::addItem(const std::string &menuId, const std::string &title,
                                              const std::string &parentId, int order)
{
    if (menuId.length() == 0 || title.length() == 0)
    {
        CCLOG("PlayerMenuServiceMac::addItem() - menuId and title must is non-empty");
        return nullptr;
    }
    
    // check menu id is exists
    if (_items.find(menuId) != _items.end())
    {
        CCLOG("PlayerMenuServiceMac::addItem() - menu id (%s) is exists", menuId.c_str());
        return nullptr;
    }
    
    // set parent
    PlayerMenuItemMac *parent = &_root;
    if (parentId.length())
    {
        // query parent menu
        auto it = _items.find(parentId);
        if (it != _items.end())
        {
            parent = it->second;
        }
    }
    
    if (!parent->_menu)
    {
        NSMenu *nsmenu = [[NSMenu alloc] initWithTitle:[parent->_menuItem title]];
        [parent->_parent->_menu setSubmenu:nsmenu forItem:parent->_menuItem];
        parent->_menu = nsmenu;
        parent->_isGroup = true;
    }


    // create new menu item
    PlayerMenuItemMac *item = PlayerMenuItemMac::create(menuId, title);
    item->_parent = parent;
    item->_parent->retain();
    
    // check new menu item position
    int childSize = (int) [parent->_menu itemArray].count;
    childSize = (int) parent->_children.size();
    if (order > childSize)
    {
        order = childSize;
    }
    else if (order < 0)
    {
        order = 0;
    }

    
    // add menu item to menu bar
    int newIndex = order;
    if (parent == &_root)
    {
        newIndex += 1;
    }
    NNMenuItem *newItem = [NNMenuItem createMenuItem:item];
    [parent->_menu insertItem:newItem atIndex:newIndex];
    item->_menuItem = newItem;

    
    // update menu state
    parent->_children.insert(order, item);
    _items[item->_menuId] = item;
    updateChildrenOrder(parent);
    
    return item;
}

PlayerMenuItem* PlayerMenuServiceMac::addItem(const std::string &menuId, const std::string &title)
{
    return addItem(menuId, title, "");
}

PlayerMenuItem* PlayerMenuServiceMac::getItem(const std::string &menuId)
{
    auto it = _items.find(menuId);
    if (it == _items.end())
    {
        CCLOG("MenuServiceWin::getItem() - Invalid menu id (%s)", menuId.c_str());
        return nullptr;
    }
    
    return it->second;
}

bool PlayerMenuServiceMac::removeItem(const std::string &menuId)
{
    return removeItemInternal(menuId, true);;
}

void PlayerMenuServiceMac::setMenuBarEnabled(bool enabled)
{
    __G_IS_MENUBAR_ENABLED__ = enabled;
}

#pragma mark - private -

bool PlayerMenuServiceMac::removeItemInternal(const std::string &menuId, bool isUpdateChildrenOrder)
{
    auto it = _items.find(menuId);
    if (it == _items.end())
    {
        CCLOG("MenuServiceWin::removeItem() - Invalid menu id (%s)", menuId.c_str());
        return false;
    }

    PlayerMenuItemMac *item = it->second;
    if (item->_children.size() == 0)
    {
        // remove item from parent
        bool removed = false;
        auto *theChildren = &item->_parent->_children;
        for (auto it = theChildren->begin(); it != theChildren->end(); ++it)
        {
            if ((*it)->_menuItem == item->_menuItem)
            {
                theChildren->erase(it);
                removed = true;
                break;
            }
        }
        
        if (!removed)
        {
            CCLOG("MenuServiceWin::removeItem() - remove menu item (%s) failed, not found command id from parent->children", item->_menuId.c_str());
        }

        // remove menu id mapping
        _items.erase(menuId);
        if (isUpdateChildrenOrder)
        {
            updateChildrenOrder(item->_parent);
        }
        return true;
    }
    else
    {
        // remove all children
        while (item->_children.size() != 0)
        {
            PlayerMenuItemMac *child = *item->_children.begin();
            if (!removeItemInternal(child->_menuId.c_str(), false))
            {
                break;
                return false;
            }
         }
        return removeItemInternal(menuId, true);
    }
    
    return false;
}

void PlayerMenuServiceMac::updateChildrenOrder(PlayerMenuItemMac *parent)
{
    auto *children = &parent->_children;
    int order = 0;
    for (auto it = children->begin(); it != children->end(); ++it)
    {
        (*it)->_order = order;
        order++;
    }
}

PLAYER_NS_END