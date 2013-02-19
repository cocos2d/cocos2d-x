//
// Bug-350 
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=350
//

#include "Bug-350.h"

bool Bug350Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite *background = CCSprite::create("Hello.png");
        background->setPosition(ccp(size.width/2, size.height/2));
        addChild(background);
        return true;
    }

    return false;
}
