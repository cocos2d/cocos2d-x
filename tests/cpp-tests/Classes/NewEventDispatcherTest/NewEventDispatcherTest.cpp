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
//  NewEventDispatcherTest.cpp
//  samples
//
//  Created by James Chen on 9/13/13.
//
//

#include "NewEventDispatcherTest.h"
#include "testResource.h"

USING_NS_CC;

EventDispatcherTests::EventDispatcherTests()
{
    ADD_TEST_CASE(TouchableSpriteTest);
    ADD_TEST_CASE(FixedPriorityTest);
    ADD_TEST_CASE(RemoveListenerWhenDispatching);
    ADD_TEST_CASE(CustomEventTest);
    ADD_TEST_CASE(LabelKeyboardEventTest);
    ADD_TEST_CASE(SpriteAccelerationEventTest);
    ADD_TEST_CASE(RemoveAndRetainNodeTest);
    ADD_TEST_CASE(RemoveListenerAfterAddingTest);
    ADD_TEST_CASE(DirectorEventTest);
    ADD_TEST_CASE(GlobalZTouchTest);
    ADD_TEST_CASE(StopPropagationTest);
    ADD_TEST_CASE(PauseResumeTargetTest);
    ADD_TEST_CASE(PauseResumeTargetTest2);
    ADD_TEST_CASE(PauseResumeTargetTest3);
    ADD_TEST_CASE(Issue4129);
    ADD_TEST_CASE(Issue4160);
    ADD_TEST_CASE(DanglingNodePointersTest);
    ADD_TEST_CASE(RegisterAndUnregisterWhileEventHanldingTest);
    ADD_TEST_CASE(WindowEventsTest);
    ADD_TEST_CASE(Issue8194);
    ADD_TEST_CASE(Issue9898)
}

std::string EventDispatcherTestDemo::title() const
{
    return "No title";
}

// TouchableSpriteTest
void TouchableSpriteTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto containerForSprite1 = Node::create();
    auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 80));
    containerForSprite1->addChild(sprite1);
    addChild(containerForSprite1, 10);
    
    auto sprite2 = Sprite::create("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = Sprite::create("Images/YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, 1);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
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
            containerForSprite1->setLocalZOrder(100);
        }
        else if(target == sprite1)
        {
            containerForSprite1->setLocalZOrder(0);
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    

    auto removeAllTouchItem = MenuItemFont::create("Remove All Touch Listeners", [this](Ref* sender){
        auto senderItem = static_cast<MenuItemFont*>(sender);
        senderItem->setString("Only Next item could be clicked");
        
        _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
        
        auto nextItem = MenuItemFont::create("Next", [=](Ref* sender){
            getTestSuite()->enterNextTest();
        });
        
        nextItem->setFontSizeObj(16);
        nextItem->setPosition(VisibleRect::right() + Vec2(-100, -30));
        
        auto menu2 = Menu::create(nextItem, nullptr);
        menu2->setPosition(Vec2(0, 0));
        menu2->setAnchorPoint(Vec2(0, 0));
        this->addChild(menu2);
    });
    
    removeAllTouchItem->setFontSizeObj(16);
    removeAllTouchItem->setPosition(VisibleRect::right() + Vec2(-100, 0));
    
    auto menu = Menu::create(removeAllTouchItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    menu->setAnchorPoint(Vec2(0, 0));
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

class TouchableSprite : public Sprite
{
public:
    static TouchableSprite* create(int priority = 0)
    {
        auto ret = new (std::nothrow) TouchableSprite(priority);
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

protected:
    TouchableSprite(int priority)
    : _listener(nullptr)
    , _fixedPriority(priority)
    , _removeListenerOnTouchEnded(false)
    {
    }

    virtual bool init() override
    {
        if (!Sprite::init())
            return false;

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [this](Touch* touch, Event* event){
            Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
            Size s = this->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            if (rect.containsPoint(locationInNode))
            {
                log("TouchableSprite: onTouchBegan ...");
                this->setColor(Color3B::RED);
                return true;
            }
            return false;
        };
        
        listener->onTouchEnded = [this](Touch* touch, Event* event){
            log("TouchableSprite: onTouchEnded ...");
            this->setColor(Color3B::WHITE);
            
            if (_removeListenerOnTouchEnded)
            {
                _eventDispatcher->removeEventListener(_listener);
                _listener = nullptr;
            }
        };
        
        if (_fixedPriority != 0)
        {
            _eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
        }
        else
        {
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        }

        _listener = listener;
        return true;
    }
    
    virtual void onExit() override
    {
        if (_listener != nullptr && _fixedPriority != 0)
        {
            _eventDispatcher->removeEventListener(_listener);
        }
        
        Sprite::onExit();
    }
public:
    void removeListenerOnTouchEnded(bool toRemove) { _removeListenerOnTouchEnded = toRemove; };
    
    inline EventListener* getListener() { return _listener; };
    
private:
    EventListener* _listener;
    int _fixedPriority;
    bool _removeListenerOnTouchEnded;
};

void FixedPriorityTest::onEnter()
{
    EventDispatcherTestDemo::onEnter();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = TouchableSprite::create(30);
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 40));
    addChild(sprite1, 10);
    
    auto sprite2 = TouchableSprite::create(20);
    sprite2->setTexture("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = TouchableSprite::create(10);
    sprite3->setTexture("Images/YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
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
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite1, 10);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    setUserObject(listener1);
    
    std::shared_ptr<bool> firstClick(new bool(true));
    
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        Vec2 locationInNode = sprite1->convertToNodeSpace(touch->getLocation());
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
    
    auto statusLabel = Label::createWithSystemFont("The sprite could be touched!", "", 20);
    statusLabel->setPosition(origin + Vec2(size.width/2, size.height-90));
    addChild(statusLabel);
    std::shared_ptr<bool> enable(new bool(true));
    // Enable/Disable item
    auto toggleItem = MenuItemToggle::createWithCallback([=](Ref* sender){
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
    }, MenuItemFont::create("Enabled"), MenuItemFont::create("Disabled"), nullptr);
    
    toggleItem->setPosition(origin + Vec2(size.width/2, 80));
    auto menu = Menu::create(toggleItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    menu->setAnchorPoint(Vec2(0, 0));
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
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    MenuItemFont::setFontSize(20);
    
    auto statusLabel = Label::createWithSystemFont("No custom event 1 received!", "", 20);
    statusLabel->setPosition(origin + Vec2(size.width/2, size.height-90));
    addChild(statusLabel);

    _listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string str("Custom event 1 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel->setString(str.c_str());
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
    
    auto sendItem = MenuItemFont::create("Send Custom Event 1", [=](Ref* sender){
        static int count = 0;
        ++count;
        char* buf = new char[10];
        sprintf(buf, "%d", count);
        EventCustom event("game_custom_event1");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
        CC_SAFE_DELETE_ARRAY(buf);
    });
    sendItem->setPosition(origin + Vec2(size.width/2, size.height/2));
    
    auto statusLabel2 = Label::createWithSystemFont("No custom event 2 received!", "", 20);
    statusLabel2->setPosition(origin + Vec2(size.width/2, size.height-120));
    addChild(statusLabel2);
    
    _listener2 = EventListenerCustom::create("game_custom_event2", [=](EventCustom* event){
        std::string str("Custom event 2 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel2->setString(str.c_str());
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(_listener2, 1);
    
    auto sendItem2 = MenuItemFont::create("Send Custom Event 2", [=](Ref* sender){
        static int count = 0;
        ++count;
        char* buf = new char[10];
        sprintf(buf, "%d", count);
        EventCustom event("game_custom_event2");
        event.setUserData(buf);
        _eventDispatcher->dispatchEvent(&event);
        CC_SAFE_DELETE_ARRAY(buf);
    });
    sendItem2->setPosition(origin + Vec2(size.width/2, size.height/2 - 40));
    
    auto menu = Menu::create(sendItem, sendItem2, nullptr);
    menu->setPosition(Vec2(0, 0));
    menu->setAnchorPoint(Vec2(0, 0));
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
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto statusLabel = Label::createWithSystemFont("No keyboard event received!", "", 20);
    statusLabel->setPosition(origin + Vec2(size.width/2, size.height/2));
    addChild(statusLabel);
        
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){
        char buf[100] = {0};
        sprintf(buf, "Key %d was pressed!", (int)keyCode);
        auto label = static_cast<Label*>(event->getCurrentTarget());
        label->setString(buf);
    };
    
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
        char buf[100] = {0};
        sprintf(buf, "Key %d was released!", (int)keyCode);
        auto label = static_cast<Label*>(event->getCurrentTarget());
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
    return "Please click keyboard\n(Only available on Desktop, Android\nand Windows Universal Apps)";
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
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    Device::setAccelerometerEnabled(true);
    
    auto sprite = Sprite::create(s_Ball);
    sprite->setPosition(origin + Vec2(size.width/2, size.height/2));
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
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    _sprite = Sprite::create("Images/CyanSquare.png");
    _sprite->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(_sprite, 10);
    
    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
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
                                        _sprite->removeFromParentAndCleanup(false);
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

    auto item1 = MenuItemFont::create("Click Me 1", [this](Ref* sender){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCASSERT(false, "Should not come here!");
            return true;
        };
        
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
        _eventDispatcher->removeEventListener(listener);
    });

    item1->setPosition(VisibleRect::center() + Vec2(0, 80));
    
    auto addNextButton = [this](){
        auto next = MenuItemFont::create("Please Click Me To Reset!", [this](Ref* sender){
            getTestSuite()->restartCurrTest();
        });
        next->setPosition(VisibleRect::center() + Vec2(0, -40));
        
        auto menu = Menu::create(next, nullptr);
        menu->setPosition(VisibleRect::leftBottom());
        menu->setAnchorPoint(Vec2::ZERO);
        this->addChild(menu);
    };
    
    auto item2 = MenuItemFont::create("Click Me 2", [=](Ref* sender){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch* touch, Event* event) -> bool{
            CCASSERT(false, "Should not come here!");
            return true;
        };
        
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -1);
        _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
        
        addNextButton();
    });
    
    item2->setPosition(VisibleRect::center() + Vec2(0, 40));
    
    auto item3 = MenuItemFont::create("Click Me 3", [=](Ref* sender){
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
    menu->setAnchorPoint(Vec2::ZERO);

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
    _label1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _label1->setPosition(30,s.height/2 + 60);
    this->addChild(_label1);

    _label2 = Label::createWithTTF(ttfConfig, "Visit: 0");
    _label2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _label2->setPosition(30,s.height/2 + 20);
    this->addChild(_label2);

    _label3 = Label::createWithTTF(ttfConfig, "Draw: 0");
    _label3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _label3->setPosition(30,30);
    _label3->setPosition(30,s.height/2 - 20);
    this->addChild(_label3);

    _label4 = Label::createWithTTF(ttfConfig, "Projection: 0");
    _label4->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
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

    Director::getInstance()->setProjection(Director::Projection::DEFAULT);

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
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
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
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
    };
    
    const int SPRITE_COUNT = 8;
    
    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        Sprite *sprite;
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
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
        
        this->addChild(sprite);
        
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

StopPropagationTest::StopPropagationTest()
{
    static const int TAG_BLUE_SPRITE = 101;
    static const int TAG_BLUE_SPRITE2 = 102;

    auto touchOneByOneListener = EventListenerTouchOneByOne::create();
    touchOneByOneListener->setSwallowTouches(true);
    
    touchOneByOneListener->onTouchBegan = [=](Touch* touch, Event* event){
        // Skip if don't touch top half screen.
        if (!this->isPointInTopHalfAreaOfScreen(touch->getLocation()))
            return false;
        
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        CCASSERT(target->getTag() == TAG_BLUE_SPRITE, "Yellow blocks shouldn't response event.");
        
        if (this->isPointInNode(touch->getLocation(), target))
        {
            target->setOpacity(180);
            return true;
        }
        
        // Stop propagation, so yellow blocks will not be able to receive event.
        event->stopPropagation();
        return false;
    };
    
    touchOneByOneListener->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);
    };
    
    auto touchAllAtOnceListener = EventListenerTouchAllAtOnce::create();
    touchAllAtOnceListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
        // Skip if don't touch top half screen.
        if (this->isPointInTopHalfAreaOfScreen(touches[0]->getLocation()))
            return;
        
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        CCASSERT(target->getTag() == TAG_BLUE_SPRITE2, "Yellow blocks shouldn't response event.");
        
        if (this->isPointInNode(touches[0]->getLocation(), target))
        {
            target->setOpacity(180);
        }
        // Stop propagation, so yellow blocks will not be able to receive event.
        event->stopPropagation();
    };
    
    touchAllAtOnceListener->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
        // Skip if don't touch top half screen.
        if (this->isPointInTopHalfAreaOfScreen(touches[0]->getLocation()))
            return;
        
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        CCASSERT(target->getTag() == TAG_BLUE_SPRITE2, "Yellow blocks shouldn't response event.");
        
        if (this->isPointInNode(touches[0]->getLocation(), target))
        {
            target->setOpacity(255);
        }
        // Stop propagation, so yellow blocks will not be able to receive event.
        event->stopPropagation();
    };
    
    auto keyboardEventListener = EventListenerKeyboard::create();
    keyboardEventListener->onKeyPressed = [](EventKeyboard::KeyCode /*key*/, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        CCASSERT(target->getTag() == TAG_BLUE_SPRITE || target->getTag() == TAG_BLUE_SPRITE2, "Yellow blocks shouldn't response event.");
        // Stop propagation, so yellow blocks will not be able to receive event.
        event->stopPropagation();
    };
    
    const int SPRITE_COUNT = 8;
    
    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        Sprite* sprite;
        Sprite* sprite2;
        
        if(i==4)
        {
            sprite = Sprite::create("Images/CyanSquare.png");
            sprite->setTag(TAG_BLUE_SPRITE);
            addChild(sprite, 100);
            
            sprite2 = Sprite::create("Images/CyanSquare.png");
            sprite2->setTag(TAG_BLUE_SPRITE2);
            addChild(sprite2, 100);
        }
        else
        {
            sprite = Sprite::create("Images/YellowSquare.png");
            addChild(sprite, 0);
            sprite2 = Sprite::create("Images/YellowSquare.png");
            addChild(sprite2, 0);
        }
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchOneByOneListener->clone(), sprite);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener->clone(), sprite);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchAllAtOnceListener->clone(), sprite2);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener->clone(), sprite2);

        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        sprite->setPosition(VisibleRect::left().x + visibleSize.width / (SPRITE_COUNT - 1) * i, VisibleRect::center().y + sprite2->getContentSize().height/2 +10);
        sprite2->setPosition(VisibleRect::left().x + visibleSize.width / (SPRITE_COUNT - 1) * i, VisibleRect::center().y - sprite2->getContentSize().height/2-10);
    }
}

bool StopPropagationTest::isPointInNode(Vec2 pt, Node* node)
{
    Vec2 locationInNode = node->convertToNodeSpace(pt);
    Size s = node->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    return false;
}

bool StopPropagationTest::isPointInTopHalfAreaOfScreen(Vec2 pt)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    if (pt.y >= winSize.height/2) {
        return true;
    }
    
    return false;
}

std::string StopPropagationTest::title() const
{
    return "Stop Propagation Test";
}

std::string StopPropagationTest::subtitle() const
{
    return "Shouldn't crash and only blue block could be clicked";
}

// PauseResumeTargetTest
PauseResumeTargetTest::PauseResumeTargetTest()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = TouchableSprite::create();
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 40));
    addChild(sprite1, -10);
    
    auto sprite2 = TouchableSprite::create();
    sprite2->setTexture("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite2, -20);
    
    auto sprite3 = TouchableSprite::create(100); // Sprite3 uses fixed priority listener
    sprite3->setTexture("Images/YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, -1);
    
    auto popup = MenuItemFont::create("Popup", [=](Ref* sender){
        
        sprite3->getListener()->setEnabled(false);
        _eventDispatcher->pauseEventListenersForTarget(this, true);
        
        auto colorLayer = LayerColor::create(Color4B(0, 0, 255, 100));
        this->addChild(colorLayer, 99999);
        
        auto closeItem = MenuItemFont::create("close", [=](Ref* sender){
            colorLayer->removeFromParent();
            _eventDispatcher->resumeEventListenersForTarget(this, true);
            sprite3->getListener()->setEnabled(true);
        });
        
        closeItem->setPosition(VisibleRect::center());
        
        auto closeMenu = Menu::create(closeItem, nullptr);
        closeMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        closeMenu->setPosition(Vec2::ZERO);
        
        colorLayer->addChild(closeMenu);
    });
    
    popup->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    popup->setPosition(VisibleRect::right());
    
    auto menu = Menu::create(popup, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu);
}

PauseResumeTargetTest::~PauseResumeTargetTest()
{
}

std::string PauseResumeTargetTest::title() const
{
    return "PauseResumeTargetTest";
}

std::string PauseResumeTargetTest::subtitle() const
{
    return "Yellow block uses fixed priority";
}

// PauseResumeTargetTest2
PauseResumeTargetTest2::PauseResumeTargetTest2()
{
    MenuItemFont::getFontSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();

    _touchableSprite = TouchableSprite::create();
    _touchableSprite->retain();
    _touchableSprite->setTexture("Images/CyanSquare.png");
    _touchableSprite->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 40));
    addChild(_touchableSprite);

    _itemPauseTouch = MenuItemFont::create("pauseTouch", [=](Ref* sender){
        _itemPauseTouch->setEnabled(false);
        _itemResumeTouch->setEnabled(true);

        _eventDispatcher->pauseEventListenersForTarget(_touchableSprite);
    });

    _itemPauseTouch->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _itemPauseTouch->setPosition(VisibleRect::right() + Vec2(-150, 0));

    _itemResumeTouch = MenuItemFont::create("resumeTouch", [=](Ref* sender){
        _itemPauseTouch->setEnabled(true);
        _itemResumeTouch->setEnabled(false);

        _eventDispatcher->resumeEventListenersForTarget(_touchableSprite);
    });

    _itemResumeTouch->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _itemResumeTouch->setPosition(VisibleRect::right() + Vec2(0, 0));

    _itemAddToScene = MenuItemFont::create("addToScene", [=](Ref* sender){
        _itemAddToScene->setEnabled(false);
        _itemRemoveFromScene->setEnabled(true);

        this->addChild(_touchableSprite);
    });

    _itemAddToScene->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _itemAddToScene->setPosition(VisibleRect::right() + Vec2(-150, -50));

    _itemRemoveFromScene = MenuItemFont::create("removeFromScene", [=](Ref* sender){
        _itemAddToScene->setEnabled(true);
        _itemRemoveFromScene->setEnabled(false);
        _touchableSprite->removeFromParentAndCleanup(false);
    });

    _itemRemoveFromScene->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _itemRemoveFromScene->setPosition(VisibleRect::right() + Vec2(0, -50));

    _itemAddToScene->setEnabled(false);
    _itemResumeTouch->setEnabled(false);

    _itemPauseTouch->setFontSizeObj(20);
    _itemResumeTouch->setFontSizeObj(20);
    _itemAddToScene->setFontSizeObj(20);
    _itemRemoveFromScene->setFontSizeObj(20);

    auto menu = Menu::create(_itemPauseTouch, _itemResumeTouch, _itemAddToScene, _itemRemoveFromScene, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2::ZERO);

    addChild(menu);
}

PauseResumeTargetTest2::~PauseResumeTargetTest2()
{
    _touchableSprite->release();
}

std::string PauseResumeTargetTest2::title() const
{
    return "PauseResumeTargetTest2";
}

std::string PauseResumeTargetTest2::subtitle() const
{
    return "";
}

// PauseResumeTargetTest3
PauseResumeTargetTest3::PauseResumeTargetTest3()
{
    MenuItemFont::getFontSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();

    _touchableSprite = Sprite::create("Images/CyanSquare.png");
    _touchableSprite->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 40));
    addChild(_touchableSprite);

    auto item = MenuItemFont::create("addListener", [=](Ref* sender){

        MenuItemFont* senderItem = static_cast<MenuItemFont*>(sender);
        senderItem->setEnabled(false);

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [=](Touch* touch, Event* event){
            Vec2 locationInNode = _touchableSprite->convertToNodeSpace(touch->getLocation());
            Size s = _touchableSprite->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                log("TouchableSprite: onTouchBegan ...");
                _touchableSprite->setColor(Color3B::RED);
                return true;
            }
            return false;
        };

        listener->onTouchEnded = [this](Touch* touch, Event* event){
            log("TouchableSprite: onTouchEnded ...");
            _touchableSprite->setColor(Color3B::WHITE);
        };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _touchableSprite);
        _eventDispatcher->pauseEventListenersForTarget(_touchableSprite);
    });

    item->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    item->setPosition(VisibleRect::right());

    auto menu = Menu::create(item, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2::ZERO);

    addChild(menu);
}

PauseResumeTargetTest3::~PauseResumeTargetTest3()
{

}

std::string PauseResumeTargetTest3::title() const
{
    return "PauseResumeTargetTest3";
}

std::string PauseResumeTargetTest3::subtitle() const
{
    return "Sprite should not be touchable";
}

// Issue4129
Issue4129::Issue4129()
: _bugFixed(false)
{
    _customlistener = _eventDispatcher->addCustomEventListener(EVENT_COME_TO_BACKGROUND, [this](EventCustom* event){
        
        auto label = Label::createWithSystemFont("Yeah, this issue was fixed.", "", 20);
        label->setAnchorPoint(Vec2(0, 0.5f));
        label->setPosition(Vec2(VisibleRect::left() + Vec2(0, 30)));
        this->addChild(label);
        
        // After test, remove it.
        _eventDispatcher->removeEventListener(_customlistener);
        _customlistener = nullptr;

        _bugFixed = true;
    });

    auto removeAllTouchItem = MenuItemFont::create("Remove All Listeners", [this](Ref* sender){
        auto senderItem = static_cast<MenuItemFont*>(sender);
        senderItem->setString("Only 'Reset' item could be clicked");
        
        _eventDispatcher->removeAllEventListeners();
        
        auto nextItem = MenuItemFont::create("Reset", [=](Ref* sender){
            CCASSERT(_bugFixed, "This issue was not fixed!");
            getTestSuite()->restartCurrTest();
        });
        
        nextItem->setFontSizeObj(16);
        nextItem->setPosition(VisibleRect::right() + Vec2(-100, -30));
        
        auto menu2 = Menu::create(nextItem, nullptr);
        menu2->setPosition(Vec2(0, 0));
        menu2->setAnchorPoint(Vec2(0, 0));
        this->addChild(menu2);
        
        // Simulate to dispatch 'come to background' event
        _eventDispatcher->dispatchCustomEvent(EVENT_COME_TO_BACKGROUND);
    });
    
    removeAllTouchItem->setFontSizeObj(16);
    removeAllTouchItem->setPosition(VisibleRect::right() + Vec2(-100, 0));
    
    auto menu = Menu::create(removeAllTouchItem, nullptr);
    menu->setPosition(Vec2(0, 0));
    menu->setAnchorPoint(Vec2(0, 0));
    addChild(menu);
}

Issue4129::~Issue4129()
{
    if (_customlistener)
    {
        _eventDispatcher->removeEventListener(_customlistener);
    }
}

std::string Issue4129::title() const
{
    return "Issue 4129: Remove All Listeners";
}

std::string Issue4129::subtitle() const
{
    return "Should see 'Yeah, this issue was fixed.'";
}

// Issue4160
Issue4160::Issue4160()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto sprite1 = TouchableSprite::create(-30);
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 40));
    addChild(sprite1, -10);
    
    auto sprite2 = TouchableSprite::create(-20);
    sprite2->setTexture("Images/MagentaSquare.png");
    sprite2->removeListenerOnTouchEnded(true);
    sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite2, -20);
    
    auto sprite3 = TouchableSprite::create(-10);
    sprite3->setTexture("Images/YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, -1);
}

Issue4160::~Issue4160()
{
}

std::string Issue4160::title() const
{
    return "Issue 4160: Out of range exception";
}

std::string Issue4160::subtitle() const
{
    return "Touch the red block twice \n should not crash and the red one couldn't be touched";
}

// DanglingNodePointersTest
class DanglingNodePointersTestSprite : public Sprite
{
public:
    
    typedef std::function<void (DanglingNodePointersTestSprite * sprite)> TappedCallback;
    
    static DanglingNodePointersTestSprite * create(const TappedCallback & tappedCallback)
    {
        auto ret = new (std::nothrow) DanglingNodePointersTestSprite(tappedCallback);
        
        if (ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }

protected:
    
    DanglingNodePointersTestSprite(const TappedCallback & tappedCallback)
    :
        _eventListener(nullptr),
        _tappedCallback(tappedCallback)
    {
        
    }
    
public:
    
    void onEnter() override
    {
        Sprite::onEnter();
        
        _eventListener = EventListenerTouchOneByOne::create();
        _eventListener->setSwallowTouches(false);
        
        _eventListener->onTouchBegan = [this](Touch* touch, Event* event) -> bool
        {
            _tappedCallback(this);
            return false;           // Don't claim the touch so it can propagate
        };
        
        _eventListener->onTouchEnded = [](Touch* touch, Event* event)
        {
            // Do nothing
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListener, this);
    }
    
    void onExit() override
    {
        _eventDispatcher->removeEventListenersForTarget(this);
        _eventListener = nullptr;
        Sprite::onExit();
    }
    
private:    
    EventListenerTouchOneByOne* _eventListener;
    TappedCallback _tappedCallback;
};

DanglingNodePointersTest::DanglingNodePointersTest()
{
#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS == 1 && COCOS2D_DEBUG > 0
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto callback2 = [](DanglingNodePointersTestSprite * sprite2)
    {
        CCASSERT(false, "This should never be called because the sprite gets removed from it's parent and destroyed!");
        exit(1);
    };
    
    auto callback1 = [callback2, origin, size](DanglingNodePointersTestSprite * sprite1)
    {
        DanglingNodePointersTestSprite * sprite2 = dynamic_cast<DanglingNodePointersTestSprite*>(sprite1->getChildren().at(0));
        CCASSERT(sprite2, "The first child of sprite 1 should be sprite 2!");
        CCASSERT(sprite2->getReferenceCount() == 1, "There should only be 1 reference to sprite 1, from it's parent node. Hence removing it will destroy it!");
        sprite1->removeAllChildren();   // This call should cause sprite 2 to be destroyed
        
        // Recreate sprite 1 again
        sprite2 = DanglingNodePointersTestSprite::create(callback2);
        sprite2->setTexture("Images/MagentaSquare.png");
        sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
        sprite1->addChild(sprite2, -20);
    };
    
    auto sprite1 = DanglingNodePointersTestSprite::create(callback1);    // Sprite 1 will receive touch before sprite 2
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite1, -10);
    
    auto sprite2 = DanglingNodePointersTestSprite::create(callback2);   // Sprite 2 will be removed when sprite 1 is touched, should never receive an event.
    sprite2->setTexture("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
    sprite1->addChild(sprite2, -20);
    
#endif
}

DanglingNodePointersTest::~DanglingNodePointersTest()
{
    
}

std::string DanglingNodePointersTest::title() const
{
    return "DanglingNodePointersTest";
}

std::string DanglingNodePointersTest::subtitle() const
{
#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS == 1 && COCOS2D_DEBUG > 0
    return  "Tap the square - should not crash!";
#else
    return  "For test to work, must be compiled with:\n"
            "CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS == 1\n&& COCOS2D_DEBUG > 0";
#endif
}


RegisterAndUnregisterWhileEventHanldingTest::RegisterAndUnregisterWhileEventHanldingTest()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto callback1 = [=](DanglingNodePointersTestSprite * sprite)
    {
        auto callback2 = [](DanglingNodePointersTestSprite * sprite)
        {
            CCASSERT(false, "This should never get called!");
        };
        
        {
            AutoreleasePool pool;
            
            auto sprite2 = DanglingNodePointersTestSprite::create(callback2);
            sprite2->setTexture("Images/CyanSquare.png");
            sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
            
            addChild(sprite2, 0);
            removeChild(sprite2);
        }
    };
    
    auto sprite1 = DanglingNodePointersTestSprite::create(callback1);
    sprite1->setTexture("Images/CyanSquare.png");
    sprite1->setPosition(origin+Vec2(size.width/2, size.height/2));
    addChild(sprite1, -10);
}

std::string RegisterAndUnregisterWhileEventHanldingTest::title() const
{
    return "RegisterAndUnregisterWhileEventHanldingTest";
}

std::string RegisterAndUnregisterWhileEventHanldingTest::subtitle() const
{
    return  "Tap the square multiple times - should not crash!";
}

//
WindowEventsTest::WindowEventsTest()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener(GLViewImpl::EVENT_WINDOW_RESIZED, [](EventCustom* event) {
        // TODO: need to create resizeable window
        log("<<< WINDOW RESIZED! >>> ");
    });
    dispatcher->addCustomEventListener(GLViewImpl::EVENT_WINDOW_FOCUSED, [](EventCustom* event) {
        log("<<< WINDOW FOCUSED! >>> ");
    });
    dispatcher->addCustomEventListener(GLViewImpl::EVENT_WINDOW_UNFOCUSED, [](EventCustom* event) {
        log("<<< WINDOW BLURRED! >>> ");
    });
#endif
}

std::string WindowEventsTest::title() const
{
    return "WindowEventsTest";
}

std::string WindowEventsTest::subtitle() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return  "Resize and Switch to another window and back. Read Logs.";
#else
    return  "Unsupported platform.";
#endif
}


// https://github.com/cocos2d/cocos2d-x/issues/8194
Issue8194::Issue8194()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    static bool nodesAdded = false;
#define tagA 100
#define tagB 101
    // dispatch custom event in another custom event, make the custom event "Issue8194" take effect immediately
    _listener = getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_UPDATE, [this](cocos2d::EventCustom *event){
        if (nodesAdded)
        {
            // CCLOG("Fire Issue8194 Event");
            getEventDispatcher()->dispatchCustomEvent("Issue8194");
            
            // clear test nodes and listeners
            getEventDispatcher()->removeCustomEventListeners("Issue8194");
            removeChildByTag(tagA);
            removeChildByTag(tagB);
            nodesAdded = false;
        }
    });
    
    // When click this menuitem, it will add two node A and B, then send a custom event.
    // Because Node B's localZOrder < A's, the custom event should process by node B.
    auto menuItem = MenuItemFont::create("Dispatch Custom Event", [this](Ref *sender) {
        // add nodeA to scene
        auto nodeA = Node::create();
        addChild(nodeA, 1, tagA);
        
        cocos2d::EventListenerCustom* listenerA = cocos2d::EventListenerCustom::create("Issue8194", [&](cocos2d::EventCustom *event){
            _subtitleLabel->setString("Bug has been fixed.");
            event->stopPropagation();
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerA, nodeA);
       
        // add nodeB to scene
        auto nodeB = Node::create();
        addChild(nodeB, -1, tagB);
        
        cocos2d::EventListenerCustom* listenerB = cocos2d::EventListenerCustom::create("Issue8194", [&](cocos2d::EventCustom *event){
            _subtitleLabel->setString("Bug exist yet.");
            event->stopPropagation();
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerB, nodeB);
        
        nodesAdded = true;
    });
    
    menuItem->setPosition(origin.x + size.width/2, origin.y + size.height/2);
    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
}

Issue8194::~Issue8194()
{
    getEventDispatcher()->removeEventListener(_listener);
}

std::string Issue8194::title() const
{
    return "Issue 8194";
}

std::string Issue8194::subtitle() const
{
    return  "After click button, should show 'Bug has been fixed.'";
}

Issue9898::Issue9898()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();

    auto nodeA = Node::create();
    addChild(nodeA);

    _listener = cocos2d::EventListenerCustom::create("Issue9898", [&](cocos2d::EventCustom *event){
        _eventDispatcher->removeEventListener(_listener);
        _eventDispatcher->dispatchCustomEvent("Issue9898");
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, nodeA);

    auto menuItem = MenuItemFont::create("Dispatch Custom Event", [&](Ref *sender) {
        _eventDispatcher->dispatchCustomEvent("Issue9898");
    });
    menuItem->setPosition(origin.x + size.width/2, origin.y + size.height/2);
    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
}

std::string Issue9898::title() const
{
    return "Issue 9898";
}

std::string Issue9898::subtitle() const
{
    return  "Should not crash if dispatch event after remove\n event listener in callback";
}
