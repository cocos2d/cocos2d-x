/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
