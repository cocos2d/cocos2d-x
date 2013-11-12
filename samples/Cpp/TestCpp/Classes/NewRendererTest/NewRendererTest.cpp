//
// Created by NiTe Luo on 11/1/13.
//


#include "NewRendererTest.h"
#include "CCNewSprite.h"
#include "CCNewSpriteBatchNode.h"

static int sceneIdx = -1;

Layer* nextSpriteTestAction();
Layer* backSpriteTestAction();
Layer* restartSpriteTestAction();

static std::function<Layer*()> createFunctions[] =
{
    CL(NewSpriteTest),
    CL(NewSpriteBatchTest),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();

    return layer;
}

Layer* prevTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();

    return layer;
}

Layer* restartTest()
{
    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();

    return layer;
}

void NewRendererTestScene::runThisTest()
{
    auto layer = nextTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

MultiSceneTest::MultiSceneTest()
{

}

MultiSceneTest::~MultiSceneTest()
{

}

string MultiSceneTest::title()
{
    return BaseTest::title();
}

string MultiSceneTest::subtitle()
{
    return BaseTest::subtitle();
}

void MultiSceneTest::onEnter()
{
    BaseTest::onEnter();
}

void MultiSceneTest::restartCallback(Object *sender)
{
    auto s = new NewRendererTestScene();
    s->addChild(restartTest());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void MultiSceneTest::nextCallback(Object *sender)
{
    auto s = new NewRendererTestScene();
    s->addChild(nextTest());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void MultiSceneTest::backCallback(Object *sender)
{
    auto s = new NewRendererTestScene();
    s->addChild(prevTest());

    Director::getInstance()->replaceScene(s);
    s->release();
}

NewSpriteTest::NewSpriteTest()
{
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(NewSpriteTest::onTouchesEnded, this);

    createSpriteTest();
    createNewSpriteTest();
}

NewSpriteTest::~NewSpriteTest()
{

}

void NewSpriteTest::createSpriteTest()
{
    Size winSize = Director::getInstance()->getWinSize();

    Sprite* parent = Sprite::create("Images/grossini.png");
    parent->setPosition(winSize.width/4, winSize.height/2);
    Sprite* child1 = Sprite::create("Images/grossinis_sister1.png");
    child1->setPosition(0.0f, -20.0f);
    Sprite* child2 = Sprite::create("Images/grossinis_sister2.png");
    child2->setPosition(20.0f, -20.0f);
    Sprite* child3 = Sprite::create("Images/grossinis_sister1.png");
    child3->setPosition(40.0f, -20.0f);
    Sprite* child4 = Sprite::create("Images/grossinis_sister2.png");
    child4->setPosition(60.0f, -20.0f);
    Sprite* child5 = Sprite::create("Images/grossinis_sister2.png");
    child5->setPosition(80.0f, -20.0f);
    Sprite* child6 = Sprite::create("Images/grossinis_sister2.png");
    child6->setPosition(100.0f, -20.0f);
    Sprite* child7 = Sprite::create("Images/grossinis_sister2.png");
    child7->setPosition(120.0f, -20.0f);

    parent->addChild(child1);
    parent->addChild(child2);
    parent->addChild(child3);
    parent->addChild(child4);
    parent->addChild(child5);
    parent->addChild(child6);
    parent->addChild(child7);
    addChild(parent);
}

void NewSpriteTest::createNewSpriteTest()
{
    Size winSize = Director::getInstance()->getWinSize();

    NewSprite* parent = NewSprite::create("Images/grossini.png");
    parent->setPosition(winSize.width*2/3, winSize.height/2);
    NewSprite* child1 = NewSprite::create("Images/grossinis_sister1.png");
    child1->setPosition(0.0f, -20.0f);
    NewSprite* child2 = NewSprite::create("Images/grossinis_sister2.png");
    child2->setPosition(20.0f, -20.0f);
    NewSprite* child3 = NewSprite::create("Images/grossinis_sister1.png");
    child3->setPosition(40.0f, -20.0f);
    NewSprite* child4 = NewSprite::create("Images/grossinis_sister2.png");
    child4->setPosition(60.0f, -20.0f);
    NewSprite* child5 = NewSprite::create("Images/grossinis_sister2.png");
    child5->setPosition(80.0f, -20.0f);
    NewSprite* child6 = NewSprite::create("Images/grossinis_sister2.png");
    child6->setPosition(100.0f, -20.0f);
    NewSprite* child7 = NewSprite::create("Images/grossinis_sister2.png");
    child7->setPosition(120.0f, -20.0f);

    parent->addChild(child1);
    parent->addChild(child2);
    parent->addChild(child3);
    parent->addChild(child4);
    parent->addChild(child5);
    parent->addChild(child6);
    parent->addChild(child7);
    addChild(parent);
}

void NewSpriteTest::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{

}


string NewSpriteTest::title()
{
    return "NewRender";
}

string NewSpriteTest::subtitle()
{
    return "SpriteTest";
}

//-------- New Sprite Batch Test

NewSpriteBatchTest::NewSpriteBatchTest()
{
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(NewSpriteBatchTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto BatchNode = NewSpriteBatchNode::create("Images/grossini_dance_atlas.png", 50);
    addChild(BatchNode, 0, kTagSpriteBatchNode);
}

NewSpriteBatchTest::~NewSpriteBatchTest()
{

}

string NewSpriteBatchTest::title()
{
    return "NewRender";
}

string NewSpriteBatchTest::subtitle()
{
    return "SpriteBatchTest";
}

void NewSpriteBatchTest::onTouchesEnded(const vector<Touch *> &touches, Event *event)
{
    for (auto &touch : touches)
    {
        auto location = touch->getLocation();
        addNewSpriteWithCoords(location);
    }
}

void NewSpriteBatchTest::addNewSpriteWithCoords(Point p)
{
    auto BatchNode = static_cast<NewSpriteBatchNode*>( getChildByTag(kTagSpriteBatchNode) );

    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;


    auto sprite = Sprite::createWithTexture(BatchNode->getTexture(), Rect(x,y,85,121));
    BatchNode->addChild(sprite);

    sprite->setPosition( Point( p.x, p.y) );

//    ActionInterval* action;
//    float random = CCRANDOM_0_1();
//
//    if( random < 0.20 )
//        action = ScaleBy::create(3, 2);
//    else if(random < 0.40)
//        action = RotateBy::create(3, 360);
//    else if( random < 0.60)
//        action = Blink::create(1, 3);
//    else if( random < 0.8 )
//        action = TintBy::create(2, 0, -255, -255);
//    else
//        action = FadeOut::create(2);
//
//    auto action_back = action->reverse();
//    auto seq = Sequence::create(action, action_back, NULL);
//
//    sprite->runAction( RepeatForever::create(seq));
}