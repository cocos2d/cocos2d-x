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
        self.scriptHandler = 0;
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

void MenuServiceMac::addItem( const MenuItem &item,
                              int parentIndex,
                              int index)
{
    if (parentIndex <= 0)
    {
        NSApplication *thisApp = [NSApplication sharedApplication];
        //Now get the main menu object
        NSMenu *mainMenu = [thisApp mainMenu];

        if (index < 0 || index > [mainMenu itemArray].count) {
            index = (int)[mainMenu itemArray].count;
        }
        
        
        NSString *title = [NSString stringWithUTF8String:item.title.c_str()];
        NSMenu *nsmenu         = [[NSMenu alloc] initWithTitle:title];
        NSMenuItem *nsMenuItem = [[NSMenuItem alloc] initWithTitle:title action:nil keyEquivalent:@""];
        
        [mainMenu insertItem:nsMenuItem atIndex:index];
        [mainMenu setSubmenu:nsmenu forItem:nsMenuItem];

    }
    else
    {
        NNMenuItem *newItem = [[NNMenuItem alloc] initWithData:item];
        newItem.scriptHandler = item.scriptHandlerId;
    }
}


void MenuServiceMac::modifyItem(const MenuItem &item)
{
    
}

void MenuServiceMac::deleteItem(const MenuItem &item)
{
    
}

PLAYER_NS_END