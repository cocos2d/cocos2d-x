#include "CocosNodeTest.h"
#include "../testResource.h"

enum 
{
	kTagSprite1 = 1,
	kTagSprite2 = 2,
	kTagSprite3 = 3,
	kTagSlider,
};


CCLayer* nextCocosNodeAction();
CCLayer* backCocosNodeAction();
CCLayer* restartCocosNodeAction();

//------------------------------------------------------------------
//
// TestCocosNodeDemo
//
//------------------------------------------------------------------

static int sceneIdx = -1; 

#define MAX_LAYER	12

CCLayer* createCocosNodeLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new CameraCenterTest();
		case 1: return new Test2();
		case 2: return new Test4();
		case 3: return new Test5();
		case 4: return new Test6();
		case 5: return new StressTest1();
		case 6: return new StressTest2();
		case 7: return new NodeToWorld();
		case 8: return new SchedulerTest1();
		case 9: return new CameraOrbitTest();
		case 10: return new CameraZoomTest();
		case 11: return new ConvertToNode();
	}

	return NULL;
}

CCLayer* nextCocosNodeAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createCocosNodeLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backCocosNodeAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createCocosNodeLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartCocosNodeAction()
{
	CCLayer* pLayer = createCocosNodeLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


TestCocosNodeDemo::TestCocosNodeDemo(void)
{
}

TestCocosNodeDemo::~TestCocosNodeDemo(void)
{
}

std::string TestCocosNodeDemo::title()
{
	return "No title";
}

std::string TestCocosNodeDemo::subtitle()
{
	return "";
}

void TestCocosNodeDemo::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( CCPointMake(s.width/2, s.height-50) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition( CCPointMake(s.width/2, s.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(TestCocosNodeDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1,s_pPathR2, this, menu_selector(TestCocosNodeDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(TestCocosNodeDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( CCPointMake( s.width/2 - 100,30) );
	item2->setPosition( CCPointMake( s.width/2, 30) );
	item3->setPosition( CCPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void TestCocosNodeDemo::restartCallback(CCObject* pSender)
{
	CCScene* s = new CocosNodeTestScene();//CCScene::node();
	s->addChild(restartCocosNodeAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TestCocosNodeDemo::nextCallback(CCObject* pSender)
{
	CCScene* s = new CocosNodeTestScene();//CCScene::node();
	s->addChild( nextCocosNodeAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TestCocosNodeDemo::backCallback(CCObject* pSender)
{
	CCScene* s = new CocosNodeTestScene();//CCScene::node();
	s->addChild( backCocosNodeAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Test2
//
//------------------------------------------------------------------
void Test2::onEnter()
{
	TestCocosNodeDemo::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite *sp2 = CCSprite::spriteWithFile(s_pPathSister2);
	CCSprite *sp3 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite *sp4 = CCSprite::spriteWithFile(s_pPathSister2);
	
	sp1->setPosition(CCPointMake(100, s.height /2 ));
	sp2->setPosition(CCPointMake(380, s.height /2 ));
	addChild(sp1);
	addChild(sp2);
	
	sp3->setScale(0.25f);
	sp4->setScale(0.25f);
	
	sp1->addChild(sp3);
	sp2->addChild(sp4);
	
	CCActionInterval* a1 = CCRotateBy::actionWithDuration(2, 360);
	CCActionInterval* a2 = CCScaleBy::actionWithDuration(2, 2);
	
	CCAction* action1 = CCRepeatForever::actionWithAction(
													(CCActionInterval*)(CCSequence::actions(a1, a2, a2->reverse(), NULL))
												);
	CCAction* action2 = CCRepeatForever::actionWithAction(
													(CCActionInterval*)(CCSequence::actions(
																						(CCActionInterval*)(a1->copy()->autorelease()), 
																						(CCActionInterval*)(a2->copy()->autorelease()), 
																						a2->reverse(), 
																						NULL) )
												);
	
	sp2->setAnchorPoint(CCPointMake(0,0));
	
	sp1->runAction(action1);
	sp2->runAction(action2);
}

std::string Test2::title()
{
	return "anchorPoint and children";
}


//------------------------------------------------------------------
//
// Test4
//
//------------------------------------------------------------------
#define SID_DELAY2		1
#define SID_DELAY4		2

Test4::Test4()
{
	CCSprite *sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite *sp2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	sp1->setPosition( CCPointMake(100,160) );
	sp2->setPosition( CCPointMake(380,160) );
	
	addChild(sp1, 0, 2);
	addChild(sp2, 0, 3);
	
	schedule( schedule_selector(Test4::delay2), 2.0f); 
	schedule( schedule_selector(Test4::delay4), 4.0f); 
}

void Test4::delay2(ccTime dt)
{
	CCSprite* node = (CCSprite*)(getChildByTag(2));
	CCAction* action1 = CCRotateBy::actionWithDuration(1, 360);
	node->runAction(action1);
}

void Test4::delay4(ccTime dt)
{
	unschedule(schedule_selector(Test4::delay4)); 
	removeChildByTag(3, false);
}

std::string Test4::title()
{
	return "tags";
}


//------------------------------------------------------------------
//
// Test5
//
//------------------------------------------------------------------
Test5::Test5()
{
	CCSprite* sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* sp2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	sp1->setPosition(CCPointMake(100,160));
	sp2->setPosition(CCPointMake(380,160));

	CCRotateBy* rot = CCRotateBy::actionWithDuration(2, 360);
	CCActionInterval* rot_back = rot->reverse();
	CCAction* forever = CCRepeatForever::actionWithAction(
													(CCActionInterval*)(CCSequence::actions(rot, rot_back, NULL)) 
												);
	CCAction* forever2 = (CCAction*)(forever->copy()->autorelease());
	forever->setTag(101);
	forever2->setTag(102);
												  
	addChild(sp1, 0, kTagSprite1);
	addChild(sp2, 0, kTagSprite2);
			
	sp1->runAction(forever);
	sp2->runAction(forever2);
	
	schedule( schedule_selector(Test5::addAndRemove), 2.0f);
}

void Test5::addAndRemove(ccTime dt)
{
	CCNode* sp1 = getChildByTag(kTagSprite1);
	CCNode* sp2 = getChildByTag(kTagSprite2);

	sp1->retain();
	sp2->retain();
	
	removeChild(sp1, false);
	removeChild(sp2, true);
	
	addChild(sp1, 0, kTagSprite1);
	addChild(sp2, 0, kTagSprite2);
	
	sp1->release();
	sp2->release();
}

std::string Test5::title()
{
	return "remove and cleanup";
}

//------------------------------------------------------------------
//
// Test6
//
//------------------------------------------------------------------
Test6::Test6()
{
	CCSprite* sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* sp11 = CCSprite::spriteWithFile(s_pPathSister1);

	CCSprite* sp2 = CCSprite::spriteWithFile(s_pPathSister2);
	CCSprite* sp21 = CCSprite::spriteWithFile(s_pPathSister2);
		
	sp1->setPosition(CCPointMake(100,160));
	sp2->setPosition(CCPointMake(380,160));
		
	CCActionInterval* rot = CCRotateBy::actionWithDuration(2, 360);
	CCActionInterval* rot_back = rot->reverse();
	CCAction* forever1 = CCRepeatForever::actionWithAction(
															(CCActionInterval*)(CCSequence::actions(rot, rot_back, NULL)));
	CCAction* forever11 =  (CCAction*)(forever1->copy()->autorelease());

	CCAction* forever2 =  (CCAction*)(forever1->copy()->autorelease());
	CCAction* forever21 =  (CCAction*)(forever1->copy()->autorelease());
	
	addChild(sp1, 0, kTagSprite1);
	sp1->addChild(sp11);
	addChild(sp2, 0, kTagSprite2);
	sp2->addChild(sp21);
	
	sp1->runAction(forever1);
	sp11->runAction(forever11);
	sp2->runAction(forever2);
	sp21->runAction(forever21);
	
	schedule( schedule_selector(Test6::addAndRemove), 2.0f);
}

void Test6::addAndRemove(ccTime dt)
{
	CCNode* sp1 = getChildByTag(kTagSprite1);
	CCNode* sp2 = getChildByTag(kTagSprite2);

	sp1->retain();
	sp2->retain();
	
	removeChild(sp1, false);
	removeChild(sp2, true);
	
	addChild(sp1, 0, kTagSprite1);
	addChild(sp2, 0, kTagSprite2);
	
	sp1->release();
	sp2->release();

}

std::string Test6::title()
{
	return "remove/cleanup with children";
}

//------------------------------------------------------------------
//
// StressTest1
//
//------------------------------------------------------------------
StressTest1::StressTest1()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite *sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	addChild(sp1, 0, kTagSprite1);
	
	sp1->setPosition( CCPointMake(s.width/2, s.height/2) );		

	schedule( schedule_selector(StressTest1::shouldNotCrash), 1.0f);
}

void StressTest1::shouldNotCrash(ccTime dt)
{
	unschedule(schedule_selector(StressTest1::shouldNotCrash));

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	// if the node has timers, it crashes
	CCNode* explosion = CCParticleSun::node();
	((CCParticleSun*)explosion)->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
	
	// if it doesn't, it works Ok.
//	CocosNode *explosion = [Sprite spriteWithFile:@"grossinis_sister2.png");

	explosion->setPosition( CCPointMake(s.width/2, s.height/2) );
	
	runAction( CCSequence::actions(
							CCRotateBy::actionWithDuration(2, 360),
							CCCallFuncN::actionWithTarget(this, callfuncN_selector(StressTest1::removeMe)), 
							NULL) );
	
	addChild(explosion);
}

// remove
void StressTest1::removeMe(CCNode* node)
{	
	m_pParent->removeChild(node, true);
	nextCallback(this);
}


std::string StressTest1::title()
{
	return "stress test #1: no crashes";
}

//------------------------------------------------------------------
//
// StressTest2
//
//------------------------------------------------------------------
StressTest2::StressTest2()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCLayer* sublayer = CCLayer::node();
	
	CCSprite *sp1 = CCSprite::spriteWithFile(s_pPathSister1);
	sp1->setPosition( CCPointMake(80, s.height/2) );
	
	CCActionInterval* move = CCMoveBy::actionWithDuration(3, CCPointMake(350,0));
	CCActionInterval* move_ease_inout3 = CCEaseInOut::actionWithAction((CCActionInterval*)(move->copy()->autorelease()), 2.0f);
	CCActionInterval* move_ease_inout_back3 = move_ease_inout3->reverse();
	CCFiniteTimeAction* seq3 = CCSequence::actions( move_ease_inout3, move_ease_inout_back3, NULL);
	sp1->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)seq3) );
	sublayer->addChild(sp1, 1);

	CCParticleFire* fire = CCParticleFire::node();
	fire->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
	fire->setPosition( CCPointMake(80, s.height/2-50) );
	
	CCActionInterval* copy_seq3 = (CCActionInterval*)(seq3->copy()->autorelease());
	
	fire->runAction( CCRepeatForever::actionWithAction(copy_seq3) );
	sublayer->addChild(fire, 2);
			
	schedule(schedule_selector(StressTest2::shouldNotLeak), 6.0f);
	
	addChild(sublayer, 0, kTagSprite1);
}

void StressTest2::shouldNotLeak(ccTime dt)
{
	unschedule( schedule_selector(StressTest2::shouldNotLeak) );
	CCLayer* sublayer = (CCLayer*)getChildByTag(kTagSprite1);
	sublayer->removeAllChildrenWithCleanup(true); 
}

std::string StressTest2::title()
{
	return "stress test #2: no leaks";
}


//------------------------------------------------------------------
//
// SchedulerTest1
//
//------------------------------------------------------------------
SchedulerTest1::SchedulerTest1()
{
	CCLayer*layer = CCLayer::node();
	//UXLOG("retain count after init is %d", layer->retainCount());                // 1
	
	addChild(layer, 0);
	//UXLOG("retain count after addChild is %d", layer->retainCount());      // 2
	
	layer->schedule( schedule_selector(SchedulerTest1::doSomething) );
	//UXLOG("retain count after schedule is %d", layer->retainCount());      // 3 : (object-c viersion), but win32 version is still 2, because CCTimer class don't save target.
	
	layer->unschedule(schedule_selector(SchedulerTest1::doSomething));
	//UXLOG("retain count after unschedule is %d", layer->retainCount());		// STILL 3!  (win32 is '2')
}

void SchedulerTest1::doSomething(ccTime dt)
{

}

std::string SchedulerTest1::title()
{
	return "cocosnode scheduler test #1";
}

//------------------------------------------------------------------
//
// NodeToWorld
//
//------------------------------------------------------------------
NodeToWorld::NodeToWorld()
{
	//
	// This code tests that nodeToParent works OK:
	//  - It tests different anchor Points
	//  - It tests different children anchor points

	CCSprite *back = CCSprite::spriteWithFile(s_back3);
	addChild( back, -10);
	back->setAnchorPoint( CCPointMake(0,0) );
	CCSize backSize = back->getContentSize();
	
	CCMenuItem *item = CCMenuItemImage::itemFromNormalImage(s_PlayNormal, s_PlaySelect);
	CCMenu *menu = CCMenu::menuWithItems(item, NULL);
	menu->alignItemsVertically();
	menu->setPosition( CCPointMake(backSize.width/2, backSize.height/2));
	back->addChild(menu);
	
	CCActionInterval* rot = CCRotateBy::actionWithDuration(5, 360);
	CCAction* fe = CCRepeatForever::actionWithAction( rot);
	item->runAction( fe );
	
	CCActionInterval* move = CCMoveBy::actionWithDuration(3, CCPointMake(200,0));
	CCActionInterval* move_back = move->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions( move, move_back, NULL);
	CCAction* fe2 = CCRepeatForever::actionWithAction((CCActionInterval*)seq);
	back->runAction(fe2);
}

std::string NodeToWorld::title()
{
	return "nodeToParent transform";
}

//------------------------------------------------------------------
//
// CameraOrbitTest
//
//------------------------------------------------------------------
void CameraOrbitTest::onEnter()
{
	TestCocosNodeDemo::onEnter();
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void CameraOrbitTest::onExit()
{
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	TestCocosNodeDemo::onExit();
}

CameraOrbitTest::CameraOrbitTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite *p = CCSprite::spriteWithFile(s_back3);
	addChild( p, 0);
	p->setPosition( CCPointMake(s.width/2, s.height/2) );
	p->setOpacity( 128 );
	
	CCSprite* sprite;
	CCOrbitCamera* orbit;
	CCCamera* cam;
	CCSize ss;

	// LEFT
    s = p->getContentSize();
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	sprite->setScale(0.5f);
	p->addChild(sprite, 0);		
	sprite->setPosition( CCPointMake(s.width/4*1, s.height/2) );
	cam = sprite->getCamera();
	orbit = CCOrbitCamera::actionWithDuration(2, 1, 0, 0, 360, 0, 0);
	sprite->runAction( CCRepeatForever::actionWithAction( orbit ) );
	
	// CENTER
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	sprite->setScale( 1.0f );
	p->addChild(sprite, 0);		
	sprite->setPosition( CCPointMake(s.width/4*2, s.height/2) );
	orbit = CCOrbitCamera::actionWithDuration(2, 1, 0, 0, 360, 45, 0);
	sprite->runAction( CCRepeatForever::actionWithAction( orbit ) );
	
	
	// RIGHT
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	sprite->setScale( 2.0f );
	p->addChild(sprite, 0);		
	sprite->setPosition( CCPointMake(s.width/4*3, s.height/2) );
	ss = sprite->getContentSize();		
	orbit = CCOrbitCamera::actionWithDuration(2, 1, 0, 0, 360, 90, -45),
	sprite->runAction( CCRepeatForever::actionWithAction(orbit) );
			
	
	// PARENT
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 90);
	p->runAction( CCRepeatForever::actionWithAction( orbit ) );

	setScale( 1 );
}

std::string CameraOrbitTest::title()
{
	return "Camera Orbit test";
}

//------------------------------------------------------------------
//
// CameraZoomTest
//
//------------------------------------------------------------------

void CameraZoomTest::onEnter()
{
	TestCocosNodeDemo::onEnter();
	
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void CameraZoomTest::onExit()
{
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	TestCocosNodeDemo::onExit();
}

CameraZoomTest::CameraZoomTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite *sprite;
	CCCamera *cam;
	
	// LEFT
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild( sprite, 0);		
	sprite->setPosition( CCPointMake(s.width/4*1, s.height/2) );
	cam = sprite->getCamera();
	cam->setEyeXYZ(0, 0, 415);
	
	// CENTER
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild( sprite, 0, 40);
	sprite->setPosition(CCPointMake(s.width/4*2, s.height/2));
//		cam = [sprite camera);
//		[cam setEyeX:0 eyeY:0 eyeZ:415/2);
	
	// RIGHT
	sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild( sprite, 0, 20);
	sprite->setPosition(CCPointMake(s.width/4*3, s.height/2));
//		cam = [sprite camera);
//		[cam setEyeX:0 eyeY:0 eyeZ:-485);
//		[cam setCenterX:0 centerY:0 centerZ:0);

	m_z = 0;
	scheduleUpdate();
}

void CameraZoomTest::update(ccTime dt)
{
	CCNode *sprite;
	CCCamera *cam;
	
	m_z += dt * 100;
	
	sprite = getChildByTag(20);
	cam = sprite->getCamera();
	cam->setEyeXYZ(0, 0, m_z);
	
	sprite = getChildByTag(40);
	cam = sprite->getCamera();
	cam->setEyeXYZ(0, 0, m_z);	
}

std::string CameraZoomTest::title()
{
	return "Camera Zoom test";
}

//------------------------------------------------------------------
//
// CameraCenterTest
//
//------------------------------------------------------------------
CameraCenterTest::CameraCenterTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
			
	CCSprite *sprite;
	CCOrbitCamera *orbit;
	
	// LEFT-TOP
	sprite = new CCSprite();//::node();
    sprite->init();
	addChild( sprite, 0);
	sprite->setPosition(CCPointMake(s.width/5*1, s.height/5*1));
	sprite->setColor(ccRED);
	sprite->setTextureRect(CCRectMake(0, 0, 120, 50));
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0);
	sprite->runAction(CCRepeatForever::actionWithAction( orbit ));
    sprite->release();
//		[sprite setAnchorPoint: CCPointMake(0,1));

	
	
	// LEFT-BOTTOM
	sprite = new CCSprite();//::node();
    sprite->init();
	addChild( sprite, 0, 40);
	sprite->setPosition(CCPointMake(s.width/5*1, s.height/5*4));
	sprite->setColor(ccBLUE);
	sprite->setTextureRect(CCRectMake(0, 0, 120, 50));
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0);
	sprite->runAction(CCRepeatForever::actionWithAction( orbit ));
    sprite->release();
    //		[sprite setAnchorPoint: CCPointMake(0,0));


	// RIGHT-TOP
	sprite = new CCSprite();//::node();
    sprite->init();
	addChild( sprite, 0);	
	sprite->setPosition(CCPointMake(s.width/5*4, s.height/5*1));
	sprite->setColor(ccYELLOW);
	sprite->setTextureRect(CCRectMake(0, 0, 120, 50));
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0);
	sprite->runAction(CCRepeatForever::actionWithAction( orbit) );
    sprite->release();
//		[sprite setAnchorPoint: CCPointMake(1,1));

	
	// RIGHT-BOTTOM
	sprite = new CCSprite();//::node();
    sprite->init();
	addChild( sprite, 0, 40);
	sprite->setPosition(CCPointMake(s.width/5*4, s.height/5*4));
	sprite->setColor(ccGREEN);
	sprite->setTextureRect(CCRectMake(0, 0, 120, 50));
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0);
	sprite->runAction( CCRepeatForever::actionWithAction( orbit ) );
    sprite->release();
//		[sprite setAnchorPoint: CCPointMake(1,0));

	// CENTER
	sprite = new CCSprite();
    sprite->init();
	addChild( sprite, 0, 40);
	sprite->setPosition(CCPointMake(s.width/2, s.height/2));
	sprite->setColor(ccWHITE);
	sprite->setTextureRect(CCRectMake(0, 0, 120, 50));
	orbit = CCOrbitCamera::actionWithDuration(10, 1, 0, 0, 360, 0, 0);
	sprite->runAction(CCRepeatForever::actionWithAction( orbit ) );
    sprite->release();
//		[sprite setAnchorPoint: CCPointMake(0.5f, 0.5f));
}

std::string CameraCenterTest::title()
{
	return "Camera Center test";
}

std::string CameraCenterTest::subtitle()
{
	return "Sprites should rotate at the same speed";
}

//------------------------------------------------------------------
//
// ConvertToNode
//
//------------------------------------------------------------------
ConvertToNode::ConvertToNode()
{
    setIsTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCRotateBy* rotate = CCRotateBy::actionWithDuration(10, 360);
    CCRepeatForever* action = CCRepeatForever::actionWithAction(rotate);
    for(int i = 0; i < 3; i++)
    {
        CCSprite *sprite = CCSprite::spriteWithFile("Images/grossini.png");
        sprite->setPosition(ccp( s.width/4*(i+1), s.height/2));

        CCSprite *point = CCSprite::spriteWithFile("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 10, 100 + i);

        switch(i)
        {
        case 0:
            sprite->setAnchorPoint(CCPointZero);
            break;
        case 1:
            sprite->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(ccp(1,1));
            break;
        }

        point->setPosition(sprite->getPosition());

        CCRepeatForever* copy = (CCRepeatForever*) action->copy();
        copy->autorelease();
        sprite->runAction(copy);
        addChild(sprite, i);
    }
}

void ConvertToNode::ccTouchesEnded(CCSet* touches, CCEvent *event)
{
    for( CCSetIterator it = touches->begin(); it != touches->end(); ++it)
    {
        CCTouch* touch = (CCTouch*)(*it);
        CCPoint location = touch->locationInView(touch->view());

        location = CCDirector::sharedDirector()->convertToGL(location);

        for( int i = 0; i < 3; i++)
        {
            CCNode *node = getChildByTag(100+i);
            CCPoint p1, p2;

            p1 = node->convertToNodeSpaceAR(location);
            p2 = node->convertToNodeSpace(location);

            CCLOG("AR: x=%.2f, y=%.2f -- Not AR: x=%.2f, y=%.2f", p1.x, p1.y, p2.x, p2.y);
        }
    }	
}

std::string ConvertToNode::title()
{
    return "Convert To Node Space";
}

std::string ConvertToNode::subtitle()
{
    return "testing convertToNodeSpace / AR. Touch and see console";
}

void CocosNodeTestScene::runThisTest()
{
    CCLayer* pLayer = nextCocosNodeAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
