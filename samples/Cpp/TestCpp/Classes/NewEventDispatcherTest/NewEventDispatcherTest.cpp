//
//  NewEventDispatcherTest.cpp
//  samples
//
//  Created by James Chen on 9/13/13.
//
//

#include "NewEventDispatcherTest.h"
#include "testResource.h"

namespace {
    
std::function<Layer*()> createFunctions[] =
{
    CL(TouchableSpriteTest),
    CL(FixedPriorityTest),
    CL(RemoveListenerWhenDispatching),
    CL(CustomEventTest),
    CL(LabelKeyboardEventTest),
    CL(SpriteAccelerationEventTest)
};

unsigned int TEST_CASE_COUNT = sizeof(createFunctions) / sizeof(createFunctions[0]);

int sceneIdx=-1;
Layer* createTest(int index)
{
    auto layer = (createFunctions[index])();;
    
    if (layer)
    {
        layer->autorelease();
    }
    
    return layer;
}

Layer* nextAction();
Layer* backAction();
Layer* restartAction();

Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % TEST_CASE_COUNT;
    
    return createTest(sceneIdx);
}

Layer* backAction()
{
    sceneIdx--;
    if( sceneIdx < 0 )
        sceneIdx = TEST_CASE_COUNT -1;
    
    return createTest(sceneIdx);
}

Layer* restartAction()
{
    return createTest(sceneIdx);
}

}

void EventDispatcherTestScene::runThisTest()
{
    auto layer = nextAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}


void EventDispatcherTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void EventDispatcherTestDemo::backCallback(Object* sender)
{
    auto scene = new EventDispatcherTestScene();
    auto layer = backAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void EventDispatcherTestDemo::nextCallback(Object* sender)
{
    auto scene = new EventDispatcherTestScene();
    auto layer = nextAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void EventDispatcherTestDemo::restartCallback(Object* sender)
{
    auto scene = new EventDispatcherTestScene();
    auto layer = restartAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

string EventDispatcherTestDemo::title()
{
    return "No title";
}

string EventDispatcherTestDemo::subtitle()
{
    return "";
}

// TouchableSpriteTest
void TouchableSpriteTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();

    auto dispatcher = EventDispatcher::getInstance();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Point(size.width/2, size.height/2) + Point(-80, 80));
    addChild(sprite1, 10);
    
    auto sprite2 = Sprite::create("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = Sprite::create("Images/YellowSquare.png");
    sprite3->setPosition(Point(0, 0));
    sprite2->addChild(sprite3, 1);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
        if (target == sprite2)
        {
            sprite1->setZOrder(100);
        }
        else if(target == sprite1)
        {
            sprite1->setZOrder(0);
        }
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    dispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    dispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    

    auto removeAllTouchItem = MenuItemFont::create("Remove All Touch Listeners", [this](Object* sender){
        auto senderItem = static_cast<MenuItemFont*>(sender);
        senderItem->setString("Only Next item could be clicked");
        
        EventDispatcher::getInstance()->removeListenersForEventType(EventTouch::EVENT_TYPE);
        
        auto nextItem = MenuItemFont::create("Next", [=](Object* sender){
            nextCallback(nullptr);
        });
        
        nextItem->setFontSizeObj(16);
        nextItem->setPosition(VisibleRect::right() + Point(-100, -30));
        
        auto menu2 = Menu::create(nextItem, NULL);
        menu2->setPosition(Point(0, 0));
        menu2->setAnchorPoint(Point(0, 0));
        this->addChild(menu2);
    });
    
    removeAllTouchItem->setFontSizeObj(16);
    removeAllTouchItem->setPosition(VisibleRect::right() + Point(-100, 0));
    
    auto menu = Menu::create(removeAllTouchItem, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setAnchorPoint(Point(0, 0));
    addChild(menu);
}

std::string TouchableSpriteTest::title()
{
    return "Touchable Sprite Test";
}

std::string TouchableSpriteTest::subtitle()
{
    return "Please drag the blocks";
}

// FixedPriorityChangedTest

class TouchableSpriteWithFixedPriority : public Sprite
{
public:
    TouchableSpriteWithFixedPriority()
    : _listener(nullptr)
    , _fixedPriority(0)
    , _useNodePriority(false)
    {
    }
    
    void setPriority(int fixedPriority) { _fixedPriority = fixedPriority; _useNodePriority = false; };
    void setPriorityWithThis(bool useNodePriority) { _useNodePriority = useNodePriority; _fixedPriority = true; }
    
    void onEnter() override
    {
        Sprite::onEnter();
        
        auto dispatcher = EventDispatcher::getInstance();
        
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [=](Touch* touch, Event* event){
            
            Point locationInNode = this->convertToNodeSpace(touch->getLocation());
            Size s = this->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            if (rect.containsPoint(locationInNode))
            {
                this->setColor(Color3B::RED);
                return true;
            }
            return false;
        };
        
        listener->onTouchMoved = [=](Touch* touch, Event* event){
            //this->setPosition(this->getPosition() + touch->getDelta());
        };
        
        listener->onTouchEnded = [=](Touch* touch, Event* event){
            this->setColor(Color3B::WHITE);
        };
        
        if (_useNodePriority)
        {
            dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        }
        else
        {
            dispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
        }
        _listener = listener;
    }
    
    void onExit() override
    {
        auto dispatcher = EventDispatcher::getInstance();
        dispatcher->removeEventListener(_listener);
        
        Sprite::onExit();
    }

private:
    EventListener* _listener;
    int _fixedPriority;
    bool _useNodePriority;
};

void FixedPriorityTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = new TouchableSpriteWithFixedPriority();
    sprite1->initWithFile("Images/CyanSquare.png");
    sprite1->autorelease();
    sprite1->setPriority(30);
    sprite1->setPosition(origin+Point(size.width/2, size.height/2) + Point(-80, 40));
    addChild(sprite1, 10);
    
    auto sprite2 = new TouchableSpriteWithFixedPriority();
    sprite2->initWithFile("Images/MagentaSquare.png");
    sprite2->autorelease();
    sprite2->setPriority(20);
    sprite2->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = new TouchableSpriteWithFixedPriority();
    sprite3->initWithFile("Images/YellowSquare.png");
    sprite3->autorelease();
    sprite3->setPriority(10);
    sprite3->setPosition(Point(0, 0));
    sprite2->addChild(sprite3, 1);

}

std::string FixedPriorityTest::title()
{
    return "Fixed priority test";
}

std::string FixedPriorityTest::subtitle()
{
    return "Fixed Priority, Blue: 30, Red: 20, Yellow: 10\n The lower value the higher priority will be.";
}

// RemoveListenerWhenDispatching
void RemoveListenerWhenDispatching::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    auto dispatcher = EventDispatcher::getInstance();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite1, 10);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener1->setSwallowTouches(true);
    setUserObject(listener1);
    
    std::shared_ptr<bool> firstClick(new bool(true));
    
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        Point locationInNode = sprite1->convertToNodeSpace(touch->getLocation());
        Size s = sprite1->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            sprite1->setColor(Color3B::RED);
            return true;
        }
        return false;
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        sprite1->setColor(Color3B::WHITE);
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    
    auto statusLabel = LabelTTF::create("The sprite could be touched!", "", 20);
    statusLabel->setPosition(origin + Point(size.width/2, size.height-90));
    addChild(statusLabel);
    std::shared_ptr<bool> enable(new bool(true));
    // Enable/Disable item
    auto toggleItem = MenuItemToggle::createWithCallback([=](Object* sender){
        if (*enable)
        {
            dispatcher->removeEventListener(listener1);
            statusLabel->setString("The sprite could not be touched!");
            
            (*enable) = false;
        }
        else
        {
            dispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
            statusLabel->setString("The sprite could be touched!");

            (*enable) = true;
        }
    }, MenuItemFont::create("Enabled"), MenuItemFont::create("Disabled"), NULL);
    
    toggleItem->setPosition(origin + Point(size.width/2, 80));
    auto menu = Menu::create(toggleItem, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setAnchorPoint(Point(0, 0));
    addChild(menu, -1);
}

std::string RemoveListenerWhenDispatching::title()
{
    return "Add and remove listener\n when dispatching event";
}

std::string RemoveListenerWhenDispatching::subtitle()
{
    return "";
}

// CustomEventTest
void CustomEventTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    auto dispatcher = EventDispatcher::getInstance();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto statusLabel = LabelTTF::create("No custom event received!", "", 20);
    statusLabel->setPosition(origin + Point(size.width/2, size.height-90));
    addChild(statusLabel);

    _listener = EventListenerCustom::create("game_custom_event", [=](EventCustom* event){
        std::string str("Custom event received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel->setString(str.c_str());
        delete[] buf;
    });
    
    dispatcher->addEventListenerWithFixedPriority(_listener, 1);
    
    auto sendItem = MenuItemFont::create("Send Custom Event", [=](Object* sender){
        static int count = 0;
        ++count;
        char* buf = new char[10];
        sprintf(buf, "%d", count);
        EventCustom event("game_custom_event");
        event.setUserData(buf);
        dispatcher->dispatchEvent(&event);
    });
    sendItem->setPosition(origin + Point(size.width/2, size.height/2));
    auto menu = Menu::create(sendItem, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setAnchorPoint(Point(0, 0));
    addChild(menu, -1);
}

void CustomEventTest::onExit()
{
    EventDispatcher::getInstance()->removeEventListener(_listener);
    EventDispatcherTestDemo::onExit();
}

std::string CustomEventTest::title()
{
    return "Send custom event";
}

std::string CustomEventTest::subtitle()
{
    return "";
}

// LabelKeyboardEventTest
void LabelKeyboardEventTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    auto dispatcher = EventDispatcher::getInstance();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto statusLabel = LabelTTF::create("No keyboard event received!", "", 20);
    statusLabel->setPosition(origin + Point(size.width/2, size.height/2));
    addChild(statusLabel);
        
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){
        char buf[100] = {0};
        sprintf(buf, "Key %d was pressed!", (int)keyCode);
        auto label = static_cast<LabelTTF*>(event->getCurrentTarget());
        label->setString(buf);
    };
    
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
        char buf[100] = {0};
        sprintf(buf, "Key %d was released!", (int)keyCode);
        auto label = static_cast<LabelTTF*>(event->getCurrentTarget());
        label->setString(buf);
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, statusLabel);
}

std::string LabelKeyboardEventTest::title()
{
    return "Label Receives Keyboard Event";
}

std::string LabelKeyboardEventTest::subtitle()
{
    return "Please click keyboard\n(Only available on Desktop and Android)";
}

// SpriteAccelerationEventTest
void SpriteAccelerationEventTest::onEnter()
{
#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
_pos = _min;        \
else if (_pos > _max)   \
_pos = _max;        \

    EventDispatcherTestDemo::onEnter();
    
    auto dispatcher = EventDispatcher::getInstance();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    Device::setAccelerometerEnabled(true);
    
    auto sprite = Sprite::create(s_Ball);
    sprite->setPosition(origin + Point(size.width/2, size.height/2));
    addChild(sprite);
    
    auto listener = EventListenerAcceleration::create([=](Acceleration* acc, Event* event){
        auto ballSize  = sprite->getContentSize();
        
        auto ptNow  = sprite->getPosition();
        
        log("acc: x = %lf, y = %lf", acc->x, acc->y);
        
        ptNow.x += acc->x * 9.81f;
        ptNow.y += acc->y * 9.81f;
        
        FIX_POS(ptNow.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
        FIX_POS(ptNow.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
        sprite->setPosition(ptNow);
    });
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
}

void SpriteAccelerationEventTest::onExit()
{
    Device::setAccelerometerEnabled(false);
    EventDispatcherTestDemo::onExit();
}

std::string SpriteAccelerationEventTest::title()
{
    return "Sprite Receives Acceleration Event";
}

std::string SpriteAccelerationEventTest::subtitle()
{
    return "Please move your device\n(Only available on mobile)";
}