//
// Bug-899
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=899
//
// Test coded by: JohnnyFlash
//

#include "Bug-899.h"

bool Bug899Layer::init()
{
//    Director::sharedDirector()->enableRetinaDisplay(true);
    if (BugsTestBaseLayer::init())
    {
        Sprite *bg = Sprite::create("Images/bugs/RetinaDisplay.jpg");
        addChild(bg, 0);
        bg->setAnchorPoint(PointZero);

        return true;
    }
    return false;
}
