//
// Bug-886
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=886
//

#include "Bug-886.h"

bool Bug886Layer::init()
{
    if(BugsTestBaseLayer::init())
    {
        // ask director the the window size
        //        CGSize size = [[Director sharedDirector] winSize];
        
        Sprite* sprite = Sprite::create("Images/bugs/bug886.jpg");
        sprite->setAnchorPoint(PointZero);
        sprite->setPosition(PointZero);
        sprite->setScaleX(0.6f);
        addChild(sprite);

        Sprite* sprite2 = Sprite::create("Images/bugs/bug886.png");
        sprite2->setAnchorPoint(PointZero);
        sprite2->setScaleX(0.6f);
        sprite2->setPosition(ccp(sprite->getContentSize().width * 0.6f + 10, 0));
        addChild(sprite2);

        return true;
    }

    return false;
}
