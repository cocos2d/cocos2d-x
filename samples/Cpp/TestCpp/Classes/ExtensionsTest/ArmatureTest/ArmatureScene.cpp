#include "ArmatureScene.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocos2d::extension::armature;

Layer* NextTest();
Layer* BackTest();
Layer* RestartTest();

static int s_nActionIdx = -1;


Layer *CreateLayer(int index)
{
 	Layer *layer = NULL;
	switch(index)
	{
	case TEST_DRAGON_BONES_2_0:
		layer = new TestDragonBones20(); break;
	case TEST_COCOSTUDIO_WITH_SKELETON:
		layer = new TestCSWithSkeleton(); break;
	case TEST_COCOSTUDIO_WITHOUT_SKELETON:
		layer = new TestCSWithoutSkeleton(); break;
	case TEST_PERFORMANCE:
		layer = new TestPerformance(); break;
	case TEST_CHANGE_ZORDER:
		layer = new TestChangeZorder(); break;
	case TEST_ANIMATION_EVENT:
		layer = new TestAnimationEvent(); break;
	case  TEST_PARTICLE_DISPLAY:
		layer = new TestParticleDisplay(); break;
	case TEST_USE_DIFFERENT_PICTURE:
		layer = new TestUseMutiplePicture(); break;
	case TEST_BOX2D_DETECTOR:
		layer = new TestBox2DDetector(); break;
	case TEST_BOUDINGBOX:
		layer = new TestBoundingBox(); break;
	case TEST_ANCHORPOINT:
		layer = new TestAnchorPoint(); break;
	case TEST_ARMATURE_NESTING:
		layer = new TestArmatureNesting(); break;
	default:
		break;
	}

	return layer;
}


Layer* NextTest()
{
	++s_nActionIdx;
	s_nActionIdx = s_nActionIdx % TEST_LAYER_COUNT;

	Layer* layer = CreateLayer(s_nActionIdx);
	layer->autorelease();

	return layer;
}

Layer* BackTest()
{
	--s_nActionIdx;
	if( s_nActionIdx < 0 )
		s_nActionIdx += TEST_LAYER_COUNT;    

	Layer* layer = CreateLayer(s_nActionIdx);
	layer->autorelease();

	return layer;
}

Layer* RestartTest()
{
	Layer* layer = CreateLayer(s_nActionIdx);
	layer->autorelease();

	return layer;
}


ArmatureTestScene::ArmatureTestScene(bool bPortrait)
{
	TestScene::init();

	Sprite *bg = Sprite::create("armature/bg.jpg");
	bg->setPosition(VisibleRect::center());

	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);

	addChild(bg);
}
void ArmatureTestScene::runThisTest()
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/TestBone0.png", "armature/TestBone0.plist", "armature/TestBone.json");
 	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Cowboy0.png", "armature/Cowboy0.plist", "armature/Cowboy.json");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/robot.png", "armature/robot.plist", "armature/robot.xml");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml");

	s_nActionIdx = -1;
	addChild(NextTest());

	Director::getInstance()->replaceScene(this);
}
void ArmatureTestScene::MainMenuCallback(Object* sender)
{
	removeAllChildren();
	ArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
}



void ArmatureTestLayer::onEnter()
{

	Layer::onEnter();

	// add title and subtitle
	std::string str = title();
	const char * pTitle = str.c_str();
	LabelTTF* label = LabelTTF::create(pTitle, "Arial", 18);
	label->setColor(Color3B(0, 0, 0));
	addChild(label, 1, 10000);
	label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		LabelTTF* l = LabelTTF::create(strSubtitle.c_str(), "Arial", 18);
		l->setColor(Color3B(0, 0, 0));
		addChild(l, 1, 10001);
		l->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 60) );
	}    

	// add menu
	MenuItemImage *item1 = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ArmatureTestLayer::backCallback,this));
	MenuItemImage *item2 = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ArmatureTestLayer::restartCallback, this));
	MenuItemImage *item3 = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ArmatureTestLayer::nextCallback, this));

	Menu *menu = Menu::create(item1, item2, item3, NULL);

	menu->setPosition(Point::ZERO);
	item1->setPosition(Point(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item2->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item3->setPosition(Point(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

	addChild(menu, 100);

	setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

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

void ArmatureTestLayer::restartCallback(Object* sender)
{
	Scene* s = new ArmatureTestScene();
	s->addChild( RestartTest() );
	Director::getInstance()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::nextCallback(Object* sender)
{
	Scene* s = new ArmatureTestScene();
	s->addChild( NextTest() );
	Director::getInstance()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::backCallback(Object* sender)
{
	Scene* s = new ArmatureTestScene();
	s->addChild( BackTest() );
	Director::getInstance()->replaceScene(s);
	s->release();
}
void ArmatureTestLayer::draw()
{
	Layer::draw();
}



void TestDragonBones20::onEnter()
{
	ArmatureTestLayer::onEnter();

	Armature *armature = NULL;
	armature = Armature::create("Dragon");
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
	Armature *armature = NULL;
	armature = Armature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.2f);
	armature->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
	addChild(armature);
}

std::string TestCSWithSkeleton::title()
{
	return "Test Export From CocoStudio With Skeleton Effect";
}



void TestCSWithoutSkeleton::onEnter()
{
	ArmatureTestLayer::onEnter();
	Armature *armature = NULL;
	armature = Armature::create("TestBone");
	armature->getAnimation()->playByIndex(0);
    armature->setAnchorPoint(Point(0.5f, -0.1f));
	armature->setScale(0.2f);
	armature->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y-100));
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
	return "Current Armature Count : ";
}
void TestPerformance::addArmature(Armature *armature)
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
		Armature *armature = NULL;
		armature = new Armature();
		armature->init("Knight_f/Knight");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(50 + armatureCount * 2, 150);
    	armature->setScale(0.6f);
		addArmature(armature);
		armature->release();

		char pszCount[255];
		sprintf(pszCount, "%s %i", subtitle().c_str(), armatureCount);
		LabelTTF *label = (LabelTTF*)getChildByTag(10001);
		label->setString(pszCount);
	}
}






void TestChangeZorder::onEnter()
{
	ArmatureTestLayer::onEnter();

	Armature *armature = NULL;
	currentTag = -1;

	armature = Armature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y-100));
	++currentTag;
	armature->setScale(0.6f);
	addChild(armature, currentTag, currentTag);

	armature = Armature::create("TestBone");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.24f);
	armature->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y-100));
	++currentTag;
	addChild(armature, currentTag, currentTag);

	armature = Armature::create("Dragon");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(Point(VisibleRect::center().x , VisibleRect::center().y-100));
	++currentTag;
	armature->setScale(0.6f);
	addChild(armature, currentTag, currentTag);

	schedule( schedule_selector(TestChangeZorder::changeZorder), 1);      

	currentTag = 0;
}
std::string TestChangeZorder::title()
{
	return "Test Change ZOrder Of Different Armature";
}
void TestChangeZorder::changeZorder(float dt)
{
	
	Node *node = getChildByTag(currentTag);

	node->setZOrder(CCRANDOM_0_1() * 3);

	currentTag ++;
	currentTag = currentTag % 3;
}




void TestAnimationEvent::onEnter()
{
	ArmatureTestLayer::onEnter();
	armature = Armature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->setScaleX(-0.24f);
	armature->setScaleY(0.24f);
	armature->setPosition(Point(VisibleRect::left().x + 50, VisibleRect::left().y));
	armature->getAnimation()->MovementEventSignal.connect(this, &TestAnimationEvent::animationEvent);
	addChild(armature);
}
std::string TestAnimationEvent::title()
{
	return "Test Armature Animation Event";
}
void TestAnimationEvent::animationEvent(Armature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Fire") == 0)
		{
			ActionInterval *actionToRight = MoveTo::create(2, Point(VisibleRect::right().x - 50, VisibleRect::right().y));
			armature->stopAllActions();
			armature->runAction(Sequence::create(actionToRight,  CallFunc::create(CC_CALLBACK_0(TestAnimationEvent::callback1,this)), NULL));
			armature->getAnimation()->play("Walk");
		}
		else if (id.compare("FireMax") == 0)
		{
			ActionInterval *actionToLeft = MoveTo::create(2, Point(VisibleRect::left().x + 50, VisibleRect::left().y));
			armature->stopAllActions();
			armature->runAction(Sequence::create(actionToLeft,  CallFunc::create(CC_CALLBACK_0(TestAnimationEvent::callback2,this)), NULL));
			armature->getAnimation()->play("Walk");
		}
	}
}
void TestAnimationEvent::callback1()
{
	armature->runAction(ScaleTo::create(0.3f, 0.3f, 0.3f));
	armature->getAnimation()->play("FireMax", 10);
}
void TestAnimationEvent::callback2()
{
	armature->runAction(ScaleTo::create(0.3f, -0.3f, 0.3f));
	armature->getAnimation()->play("Fire", 10);
}




void TestParticleDisplay::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	animationID = 0;

	armature = Armature::create("robot");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
	armature->setScale(0.48f);
	addChild(armature);

	ParticleDisplayData displayData;
	displayData.setParam("Particles/SmallSun.plist");

	Bone *bone  = Bone::create("p1");
	bone->addDisplay(&displayData, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	armature->addBone(bone, "bady-a3");
	
	bone  = Bone::create("p2");
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
bool TestParticleDisplay::ccTouchBegan(Touch  *touch, Event  *event)
{
	++animationID;
	animationID = animationID % armature->getAnimation()->getMovementCount();
	armature->getAnimation()->playByIndex(animationID);
	return false;
}

void TestParticleDisplay::registerWithTouchDispatcher()
{
	Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}




void TestUseMutiplePicture::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	displayIndex = 0;

	armature = Armature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(Point(VisibleRect::left().x+70, VisibleRect::left().y));
	armature->setScale(1.2f);
	addChild(armature);

	std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};

	SpriteDisplayData displayData;
	for (int i = 0; i < 7; i++)
	{
		displayData.setParam(weapon[i].c_str());
		armature->getBone("weapon")->addDisplay(&displayData, i);
	}
}
std::string TestUseMutiplePicture::title()
{
	return "Test One Armature Use Different Picture";
}
std::string TestUseMutiplePicture::subtitle()
{
	return "weapon and armature are in different picture";
}
bool TestUseMutiplePicture::ccTouchBegan(Touch  *touch, Event  *event)
{
	++displayIndex;
	displayIndex = (displayIndex) % 6;
	armature->getBone("weapon")->changeDisplayByIndex(displayIndex, true);
	return false;
}
void TestUseMutiplePicture::registerWithTouchDispatcher()
{
	Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}



void TestBox2DDetector::onEnter()
{
	ArmatureTestLayer::onEnter();

	scheduleUpdate();

	armature = Armature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->getAnimation()->setAnimationScale(0.1f);
	armature->setScaleX(-0.2f);
	armature->setScaleY(0.2f);
	armature->setPosition(Point(VisibleRect::left().x + 70, VisibleRect::left().y));
	addChild(armature);

	armature2 = Armature::create("Cowboy");
	armature2->getAnimation()->play("Walk");
	armature2->setScaleX(-0.2f);
	armature2->setScaleY(0.2f);
	armature2->setPosition(Point(VisibleRect::right().x - 30, VisibleRect::left().y));
	addChild(armature2);

	PhysicsWorld::sharedPhysicsWorld()->BoneColliderSignal.connect(this, &TestBox2DDetector::onHit);
}
std::string TestBox2DDetector::title()
{
	return "Test Box2D Detector";
}
void TestBox2DDetector::draw()
{
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

	kmGLPushMatrix();

	PhysicsWorld::sharedPhysicsWorld()->drawDebug();

	kmGLPopMatrix();
	
}
void TestBox2DDetector::update(float delta)
{
	armature2->setVisible(true);
	PhysicsWorld::sharedPhysicsWorld()->update(delta);
}
void TestBox2DDetector::onHit(Bone *bone, Bone *bone2)
{
	armature2->setVisible(false);
}




void TestBoundingBox::onEnter()
{
	ArmatureTestLayer::onEnter();

	armature = Armature::create("Cowboy");
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

	rect = RectApplyAffineTransform(armature->getBoundingBox(), armature->getNodeToParentTransform());
	
	DrawPrimitives::setDrawColor4B(100, 100, 100, 255);
	DrawPrimitives::drawRect(rect.origin, Point(rect.getMaxX(), rect.getMaxY()));
}



void TestAnchorPoint::onEnter()
{
	ArmatureTestLayer::onEnter();

	for (int i = 0; i<5; i++)
	{
		Armature *armature = Armature::create("Cowboy");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(VisibleRect::center());
    	armature->setScale(0.2f);
		addChild(armature, 0, i);
	}

	getChildByTag(0)->setAnchorPoint(Point(0,0));
	getChildByTag(1)->setAnchorPoint(Point(0,1));
	getChildByTag(2)->setAnchorPoint(Point(1,0));
	getChildByTag(3)->setAnchorPoint(Point(1,1));
	getChildByTag(4)->setAnchorPoint(Point(0.5,0.5));

}
std::string TestAnchorPoint::title()
{
	return "Test Set AnchorPoint";
}


void TestArmatureNesting::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	armature = Armature::create("cyborg");
	armature->getAnimation()->playByIndex(1);
	armature->setPosition(VisibleRect::center());
	armature->setScale(1.2f);
	armature->getAnimation()->setAnimationScale(0.4f);
	addChild(armature);

	weaponIndex = 0;
}
std::string TestArmatureNesting::title()
{
	return "Test Armature Nesting";
}
bool TestArmatureNesting::ccTouchBegan(Touch  *touch, Event  *event)
{
	++weaponIndex;
	weaponIndex = weaponIndex % 4;

	armature->getBone("armInside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	armature->getBone("armOutside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	return false;
}
void TestArmatureNesting::registerWithTouchDispatcher()
{
	Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}