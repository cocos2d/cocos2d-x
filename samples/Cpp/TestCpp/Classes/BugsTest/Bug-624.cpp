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
        Size size = Director::sharedDirector()->getWinSize();
        LabelTTF *label = LabelTTF::create("Layer1", "Marker Felt", 36);

        label->setPosition(ccp(size.width/2, size.height/2));
        addChild(label);
        setAccelerometerEnabled(true);
        schedule(schedule_selector(Bug624Layer::switchLayer), 5.0f);

        return true;
    }
    
    return false;
}

void Bug624Layer::switchLayer(float dt)
{
    unschedule(schedule_selector(Bug624Layer::switchLayer));

    Scene *scene = Scene::create();    
    scene->addChild(Bug624Layer2::create(), 0);
    Director::sharedDirector()->replaceScene(TransitionFade::create(2.0f, scene, ccWHITE));
}

void Bug624Layer::didAccelerate(Acceleration* acceleration)
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
        Size size = Director::sharedDirector()->getWinSize();
        LabelTTF *label = LabelTTF::create("Layer2", "Marker Felt", 36);

        label->setPosition(ccp(size.width/2, size.height/2));
        addChild(label);
        setAccelerometerEnabled(true);
        schedule(schedule_selector(Bug624Layer2::switchLayer), 5.0f);

        return true;
    }

    return false;
}

void Bug624Layer2::switchLayer(float dt)
{
    unschedule(schedule_selector(Bug624Layer::switchLayer));

    Scene *scene = Scene::create();    
    scene->addChild(Bug624Layer::create(), 0);
    Director::sharedDirector()->replaceScene(TransitionFade::create(2.0f, scene, ccRED));
}

void Bug624Layer2::didAccelerate(Acceleration* acceleration)
{    
    CCLog("Layer2 accel");
}
