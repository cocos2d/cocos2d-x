//
// Created by NiTe Luo on 11/1/13.
//


#include "NewRendererTest.h"
#include "CCNewSprite.h"


NewRendererTest::NewRendererTest()
{
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(NewRendererTest::onTouchesEnded, this);

    createSpriteTest();
    createNewSpriteTest();
}

NewRendererTest::~NewRendererTest()
{

}

void NewRendererTest::createSpriteTest()
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

void NewRendererTest::createNewSpriteTest()
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

void NewRendererTest::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{

}

void NewRendererTestScene::runThisTest()
{
    auto layer = new NewRendererTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
