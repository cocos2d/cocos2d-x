#include "ActionManagerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

enum 
{
    kTagNode,
    kTagGrossini,
    kTagSequence,
}; 

Layer* nextActionManagerAction();
Layer* backActionManagerAction();
Layer* restartActionManagerAction();

static int sceneIdx = -1; 

#define MAX_LAYER    5

Layer* createActionManagerLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new CrashTest();
        case 1: return new LogicTest();
        case 2: return new PauseTest();
        case 3: return new StopActionTest();
        case 4: return new ResumeTest();
    }

    return NULL;
}

Layer* nextActionManagerAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = createActionManagerLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backActionManagerAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = createActionManagerLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartActionManagerAction()
{
    auto layer = createActionManagerLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 

//------------------------------------------------------------------
//
// ActionManagerTest
//
//------------------------------------------------------------------

ActionManagerTest::ActionManagerTest(void)
{
}

ActionManagerTest::~ActionManagerTest(void)
{
}

std::string ActionManagerTest::title() const
{
    return "ActionManager Test";
}
std::string ActionManagerTest::subtitle() const
{
    return "No title";
}
void ActionManagerTest::restartCallback(Ref* sender)
{
    auto s = new ActionManagerTestScene();
    s->addChild(restartActionManagerAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionManagerTest::nextCallback(Ref* sender)
{
    auto s = new ActionManagerTestScene();
    s->addChild( nextActionManagerAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionManagerTest::backCallback(Ref* sender)
{
    auto s = new ActionManagerTestScene();
    s->addChild( backActionManagerAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

//------------------------------------------------------------------
//
// Test1
//
//------------------------------------------------------------------

void CrashTest::onEnter()
{
    ActionManagerTest::onEnter();

    auto child = Sprite::create(s_pathGrossini);
    child->setPosition( VisibleRect::center() );
    addChild(child, 1);

    //Sum of all action's duration is 1.5 second.
    child->runAction(RotateBy::create(1.5f, 90));
    child->runAction(Sequence::create(
                                            DelayTime::create(1.4f),
                                            FadeOut::create(1.1f),
                                            NULL)
                    );
    
    //After 1.5 second, self will be removed.
    runAction( Sequence::create(
                                    DelayTime::create(1.4f),
                                    CallFunc::create( CC_CALLBACK_0(CrashTest::removeThis,this)),
                                    NULL)
             );
}

void CrashTest::removeThis()
{
    _parent->removeChild(this, true);
    
    nextCallback(this);
}

std::string CrashTest::subtitle() const
{
    return "Test 1. Should not crash";
}

//------------------------------------------------------------------
//
// Test2
//
//------------------------------------------------------------------
void LogicTest::onEnter()
{
    ActionManagerTest::onEnter();

    auto grossini = Sprite::create(s_pathGrossini);
    addChild(grossini, 0, 2);
    grossini->setPosition(VisibleRect::center());

    grossini->runAction( Sequence::create( 
                                                MoveBy::create(1, Point(150,0)),
                                                CallFuncN::create(CC_CALLBACK_1(LogicTest::bugMe,this)),
                                                NULL) 
                        );
}

void LogicTest::bugMe(Node* node)
{
    node->stopAllActions(); //After this stop next action not working, if remove this stop everything is working
    node->runAction(ScaleTo::create(2, 2));
}

std::string LogicTest::subtitle() const
{
    return "Logic test"; 
}

//------------------------------------------------------------------
//
// PauseTest
//
//------------------------------------------------------------------

void PauseTest::onEnter()
{
    //
    // This test MUST be done in 'onEnter' and not on 'init'
    // otherwise the paused action will be resumed at 'onEnter' time
    //
    ActionManagerTest::onEnter();
    

    auto l = Label::createWithTTF("After 5 seconds grossini should move", "fonts/Thonburi.ttf", 16.0f);
    addChild(l);
    l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y-75) );
    
    
    //
    // Also, this test MUST be done, after [super onEnter]
    //
    auto grossini = Sprite::create(s_pathGrossini);
    addChild(grossini, 0, kTagGrossini);
    grossini->setPosition(VisibleRect::center() );
    
    auto action = MoveBy::create(1, Point(150,0));

    auto director = Director::getInstance();
    director->getActionManager()->addAction(action, grossini, true);

    schedule( schedule_selector(PauseTest::unpause), 3); 
}

void PauseTest::unpause(float dt)
{
    unschedule( schedule_selector(PauseTest::unpause) );
    auto node = getChildByTag( kTagGrossini );
    auto director = Director::getInstance();
    director->getActionManager()->resumeTarget(node);
}

std::string PauseTest::subtitle() const
{
    return "Pause Test";
}

//------------------------------------------------------------------
//
// RemoveTest
//
//------------------------------------------------------------------
void StopActionTest::onEnter()
{
    ActionManagerTest::onEnter();

    auto l = Label::createWithTTF("Should not crash", "fonts/Thonburi.ttf", 16.0f);
    addChild(l);
    l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 75) );

    auto pMove = MoveBy::create(2, Point(200, 0));
    auto pCallback = CallFunc::create(CC_CALLBACK_0(StopActionTest::stopAction,this));
    auto pSequence = Sequence::create(pMove, pCallback, NULL);
    pSequence->setTag(kTagSequence);

    auto pChild = Sprite::create(s_pathGrossini);
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, kTagGrossini);
    pChild->runAction(pSequence);
}

void StopActionTest::stopAction()
{
    auto sprite = getChildByTag(kTagGrossini);
    sprite->stopActionByTag(kTagSequence);
}

std::string StopActionTest::subtitle() const
{
    return "Stop Action Test";
}

//------------------------------------------------------------------
//
// ResumeTest
//
//------------------------------------------------------------------
std::string ResumeTest::subtitle() const
{
    return "Resume Test";
}

void ResumeTest::onEnter()
{
    ActionManagerTest::onEnter();

    auto l = Label::createWithTTF("Grossini only rotate/scale in 3 seconds", "fonts/Thonburi.ttf", 16.0f);
    addChild(l);
    l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 75));

    auto pGrossini = Sprite::create(s_pathGrossini);
    addChild(pGrossini, 0, kTagGrossini);
    pGrossini->setPosition(VisibleRect::center());

    pGrossini->runAction(ScaleBy::create(2, 2));

    auto director = Director::getInstance();
    director->getActionManager()->pauseTarget(pGrossini);
    pGrossini->runAction(RotateBy::create(2, 360));

    this->schedule(schedule_selector(ResumeTest::resumeGrossini), 3.0f);
}

void ResumeTest::resumeGrossini(float time)
{
    this->unschedule(schedule_selector(ResumeTest::resumeGrossini));

    auto pGrossini = getChildByTag(kTagGrossini);
    auto director = Director::getInstance();
    director->getActionManager()->resumeTarget(pGrossini);
}

//------------------------------------------------------------------
//
// ActionManagerTestScene
//
//------------------------------------------------------------------
void ActionManagerTestScene::runThisTest()
{
    auto layer = nextActionManagerAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
