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
	case TEST_DRAGON_BONES_2_0:
		pLayer = new TestDragonBones20(); break;
	case TEST_COCOSTUDIO_WITH_SKELETON:
		pLayer = new TestCSWithSkeleton(); break;
	case TEST_COCOSTUDIO_WITHOUT_SKELETON:
		pLayer = new TestCSWithoutSkeleton(); break;
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
	case TEST_BOX2D_DETECTOR:
		pLayer = new TestBox2DDetector(); break;
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
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/TestBone0.png", "armature/TestBone0.plist", "armature/TestBone.json");
 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Cowboy0.png", "armature/Cowboy0.plist", "armature/Cowboy.json");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/robot.png", "armature/robot.plist", "armature/robot.xml");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml");

	s_nActionIdx = -1;
	addChild(NextTest());

	CCDirector::sharedDirector()->replaceScene(this);
}
void ArmatureTestScene::MainMenuCallback(CCObject* pSender)
{
	TestScene::MainMenuCallback(pSender);

	removeAllChildren();
	CCArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
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
	CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ArmatureTestLayer::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ArmatureTestLayer::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ArmatureTestLayer::nextCallback) );

	CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

	menu->setPosition(CCPointZero);
	item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

	addChild(menu, 100);

	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

}
void ArmatureTestLayer::onExit()
{
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



void TestDragonBones20::onEnter()
{
	ArmatureTestLayer::onEnter();

	cocos2d::extension::CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("Dragon");
	armature->getAnimation()->playByIndex(1);
	armature->getAnimation()->setAnimationScale(0.4f);
	armature->setPosition(VisibleRect::center().x, VisibleRect::center().y * 0.3f);
	armature->setScale(0.6f);
    addChild(armature);
}

std::string TestDragonBones20::title()
{
	return "Test Export From DragonBones version 2.0";
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



void TestCSWithoutSkeleton::onEnter()
{
	ArmatureTestLayer::onEnter();
	cocos2d::extension::CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("TestBone");
	armature->getAnimation()->playByIndex(0);
    armature->setAnchorPoint(ccp(0.5, -0.1));
	armature->setScale(0.2f);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	addChild(armature);
}

std::string TestCSWithoutSkeleton::title()
{
	return "Test Export From CocoStudio Without Skeleton Effect";
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

	armature = cocos2d::extension::CCArmature::create("TestBone");
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
	armature->getAnimation()->MovementEventSignal.connect(this, &TestAnimationEvent::animationEvent);
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
	addChild(armature);

	CCParticleDisplayData displayData;
	displayData.setParam("Particles/SmallSun.plist");

	cocos2d::extension::CCBone *bone  = cocos2d::extension::CCBone::create("p1");
	bone->addDisplay(&displayData, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	armature->addBone(bone, "bady-a3");
	
	bone  = cocos2d::extension::CCBone::create("p2");
	bone->addDisplay(&displayData, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	armature->addBone(bone, "bady-a30");
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
	armature->setPosition(ccp(VisibleRect::left().x+70, VisibleRect::left().y));
	armature->setScale(1.2f);
	addChild(armature);

	std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};

	CCSpriteDisplayData displayData;
	for (int i = 0; i < 7; i++)
	{
		displayData.setParam(weapon[i].c_str());
		armature->getBone("weapon")->addDisplay(&displayData, i);
	}
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
	displayIndex = (displayIndex) % 6;
	armature->getBone("weapon")->changeDisplayByIndex(displayIndex, true);
	return false;
}
void TestUseMutiplePicture::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}



void TestBox2DDetector::onEnter()
{
	ArmatureTestLayer::onEnter();

	scheduleUpdate();

	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->getAnimation()->setAnimationScale(0.1f);
	armature->setScaleX(-0.2f);
	armature->setScaleY(0.2f);
	armature->setPosition(ccp(VisibleRect::left().x + 70, VisibleRect::left().y));
	addChild(armature);

	armature2 = cocos2d::extension::CCArmature::create("Cowboy");
	armature2->getAnimation()->play("Walk");
	armature2->setScaleX(-0.2f);
	armature2->setScaleY(0.2f);
	armature2->setPosition(ccp(VisibleRect::right().x - 30, VisibleRect::left().y));
	addChild(armature2);

	CCPhysicsWorld::sharedPhysicsWorld()->BoneColliderSignal.connect(this, &TestBox2DDetector::onHit);
}
std::string TestBox2DDetector::title()
{
	return "Test Box2D Detector";
}
void TestBox2DDetector::draw()
{
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

	CCPhysicsWorld::sharedPhysicsWorld()->drawDebug();

	kmGLPopMatrix();
	
}
void TestBox2DDetector::update(float delta)
{
	armature2->setVisible(true);
	CCPhysicsWorld::sharedPhysicsWorld()->update(delta);
}
void TestBox2DDetector::onHit(cocos2d::extension::CCBone *bone, cocos2d::extension::CCBone *bone2)
{
	armature2->setVisible(false);
}




void TestBoundingBox::onEnter()
{
	ArmatureTestLayer::onEnter();

	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
   	armature->setScale(0.2f); 
	addChild(armature);
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
	armature->getAnimation()->setAnimationScale(0.4f);
	addChild(armature);

	weaponIndex = 0;
}
std::string TestArmatureNesting::title()
{
	return "Test CCArmature Nesting";
}
bool TestArmatureNesting::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	++weaponIndex;
	weaponIndex = weaponIndex % 4;

	armature->getBone("armInside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	armature->getBone("armOutside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	return false;
}
void TestArmatureNesting::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}