#include "HelloWorldScene.h"
#include "AppMacros.h"



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
    closeItem->setRotation(30);
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
    closeItem2->setRotation(30);
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
    this->addChild(sprite, 0);
    
    sprite->registerEventCallback(TouchEvent::EVENT_TYPE, [](Event* evt){
        TouchEvent* touchEvent = static_cast<TouchEvent*>(evt);
        if (touchEvent->getEventCode() == TouchEvent::EventCode::BEGAN)
        {
            CCLOG("Touch sprite.... began...");
        }
        return true;
    }, false);
    
    
    CallbackId touchEventId = closeItem->registerEventCallback(TouchEvent::EVENT_TYPE, [=](Event* evt) {
        TouchEvent* touchEvent = static_cast<TouchEvent*>(evt);
        
//        CCLOG("helloworld handle event. %d", touchEvent->_eventCode);
        
        auto touchBegan = [=] (Touch* touch) -> bool {
            label->setString("touch Began....");
            CCLOG("Touch began...");
            return true;
        };
        
        if (touchEvent->getEventCode() == TouchEvent::EventCode::BEGAN)
        {
            touchBegan(touchEvent->getTouches()[0]);
        }
        
        
        
        return true;
    }, false);
    
    
    
    CallbackId touchEventId2 = closeItem2->registerEventCallback(TouchEvent::EVENT_TYPE, [=](Event* evt) {
        TouchEvent* touchEvent = static_cast<TouchEvent*>(evt);
        
//        CCLOG("helloworld2 handle event. %d", touchEvent->_eventCode);
        
        auto touchBegan = [=] (Touch* touch) -> bool {
            CCLOG("Touch2 began...");
            return true;
        };
        
        if (touchEvent->getEventCode() == TouchEvent::EventCode::BEGAN)
        {
            touchBegan(touchEvent->getTouches()[0]);
        }
//        evt->stopPropagation();
        return true;
    }, false);
    
//    closeItem->unregisterEventCallback(touchEventId);
    
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
