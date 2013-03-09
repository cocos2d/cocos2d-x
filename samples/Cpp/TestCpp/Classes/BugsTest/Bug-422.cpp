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
    CCNode *node = getChildByTag(localtag-1);
    CCLog("Menu: %p", node);
    removeChild(node, false);
//    [self removeChildByTag:localtag-1 cleanup:NO];

    CCMenuItem *item1 = CCMenuItemFont::create("One", this, menu_selector(Bug422Layer::menuCallback));
    CCLog("MenuItemFont: %p", item1);
    CCMenuItem *item2 = CCMenuItemFont::create("Two", this, menu_selector(Bug422Layer::menuCallback));
    CCMenu *menu = CCMenu::create(item1, item2, NULL);
    menu->alignItemsVertically();

    float x = CCRANDOM_0_1() * 50;
    float y = CCRANDOM_0_1() * 50;
    menu->setPosition(ccpAdd( menu->getPosition(), ccp(x,y)));
    addChild(menu, 0, localtag);    

    //[self check:self];
}

void Bug422Layer::check(CCNode* t)
{
    CCArray *array = t->getChildren();
    CCObject* pChild = NULL;
    CCARRAY_FOREACH(array, pChild)
    {
        CC_BREAK_IF(! pChild);
        CCNode* pNode = (CCNode*) pChild;
        CCLog("%p, rc: %d", pNode, pNode->retainCount());
        check(pNode);
    }
}

void Bug422Layer::menuCallback(CCObject* sender)
{
    reset();
}
