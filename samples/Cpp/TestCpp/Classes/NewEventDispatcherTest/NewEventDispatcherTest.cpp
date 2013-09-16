//
//  NewEventDispatcherTest.cpp
//  samples
//
//  Created by James Chen on 9/13/13.
//
//

#include "NewEventDispatcherTest.h"

namespace {
    
std::function<Layer*()> createFunctions[] =
{
    CL(TouchableSpriteTest),
    CL(FixedPriorityTest)
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
    auto listener1 = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            log("sprite tag %d, began... x = %f, y = %f", target->getTag(), locationInNode.x, locationInNode.y);
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
        log("sprite tag %d onTouchesEnded.. ", target->getTag());
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
}

std::string TouchableSpriteTest::title()
{
    return "Touchable Sprite Test";
}

std::string TouchableSpriteTest::subtitle()
{
    return "";
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
        
        auto listener = TouchEventListener::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = [&](Touch* touch, Event* event){
            
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
        
        listener->onTouchMoved = [&](Touch* touch, Event* event){
            //this->setPosition(this->getPosition() + touch->getDelta());
        };
        
        listener->onTouchEnded = [&](Touch* touch, Event* event){
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
