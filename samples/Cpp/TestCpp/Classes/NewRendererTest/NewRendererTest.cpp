//
// Created by NiTe Luo on 11/1/13.
//


#include "NewRendererTest.h"
#include "CCNewSprite.h"
#include "CCNewSpriteBatchNode.h"
#include "NewClippingNode.h"

static int sceneIdx = -1;

Layer* nextSpriteTestAction();
Layer* backSpriteTestAction();
Layer* restartSpriteTestAction();

static std::function<Layer*()> createFunctions[] =
{
    CL(NewSpriteTest),
    CL(NewSpriteBatchTest),
    CL(NewClippingNodeTest),
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
}

NewClippingNodeTest::NewClippingNodeTest()
{
    auto clipper = NewClippingNode::create();
    clipper->setTag( kTagClipperNode );
    clipper->setContentSize(  Size(200, 200) );
    clipper->setAnchorPoint(  Point(0.5, 0.5) );
    clipper->setPosition( Point(this->getContentSize().width / 2, this->getContentSize().height / 2) );
    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);

    auto stencil = DrawNode::create();
    Point rectangle[4];
    rectangle[0] = Point(0, 0);
    rectangle[1] = Point(clipper->getContentSize().width, 0);
    rectangle[2] = Point(clipper->getContentSize().width, clipper->getContentSize().height);
    rectangle[3] = Point(0, clipper->getContentSize().height);

    Color4F white(1, 1, 1, 1);
    stencil->drawPolygon(rectangle, 4, white, 1, white);
    clipper->setStencil(stencil);

    auto content = NewSprite::create("Images/background2.png");
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Point(0.5, 0.5) );
    content->setPosition( Point(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
    clipper->addChild(content);

    _scrolling = false;

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(NewClippingNodeTest::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(NewClippingNodeTest::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(NewClippingNodeTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

NewClippingNodeTest::~NewClippingNodeTest()
{

}

string NewClippingNodeTest::title()
{
    return "New Render";
}

string NewClippingNodeTest::subtitle()
{
    return "ClipNode";
}

void NewClippingNodeTest::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
    Point point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    auto rect = Rect(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void NewClippingNodeTest::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{
    if (!_scrolling) return;
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
    auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Point diff = point - _lastPoint;
    auto content = clipper->getChildByTag(kTagContentNode);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void NewClippingNodeTest::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    if (!_scrolling) return;
    _scrolling = false;
}
