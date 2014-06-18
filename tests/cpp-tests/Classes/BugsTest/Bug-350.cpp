//
// Bug-350 
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=350
//

#include "Bug-350.h"

bool Bug350Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto background = Sprite::create("Hello.png");
        background->setPosition(Vec2(size.width/2, size.height/2));
        addChild(background);
        return true;
    }

    return false;
}
