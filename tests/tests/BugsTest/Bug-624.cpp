//
// Bug-624
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=624
//

#include "Bug-624.h"

////////////////////////////////////////////////////////
//
// Bug624Layer
//
////////////////////////////////////////////////////////
bool Bug624Layer::init()
{
    if(BugsTestBaseLayer::init())
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::labelWithString("Layer1", "Marker Felt", 36);

		label->setPosition(ccp(size.width/2, size.height/2));
		addChild(label);
		setIsAccelerometerEnabled(true);
        schedule(schedule_selector(Bug624Layer::switchLayer), 5.0f);

        return true;
	}
    
	return false;
}

void Bug624Layer::switchLayer(ccTime dt)
{
	unschedule(schedule_selector(Bug624Layer::switchLayer));

    CCScene *scene = CCScene::node();	
    scene->addChild(Bug624Layer2::node(), 0);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, scene, ccWHITE));
}

void Bug624Layer::didAccelerate(CCAcceleration* acceleration)
{	
	CCLog("Layer1 accel");
}

////////////////////////////////////////////////////////
//
// Bug624Layer2
//
////////////////////////////////////////////////////////
bool Bug624Layer2::init()
{
    if(BugsTestBaseLayer::init())
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::labelWithString("Layer2", "Marker Felt", 36);

        label->setPosition(ccp(size.width/2, size.height/2));
        addChild(label);
        setIsAccelerometerEnabled(true);
        schedule(schedule_selector(Bug624Layer2::switchLayer), 5.0f);

        return true;
    }

    return false;
}

void Bug624Layer2::switchLayer(ccTime dt)
{
    unschedule(schedule_selector(Bug624Layer::switchLayer));

    CCScene *scene = CCScene::node();	
    scene->addChild(Bug624Layer::node(), 0);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(2.0f, scene, ccRED));
}

void Bug624Layer2::didAccelerate(CCAcceleration* acceleration)
{	
	CCLog("Layer2 accel");
}
