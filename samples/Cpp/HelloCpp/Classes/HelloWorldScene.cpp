#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "event_dispatcher/CCTouchEventListener.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Point(visibleSize) - Point(closeItem->getContentSize() / 2));
//    closeItem->setRotation(30);
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
//    closeItem->setVisible(false);

    auto closeItem2 = MenuItemImage::create(
                                      "CloseNormal.png",
                                      "CloseSelected.png",
                                      CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem2->setPosition(origin + Point(visibleSize) - Point(closeItem->getContentSize() / 2) - Point(0, 20));
//    closeItem2->setRotation(30);
    menu->addChild(closeItem2, 100);
    // create menu, it's an autorelease object
    

    
//    closeItem->unregisterEventCallback(touchEventId);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    auto dispatcher = EventDispatcher::getInstance();
    
    auto layerTouchListener = TouchEventListener::create(Touch::DispatchMode::ALL_AT_ONCE);
    layerTouchListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
        CCLOG("layer touches began... count = %d", (int)touches.size());
    };
    
    
    int layerTouchId = dispatcher->registerEventListenerWithSceneGraphPriority(layerTouchListener, this);
    
    auto spriteTouchListener = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
    spriteTouchListener->setSwallowTouches(true);
    
    spriteTouchListener->onTouchBegan = [=](Touch* touch, Event* evt){
        CCLOG("Touch sprite.... began... %d， drawOrder = %d", sprite->getZOrder(), sprite->getEventPriority());
        dispatcher->unregisterEventListener(layerTouchId);
        return false;
    };
    
    dispatcher->registerEventListenerWithSceneGraphPriority(spriteTouchListener, sprite);
    
    
    for (int i = 0; i < 10; ++i) {
        int zorder = rand() % 50;
        auto sprite1 = Sprite::create("CloseNormal.png");
        
        // position the sprite on the center of the screen
        sprite1->setPosition(Point(30*(i+1), visibleSize.height/2) + origin);
        

        if (zorder % 2 == 0)
        {
            // add the sprite as a child to this layer
            this->addChild(sprite1, zorder);
        }
        else
        {
            sprite->addChild(sprite1, zorder);
        }
    
        char buf[100] = {0};
        sprintf(buf, "%d", zorder);
        auto label = LabelTTF::create(buf, "", 16);
        sprite1->addChild(label);

        auto spriteItemTouchListener = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
        spriteItemTouchListener->onTouchBegan = [=](Touch* touch, Event* event){
            Rect hitRect;
            hitRect.size = sprite1->getContentSize();
            
            Point localPoint = sprite1->convertToNodeSpace(touch->getLocation());
            // HitTest
            if (!hitRect.containsPoint(localPoint))
                return false;
            
            CCLOG("Touch sprite222.... began..zorder: %d. drawOrder: %d", sprite1->getZOrder(), sprite1->getEventPriority());
            sprite1->setColor(Color3B::BLACK);
            return true;
        };
        
        spriteItemTouchListener->onTouchEnded = [=](Touch* touch, Event* event) {
            sprite1->setColor(Color3B::WHITE);
        };
        
        spriteItemTouchListener->setSwallowTouches(true);
        
        dispatcher->registerEventListenerWithSceneGraphPriority(spriteItemTouchListener, sprite1);

        
//        EventDispatcher::getInstance()->registerEventListener(TouchEvent::EVENT_TYPE, [=](Event* evt){
//            TouchEvent* touchEvent = static_cast<TouchEvent*>(evt);
//            if (touchEvent->getEventCode() == TouchEvent::EventCode::BEGAN)
//            {
//                CCLOG("Touch sprite333.... began..zorder: %d. drawOrder: %d", sprite1->getZOrder(), sprite1->getEventPriority());
//            }
//        }, zorder);
        
        CCLOG("set zorder : %d", zorder);
    }
    
    return true;
}

void HelloWorld::menuCloseCallback(Object* sender)
{
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
