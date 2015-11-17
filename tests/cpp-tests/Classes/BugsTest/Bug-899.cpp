//
// Bug-899
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=899
//
// Test coded by: JohnnyFlash
//

#include "Bug-899.h"

USING_NS_CC;

bool Bug899Layer::init()
{
//    Director::getInstance()->enableRetinaDisplay(true);
    if (BugsTestBase::init())
    {
        auto bg = Sprite::create("Images/bugs/RetinaDisplay.jpg");
        addChild(bg, 0);
        bg->setAnchorPoint(Vec2::ZERO);

        return true;
    }
    return false;
}
