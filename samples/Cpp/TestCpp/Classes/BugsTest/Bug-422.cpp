//
// Bug-422 test case by lhunath
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=422
//

#include "Bug-422.h"

bool Bug422Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        reset();
        return true;
    }

    return false;
}

void Bug422Layer::reset()
{
    static int localtag = 0;
    localtag++;

    // TO TRIGGER THE BUG:
    // remove the itself from parent from an action
    // The menu will be removed, but the instance will be alive
    // and then a new node will be allocated occupying the memory.
    // => CRASH BOOM BANG
    Node *node = getChildByTag(localtag-1);
    CCLog("Menu: %p", node);
    removeChild(node, false);
//    [self removeChildByTag:localtag-1 cleanup:NO];

    MenuItem *item1 = MenuItemFont::create("One", CC_CALLBACK_1(Bug422Layer::menuCallback, this) );
    CCLog("MenuItemFont: %p", item1);
	MenuItem *item2 = MenuItemFont::create("Two", CC_CALLBACK_1(Bug422Layer::menuCallback, this) );
    Menu *menu = Menu::create(item1, item2, NULL);
    menu->alignItemsVertically();

    float x = CCRANDOM_0_1() * 50;
    float y = CCRANDOM_0_1() * 50;
    menu->setPosition(ccpAdd( menu->getPosition(), ccp(x,y)));
    addChild(menu, 0, localtag);    

    //[self check:self];
}

void Bug422Layer::check(Node* t)
{
    Array *array = t->getChildren();
    Object* pChild = NULL;
    CCARRAY_FOREACH(array, pChild)
    {
        CC_BREAK_IF(! pChild);
        Node* pNode = (Node*) pChild;
        CCLog("%p, rc: %d", pNode, pNode->retainCount());
        check(pNode);
    }
}

void Bug422Layer::menuCallback(Object* sender)
{
    reset();
}
