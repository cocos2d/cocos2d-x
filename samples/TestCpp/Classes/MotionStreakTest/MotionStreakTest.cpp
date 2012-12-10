#include "MotionStreakTest.h"
#include "../testResource.h"

enum {
	kTagLabel = 1,
	kTagSprite1 = 2,
	kTagSprite2 = 3,
};

CCLayer* nextMotionAction();
CCLayer* backMotionAction();
CCLayer* restartMotionAction();

//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
    MotionStreakTest::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
  
    // the root object just rotates around
    m_root = CCSprite::create(s_pPathR1);
    addChild(m_root, 1);
    m_root->setPosition(ccp(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    m_target = CCSprite::create(s_pPathR1);
    m_root->addChild(m_target);
    m_target->setPosition(ccp(s.width/4, 0));

    // create the streak object and add it to the scene
    streak = CCMotionStreak::create(2, 3, 32, ccGREEN, s_streak);
    addChild(streak);
    // schedule an update on each frame so we can syncronize the streak with the target
    schedule(schedule_selector(MotionStreakTest1::onUpdate));
  
    CCActionInterval* a1 = CCRotateBy::create(2, 360);

    CCAction* action1 = CCRepeatForever::create(a1);
    CCActionInterval* motion = CCMoveBy::create(2, ccp(100,0) );
    m_root->runAction( CCRepeatForever::create(CCSequence::create(motion, motion->reverse(), NULL) ) );
    m_root->runAction( action1 );

    CCActionInterval *colorAction = CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(0.2f, 255, 0, 0),
        CCTintTo::create(0.2f, 0, 255, 0),
        CCTintTo::create(0.2f, 0, 0, 255),
        CCTintTo::create(0.2f, 0, 255, 255),
        CCTintTo::create(0.2f, 255, 255, 0),
        CCTintTo::create(0.2f, 255, 0, 255),
        CCTintTo::create(0.2f, 255, 255, 255),
        NULL));

    streak->runAction(colorAction);
}

void MotionStreakTest1::onUpdate(float delta)
{
    streak->setPosition( m_target->convertToWorldSpace(CCPointZero) );
}

std::string MotionStreakTest1::title()
{
    return "MotionStreak test 1";
}

//------------------------------------------------------------------
//
// MotionStreakTest2
//
//------------------------------------------------------------------

void MotionStreakTest2::onEnter()
{
    MotionStreakTest::onEnter();

    setTouchEnabled(true);

    CCSize s = CCDirector::sharedDirector()->getWinSize();
        
    // create the streak object and add it to the scene
    streak = CCMotionStreak::create(3, 3, 64, ccWHITE, s_streak );
    addChild(streak);
    
    streak->setPosition( ccp(s.width/2, s.height/2) ); 
}

void MotionStreakTest2::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    
    streak->setPosition( touchLocation );
}

std::string MotionStreakTest2::title()
{
    return "MotionStreak test";
}

//------------------------------------------------------------------
//
// Issue1358
//
//------------------------------------------------------------------

void Issue1358::onEnter()
{
    MotionStreakTest::onEnter();
    
    // ask director the the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    streak = CCMotionStreak::create(2.0f, 1.0f, 50.0f, ccc3(255, 255, 0), "Images/Icon.png");
    addChild(streak);
    
    
    m_center  = ccp(size.width/2, size.height/2);
    m_fRadius = size.width/3;
    m_fAngle = 0.0f;
    
    schedule(schedule_selector(Issue1358::update), 0);
}

void Issue1358::update(float dt)
{
    m_fAngle += 1.0f;
    streak->setPosition(ccp(m_center.x + cosf(m_fAngle/180 * M_PI)*m_fRadius,
                            m_center.y + sinf(m_fAngle/ 180 * M_PI)*m_fRadius));
}

std::string Issue1358::title()
{
    return "Issue 1358";
}

std::string Issue1358::subtitle()
{
    return "The tail should use the texture";
}

//------------------------------------------------------------------
//
// MotionStreakTest
//
//------------------------------------------------------------------

// enum
// {
//     IDC_NEXT = 100,
//     IDC_BACK,
//     IDC_RESTART
// };

static int sceneIdx = -1; 

#define MAX_LAYER    3

CCLayer* createMotionLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new MotionStreakTest1();
        case 1: return new MotionStreakTest2();
        case 2: return new Issue1358();
    }

    return NULL;
}

CCLayer* nextMotionAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backMotionAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartMotionAction()
{
    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


MotionStreakTest::MotionStreakTest(void)
{
}

MotionStreakTest::~MotionStreakTest(void)
{
}

std::string MotionStreakTest::title()
{
    return "No title";
}

std::string MotionStreakTest::subtitle()
{
    return "";
}

void MotionStreakTest::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 0, kTagLabel);
    label->setPosition(ccp(s.width/2, s.height-50));
    
    string subTitle = this->subtitle();
    if (subTitle.size() > 0)
    {
        CCLabelTTF *l = CCLabelTTF::create(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(MotionStreakTest::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(MotionStreakTest::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(MotionStreakTest::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    

    CCMenuItemToggle *itemMode = CCMenuItemToggle::createWithTarget(this, menu_selector(MotionStreakTest::modeCallback),
        CCMenuItemFont::create("Use High Quality Mode"),
        CCMenuItemFont::create("Use Fast Mode"),
        NULL);

    CCMenu *menuMode = CCMenu::create(itemMode, NULL);
    addChild(menuMode);

    menuMode->setPosition(ccp(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(CCObject *pSender)
{
    bool fastMode = streak->isFastMode();
    streak->setFastMode(! fastMode);
}

void MotionStreakTest::restartCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild(restartMotionAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::nextCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild( nextMotionAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::backCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene;//CCScene::create();
    s->addChild( backMotionAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void MotionStreakTestScene::runThisTest()
{
    CCLayer* pLayer = nextMotionAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
