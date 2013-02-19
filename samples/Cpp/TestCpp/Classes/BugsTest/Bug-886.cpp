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
        //        CGSize size = [[CCDirector sharedDirector] winSize];
        
        CCSprite* sprite = CCSprite::create("Images/bugs/bug886.jpg");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(CCPointZero);
        sprite->setScaleX(0.6f);
        addChild(sprite);

        CCSprite* sprite2 = CCSprite::create("Images/bugs/bug886.png");
        sprite2->setAnchorPoint(CCPointZero);
        sprite2->setScaleX(0.6f);
        sprite2->setPosition(ccp(sprite->getContentSize().width * 0.6f + 10, 0));
        addChild(sprite2);

        return true;
    }

    return false;
}
