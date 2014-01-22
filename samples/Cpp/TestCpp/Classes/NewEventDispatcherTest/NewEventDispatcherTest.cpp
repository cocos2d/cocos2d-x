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
    CL(SpriteAccelerationEventTest),
    CL(RemoveAndRetainNodeTest),
    CL(RemoveListenerAfterAddingTest),
    CL(DirectorEventTest),
    CL(GlobalZTouchTest),
};

unsigned int TEST_CASE_COUNT = sizeof(createFunctions) / sizeof(createFunctions[0]);

int sceneIdx=-1;
Layer* createTest(int index)
{
    auto layer = (createFunctions[index])();;    
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

std::string EventDispatcherTestDemo::title() const
{
    return "No title";
}

std::string EventDispatcherTestDemo::subtitle() const
{
    return "";
}

// TouchableSpriteTest
void TouchableSpriteTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();

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
    auto listener1 = EventListenerTouchOneByOne::create();
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
            sprite1->setLocalZOrder(100);
        }
        else if(target == sprite1)
        {
            sprite1->setLocalZOrder(0);
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    

    auto removeAllTouchItem = MenuItemFont::create("Remove All Touch Listeners", [this](Object* sender){
        auto senderItem = static_cast<MenuItemFont*>(sender);
        senderItem->setString("Only Next item could be clicked");
        
        _eventDispatcher->removeEventListeners(EventListener::Type::TOUCH_ONE_BY_ONE);
        
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

std::string TouchableSpriteTest::title() const
{
    return "Touchable Sprite Test";
}

std::string TouchableSpriteTest::subtitle() const
{
    return "Please drag the blocks";
}

// FixedPriorityChangedTest

class TouchableSpriteWithFixedPriority : public Sprite
{
public:

    CREATE_FUNC(TouchableSpriteWithFixedPriority);
    
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
        
        auto listener = EventListenerTouchOneByOne::create();
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
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        }
        else
        {
            _eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
        }
        _listener = listener;
    }
    
    void onExit() override
    {
        _eventDispatcher->removeEventListener(_listener);
        
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
    
    auto sprite1 = TouchableSpriteWithFixedPriority::create();
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPriority(30);
    sprite1->setPosition(origin+Point(size.width/2, size.height/2) + Point(-80, 40));
    addChild(sprite1, 10);
    
    auto sprite2 = TouchableSpriteWithFixedPriority::create();
    sprite2->setTexture("Images/MagentaSquare.png");
    sprite2->setPriority(20);
    sprite2->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = TouchableSpriteWithFixedPriority::create();
    sprite3->setTexture("Images/YellowSquare.png");
    sprite3->setPriority(10);
    sprite3->setPosition(Point(0, 0));
    sprite2->addChild(sprite3, 1);

}

std::string FixedPriorityTest::title() const
{
    return "Fixed priority test";
}

std::string FixedPriorityTest::subtitle() const
{
    return "Fixed Priority, Blue: 30, Red: 20, Yellow: 10\n The lower value the higher priority will be.";
}

// RemoveListenerWhenDispatching
void RemoveListenerWhenDispatching::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite1, 10);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
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
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    
    auto statusLabel = LabelTTF::create("The sprite could be touched!", "", 20);
    statusLabel->setPosition(origin + Point(size.width/2, size.height-90));
    addChild(statusLabel);
    std::shared_ptr<bool> enable(new bool(true));
    // Enable/Disable item
    auto toggleItem = MenuItemToggle::createWithCallback([=](Object* sender){
        if (*enable)
        {
            _eventDispatcher->removeEventListener(listener1);
            statusLabel->setString("The sprite could not be touched!");
            
            (*enable) = false;
        }
        else
        {
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
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

std::string RemoveListenerWhenDispatching::title() const
{
    return "Add and remove listener\n when dispatching event";
}

std::string RemoveListenerWhenDispatching::subtitle() const
{
    return "";
}

// CustomEventTest
void CustomEventTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    MenuItemFont::setFontSize(20);
    
    auto statusLabel = LabelTTF::create("No custom event 1 received!", "", 20);
    statusLabel->setPosition(origin + Point(size.width/2, size.height-90));
    addChild(statusLabel);

    _listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string str("Custom event 1 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel->setString(str.c_str());
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
    
    auto sendItem = MenuItemFont::create("Send Custom Event 1", [=](Object* sender){
        static int count = 0;
        ++count;
        char* buf = new char[10];
        sprintf(buf, "%d", count);
        EventCustom event("game_custom_event1");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
        CC_SAFE_DELETE_ARRAY(buf);
    });
    sendItem->setPosition(origin + Point(size.width/2, size.height/2));
    
    auto statusLabel2 = LabelTTF::create("No custom event 2 received!", "", 20);
    statusLabel2->setPosition(origin + Point(size.width/2, size.height-120));
    addChild(statusLabel2);
    
    _listener2 = EventListenerCustom::create("game_custom_event2", [=](EventCustom* event){
        std::string str("Custom event 2 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel2->setString(str.c_str());
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(_listener2, 1);
    
    auto sendItem2 = MenuItemFont::create("Send Custom Event 2", [=](Object* sender){
        static int count = 0;
        ++count;
        char* buf = new char[10];
        sprintf(buf, "%d", count);
        EventCustom event("game_custom_event2");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
        CC_SAFE_DELETE_ARRAY(buf);
    });
    sendItem2->setPosition(origin + Point(size.width/2, size.height/2 - 40));
    
    auto menu = Menu::create(sendItem, sendItem2, nullptr);
    menu->setPosition(Point(0, 0));
    menu->setAnchorPoint(Point(0, 0));
    addChild(menu, -1);
}

void CustomEventTest::onExit()
{
    _eventDispatcher->removeEventListener(_listener);
    _eventDispatcher->removeEventListener(_listener2);
    EventDispatcherTestDemo::onExit();
}

std::string CustomEventTest::title() const
{
    return "Send custom event";
}

std::string CustomEventTest::subtitle() const
{
    return "";
}

// LabelKeyboardEventTest
void LabelKeyboardEventTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
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
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, statusLabel);
}

std::string LabelKeyboardEventTest::title() const
{
    return "Label Receives Keyboard Event";
}

std::string LabelKeyboardEventTest::subtitle() const
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
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
}

void SpriteAccelerationEventTest::onExit()
{
    Device::setAccelerometerEnabled(false);
    EventDispatcherTestDemo::onExit();
}

std::string SpriteAccelerationEventTest::title() const
{
    return "Sprite Receives Acceleration Event";
}

std::string SpriteAccelerationEventTest::subtitle() const
{
    return "Please move your device\n(Only available on mobile)";
}

// RemoveAndRetainNodeTest
void RemoveAndRetainNodeTest::onEnter()
{
    _spriteSaved = false;
    
    EventDispatcherTestDemo::onEnter();
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    _sprite = Sprite::create("Images/CyanSquare.png");
    _sprite->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(_sprite, 10);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
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
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _sprite);
    
    this->runAction(Sequence::create(DelayTime::create(5.0f),
                                     CallFunc::create([this](){
                                        _spriteSaved = true;
                                        _sprite->retain();
                                        _sprite->removeFromParent();
                                     }),
                                     DelayTime::create(5.0f),
                                     CallFunc::create([this](){
                                        _spriteSaved = false;
                                        this->addChild(_sprite);
                                        _sprite->release();
                                     }),
                                     nullptr
                                     ));
}

void RemoveAndRetainNodeTest::onExit()
{
    EventDispatcherTestDemo::onExit();
    if (_spriteSaved)
    {
        _sprite->release();
    }
}

std::string RemoveAndRetainNodeTest::title() const
{
    return "RemoveAndRetainNodeTest";
}

std::string RemoveAndRetainNodeTest::subtitle() const
{
    return "Sprite should be removed after 5s, add to scene again after 5s";
}

//RemoveListenerAfterAddingTest
void RemoveListenerAfterAddingTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();

    auto item1 = MenuItemFont::create("Click Me 1", [this](Object* sender){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCASSERT(false, "Should not come here!");
            return true;
        };
        
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
        _eventDispatcher->removeEventListener(listener);
    });

    item1->setPosition(VisibleRect::center() + Point(0, 80));
    
    auto addNextButton = [this](){
        auto next = MenuItemFont::create("Please Click Me To Reset!", [this](Object* sender){
            this->restartCallback(nullptr);
        });
        next->setPosition(VisibleRect::center() + Point(0, -40));
        
        auto menu = Menu::create(next, nullptr);
        menu->setPosition(VisibleRect::leftBottom());
        menu->setAnchorPoint(Point::ZERO);
        this->addChild(menu);
    };
    
    auto item2 = MenuItemFont::create("Click Me 2", [=](Object* sender){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCASSERT(false, "Should not come here!");
            return true;
        };
        
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
        _eventDispatcher->removeEventListeners(EventListener::Type::TOUCH_ONE_BY_ONE);
        
        addNextButton();
    });
    
    item2->setPosition(VisibleRect::center() + Point(0, 40));
    
    auto item3 = MenuItemFont::create("Click Me 3", [=](Object* sender){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCASSERT(false, "Should not come here!");
            return true;
        };
        
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
        _eventDispatcher->removeAllEventListeners();
        
        addNextButton();
    });
    
    item3->setPosition(VisibleRect::center());
    
    auto menu = Menu::create(item1, item2, item3, nullptr);
    menu->setPosition(VisibleRect::leftBottom());
    menu->setAnchorPoint(Point::ZERO);

    addChild(menu);
}

void RemoveListenerAfterAddingTest::onExit()
{
    EventDispatcherTestDemo::onExit();
}

std::string RemoveListenerAfterAddingTest::title() const
{
    return "RemoveListenerAfterAddingTest";
}

std::string RemoveListenerAfterAddingTest::subtitle() const
{
    return "Should not crash!";
}


//
//DirectorEventTest
//
DirectorEventTest::DirectorEventTest()
:_count1(0)
,_count2(0)
,_count3(0)
,_count4(0)
{

}

void DirectorEventTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();

    Size s = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 20);

    _label1 = Label::createWithTTF(ttfConfig, "Update: 0");
    _label1->setPosition(30,s.height/2 + 60);
    this->addChild(_label1);

    _label2 = Label::createWithTTF(ttfConfig, "Visit: 0");
    _label2->setPosition(30,s.height/2 + 20);
    this->addChild(_label2);

    _label3 = Label::createWithTTF(ttfConfig, "Draw: 0");
    _label3->setPosition(30,30);
    _label3->setPosition(30,s.height/2 - 20);
    this->addChild(_label3);

    _label4 = Label::createWithTTF(ttfConfig, "Projection: 0");
    _label4->setPosition(30,30);
    _label4->setPosition(30,s.height/2 - 60);
    this->addChild(_label4);

    auto dispatcher = Director::getInstance()->getEventDispatcher();

    _event1 = dispatcher->addCustomEventListener(Director::EVENT_AFTER_UPDATE, std::bind(&DirectorEventTest::onEvent1, this, std::placeholders::_1));
    _event2 = dispatcher->addCustomEventListener(Director::EVENT_AFTER_VISIT, std::bind(&DirectorEventTest::onEvent2, this, std::placeholders::_1));
    _event3 = dispatcher->addCustomEventListener(Director::EVENT_AFTER_DRAW, [&](EventCustom *event) {
        char buf[20];
        snprintf(buf, sizeof(buf)-1, "Draw: %d", _count3++);
        _label3->setString(buf);
    });
    _event4 = dispatcher->addCustomEventListener(Director::EVENT_PROJECTION_CHANGED, [&](EventCustom *event) {
        char buf[20];
        snprintf(buf, sizeof(buf)-1, "Projection: %d", _count4++);
        _label4->setString(buf);
    });

    _event1->retain();
    _event2->retain();
    _event3->retain();
    _event4->retain();

    scheduleUpdate();
}

void DirectorEventTest::update(float dt)
{
    static float time = 0;

    time += dt;
    if(time > 0.5) {
        Director::getInstance()->setProjection(Director::Projection::_2D);
        time = 0;
    }
}

void DirectorEventTest::onExit()
{
    EventDispatcherTestDemo::onExit();

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(_event1);
    dispatcher->removeEventListener(_event2);
    dispatcher->removeEventListener(_event3);
    dispatcher->removeEventListener(_event4);

    _event1->release();
    _event2->release();
    _event3->release();
    _event4->release();
}

void DirectorEventTest::onEvent1(EventCustom *event)
{
    char buf[20];
    snprintf(buf, sizeof(buf)-1, "Update: %d", _count1++);
    _label1->setString(buf);
}

void DirectorEventTest::onEvent2(EventCustom *event)
{
    char buf[20];
    snprintf(buf, sizeof(buf)-1, "Visit: %d", _count2++);
    _label2->setString(buf);
}


std::string DirectorEventTest::title() const
{
    return "Testing Director Events";
}

std::string DirectorEventTest::subtitle() const
{
    return "after visit, after draw, after update, projection changed";
}

// GlobalZTouchTest
GlobalZTouchTest::GlobalZTouchTest()
: _sprite(nullptr)
, _accum(0)
{
    
    auto listener1 = EventListenerTouchOneByOne::create();
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
    };
    
    const int SPRITE_COUNT = 8;
    
    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        Sprite *sprite;
        auto parent = Node::create();
        if(i==4)
        {
            sprite = Sprite::create("Images/CyanSquare.png");
            _sprite = sprite;
            _sprite->setGlobalZOrder(-1);
        }
        else
        {
            sprite = Sprite::create("Images/YellowSquare.png");
        }
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite);
        
        parent->addChild(sprite);
        this->addChild(parent);
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        sprite->setPosition(VisibleRect::left().x + visibleSize.width / (SPRITE_COUNT - 1) * i, VisibleRect::center().y);
    }
    
    this->scheduleUpdate();
}

void GlobalZTouchTest::update(float dt)
{
    _accum += dt;
    if( _accum > 2.0f) {
        float z = _sprite->getGlobalZOrder();
        _sprite->setGlobalZOrder(-z);
        _accum = 0;
    }
}

std::string GlobalZTouchTest::title() const
{
    return "Global Z Value, Try touch blue sprite";
}

std::string GlobalZTouchTest::subtitle() const
{
    return "Blue Sprite should change go from foreground to background";
}

