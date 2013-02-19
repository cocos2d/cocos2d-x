//
// Bug-899
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=899
//
// Test coded by: JohnnyFlash
//

#include "Bug-899.h"

bool Bug899Layer::init()
{
//    CCDirector::sharedDirector()->enableRetinaDisplay(true);
    if (BugsTestBaseLayer::init())
    {
        CCSprite *bg = CCSprite::create("Images/bugs/RetinaDisplay.jpg");
        addChild(bg, 0);
        bg->setAnchorPoint(CCPointZero);

        return true;
    }
    return false;
}
