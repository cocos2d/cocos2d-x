#include "ActionsProgressTest.h"
#include "../testResource.h"

static int sceneIdx = -1; 

#define MAX_LAYER    7

Layer* nextAction();
Layer* backAction();
Layer* restartAction();

Layer* createLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new SpriteProgressToRadial();
        case 1: return new SpriteProgressToHorizontal();
        case 2: return new SpriteProgressToVertical();
        case 3: return new SpriteProgressToRadialMidpointChanged();
        case 4: return new SpriteProgressBarVarious();
        case 5: return new SpriteProgressBarTintAndFade();
        case 6: return new SpriteProgressWithSpriteFrame();
    }

    return NULL;
}

Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = createLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = createLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartAction()
{
    auto layer = createLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 


void ProgressActionsTestScene::runThisTest()
{
    addChild(nextAction());
    Director::getInstance()->replaceScene(this);
}


//------------------------------------------------------------------
//
// SpriteDemo
//
//------------------------------------------------------------------
SpriteDemo::SpriteDemo(void)
{
}

SpriteDemo::~SpriteDemo(void)
{
}

std::string SpriteDemo::title()
{
    return "ActionsProgressTest";
}

std::string SpriteDemo::subtitle()
{
    return "";
}

void SpriteDemo::onEnter()
{
    BaseTest::onEnter();

    auto background = LayerColor::create(Color4B(255,0,0,255));
    addChild(background, -10);
}

void SpriteDemo::restartCallback(Object* sender)
{
    auto s = new ProgressActionsTestScene();
    s->addChild(restartAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void SpriteDemo::nextCallback(Object* sender)
{
    auto s = new ProgressActionsTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SpriteDemo::backCallback(Object* sender)
{
    auto s = new ProgressActionsTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

//------------------------------------------------------------------
//
// SpriteProgressToRadial
//
//------------------------------------------------------------------
void SpriteProgressToRadial::onEnter()
{
    SpriteDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();

    auto to1 = ProgressTo::create(2, 100);
    auto to2 = ProgressTo::create(2, 100);

    auto left = ProgressTimer::create(Sprite::create(s_pathSister1));
    left->setType( ProgressTimer::Type::RADIAL );
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    auto right = ProgressTimer::create(Sprite::create(s_pathBlock));
    right->setType(ProgressTimer::Type::RADIAL);
    // Makes the ridial CCW
    right->setReverseProgress(true);
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToRadial::subtitle()
{
    return "ProgressTo Radial";
}

//------------------------------------------------------------------
//
// SpriteProgressToHorizontal
//
//------------------------------------------------------------------

void SpriteProgressToHorizontal::onEnter()
{
    SpriteDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto to1 = ProgressTo::create(2, 100);
    auto to2 = ProgressTo::create(2, 100);
    
    auto left = ProgressTimer::create(Sprite::create(s_pathSister1));
    left->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    left->setMidpoint(Point(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left->setBarChangeRate(Point(1, 0));
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    auto right = ProgressTimer::create(Sprite::create(s_pathSister2));
    right->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 1 for the x
    right->setMidpoint(Point(1, 0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right->setBarChangeRate(Point(1, 0));
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToHorizontal::subtitle()
{
    return "ProgressTo Horizontal";
}

//------------------------------------------------------------------
//
// SpriteProgressToVertical
//
//------------------------------------------------------------------
void SpriteProgressToVertical::onEnter()
{
    SpriteDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto to1 = ProgressTo::create(2, 100);
    auto to2 = ProgressTo::create(2, 100);
    
    auto left = ProgressTimer::create(Sprite::create(s_pathSister1));
    left->setType(ProgressTimer::Type::BAR);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(Point(0,0));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(Point(0, 1));
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction( RepeatForever::create(to1));
    
    auto right = ProgressTimer::create(Sprite::create(s_pathSister2));
    right->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(Point(0, 1));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(Point(0, 1));
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction( RepeatForever::create(to2));
}

std::string SpriteProgressToVertical::subtitle()
{
    return "ProgressTo Vertical";
}

//------------------------------------------------------------------
//
// SpriteProgressToRadialMidpointChanged
//
//------------------------------------------------------------------
void SpriteProgressToRadialMidpointChanged::onEnter()
{
    SpriteDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto action = ProgressTo::create(2, 100);

    /**
   *  Our image on the left should be a radial progress indicator, clockwise
   */
    auto left = ProgressTimer::create(Sprite::create(s_pathBlock));
    left->setType(ProgressTimer::Type::RADIAL);
    addChild(left);
    left->setMidpoint(Point(0.25f, 0.75f));
    left->setPosition(Point(100, s.height/2));
    left->runAction(RepeatForever::create(action->clone()));

    /**
   *  Our image on the left should be a radial progress indicator, counter clockwise
   */
    auto right = ProgressTimer::create(Sprite::create(s_pathBlock));
    right->setType(ProgressTimer::Type::RADIAL);
    right->setMidpoint(Point(0.75f, 0.25f));

    /**
   *  Note the reverse property (default=NO) is only added to the right image. That's how
   *  we get a counter clockwise progress.
   */
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(action->clone()));
}

std::string SpriteProgressToRadialMidpointChanged::subtitle()
{
    return "Radial w/ Different Midpoints";
}

//------------------------------------------------------------------
//
// SpriteProgressBarVarious
//
//------------------------------------------------------------------
void SpriteProgressBarVarious::onEnter()
{
    SpriteDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto to = ProgressTo::create(2, 100);

    auto left = ProgressTimer::create(Sprite::create(s_pathSister1));
    left->setType(ProgressTimer::Type::BAR);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(Point(1, 0));
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));

    auto middle = ProgressTimer::create(Sprite::create(s_pathSister2));
    middle->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(Point(1,1));
    addChild(middle);
    middle->setPosition(Point(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));

    auto right = ProgressTimer::create(Sprite::create(s_pathSister2));
    right->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(Point(0, 1));
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
}

std::string SpriteProgressBarVarious::subtitle()
{
    return "ProgressTo Bar Mid";
}

//------------------------------------------------------------------
//
// SpriteProgressBarTintAndFade
//
//------------------------------------------------------------------
void SpriteProgressBarTintAndFade::onEnter()
{
    SpriteDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto to = ProgressTo::create(6, 100);
	auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
								   TintTo::create(1, 0, 255, 0),
								   TintTo::create(1, 0, 0, 255),
								   NULL);
	auto fade = Sequence::create(FadeTo::create(1.0f, 0),
								   FadeTo::create(1.0f, 255),
								   NULL);

    auto left = ProgressTimer::create(Sprite::create(s_pathSister1));
    left->setType(ProgressTimer::Type::BAR);

    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(Point(1, 0));
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));
    left->runAction(RepeatForever::create(tint->clone()));

    left->addChild(LabelTTF::create("Tint", "Marker Felt", 20.0f));

    auto middle = ProgressTimer::create(Sprite::create(s_pathSister2));
    middle->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(Point(1, 1));
    addChild(middle);
    middle->setPosition(Point(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));
    middle->runAction(RepeatForever::create(fade->clone()));

    middle->addChild(LabelTTF::create("Fade", "Marker Felt", 20.0f));

    auto right = ProgressTimer::create(Sprite::create(s_pathSister2));
    right->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(Point(0, 1));
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
	right->runAction(RepeatForever::create(tint->clone()));
    right->runAction(RepeatForever::create(fade->clone()));

    right->addChild(LabelTTF::create("Tint and Fade", "Marker Felt", 20.0f));
}

std::string SpriteProgressBarTintAndFade::subtitle()
{
    return "ProgressTo Bar Mid";
}

//------------------------------------------------------------------
//
// SpriteProgressWithSpriteFrame
//
//------------------------------------------------------------------
void SpriteProgressWithSpriteFrame::onEnter()
{
    SpriteDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto to = ProgressTo::create(6, 100);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwoptex/grossini.plist");

    auto left = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_01.png"));
    left->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left->setBarChangeRate(Point(1, 0));
    addChild(left);
    left->setPosition(Point(100, s.height/2));
    left->runAction(RepeatForever::create(to->clone()));

    auto middle = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_02.png"));
    middle->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(Point(1, 1));
    addChild(middle);
    middle->setPosition(Point(s.width/2, s.height/2));
    middle->runAction(RepeatForever::create(to->clone()));

    auto right = ProgressTimer::create(Sprite::createWithSpriteFrameName("grossini_dance_03.png"));
    right->setType(ProgressTimer::Type::RADIAL);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right->setMidpoint(Point(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right->setBarChangeRate(Point(0, 1));
    addChild(right);
    right->setPosition(Point(s.width-100, s.height/2));
    right->runAction(RepeatForever::create(to->clone()));
}

std::string SpriteProgressWithSpriteFrame::subtitle()
{
    return "Progress With Sprite Frame";
}
