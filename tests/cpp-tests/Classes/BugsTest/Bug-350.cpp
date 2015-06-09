//
// Bug-350 
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=350
//

#include "Bug-350.h"

USING_NS_CC;

bool Bug350Layer::init()
{
    if (BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto background = Sprite::create("Hello.png");
        background->setPosition(size.width/2, size.height/2);
        addChild(background);
        return true;
    }

    return false;
}
