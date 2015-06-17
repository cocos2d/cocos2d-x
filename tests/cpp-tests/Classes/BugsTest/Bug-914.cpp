//
//  HelloWorldLayer.m
//  EAGLViewBug
//
//  Created by Wylan Werth on 7/5/10.
//  Copyright BanditBear Games 2010. All rights reserved.
//

// Import the interfaces
#include"Bug-914.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Bug914Layer::init()
{
    // always call "super" init
    // Apple recommends to re-assign "self" with the "super" return value
    if (BugsTestBase::init())
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(Bug914Layer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(Bug914Layer::onTouchesMoved, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        // ask director the the window size
        auto size = Director::getInstance()->getWinSize();
        LayerColor *layer;
        for( int i=0;i < 5;i++)
        {
            layer = LayerColor::create(Color4B(i*20, i*20, i*20,255));
            layer->setContentSize(Size(i*100, i*100));
            layer->setPosition(size.width/2, size.height/2);
            layer->setAnchorPoint(Vec2(0.5f, 0.5f));
            layer->ignoreAnchorPointForPosition(false);
            addChild(layer, -1-i);
        }

        // create and initialize a Label
        auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 64.0f);
        auto item1 = MenuItemFont::create("restart", CC_CALLBACK_1(Bug914Layer::restart, this));

        auto menu = Menu::create(item1, nullptr);
        menu->alignItemsVertically();
        menu->setPosition(size.width/2, 100);
        addChild(menu);

        // position the label on the center of the screen
        label->setPosition(size.width /2 , size.height/2);

        // add the label as a child to this Layer
        addChild(label);
        return true;
    }
    return false;
}

void Bug914Layer::onTouchesMoved(const std::vector<Touch*>& touches, Event * event)
{
    log("Number of touches: %d", (int)touches.size());
}

void Bug914Layer::onTouchesBegan(const std::vector<Touch*>& touches, Event * event)
{
    onTouchesMoved(touches, event);
}

void Bug914Layer::restart(Ref* sender)
{
    Director::getInstance()->replaceScene(Bug914Layer::create());
}
