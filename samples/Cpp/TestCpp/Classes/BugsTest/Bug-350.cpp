//
// Bug-350 
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=350
//

#include "Bug-350.h"

bool Bug350Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        Size size = Director::getInstance()->getWinSize();
        Sprite *background = Sprite::create("Hello.png");
        background->setPosition(Point(size.width/2, size.height/2));
        addChild(background);
        return true;
    }

    return false;
}
