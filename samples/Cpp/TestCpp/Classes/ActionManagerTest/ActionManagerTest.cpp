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
        case 3: return new RemoveTest();
        case 4: return new ResumeTest();
    }

    return NULL;
}

Layer* nextActionManagerAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createActionManagerLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backActionManagerAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createActionManagerLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartActionManagerAction()
{
    Layer* pLayer = createActionManagerLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
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

std::string ActionManagerTest::title()
{
    return "No title";
}

void ActionManagerTest::restartCallback(Object* pSender)
{
    Scene* s = new ActionManagerTestScene();
    s->addChild(restartActionManagerAction()); 

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionManagerTest::nextCallback(Object* pSender)
{
    Scene* s = new ActionManagerTestScene();
    s->addChild( nextActionManagerAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionManagerTest::backCallback(Object* pSender)
{
    Scene* s = new ActionManagerTestScene();
    s->addChild( backActionManagerAction() );
    Director::sharedDirector()->replaceScene(s);
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

    Sprite* child = Sprite::create(s_pPathGrossini);
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
                                    CallFunc::create(this, callfunc_selector(CrashTest::removeThis)),
                                    NULL)
             );
}

void CrashTest::removeThis()
{
    _parent->removeChild(this, true);
    
    nextCallback(this);
}

std::string CrashTest::title()
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

    Sprite* grossini = Sprite::create(s_pPathGrossini);
    addChild(grossini, 0, 2);
    grossini->setPosition(VisibleRect::center());

    grossini->runAction( Sequence::create( 
                                                MoveBy::create(1, ccp(150,0)),
                                                CallFuncN::create(this, callfuncN_selector(LogicTest::bugMe)),
                                                NULL) 
                        );
}

void LogicTest::bugMe(Node* node)
{
    node->stopAllActions(); //After this stop next action not working, if remove this stop everything is working
    node->runAction(ScaleTo::create(2, 2));
}

std::string LogicTest::title()
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
    

    LabelTTF* l = LabelTTF::create("After 5 seconds grossini should move", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-75) );
    
    
    //
    // Also, this test MUST be done, after [super onEnter]
    //
    Sprite* grossini = Sprite::create(s_pPathGrossini);
    addChild(grossini, 0, kTagGrossini);
    grossini->setPosition(VisibleRect::center() );
    
    Action* action = MoveBy::create(1, ccp(150,0));

    Director* pDirector = Director::sharedDirector();
    pDirector->getActionManager()->addAction(action, grossini, true);

    schedule( schedule_selector(PauseTest::unpause), 3); 
}

void PauseTest::unpause(float dt)
{
    unschedule( schedule_selector(PauseTest::unpause) );
    Node* node = getChildByTag( kTagGrossini );
    Director* pDirector = Director::sharedDirector();
    pDirector->getActionManager()->resumeTarget(node);
}

std::string PauseTest::title()
{
    return "Pause Test";
}

//------------------------------------------------------------------
//
// RemoveTest
//
//------------------------------------------------------------------
void RemoveTest::onEnter()
{
    ActionManagerTest::onEnter();

    LabelTTF* l = LabelTTF::create("Should not crash", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 75) );

    MoveBy* pMove = MoveBy::create(2, ccp(200, 0));
    CallFunc* pCallback = CallFunc::create(this, callfunc_selector(RemoveTest::stopAction));
    ActionInterval* pSequence = Sequence::create(pMove, pCallback, NULL);
    pSequence->setTag(kTagSequence);

    Sprite* pChild = Sprite::create(s_pPathGrossini);
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, kTagGrossini);
    pChild->runAction(pSequence);
}

void RemoveTest::stopAction()
{
    Node* pSprite = getChildByTag(kTagGrossini);
    pSprite->stopActionByTag(kTagSequence);
}

std::string RemoveTest::title()
{
    return "Remove Test";
}

//------------------------------------------------------------------
//
// ResumeTest
//
//------------------------------------------------------------------
std::string ResumeTest::title()
{
    return "Resume Test";
}

void ResumeTest::onEnter()
{
    ActionManagerTest::onEnter();

    LabelTTF* l = LabelTTF::create("Grossini only rotate/scale in 3 seconds", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 75));

    Sprite* pGrossini = Sprite::create(s_pPathGrossini);
    addChild(pGrossini, 0, kTagGrossini);
    pGrossini->setPosition(VisibleRect::center());

    pGrossini->runAction(ScaleBy::create(2, 2));

    Director* pDirector = Director::sharedDirector();
    pDirector->getActionManager()->pauseTarget(pGrossini);
    pGrossini->runAction(RotateBy::create(2, 360));

    this->schedule(schedule_selector(ResumeTest::resumeGrossini), 3.0f);
}

void ResumeTest::resumeGrossini(float time)
{
    this->unschedule(schedule_selector(ResumeTest::resumeGrossini));

    Node* pGrossini = getChildByTag(kTagGrossini);
    Director* pDirector = Director::sharedDirector();
    pDirector->getActionManager()->resumeTarget(pGrossini);
}

//------------------------------------------------------------------
//
// ActionManagerTestScene
//
//------------------------------------------------------------------
void ActionManagerTestScene::runThisTest()
{
    Layer* pLayer = nextActionManagerAction();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
