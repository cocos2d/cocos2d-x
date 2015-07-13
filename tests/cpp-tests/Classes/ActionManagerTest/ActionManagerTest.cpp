#include "ActionManagerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

USING_NS_CC;

enum 
{
    kTagNode,
    kTagGrossini,
    kTagSequence,
}; 

ActionManagerTests::ActionManagerTests()
{
    ADD_TEST_CASE(CrashTest);
    ADD_TEST_CASE(LogicTest);
    ADD_TEST_CASE(PauseTest);
    ADD_TEST_CASE(StopActionTest);
    ADD_TEST_CASE(StopAllActionsTest);
    ADD_TEST_CASE(StopActionsByFlagsTest);
    ADD_TEST_CASE(ResumeTest);
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
    addChild(child, 1, kTagGrossini);

    //Sum of all action's duration is 1.5 second.
    child->runAction(RotateBy::create(1.5f, 90));
    child->runAction(Sequence::create(
                                            DelayTime::create(1.4f),
                                            FadeOut::create(1.1f),
                                            nullptr)
                    );
    
    //After 1.5 second, self will be removed.
    child->runAction(Sequence::create(
                                    DelayTime::create(1.4f),
                                    CallFunc::create( CC_CALLBACK_0(CrashTest::removeThis,this)),
                                    nullptr)
             );
}

void CrashTest::removeThis()
{
    auto child = getChildByTag(kTagGrossini);
    child->removeChild(child, true);
    
    getTestSuite()->enterNextTest();
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
                                                MoveBy::create(1, Vec2(150,0)),
                                                CallFuncN::create(CC_CALLBACK_1(LogicTest::bugMe,this)),
                                                nullptr) 
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
    l->setPosition(VisibleRect::center().x, VisibleRect::top().y-75);
    
    
    //
    // Also, this test MUST be done, after [super onEnter]
    //
    auto grossini = Sprite::create(s_pathGrossini);
    addChild(grossini, 0, kTagGrossini);
    grossini->setPosition(VisibleRect::center() );
    
    auto action = MoveBy::create(1, Vec2(150,0));

    auto director = Director::getInstance();
    director->getActionManager()->addAction(action, grossini, true);

    schedule( CC_SCHEDULE_SELECTOR(PauseTest::unpause), 3); 
}

void PauseTest::unpause(float dt)
{
    unschedule( CC_SCHEDULE_SELECTOR(PauseTest::unpause) );
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
    l->setPosition(VisibleRect::center().x, VisibleRect::top().y - 75);

    auto pMove = MoveBy::create(2, Vec2(200, 0));
    auto pCallback = CallFunc::create(CC_CALLBACK_0(StopActionTest::stopAction,this));
    auto pSequence = Sequence::create(pMove, pCallback, nullptr);
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
// RemoveTest
//
//------------------------------------------------------------------
void StopAllActionsTest::onEnter()
{
    ActionManagerTest::onEnter();
    
    auto l = Label::createWithTTF("Should stop scale & move after 4 seconds but keep rotate", "fonts/Thonburi.ttf", 16.0f);
    addChild(l);
    l->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 75) );
    
    auto pMove1 = MoveBy::create(2, Vec2(200, 0));
    auto pMove2 = MoveBy::create(2, Vec2(-200, 0));
    auto pSequenceMove = Sequence::createWithTwoActions(pMove1, pMove2);
    auto pRepeatMove = RepeatForever::create(pSequenceMove);
    pRepeatMove->setTag(kTagSequence);
    
    auto pScale1 = ScaleBy::create(2, 1.5f);
    auto pScale2 = ScaleBy::create(2, 1.0f/1.5f);
    auto pSequenceScale = Sequence::createWithTwoActions(pScale1, pScale2);
    auto pRepeatScale = RepeatForever::create(pSequenceScale);
    pRepeatScale->setTag(kTagSequence);
    
    auto pRotate = RotateBy::create(2, 360);
    auto pRepeatRotate = RepeatForever::create(pRotate);
    
    auto pChild = Sprite::create(s_pathGrossini);
    pChild->setPosition( VisibleRect::center() );
    
    addChild(pChild, 1, kTagGrossini);
    pChild->runAction(pRepeatMove);
    pChild->runAction(pRepeatScale);
    pChild->runAction(pRepeatRotate);
    this->scheduleOnce((SEL_SCHEDULE)&StopAllActionsTest::stopAction, 4);
}

void StopAllActionsTest::stopAction(float time)
{
    auto sprite = getChildByTag(kTagGrossini);
    sprite->stopAllActionsByTag(kTagSequence);
}

std::string StopAllActionsTest::subtitle() const
{
    return "Stop All Action Test";
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
    l->setPosition(VisibleRect::center().x, VisibleRect::top().y - 75);

    auto pGrossini = Sprite::create(s_pathGrossini);
    addChild(pGrossini, 0, kTagGrossini);
    pGrossini->setPosition(VisibleRect::center());

    pGrossini->runAction(ScaleBy::create(2, 2));

    auto director = Director::getInstance();
    director->getActionManager()->pauseTarget(pGrossini);
    pGrossini->runAction(RotateBy::create(2, 360));

    this->schedule(CC_SCHEDULE_SELECTOR(ResumeTest::resumeGrossini), 3.0f);
}

void ResumeTest::resumeGrossini(float time)
{
    this->unschedule(CC_SCHEDULE_SELECTOR(ResumeTest::resumeGrossini));

    auto pGrossini = getChildByTag(kTagGrossini);
    auto director = Director::getInstance();
    director->getActionManager()->resumeTarget(pGrossini);
}

//------------------------------------------------------------------
//
// StopActionsByFlagsTest
//
//------------------------------------------------------------------
void StopActionsByFlagsTest::onEnter()
{
    ActionManagerTest::onEnter();

    auto l = Label::createWithTTF("Should stop scale & move after 4 seconds but keep rotate", "fonts/Thonburi.ttf", 16.0f);
    addChild(l);
    l->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 75) );

    auto pMove1 = MoveBy::create(2, Vec2(200, 0));
    auto pMove2 = MoveBy::create(2, Vec2(-200, 0));
    auto pSequenceMove = Sequence::createWithTwoActions(pMove1, pMove2);
    auto pRepeatMove = RepeatForever::create(pSequenceMove);
    pRepeatMove->setFlags(kMoveFlag | kRepeatForeverFlag);

    auto pScale1 = ScaleBy::create(2, 1.5f);
    auto pScale2 = ScaleBy::create(2, 1.0f/1.5f);
    auto pSequenceScale = Sequence::createWithTwoActions(pScale1, pScale2);
    auto pRepeatScale = RepeatForever::create(pSequenceScale);
    pRepeatScale->setFlags(kScaleFlag | kRepeatForeverFlag);

    auto pRotate = RotateBy::create(2, 360);
    auto pRepeatRotate = RepeatForever::create(pRotate);
    pRepeatRotate->setFlags(kRotateFlag | kRepeatForeverFlag);

    auto pChild = Sprite::create(s_pathGrossini);
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, kTagGrossini);
    pChild->runAction(pRepeatMove);
    pChild->runAction(pRepeatScale);
    pChild->runAction(pRepeatRotate);
    this->scheduleOnce((SEL_SCHEDULE)&StopActionsByFlagsTest::stopAction, 4);
}

void StopActionsByFlagsTest::stopAction(float time)
{
    auto sprite = getChildByTag(kTagGrossini);
    sprite->stopActionsByFlags(kMoveFlag | kScaleFlag);
}

std::string StopActionsByFlagsTest::subtitle() const
{
    return "Stop All Actions By Flags Test";
}
