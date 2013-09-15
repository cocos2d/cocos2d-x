//
// Bug-899
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=899
//
// Test coded by: JohnnyFlash
//

#include "Bug-899.h"

bool Bug899Layer::init()
{
//    Director::getInstance()->enableRetinaDisplay(true);
    if (BugsTestBaseLayer::init())
    {
        auto bg = Sprite::create("Images/bugs/RetinaDisplay.jpg");
        addChild(bg, 0);
        bg->setAnchorPoint(Point::ZERO);

        return true;
    }
    return false;
}
