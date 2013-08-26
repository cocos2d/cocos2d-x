#include "ArmatureScene.h"
#include "../../testResource.h"


using namespace cocos2d;
using namespace cocos2d::extension;

CCLayer* NextTest();
CCLayer* BackTest();
CCLayer* RestartTest();

static int s_nActionIdx = -1;


CCLayer *CreateLayer(int index)
{
 	CCLayer *pLayer = NULL;
	switch(index)
	{
	case TEST_ASYNCHRONOUS_LOADING:
		pLayer = new TestAsynchronousLoading(); break;
	case TEST_DRAGON_BONES_2_0:
		pLayer = new TestDragonBones20(); break;
	case TEST_COCOSTUDIO_WITH_SKELETON:
		pLayer = new TestCSWithSkeleton(); break;
	case TEST_PERFORMANCE:
		pLayer = new TestPerformance(); break;
	case TEST_CHANGE_ZORDER:
		pLayer = new TestChangeZorder(); break;
	case TEST_ANIMATION_EVENT:
		pLayer = new TestAnimationEvent(); break;
	case  TEST_PARTICLE_DISPLAY:
		pLayer = new TestParticleDisplay(); break;
	case TEST_USE_DIFFERENT_PICTURE:
		pLayer = new TestUseMutiplePicture(); break;
	case TEST_BCOLLIDER_DETECTOR:
		pLayer = new TestColliderDetector(); break;
	case TEST_BOUDINGBOX:
		pLayer = new TestBoundingBox(); break;
	case TEST_ANCHORPOINT:
		pLayer = new TestAnchorPoint(); break;
	case TEST_ARMATURE_NESTING:
		pLayer = new TestArmatureNesting(); break;
	default:
		break;
	}

	return pLayer;
}


CCLayer* NextTest()
{
	++s_nActionIdx;
	s_nActionIdx = s_nActionIdx % TEST_LAYER_COUNT;

	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* BackTest()
{
	--s_nActionIdx;
	if( s_nActionIdx < 0 )
		s_nActionIdx += TEST_LAYER_COUNT;    

	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* RestartTest()
{
	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}


ArmatureTestScene::ArmatureTestScene(bool bPortrait)
{
	TestScene::init();

	CCSprite *bg = CCSprite::create("armature/bg.jpg");
	bg->setPosition(VisibleRect::center());

	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);

	addChild(bg);
}
void ArmatureTestScene::runThisTest()
{


	s_nActionIdx = -1;
	addChild(NextTest());

	CCDirector::sharedDirector()->replaceScene(this);
}
void ArmatureTestScene::MainMenuCallback(CCObject* pSender)
{
	TestScene::MainMenuCallback(pSender);

	removeAllChildren();
	CCArmatureDataManager::purge();
}



void ArmatureTestLayer::onEnter()
{

	CCLayer::onEnter();

	// add title and subtitle
	std::string str = title();
	const char * pTitle = str.c_str();
	CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 18);
	label->setColor(ccc3(0, 0, 0));
	addChild(label, 1, 10000);
	label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Arial", 18);
		l->setColor(ccc3(0, 0, 0));
		addChild(l, 1, 10001);
		l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
	}    

	// add menu
	backItem = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ArmatureTestLayer::backCallback) );
	restartItem = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ArmatureTestLayer::restartCallback) );
	nextItem = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ArmatureTestLayer::nextCallback) );

	CCMenu *menu = CCMenu::create(backItem, restartItem, nextItem, NULL);

	menu->setPosition(CCPointZero);
	backItem->setPosition(ccp(VisibleRect::center().x - restartItem->getContentSize().width*2, VisibleRect::bottom().y+restartItem->getContentSize().height/2));
	restartItem->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+restartItem->getContentSize().height/2));
	nextItem->setPosition(ccp(VisibleRect::center().x + restartItem->getContentSize().width*2, VisibleRect::bottom().y+restartItem->getContentSize().height/2));

	addChild(menu, 100);

	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

}
void ArmatureTestLayer::onExit()
{
	removeAllChildren();

	backItem = restartItem = nextItem = NULL;
}

std::string ArmatureTestLayer::title()
{
	return "CSArmature Test Bed";
}
std::string ArmatureTestLayer::subtitle()
{
	return "";
}

void ArmatureTestLayer::restartCallback(CCObject* pSender)
{
	CCScene* s = new ArmatureTestScene();
	s->addChild( RestartTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::nextCallback(CCObject* pSender)
{
	CCScene* s = new ArmatureTestScene();
	s->addChild( NextTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::backCallback(CCObject* pSender)
{
	CCScene* s = new ArmatureTestScene();
	s->addChild( BackTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::draw()
{
	CCLayer::draw();
}


void TestAsynchronousLoading::onEnter()
{
	ArmatureTestLayer::onEnter();

	backItem->setEnabled(false);
	restartItem->setEnabled(false);
	nextItem->setEnabled(false);

	char pszPercent[255];
	sprintf(pszPercent, "%s %f", subtitle().c_str(), 0.0f);
	CCLabelTTF *label = (CCLabelTTF*)getChildByTag(10001);
	label->setString(pszPercent);


	//! create a new thread to load data
 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/knight.png", "armature/knight.plist", "armature/knight.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/robot.png", "armature/robot.plist", "armature/robot.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/Cowboy.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));

	//! load data directly
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml");
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml");
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/robot.png", "armature/robot.plist", "armature/robot.xml");
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml");
// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml");
//	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Cowboy.ExportJson");

}

std::string TestAsynchronousLoading::title()
{
	return "Test Asynchronous Loading";
}
std::string TestAsynchronousLoading::subtitle()
{
	return "current percent : ";
}
void TestAsynchronousLoading::dataLoaded(float percent)
{
	CCLabelTTF *label = (CCLabelTTF*)getChildByTag(10001);
	if (label)
	{
		char pszPercent[255];
		sprintf(pszPercent, "%s %f", subtitle().c_str(), percent * 100);
		label->setString(pszPercent);
	}

	if (percent >= 1 && backItem && restartItem && nextItem)
	{
		backItem->setEnabled(true);
		restartItem->setEnabled(true);
		nextItem->setEnabled(true);
	}
}



void TestCSWithSkeleton::onEnter()
{
	ArmatureTestLayer::onEnter();
	cocos2d::extension::CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.2f);

	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
	addChild(armature);
}

std::string TestCSWithSkeleton::title()
{
	return "Test Export From CocoStudio With Skeleton Effect";
}




void TestDragonBones20::onEnter()
{
	ArmatureTestLayer::onEnter();

	cocos2d::extension::CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("Dragon");
	armature->getAnimation()->playByIndex(1);
	armature->getAnimation()->setSpeedScale(0.4f);
	armature->setPosition(VisibleRect::center().x, VisibleRect::center().y * 0.3f);
	armature->setScale(0.6f);
    addChild(armature);
}

std::string TestDragonBones20::title()
{
	return "Test Export From DragonBones version 2.0";
}



TestPerformance::~TestPerformance()
{
}
void TestPerformance::onEnter()
{
	ArmatureTestLayer::onEnter();

	armatureCount = frames = times = lastTimes = 0;
	generated = false;

	scheduleUpdate();
}

std::string TestPerformance::title()
{
	return "Test Performance";
}
std::string TestPerformance::subtitle()
{
	return "Current CCArmature Count : ";
}
void TestPerformance::addArmature(cocos2d::extension::CCArmature *armature)
{
	armatureCount++;
	addChild(armature, armatureCount);
}
void TestPerformance::update(float delta)
{
	frames ++;
	times += delta;

	if (frames/times > 58)
	{
		cocos2d::extension::CCArmature *armature = NULL;
		armature = new cocos2d::extension::CCArmature();
		armature->init("Knight_f/Knight");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(50 + armatureCount * 2, 150);
    	armature->setScale(0.6f);
		addArmature(armature);
		armature->release();

		char pszCount[255];
		sprintf(pszCount, "%s %i", subtitle().c_str(), armatureCount);
		CCLabelTTF *label = (CCLabelTTF*)getChildByTag(10001);
		label->setString(pszCount);
	}
}






void TestChangeZorder::onEnter()
{
	ArmatureTestLayer::onEnter();

	cocos2d::extension::CCArmature *armature = NULL;
	currentTag = -1;

	armature = cocos2d::extension::CCArmature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	++currentTag;
	armature->setScale(0.6f);
	addChild(armature, currentTag, currentTag);

	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.24f);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	++currentTag;
	addChild(armature, currentTag, currentTag);

	armature = cocos2d::extension::CCArmature::create("Dragon");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::center().x , VisibleRect::center().y-100));
	++currentTag;
	armature->setScale(0.6f);
	addChild(armature, currentTag, currentTag);

	schedule( schedule_selector(TestChangeZorder::changeZorder), 1);      

	currentTag = 0;
}
std::string TestChangeZorder::title()
{
	return "Test Change ZOrder Of Different CCArmature";
}
void TestChangeZorder::changeZorder(float dt)
{
	
	CCNode *node = getChildByTag(currentTag);

	node->setZOrder(CCRANDOM_0_1() * 3);

	currentTag ++;
	currentTag = currentTag % 3;
}




void TestAnimationEvent::onEnter()
{
	ArmatureTestLayer::onEnter();
	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->setScaleX(-0.24f);
	armature->setScaleY(0.24f);
	armature->setPosition(ccp(VisibleRect::left().x + 50, VisibleRect::left().y));

	/*
	* Set armature's movement event callback function
	* To disconnect this event, just setMovementEventCallFunc(NULL, NULL);
	*/
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(TestAnimationEvent::animationEvent));
	addChild(armature);
}
std::string TestAnimationEvent::title()
{
	return "Test CCArmature Animation Event";
}
void TestAnimationEvent::animationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Fire") == 0)
		{
			CCActionInterval *actionToRight = CCMoveTo::create(2, ccp(VisibleRect::right().x - 50, VisibleRect::right().y));
			armature->stopAllActions();
			armature->runAction(CCSequence::create(actionToRight,  CCCallFunc::create(this, callfunc_selector(TestAnimationEvent::callback1)), NULL));
			armature->getAnimation()->play("Walk");
		}
		else if (id.compare("FireMax") == 0)
		{
			CCActionInterval *actionToLeft = CCMoveTo::create(2, ccp(VisibleRect::left().x + 50, VisibleRect::left().y));
			armature->stopAllActions();
			armature->runAction(CCSequence::create(actionToLeft,  CCCallFunc::create(this, callfunc_selector(TestAnimationEvent::callback2)), NULL));
			armature->getAnimation()->play("Walk");
		}
	}
}
void TestAnimationEvent::callback1()
{
	armature->runAction(CCScaleTo::create(0.3f, 0.3f, 0.3f));
	armature->getAnimation()->play("FireMax", 10);
}
void TestAnimationEvent::callback2()
{
	armature->runAction(CCScaleTo::create(0.3f, -0.3f, 0.3f));
	armature->getAnimation()->play("Fire", 10);
}




void TestParticleDisplay::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	animationID = 0;

	armature = cocos2d::extension::CCArmature::create("robot");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
	armature->setScale(0.48f);
	armature->getAnimation()->setSpeedScale(0.5f);
	addChild(armature);


	CCParticleSystem *p1 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
	CCParticleSystem *p2 = CCParticleSystemQuad::create("Particles/SmallSun.plist");

	cocos2d::extension::CCBone *bone  = cocos2d::extension::CCBone::create("p1");
	bone->addDisplay(p1, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	armature->addBone(bone, "bady-a3");
	
	bone  = cocos2d::extension::CCBone::create("p2");
	bone->addDisplay(p2, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	armature->addBone(bone, "bady-a30");
}
void TestParticleDisplay::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	ArmatureTestLayer::onExit();
}
std::string TestParticleDisplay::title()
{
	return "Test Particle Display";
}
std::string TestParticleDisplay::subtitle()
{
	return "Touch to change animation";
}
bool TestParticleDisplay::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	++animationID;
	animationID = animationID % armature->getAnimation()->getMovementCount();
	armature->getAnimation()->playByIndex(animationID);
	return false;
}

void TestParticleDisplay::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}




void TestUseMutiplePicture::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	displayIndex = 0;

	armature = cocos2d::extension::CCArmature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::left().y));
	armature->setScale(1.2f);
	addChild(armature);

	std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};

	for (int i = 0; i < 7; i++)
	{
		CCSkin *skin = CCSkin::createWithSpriteFrameName(weapon[i].c_str());
	 	armature->getBone("weapon")->addDisplay(skin, i);
	}

// 	CCSpriteDisplayData displayData;
// 	for (int i = 0; i < 7; i++)
// 	{
// 		displayData.setParam(weapon[i].c_str());
// 		armature->getBone("weapon")->addDisplay(&displayData, i);
// 	}

	CCLabelTTF* l = CCLabelTTF::create("This is a weapon!", "Arial", 18);
	l->setAnchorPoint(ccp(0.2f, 0.5f));
	armature->getBone("weapon")->addDisplay(l, 7);
}
void TestUseMutiplePicture::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	ArmatureTestLayer::onExit();
}
std::string TestUseMutiplePicture::title()
{
	return "Test One CCArmature Use Different Picture";
}
std::string TestUseMutiplePicture::subtitle()
{
	return "weapon and armature are in different picture";
}
bool TestUseMutiplePicture::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	++displayIndex;
	displayIndex = (displayIndex) % 8;
	armature->getBone("weapon")->changeDisplayByIndex(displayIndex, true);
	return false;
}
void TestUseMutiplePicture::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}





TestColliderDetector::~TestColliderDetector()
{
}
void TestColliderDetector::onEnter()
{
	ArmatureTestLayer::onEnter();

	scheduleUpdate();

	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->play("FireWithoutBullet");
	armature->getAnimation()->setSpeedScale(0.2f);
	armature->setScaleX(-0.2f);
	armature->setScaleY(0.2f);
	armature->setPosition(ccp(VisibleRect::left().x + 70, VisibleRect::left().y));

	/*
	* Set armature's frame event callback function
	* To disconnect this event, just setFrameEventCallFunc(NULL, NULL);
	*/
	armature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(TestColliderDetector::onFrameEvent));

	addChild(armature);

	armature2 = cocos2d::extension::CCArmature::create("Cowboy");
	armature2->getAnimation()->play("Walk");
	armature2->setScaleX(-0.2f);
	armature2->setScaleY(0.2f);
	armature2->setPosition(ccp(VisibleRect::right().x - 60, VisibleRect::left().y));
	addChild(armature2);
	
	bullet = CCPhysicsSprite::createWithSpriteFrameName("25.png");
	addChild(bullet);

	initWorld();
}
std::string TestColliderDetector::title()
{
	return "Test Collider Detector";
}
void TestColliderDetector::onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt, currentFrameIndex);

	/*
	* originFrameIndex is the frame index editted in Action Editor
	* currentFrameIndex is the current index animation played to 
	* frame event may be delay emit, so originFrameIndex may be different from currentFrameIndex.
	*/

	CCPoint p = armature->getBone("Layer126")->getDisplayRenderNode()->convertToWorldSpaceAR(ccp(0, 0));
	bullet->setPosition(ccp(p.x + 60, p.y));

	bullet->stopAllActions();
	bullet->runAction(CCMoveBy::create(1.5f, ccp(350, 0)));
}



#if ENABLE_PHYSICS_BOX2D_DETECT

class Contact
{
public:
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;
};

class ContactListener : public b2ContactListener
{
	//! Callbacks for derived classes.
	virtual void BeginContact(b2Contact *contact)
	{
		if (contact)
		{
			Contact c;
			c.fixtureA = contact->GetFixtureA();
			c.fixtureB = contact->GetFixtureB();

			contact_list.push_back(c);
		}
		B2_NOT_USED(contact);
	}
	virtual void EndContact(b2Contact *contact)
	{
		contact_list.clear();
		B2_NOT_USED(contact);
	}
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}
	virtual void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<Contact> contact_list;
};


void TestColliderDetector::onExit()
{
	CC_SAFE_DELETE(world);
	CC_SAFE_DELETE(listener);
	CC_SAFE_DELETE(debugDraw);

	ArmatureTestLayer::onExit();
}
void TestColliderDetector::draw()
{
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
}
void TestColliderDetector::update(float delta)
{
	armature2->setVisible(true);

	world->Step(delta, 0, 0);

	for (std::list<Contact>::iterator it = listener->contact_list.begin(); it != listener->contact_list.end(); ++it)
	{
		Contact &contact = *it;

		CCBone *ba = (CCBone *)contact.fixtureA->GetUserData();
		CCBone *bb = (CCBone *)contact.fixtureB->GetUserData();

		bb->getArmature()->setVisible(false);
	}
}
void TestColliderDetector::initWorld()
{
	b2Vec2 noGravity(0, 0);

	world = new b2World(noGravity);
	world->SetAllowSleeping(true);

	listener = new ContactListener();
	world->SetContactListener(listener);

	debugDraw = new GLESDebugDraw( PT_RATIO );
	world->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//        flags += b2Draw::e_jointBit;
	//        flags += b2Draw::e_aabbBit;
	//        flags += b2Draw::e_pairBit;
	//        flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);


	// Define the dynamic body.
	//Set up a 1m squared box in the physics world
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	b2Body *body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;   
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);    


	bullet->setB2Body(body);
	bullet->setPTMRatio(PT_RATIO);
	bullet->setPosition( ccp( -100, -100) );

	body = world->CreateBody(&bodyDef);
	armature2->setB2Body(body);
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT

enum ColliderType
{
	eBulletTag,
	eEnemyTag
};


int TestColliderDetector::beginHit(cpArbiter *arb, cpSpace *space, void *unused)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);

	CCBone *bone = (CCBone*)a->data;
	bone->getArmature()->setVisible(false);

	return 0;
}

void TestColliderDetector::endHit(cpArbiter *arb, cpSpace *space, void *unused)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);

	CCBone *bone = (CCBone*)a->data;
	bone->getArmature()->setVisible(true);
}

void TestColliderDetector::destroyCPBody(cpBody *body)
{
	cpShape *shape = body->shapeList_private;
	while(shape)
	{
		cpShape *temp = shape->next_private;

		cpSpaceRemoveShape(space, shape);
		cpShapeFree(shape);

		shape = temp;
	}

	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);
}

void TestColliderDetector::onExit()
{
	destroyCPBody(armature2->getCPBody());
	destroyCPBody(bullet->getCPBody());

	cpSpaceFree(space);

	ArmatureTestLayer::onExit();
}

void TestColliderDetector::update(float delta)
{
	cpSpaceStep(space, delta);
}
void TestColliderDetector::initWorld()
{
	space = cpSpaceNew();
	space->gravity = cpv(0, 0);

	// Physics debug layer
	CCPhysicsDebugNode *debugLayer = CCPhysicsDebugNode::create(space);
	this->addChild(debugLayer, INT_MAX);

	CCSize size = bullet->getContentSize();

	int num = 4;
	cpVect verts[] = {
		cpv(-size.width/2,-size.height/2),
		cpv(-size.width/2,size.height/2),
		cpv(size.width/2,size.height/2),
		cpv(size.width/2,-size.height/2),
	};

	cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
	cpSpaceAddBody(space, body);

	cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
	shape->collision_type = eBulletTag;
	cpSpaceAddShape(space, shape);

	bullet->setCPBody(body);

	body = cpBodyNew(INFINITY, INFINITY);
	cpSpaceAddBody(space, body);
	armature2->setCPBody(body);

	shape = body->shapeList_private;
	while(shape){
		cpShape *next = shape->next_private;
		shape->collision_type = eEnemyTag;
		shape = next;
	}

	cpSpaceAddCollisionHandler(space, eEnemyTag, eBulletTag, beginHit, NULL, NULL, endHit, NULL);
}
#endif





void TestBoundingBox::onEnter()
{
	ArmatureTestLayer::onEnter();

	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
   	armature->setScale(0.2f); 
	addChild(armature);

	CCSprite *sprite = CCSprite::create("Images/background3.png");
	armature->addChild(sprite);
}
std::string TestBoundingBox::title()
{
	return "Test BoundingBox";
}
void TestBoundingBox::draw()
{
	CC_NODE_DRAW_SETUP();

	rect = CCRectApplyAffineTransform(armature->boundingBox(), armature->nodeToParentTransform());
	
	ccDrawColor4B(100, 100, 100, 255);
	ccDrawRect(rect.origin, ccp(rect.getMaxX(), rect.getMaxY()));
}



void TestAnchorPoint::onEnter()
{
	ArmatureTestLayer::onEnter();

	for (int i = 0; i<5; i++)
	{
		cocos2d::extension::CCArmature *armature = cocos2d::extension::CCArmature::create("Cowboy");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(VisibleRect::center());
    	armature->setScale(0.2f);
		addChild(armature, 0, i);
	}

	getChildByTag(0)->setAnchorPoint(ccp(0,0));
	getChildByTag(1)->setAnchorPoint(ccp(0,1));
	getChildByTag(2)->setAnchorPoint(ccp(1,0));
	getChildByTag(3)->setAnchorPoint(ccp(1,1));
	getChildByTag(4)->setAnchorPoint(ccp(0.5,0.5));

}
std::string TestAnchorPoint::title()
{
	return "Test Set AnchorPoint";
}


void TestArmatureNesting::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	armature = cocos2d::extension::CCArmature::create("cyborg");
	armature->getAnimation()->playByIndex(1);
	armature->setPosition(VisibleRect::center());
	armature->setScale(1.2f);
	armature->getAnimation()->setSpeedScale(0.4f);
	addChild(armature);

	weaponIndex = 0;
}
void TestArmatureNesting::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	ArmatureTestLayer::onExit();
}
std::string TestArmatureNesting::title()
{
	return "Test CCArmature Nesting";
}
bool TestArmatureNesting::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	++weaponIndex;
	weaponIndex = weaponIndex % 4;

	if(armature != NULL)
	{
		armature->getBone("armInside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
		armature->getBone("armOutside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	}

	return false;
}
void TestArmatureNesting::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}