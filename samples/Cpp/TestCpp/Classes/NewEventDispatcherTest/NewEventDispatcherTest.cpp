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
    addChild(sprite1, 1, 100);
    
    auto sprite2 = Sprite::create("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite2, 2, 200);
    
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
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        log("sprite tag: %d moved... x = %f, y = %f", target->getTag(), locationInNode.x, locationInNode.y);
        
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite tag %d onTouchesEnded.. ", target->getTag());
        target->setOpacity(255);
    };
    
    dispatcher->registerEventListenerWithSceneGraphPriority(listener1, sprite1);
    dispatcher->registerEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
}

std::string TouchableSpriteTest::title()
{
    return "Touchable Sprite Test";
}

std::string TouchableSpriteTest::subtitle()
{
    return "";
}
