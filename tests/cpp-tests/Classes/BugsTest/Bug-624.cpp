//
// Bug-624
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=624
//

#include "Bug-624.h"

USING_NS_CC;

////////////////////////////////////////////////////////
//
// Bug624Layer
//
////////////////////////////////////////////////////////
Bug624Layer::~Bug624Layer()
{
    Device::setAccelerometerEnabled(false);
}

bool Bug624Layer::init()
{
    if(BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto label = Label::createWithTTF("Layer1", "fonts/Marker Felt.ttf", 36.0f);

        label->setPosition(size.width/2, size.height/2);
        addChild(label);
        
        Device::setAccelerometerEnabled(true);
        auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Bug624Layer::onAcceleration,  this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        schedule(CC_SCHEDULE_SELECTOR(Bug624Layer::switchLayer), 5.0f);

        return true;
    }
    
    return false;
}

void Bug624Layer::switchLayer(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(Bug624Layer::switchLayer));

    auto scene = Scene::create();    
    scene->addChild(Bug624Layer2::create(), 0);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene, Color3B::WHITE));
}

void Bug624Layer::onAcceleration(Acceleration* acc, Event* event)
{    
    log("Layer1 accel");
}

////////////////////////////////////////////////////////
//
// Bug624Layer2
//
////////////////////////////////////////////////////////
Bug624Layer2::~Bug624Layer2()
{
    Device::setAccelerometerEnabled(false);
}

bool Bug624Layer2::init()
{
    if(BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto label = Label::createWithTTF("Layer2", "fonts/Marker Felt.ttf", 36.0f);

        label->setPosition(size.width/2, size.height/2);
        addChild(label);
        
        Device::setAccelerometerEnabled(true);
        auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Bug624Layer2::onAcceleration, this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        schedule(CC_SCHEDULE_SELECTOR(Bug624Layer2::switchLayer), 5.0f);

        return true;
    }

    return false;
}

void Bug624Layer2::switchLayer(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(Bug624Layer::switchLayer));

    auto scene = Scene::create();    
    scene->addChild(Bug624Layer::create(), 0);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene, Color3B::RED));
}

void Bug624Layer2::onAcceleration(Acceleration* acc, Event* event)
{    
    log("Layer2 accel");
}
