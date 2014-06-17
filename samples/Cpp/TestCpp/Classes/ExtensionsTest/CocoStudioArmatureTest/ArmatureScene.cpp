#include "ArmatureScene.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CCLayer *NextTest();
CCLayer *BackTest();
CCLayer *RestartTest();

static int s_nActionIdx = -1;


CCLayer *CreateLayer(int index)
{
    CCLayer *pLayer = NULL;
    switch(index)
    {
    case TEST_ASYNCHRONOUS_LOADING:
        pLayer = new TestAsynchronousLoading();
        break;
    case TEST_DIRECT_LOADING:
        pLayer = new TestDirectLoading();
        break;
    case TEST_DRAGON_BONES_2_0:
        pLayer = new TestDragonBones20();
        break;
    case TEST_COCOSTUDIO_WITH_SKELETON:
        pLayer = new TestCSWithSkeleton();
        break;
    case TEST_PERFORMANCE:
        pLayer = new TestPerformance();
        break;
    case TEST_PERFORMANCE_BATCHNODE:
        pLayer = new TestPerformanceBatchNode();
        break;
    case TEST_CHANGE_ZORDER:
        pLayer = new TestChangeZorder();
        break;
    case TEST_ANIMATION_EVENT:
        pLayer = new TestAnimationEvent();
        break;
    case TEST_FRAME_EVENT:
        pLayer = new TestFrameEvent();
        break;
    case  TEST_PARTICLE_DISPLAY:
        pLayer = new TestParticleDisplay();
        break;
    case TEST_USE_DIFFERENT_PICTURE:
        pLayer = new TestUseMutiplePicture();
        break;
    case TEST_COLLIDER_DETECTOR:
        pLayer = new TestColliderDetector();
        break;
    case TEST_BOUDINGBOX:
        pLayer = new TestBoundingBox();
        break;
    case TEST_ANCHORPOINT:
        pLayer = new TestAnchorPoint();
        break;
    case TEST_ARMATURE_NESTING:
        pLayer = new TestArmatureNesting();
        break;
    case TEST_ARMATURE_NESTING_2:
        pLayer = new TestArmatureNesting2();
        break;
    case TEST_PLAY_SEVERAL_MOVEMENT:
        pLayer = new TestPlaySeveralMovement();
        break;
    case TEST_EASING:
        pLayer = new TestEasing();
        break;
    case TEST_CHANGE_ANIMATION_INTERNAL:
        pLayer = new TestChangeAnimationInternal();
        break;
	case TEST_DIRECT_FROM_BINARY:
		pLayer = new TestLoadFromBinary(); 
    default:
        break;
    }

    return pLayer;
}


CCLayer *NextTest()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % TEST_LAYER_COUNT;

    CCLayer *pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *BackTest()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += TEST_LAYER_COUNT;

    CCLayer *pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *RestartTest()
{
    CCLayer *pLayer = CreateLayer(s_nActionIdx);
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
void ArmatureTestScene::MainMenuCallback(CCObject *pSender)
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
    const char *pTitle = str.c_str();
    CCLabelTTF *label = CCLabelTTF::create(pTitle, "Arial", 18);
    label->setColor(ccc3(0, 0, 0));
    addChild(label, 1, 10000);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        CCLabelTTF *l = CCLabelTTF::create(strSubtitle.c_str(), "Arial", 18);
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
    backItem->setPosition(ccp(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setPosition(ccp(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));

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

void ArmatureTestLayer::restartCallback(CCObject *pSender)
{
    CCScene *s = new ArmatureTestScene();
    s->addChild( RestartTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void ArmatureTestLayer::nextCallback(CCObject *pSender)
{
    CCScene *s = new ArmatureTestScene();
    s->addChild( NextTest() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void ArmatureTestLayer::backCallback(CCObject *pSender)
{
    CCScene *s = new ArmatureTestScene();
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

    CCLOG("armature version : %s", armatureVersion());

    backItem->setEnabled(false);
    restartItem->setEnabled(false);
    nextItem->setEnabled(false);

    char pszPercent[255];
    sprintf(pszPercent, "%s %f", subtitle().c_str(), 0.0f);
    CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10001);
    label->setString(pszPercent);


    //! create a new thread to load data
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/knight.png", "armature/knight.plist", "armature/knight.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/robot.png", "armature/robot.plist", "armature/robot.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/Cowboy.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/hero.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/horse.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/bear.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/HeroAnimation.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/testEasing.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
}

std::string TestAsynchronousLoading::title()
{
    return "Test Asynchronous Loading";
}
std::string TestAsynchronousLoading::subtitle()
{
    return "current percent : ";
}
void TestAsynchronousLoading::restartCallback(CCObject* pSender)
{
    CCArmatureDataManager::sharedArmatureDataManager()->purge();
    ArmatureTestLayer::restartCallback(pSender);
}
void TestAsynchronousLoading::dataLoaded(float percent)
{
    CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10001);
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


void TestDirectLoading::onEnter()
{
    ArmatureTestLayer::onEnter();

    // remove sigle resource
    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/bear.ExportJson");

    // load resource directly
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/bear.ExportJson");

    CCArmature *armature = CCArmature::create("bear");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);
}
std::string TestDirectLoading::title()
{
    return "Test Direct Loading";
}



void TestCSWithSkeleton::onEnter()
{
    ArmatureTestLayer::onEnter();
    cocos2d::extension::CCArmature *armature = NULL;
    armature = cocos2d::extension::CCArmature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
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
    armature->getAnimation()->playWithIndex(1);
    armature->getAnimation()->setSpeedScale(0.4f);
    armature->setPosition(VisibleRect::center().x, VisibleRect::center().y * 0.3f);
    armature->setScale(0.6f);
    addChild(armature);
}

std::string TestDragonBones20::title()
{
    return "Test Export From DragonBones version 2.0";
}



#define ArmaturePerformanceTag 20000


TestPerformance::~TestPerformance()
{
}
void TestPerformance::onEnter()
{
    ArmatureTestLayer::onEnter();

    CCMenuItemFont::setFontSize(65);
    CCMenuItemFont *decrease = CCMenuItemFont::create(" - ", this, menu_selector(TestPerformance::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItemFont *increase = CCMenuItemFont::create(" + ", this, menu_selector(TestPerformance::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu *menu = CCMenu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height-100));
    addChild(menu, 10000);

    armatureCount = frames = times = lastTimes = 0;
    generated = false;

    scheduleUpdate();

    addArmature(100);
}

std::string TestPerformance::title()
{
    return "Test Performance";
}
std::string TestPerformance::subtitle()
{
    return "Current CCArmature Count : ";
}
void TestPerformance::onIncrease(CCObject* pSender)
{
    addArmature(20);
}
void TestPerformance::onDecrease(CCObject* pSender)
{
    if (armatureCount == 0)
        return;

    for (int i = 0; i<20; i++)
    {
        removeArmatureFromParent(ArmaturePerformanceTag + armatureCount);
        armatureCount --;
        refreshTitile();
    }
}
void TestPerformance::addArmature(int number)
{
    for (int i = 0; i<number; i++)
    {
        armatureCount++;

        cocos2d::extension::CCArmature *armature = NULL;
        armature = new cocos2d::extension::CCArmature();
        armature->init("Knight_f/Knight");
        armature->getAnimation()->playWithIndex(0);
        armature->setPosition(50 + armatureCount * 2, 150);
        armature->setScale(0.6f);
        addArmatureToParent(armature);
        armature->release();
    }

    refreshTitile();
}
void TestPerformance::addArmatureToParent(cocos2d::extension::CCArmature *armature)
{
    addChild(armature, 0, ArmaturePerformanceTag + armatureCount);
}
void TestPerformance::removeArmatureFromParent(int tag)
{
    removeChildByTag(ArmaturePerformanceTag + armatureCount);
}
void TestPerformance::refreshTitile()
{
    char pszCount[255];
    sprintf(pszCount, "%s %i", subtitle().c_str(), armatureCount);
    CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10001);
    label->setString(pszCount);
}


void TestPerformanceBatchNode::onEnter()
{
    batchNode = CCBatchNode::create();
    addChild(batchNode);

    TestPerformance::onEnter();
}
std::string TestPerformanceBatchNode::title()
{
    return "Test Performance of using CCBatchNode";
}
void TestPerformanceBatchNode::addArmatureToParent(cocos2d::extension::CCArmature *armature)
{
    batchNode->addChild(armature, 0, ArmaturePerformanceTag + armatureCount);
}
void TestPerformanceBatchNode::removeArmatureFromParent(int tag)
{
    batchNode->removeChildByTag(ArmaturePerformanceTag + armatureCount);
}




void TestChangeZorder::onEnter()
{
    ArmatureTestLayer::onEnter();

    cocos2d::extension::CCArmature *armature = NULL;
    currentTag = -1;

    armature = cocos2d::extension::CCArmature::create("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y - 100));
    ++currentTag;
    armature->setScale(0.6f);
    addChild(armature, currentTag, currentTag);

    armature = cocos2d::extension::CCArmature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.24f);
    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y - 100));
    ++currentTag;
    addChild(armature, currentTag, currentTag);

    armature = cocos2d::extension::CCArmature::create("Dragon");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(ccp(VisibleRect::center().x , VisibleRect::center().y - 100));
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
    armature->runAction(CCScaleTo::create(0.3f, 0.24f, 0.24f));
    armature->getAnimation()->play("FireMax", 10);
}
void TestAnimationEvent::callback2()
{
    armature->runAction(CCScaleTo::create(0.3f, -0.24f, 0.24f));
    armature->getAnimation()->play("Fire", 10);
}



#define  FRAME_EVENT_ACTION_TAG 10000

void TestFrameEvent::onEnter()
{
    ArmatureTestLayer::onEnter();
    cocos2d::extension::CCArmature *armature = cocos2d::extension::CCArmature::create("HeroAnimation");
    armature->getAnimation()->play("attack");
    armature->getAnimation()->setSpeedScale(0.5);
    armature->setPosition(ccp(VisibleRect::center().x - 50, VisibleRect::center().y -100));

    /*
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(NULL, NULL);
     */
    armature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(TestFrameEvent::onFrameEvent));

    addChild(armature);

    schedule( schedule_selector(TestFrameEvent::checkAction) );
}
std::string TestFrameEvent::title()
{
    return "Test Frame Event";
}
void TestFrameEvent::onFrameEvent(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex)
{
    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt, currentFrameIndex);


    if (!this->getActionByTag(FRAME_EVENT_ACTION_TAG) || this->getActionByTag(FRAME_EVENT_ACTION_TAG)->isDone())
    {
        this->stopAllActions();

        CCActionInterval *action =  CCShatteredTiles3D::create(0.2f, CCSizeMake(16,12), 5, false); 
        action->setTag(FRAME_EVENT_ACTION_TAG);
        this->runAction(action);
    }
}
void TestFrameEvent::checkAction(float dt)
{
    if ( this->numberOfRunningActions() == 0 && this->getGrid() != NULL)
        this->setGrid(NULL);
}


void TestParticleDisplay::onEnter()
{
    ArmatureTestLayer::onEnter();
    setTouchEnabled(true);

    animationID = 0;

    armature = cocos2d::extension::CCArmature::create("robot");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(VisibleRect::center());
    armature->setScale(0.48f);
    armature->getAnimation()->setSpeedScale(0.5f);
    addChild(armature);


    CCParticleSystem *p1 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
    CCParticleSystem *p2 = CCParticleSystemQuad::create("Particles/SmallSun.plist");

    cocos2d::extension::CCBone *bone  = cocos2d::extension::CCBone::create("p1");
    bone->addDisplay(p1, 0);
    bone->changeDisplayWithIndex(0, true);
    bone->setIgnoreMovementBoneData(true);
    bone->setZOrder(100);
    bone->setScale(1.2f);
    armature->addBone(bone, "bady-a3");

    bone  = cocos2d::extension::CCBone::create("p2");
    bone->addDisplay(p2, 0);
    bone->changeDisplayWithIndex(0, true);
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
    armature->getAnimation()->playWithIndex(animationID);
    return false;
}

void TestParticleDisplay::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);
}




void TestUseMutiplePicture::onEnter()
{
    ArmatureTestLayer::onEnter();
    setTouchEnabled(true);

    displayIndex = 0;

    armature = cocos2d::extension::CCArmature::create("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(0);
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

    CCLabelTTF *l = CCLabelTTF::create("This is a weapon!", "Arial", 18);
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
    armature->getBone("weapon")->changeDisplayWithIndex(displayIndex, true);
    return false;
}
void TestUseMutiplePicture::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);
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

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    bullet = CCPhysicsSprite::createWithSpriteFrameName("25.png");
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    bullet = CCSprite::createWithSpriteFrameName("25.png");
#endif
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
    armature2->setBody(body);
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

    CCBone *bone = (CCBone *)a->data;
    bone->getArmature()->setVisible(false);

    return 0;
}

void TestColliderDetector::endHit(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);

    CCBone *bone = (CCBone *)a->data;
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
    destroyCPBody(armature2->getBody());
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
    cpVect verts[] =
    {
        cpv(-size.width / 2, -size.height / 2),
        cpv(-size.width / 2, size.height / 2),
        cpv(size.width / 2, size.height / 2),
        cpv(size.width / 2, -size.height / 2),
    };

    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
    cpSpaceAddBody(space, body);

    cpShape *shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->collision_type = eBulletTag;
    cpSpaceAddShape(space, shape);

    bullet->setCPBody(body);

    body = cpBodyNew(1.0f, INFINITY);
    cpSpaceAddBody(space, body);
    armature2->setBody(body);

    CCColliderFilter filter = CCColliderFilter(eEnemyTag);
    armature2->setColliderFilter(&filter);

    cpSpaceAddCollisionHandler(space, eEnemyTag, eBulletTag, beginHit, NULL, NULL, endHit, NULL);
}
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
void TestColliderDetector::update(float delta)
{
    armature2->setVisible(true);

    CCRect rect = bullet->boundingBox();

    // This code is just telling how to get the vertex.
    // For a more accurate collider detection, you need to implemente yourself.
    CCDictElement *element = NULL;
    CCDictionary *dict = armature2->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        CCBone *bone = static_cast<CCBone*>(element->getObject());
        CCArray *bodyList = bone->getColliderBodyList();

        CCObject *object = NULL;
        CCARRAY_FOREACH(bodyList, object)
        {
            ColliderBody *body = static_cast<ColliderBody*>(object);
            CCArray *vertexList = body->getCalculatedVertexList();

            float minx = 0, miny = 0, maxx = 0, maxy = 0;
            int length = vertexList->count();
            for (int i = 0; i<length; i++)
            {
                CCContourVertex2 *vertex = static_cast<CCContourVertex2*>(vertexList->objectAtIndex(i));
                if (i == 0)
                {
                  minx = maxx = vertex->x;
                  miny = maxy = vertex->y;
                }
                else
                {
                    minx = vertex->x < minx ? vertex->x : minx;
                    miny = vertex->y < miny ? vertex->y : miny;
                    maxx = vertex->x > maxx ? vertex->x : maxx;
                    maxy = vertex->y > maxy ? vertex->y : maxy;
                }
            }
            CCRect temp = CCRectMake(minx, miny, maxx - minx, maxy - miny);

            if (temp.intersectsRect(rect))
            {
                armature2->setVisible(false);
            }
        }
    }
}
void TestColliderDetector::draw()
{
    armature2->drawContour();
}

#endif





void TestBoundingBox::onEnter()
{
    ArmatureTestLayer::onEnter();

    armature = cocos2d::extension::CCArmature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
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

    rect = armature->boundingBox();

    ccDrawColor4B(100, 100, 100, 255);
    ccDrawRect(rect.origin, ccp(rect.getMaxX(), rect.getMaxY()));
}



void TestAnchorPoint::onEnter()
{
    ArmatureTestLayer::onEnter();

    for (int i = 0; i < 5; i++)
    {
        cocos2d::extension::CCArmature *armature = cocos2d::extension::CCArmature::create("Cowboy");
        armature->getAnimation()->playWithIndex(0);
        armature->setPosition(VisibleRect::center());
        armature->setScale(0.2f);
        addChild(armature, 0, i);
    }

    getChildByTag(0)->setAnchorPoint(ccp(0, 0));
    getChildByTag(1)->setAnchorPoint(ccp(0, 1));
    getChildByTag(2)->setAnchorPoint(ccp(1, 0));
    getChildByTag(3)->setAnchorPoint(ccp(1, 1));
    getChildByTag(4)->setAnchorPoint(ccp(0.5, 0.5));

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
    armature->getAnimation()->playWithIndex(1);
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
        armature->getBone("armInside")->getChildArmature()->getAnimation()->playWithIndex(weaponIndex);
        armature->getBone("armOutside")->getChildArmature()->getAnimation()->playWithIndex(weaponIndex);
    }

    return false;
}
void TestArmatureNesting::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN + 1, true);
}




Hero *Hero::create(const char *name)
{
    Hero *hero = new Hero();
    if (hero && hero->init(name))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return NULL;
}

Hero::Hero()
    : m_pMount(NULL)
    , m_pLayer(NULL)
{
}

void Hero::changeMount(CCArmature *armature)
{
    if (armature == NULL)
    {
        retain();

        playWithIndex(0);
        //Remove hero from display list
        m_pMount->getBone("hero")->removeDisplay(0);
        m_pMount->stopAllActions();

        //Set position to current position
        setPosition(m_pMount->getPosition());
        //Add to layer
        m_pLayer->addChild(this);

        release();

        setMount(armature);
    }
    else
    {
        setMount(armature);

        retain();
        //Remove from layer
        removeFromParentAndCleanup(false);

        //Get the hero bone
        CCBone *bone = armature->getBone("hero");
        //Add hero as a display to this bone
        bone->addDisplay(this, 0);
        //Change this bone's display
        bone->changeDisplayWithIndex(0, true);
        bone->setIgnoreMovementBoneData(true);

        setPosition(ccp(0,0));
        //Change animation
        playWithIndex(1);

        setScale(1);

        release();
    }

}

void Hero::playWithIndex(int index)
{
    m_pAnimation->playWithIndex(index);
    if (m_pMount)
    {
        m_pMount->getAnimation()->playWithIndex(index);
    }
}

void TestArmatureNesting2::onEnter()
{
    ArmatureTestLayer::onEnter();
    setTouchEnabled(true);

    touchedMenu = false;

    CCLabelTTF* label = CCLabelTTF::create("Change Mount", "Arial", 20);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestArmatureNesting2::ChangeMountCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 67, VisibleRect::bottom().y + 50) );

    addChild(pMenu, 2);

    //Create a hero
    hero = Hero::create("hero");
    hero->setLayer(this);
    hero->playWithIndex(0);
    hero->setPosition(ccp(VisibleRect::left().x + 20, VisibleRect::left().y));
    addChild(hero);

    //Create 3 mount
    horse = createMount("horse", VisibleRect::center());

    horse2 = createMount("horse", ccp(120, 200));
    horse2->setOpacity(200);
    
    bear = createMount("bear", ccp(300,70));
}
void TestArmatureNesting2::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    ArmatureTestLayer::onExit();
}
std::string TestArmatureNesting2::title()
{
    return "Test CCArmature Nesting 2";
}
std::string TestArmatureNesting2::subtitle()
{
    return "Move to a mount and press the ChangeMount Button.";
}
bool TestArmatureNesting2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();

    CCArmature *armature = hero->getMount() == NULL ? hero : hero->getMount(); 

    //Set armature direction
    if (point.x < armature->getPositionX())
    {
        armature->setScaleX(-1);
    }
    else
    {
        armature->setScaleX(1);
    }

    CCActionInterval *move = CCMoveTo::create(2, point);
    armature->stopAllActions();
    armature->runAction(CCSequence::create(move,  CCCallFunc::create(this, NULL), NULL));

    return false;
}
void TestArmatureNesting2::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}

void TestArmatureNesting2::ChangeMountCallback(CCObject* pSender)
{
    hero->stopAllActions();

    if (hero->getMount())
    {
        hero->changeMount(NULL);
    }
    else
    {
        if (ccpDistance(hero->getPosition(), horse->getPosition()) < 20)
        {
            hero->changeMount(horse);
        }
        else if (ccpDistance(hero->getPosition(), horse2->getPosition()) < 20)
        {
            hero->changeMount(horse2);
        }
        else if (ccpDistance(hero->getPosition(), bear->getPosition()) < 30)
        {
            hero->changeMount(bear);
        }
    }
}

CCArmature * TestArmatureNesting2::createMount(const char *name, CCPoint position)
{
    CCArmature *armature = CCArmature::create(name);
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(position);
    addChild(armature);

    return armature;
}

void TestPlaySeveralMovement::onEnter()
{
    ArmatureTestLayer::onEnter();

    // To use names, you could create a std::vector like this.  
    // std::string name[] = {"Walk", "FireMax", "Fire"};
    // std::vector<std::string> names(name, name+3);
    // armature->getAnimation()->playWithNames(names);

    int index[] = {0, 1, 2};
    std::vector<int> indexes(index, index+3);

    CCArmature *armature = CCArmature::create("Cowboy");
    
    armature->getAnimation()->playWithIndexes(indexes);
    armature->setScale(0.2f);

    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
    addChild(armature);
}
std::string TestPlaySeveralMovement::title()
{
    return "Test play several movement";
}

std::string TestPlaySeveralMovement::subtitle()
{
    return "Movement is played one by one";
}


void TestEasing::onEnter()
{
    ArmatureTestLayer::onEnter();
    setTouchEnabled(true);

    animationID = 0;

    armature = cocos2d::extension::CCArmature::create("testEasing");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.8);

    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);

    updateSubTitle();
}
void TestEasing::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    ArmatureTestLayer::onExit();
}
std::string TestEasing::title()
{
    return "Test easing effect";
}
std::string TestEasing::subtitle()
{
    return "Current easing : ";
}
bool TestEasing::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    animationID++;
    animationID = animationID % armature->getAnimation()->getMovementCount();
    armature->getAnimation()->playWithIndex(animationID);

    updateSubTitle();

    return false;
}
void TestEasing::updateSubTitle()
{
    std::string str = subtitle() + armature->getAnimation()->getCurrentMovementID();
    CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10001);
    label->setString(str.c_str());
}
void TestEasing::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}




void TestChangeAnimationInternal::onEnter()
{
    ArmatureTestLayer::onEnter();
    setTouchEnabled(true);

    cocos2d::extension::CCArmature *armature = NULL;
    armature = cocos2d::extension::CCArmature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.2f);

    armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);
}
void TestChangeAnimationInternal::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCDirector::sharedDirector()->setAnimationInterval(1/60.0f);
}
std::string TestChangeAnimationInternal::title()
{
    return "Test change animation internal";
}
std::string TestChangeAnimationInternal::subtitle()
{
    return "Touch to change animation internal";
}

bool TestChangeAnimationInternal::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (CCDirector::sharedDirector()->getAnimationInterval() == 1/30.0f)
    {
        CCDirector::sharedDirector()->setAnimationInterval(1/60.0f);
    }
    else
    {
        CCDirector::sharedDirector()->setAnimationInterval(1/30.0f);
    }
    return false;
}
void TestChangeAnimationInternal::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}




//TestDirectFromBinay

const  char* TestLoadFromBinary::m_binaryFilesNames[BINARYFILECOUNT] ={"armature/bear.csb","armature/horse.csb",
	"armature/Cowboy.csb","armature/hero.csb",
	"armature/HeroAnimation.csb","armature/testEasing.csb"};
const  char* TestLoadFromBinary::m_armatureNames[BINARYFILECOUNT] ={"bear","horse",
	"Cowboy","hero",
	"HeroAnimation","testEasing"};


void TestLoadFromBinary::onEnter()
{
	ArmatureTestLayer::onEnter();
	setTouchEnabled(true);

	m_armatureIndex = -1; // none

	// remove json created 
	// remove sync resource
	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/bear.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(m_binaryFilesNames[0]);
	// load from binary
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(m_binaryFilesNames[0]);

	m_armature = cocos2d::extension::CCArmature::create(m_armatureNames[0]);
	m_armature->getAnimation()->playWithIndex(0);
	m_armature->setScale(1.0f);

	m_armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
	addChild(m_armature);

}

void TestLoadFromBinary::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->setAnimationInterval(1/60.0f);
}
std::string TestLoadFromBinary::title()
{
	return "Test load from binary file";
}
std::string TestLoadFromBinary::subtitle()
{
	return "direct load. \nTouch to change to Asynchronous load.";
}

bool TestLoadFromBinary::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	// remove json created 
	// remove sync resource
	if(-1 == m_armatureIndex )
	{
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(m_binaryFilesNames[0]);
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/Cowboy.ExportJson");
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/hero.ExportJson");
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/horse.ExportJson");
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/HeroAnimation.ExportJson");
		CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/testEasing.ExportJson");

		for( int i = 0; i < BINARYFILECOUNT; i++)
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(m_binaryFilesNames[i], this, schedule_selector(TestLoadFromBinary::dataLoaded));
		}

		m_armatureIndex = -2;    // is loading
	}
	else if(m_armatureIndex>=0 && m_armature != NULL)
	{
		this->removeChild(m_armature);
		m_armatureIndex = m_armatureIndex==BINARYFILECOUNT-1 ? 0 : m_armatureIndex+1;
		m_armature = cocos2d::extension::CCArmature::create(m_armatureNames[m_armatureIndex]);
		m_armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
		if(m_armatureIndex == 2 )  // cowboy is 0.2
			m_armature->setScale(0.2f);
		m_armature->getAnimation()->playWithIndex(0);
		addChild(m_armature);
	}
	return true;
}
void TestLoadFromBinary::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}

void TestLoadFromBinary::dataLoaded( float percent )
{
	CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10001);
	if (label)
	{
		char pszPercent[255];
		sprintf(pszPercent, "%s %f", subtitle().c_str(), percent * 100);
		label->setString(pszPercent);
	}

	if (percent >= 1)
	{
		label->setString("Touch to change armature");
		m_armatureIndex = 0;
	}
}

