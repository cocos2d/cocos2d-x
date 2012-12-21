#include "ActionManagerTest.h"
#include "../testResource.h"
#include "cocos2d.h"

enum 
{
    kTagNode,
    kTagGrossini,
    kTagSequence,
}; 

CCLayer* nextActionManagerAction();
CCLayer* backActionManagerAction();
CCLayer* restartActionManagerAction();

static int sceneIdx = -1; 

#define MAX_LAYER    5

CCLayer* createActionManagerLayer(int nIndex)
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

CCLayer* nextActionManagerAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createActionManagerLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backActionManagerAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createActionManagerLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartActionManagerAction()
{
    CCLayer* pLayer = createActionManagerLayer(sceneIdx);
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

void ActionManagerTest::onEnter()
{
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y-50));

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ActionManagerTest::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ActionManagerTest::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ActionManagerTest::nextCallback));

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y + item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y + item2->getContentSize().height/2));
    
    addChild(menu, 1);    
}

void ActionManagerTest::restartCallback(CCObject* pSender)
{
    CCScene* s = new ActionManagerTestScene();
    s->addChild(restartActionManagerAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionManagerTest::nextCallback(CCObject* pSender)
{
    CCScene* s = new ActionManagerTestScene();
    s->addChild( nextActionManagerAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ActionManagerTest::backCallback(CCObject* pSender)
{
    CCScene* s = new ActionManagerTestScene();
    s->addChild( backActionManagerAction() );
    CCDirector::sharedDirector()->replaceScene(s);
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

    CCSprite* child = CCSprite::create(s_pPathGrossini);
    child->setPosition( VisibleRect::center() );
    addChild(child, 1);

    //Sum of all action's duration is 1.5 second.
    child->runAction(CCRotateBy::create(1.5f, 90));
    child->runAction(CCSequence::create(
                                            CCDelayTime::create(1.4f),
                                            CCFadeOut::create(1.1f),
                                            NULL)
                    );
    
    //After 1.5 second, self will be removed.
    runAction( CCSequence::create(
                                    CCDelayTime::create(1.4f),
                                    CCCallFunc::create(this, callfunc_selector(CrashTest::removeThis)),
                                    NULL)
             );
}

void CrashTest::removeThis()
{
    m_pParent->removeChild(this, true);
    
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

    CCSprite* grossini = CCSprite::create(s_pPathGrossini);
    addChild(grossini, 0, 2);
    grossini->setPosition(VisibleRect::center());

    grossini->runAction( CCSequence::create( 
                                                CCMoveBy::create(1, ccp(150,0)),
                                                CCCallFuncN::create(this, callfuncN_selector(LogicTest::bugMe)),
                                                NULL) 
                        );
}

void LogicTest::bugMe(CCNode* node)
{
    node->stopAllActions(); //After this stop next action not working, if remove this stop everything is working
    node->runAction(CCScaleTo::create(2, 2));
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
    

    CCLabelTTF* l = CCLabelTTF::create("After 5 seconds grossini should move", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-75) );
    
    
    //
    // Also, this test MUST be done, after [super onEnter]
    //
    CCSprite* grossini = CCSprite::create(s_pPathGrossini);
    addChild(grossini, 0, kTagGrossini);
    grossini->setPosition(VisibleRect::center() );
    
    CCAction* action = CCMoveBy::create(1, ccp(150,0));

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getActionManager()->addAction(action, grossini, true);

    schedule( schedule_selector(PauseTest::unpause), 3); 
}

void PauseTest::unpause(float dt)
{
    unschedule( schedule_selector(PauseTest::unpause) );
    CCNode* node = getChildByTag( kTagGrossini );
    CCDirector* pDirector = CCDirector::sharedDirector();
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

    CCLabelTTF* l = CCLabelTTF::create("Should not crash", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 75) );

    CCMoveBy* pMove = CCMoveBy::create(2, ccp(200, 0));
    CCCallFunc* pCallback = CCCallFunc::create(this, callfunc_selector(RemoveTest::stopAction));
    CCActionInterval* pSequence = CCSequence::create(pMove, pCallback, NULL);
    pSequence->setTag(kTagSequence);

    CCSprite* pChild = CCSprite::create(s_pPathGrossini);
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, kTagGrossini);
    pChild->runAction(pSequence);
}

void RemoveTest::stopAction()
{
    CCNode* pSprite = getChildByTag(kTagGrossini);
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

    CCLabelTTF* l = CCLabelTTF::create("Grossini only rotate/scale in 3 seconds", "Thonburi", 16);
    addChild(l);
    l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 75));

    CCSprite* pGrossini = CCSprite::create(s_pPathGrossini);
    addChild(pGrossini, 0, kTagGrossini);
    pGrossini->setPosition(VisibleRect::center());

    pGrossini->runAction(CCScaleBy::create(2, 2));

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getActionManager()->pauseTarget(pGrossini);
    pGrossini->runAction(CCRotateBy::create(2, 360));

    this->schedule(schedule_selector(ResumeTest::resumeGrossini), 3.0f);
}

void ResumeTest::resumeGrossini(float time)
{
    this->unschedule(schedule_selector(ResumeTest::resumeGrossini));

    CCNode* pGrossini = getChildByTag(kTagGrossini);
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getActionManager()->resumeTarget(pGrossini);
}

//------------------------------------------------------------------
//
// ActionManagerTestScene
//
//------------------------------------------------------------------
void ActionManagerTestScene::runThisTest()
{
    CCLayer* pLayer = nextActionManagerAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
