#include "ArmatureScene.h"
#include "../../testResource.h"
#include "cocostudio/CocoStudio.h"


using namespace cocos2d;
using namespace cocostudio;

Layer *NextTest();
Layer *BackTest();
Layer *RestartTest();

static int s_nActionIdx = -1;


Layer *CreateLayer(int index)
{
    Layer *pLayer = nullptr;
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
//    case TEST_PERFORMANCE_BATCHNODE:
//        pLayer = new TestPerformanceBatchNode();
//        break;
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
        break;
    default:
        break;
    }

    return pLayer;
}


Layer *NextTest()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % TEST_LAYER_COUNT;

    Layer *pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer *BackTest()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += TEST_LAYER_COUNT;

    Layer *pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer *RestartTest()
{
    Layer *pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
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


    s_nActionIdx = -1;
    addChild(NextTest());

    Director::getInstance()->replaceScene(this);
}
void ArmatureTestScene::MainMenuCallback(Ref *pSender)
{
    //TestScene::MainMenuCallback(pSender);

    removeAllChildren();
    ArmatureDataManager::destroyInstance();
}



void ArmatureTestLayer::onEnter()
{

    Layer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *pTitle = str.c_str();
    auto label = Label::createWithTTF(pTitle, "fonts/arial.ttf", 18);
    label->setColor(Color3B::BLACK);
    addChild(label, 1, 10000);
    label->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        auto l = Label::createWithTTF(strSubtitle.c_str(), "fonts/arial.ttf", 18);
        l->setColor(Color3B::BLACK);
        addChild(l, 1, 10001);
        l->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
    backItem = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(ArmatureTestLayer::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(ArmatureTestLayer::restartCallback, this) );
    nextItem = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(ArmatureTestLayer::nextCallback, this) );

    Menu *menu = Menu::create(backItem, restartItem, nextItem, nullptr);

    menu->setPosition(Vec2::ZERO);
    backItem->setPosition(Vec2(VisibleRect::center().x - restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setPosition(Vec2(VisibleRect::center().x + restartItem->getContentSize().width * 2, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));

    addChild(menu, 100);

    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

}
void ArmatureTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = nullptr;

    Layer::onExit();
}

std::string ArmatureTestLayer::title() const
{
    return "Armature Test Bed";
}
std::string ArmatureTestLayer::subtitle() const
{
    return "";
}

void ArmatureTestLayer::restartCallback(Ref *pSender)
{
    Scene *s = new ArmatureTestScene();
    s->addChild( RestartTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void ArmatureTestLayer::nextCallback(Ref *pSender)
{
    Scene *s = new ArmatureTestScene();
    s->addChild( NextTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void ArmatureTestLayer::backCallback(Ref *pSender)
{
    Scene *s = new ArmatureTestScene();
    s->addChild( BackTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void TestAsynchronousLoading::onEnter()
{
    ArmatureTestLayer::onEnter();

    //CCLOG("armature version : %s", armatureVersion());

    backItem->setEnabled(false);
    restartItem->setEnabled(false);
    nextItem->setEnabled(false);

    char pszPercent[255];
    sprintf(pszPercent, "%s %f", subtitle().c_str(), 0.0f);
    auto label = (Label *)getChildByTag(10001);
    label->setString(pszPercent);


    //! create a new thread to load data
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/knight.png", "armature/knight.plist", "armature/knight.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/robot.png", "armature/robot.plist", "armature/robot.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/Cowboy.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/hero.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/horse.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/bear.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/HeroAnimation.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("armature/testEasing.ExportJson", this, schedule_selector(TestAsynchronousLoading::dataLoaded));
}

std::string TestAsynchronousLoading::title() const
{
    return "Test Asynchronous Loading";
}
std::string TestAsynchronousLoading::subtitle() const
{
    return "current percent : ";
}

void TestAsynchronousLoading::restartCallback(Ref* pSender)
{
    ArmatureDataManager::destroyInstance();
    ArmatureTestLayer::restartCallback(pSender);
}
void TestAsynchronousLoading::dataLoaded(float percent)
{
    auto label = (Label *)getChildByTag(10001);
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
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/bear.ExportJson");

    // load resource directly
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/bear.ExportJson");

    Armature *armature = Armature::create("bear");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);
}
std::string TestDirectLoading::title() const
{
    return "Test Direct Loading";
}


void TestCSWithSkeleton::onEnter()
{
    ArmatureTestLayer::onEnter();
    Armature *armature = nullptr;
    armature = Armature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.2f);

    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
    addChild(armature);
}

std::string TestCSWithSkeleton::title() const
{
    return "Test Export From CocoStudio With Skeleton Effect";
}




void TestDragonBones20::onEnter()
{
    ArmatureTestLayer::onEnter();

    Armature *armature = nullptr;
    armature = Armature::create("Dragon");
    armature->getAnimation()->playWithIndex(1);
    armature->getAnimation()->setSpeedScale(0.4f);
    armature->setPosition(VisibleRect::center().x, VisibleRect::center().y * 0.3f);
    armature->setScale(0.6f);
    addChild(armature);
}

std::string TestDragonBones20::title() const
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


    MenuItemFont::setFontSize(65);
    MenuItemFont *decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(TestPerformance::onDecrease, this));
    decrease->setColor(Color3B(0,200,20));
    MenuItemFont *increase = MenuItemFont::create(" + ", CC_CALLBACK_1(TestPerformance::onIncrease, this));
    increase->setColor(Color3B(0,200,20));

    Menu *menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height-100));
    addChild(menu, 10000);

    armatureCount = frames = times = lastTimes = 0;
    generated = false;

    addArmature(100);
}

std::string TestPerformance::title() const
{
    return "Test Performance";
}
std::string TestPerformance::subtitle() const
{
    return "Current Armature Count : ";
}
void TestPerformance::onIncrease(Ref* pSender)
{
    addArmature(20);
}
void TestPerformance::onDecrease(Ref* pSender)
{
    if (armatureCount == 0)
        return;

    for (int i = 0; i<20; i++)
    {
        removeArmatureFromParent(ArmaturePerformanceTag + armatureCount);
        armatureCount --;
        refreshTitle();
    }
}
void TestPerformance::addArmature(int number)
{
    for (int i = 0; i<number; i++)
    {
        armatureCount++;

        Armature *armature = nullptr;
        armature = new Armature();
        armature->init("Cowboy");
        armature->getAnimation()->playWithIndex(0);
        armature->setPosition(50 + armatureCount * 2, 150);
        armature->setScale(0.1f);
        addArmatureToParent(armature);
        armature->release();
    }

    refreshTitle();
}
void TestPerformance::addArmatureToParent(cocostudio::Armature *armature)
{
    addChild(armature, 0, ArmaturePerformanceTag + armatureCount);
}
void TestPerformance::removeArmatureFromParent(int tag)
{
    removeChildByTag(ArmaturePerformanceTag + armatureCount);
}
void TestPerformance::refreshTitle()
{
    char pszCount[255];
    sprintf(pszCount, "%s %i", subtitle().c_str(), armatureCount);
    auto label = (Label *)getChildByTag(10001);
    label->setString(pszCount);
}


void TestPerformanceBatchNode::onEnter()
{
    batchNode = BatchNode::create();
    addChild(batchNode);

    TestPerformance::onEnter();
}
std::string TestPerformanceBatchNode::title() const
{
    return "Test Performance of using BatchNode";
}
void TestPerformanceBatchNode::addArmatureToParent(cocostudio::Armature *armature)
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

    Armature *armature = nullptr;
    currentTag = -1;

    armature = Armature::create("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - 100));
    ++currentTag;
    armature->setScale(0.6f);
    addChild(armature, currentTag, currentTag);

    armature = Armature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.24f);
    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - 100));
    ++currentTag;
    addChild(armature, currentTag, currentTag);

    armature = Armature::create("Dragon");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(Vec2(VisibleRect::center().x , VisibleRect::center().y - 100));
    ++currentTag;
    armature->setScale(0.6f);
    addChild(armature, currentTag, currentTag);

    schedule( schedule_selector(TestChangeZorder::changeZorder), 1);

    currentTag = 0;
}
std::string TestChangeZorder::title() const
{
    return "Test Change ZOrder Of Different Armature";
}
void TestChangeZorder::changeZorder(float dt)
{

    Node *node = getChildByTag(currentTag);

    node->setLocalZOrder(CCRANDOM_0_1() * 3);

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
    armature->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::left().y));

    /*
    * Set armature's movement event callback function
    * To disconnect this event, just setMovementEventCallFunc(nullptr, nullptr);
    */
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(TestAnimationEvent::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    addChild(armature);
}
std::string TestAnimationEvent::title() const
{
    return "Test Armature Animation Event";
}
void TestAnimationEvent::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == LOOP_COMPLETE)
    {
        if (movementID == "Fire")
        {
            ActionInterval *actionToRight = MoveTo::create(2, Vec2(VisibleRect::right().x - 50, VisibleRect::right().y));
            armature->stopAllActions();
            armature->runAction(Sequence::create(actionToRight,  CallFunc::create( CC_CALLBACK_0(TestAnimationEvent::callback1, this)), nullptr));
            armature->getAnimation()->play("Walk");
        }
        else if (movementID == "FireMax")
        {
            ActionInterval *actionToLeft = MoveTo::create(2, Vec2(VisibleRect::left().x + 50, VisibleRect::left().y));
            armature->stopAllActions();
            armature->runAction(Sequence::create(actionToLeft,  CallFunc::create( CC_CALLBACK_0(TestAnimationEvent::callback2, this)), nullptr));
            armature->getAnimation()->play("Walk");
        }
    }
}
void TestAnimationEvent::callback1()
{
    armature->runAction(ScaleTo::create(0.3f, 0.24f, 0.24f));
    armature->getAnimation()->play("FireMax", 10);
}
void TestAnimationEvent::callback2()
{
    armature->runAction(ScaleTo::create(0.3f, -0.24f, 0.24f));
    armature->getAnimation()->play("Fire", 10);
}



#define  FRAME_EVENT_ACTION_TAG 10000

void TestFrameEvent::onEnter()
{
    ArmatureTestLayer::onEnter();
    _gridNode = NodeGrid::create();
    Armature *armature = Armature::create("HeroAnimation");
    armature->getAnimation()->play("attack");
    armature->getAnimation()->setSpeedScale(0.5);
    armature->setPosition(Vec2(VisibleRect::center().x - 50, VisibleRect::center().y -100));

    /*
     * Set armature's frame event callback function
     * To disconnect this event, just setFrameEventCallFunc(nullptr);
     */
    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(TestFrameEvent::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    _gridNode->addChild(armature);
    addChild(_gridNode);

    schedule( schedule_selector(TestFrameEvent::checkAction) );
}
std::string TestFrameEvent::title() const
{
    return "Test Frame Event";
}
void TestFrameEvent::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);

    if (!_gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG) || _gridNode->getActionByTag(FRAME_EVENT_ACTION_TAG)->isDone())
    {
        _gridNode->stopAllActions();

        ActionInterval *action =  ShatteredTiles3D::create(0.2f, Size(16,12), 5, false);
        action->setTag(FRAME_EVENT_ACTION_TAG);
        _gridNode->runAction(action);
    }
}
void TestFrameEvent::checkAction(float dt)
{
    if ( _gridNode->getNumberOfRunningActions() == 0 && _gridNode->getGrid() != nullptr)
        _gridNode->setGrid(nullptr);
}



void TestParticleDisplay::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestParticleDisplay::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    animationID = 0;

    armature = Armature::create("robot");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(VisibleRect::center());
    armature->setScale(0.48f);
    armature->getAnimation()->setSpeedScale(0.5f);
    addChild(armature);


    ParticleSystem *p1 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
    ParticleSystem *p2 = CCParticleSystemQuad::create("Particles/SmallSun.plist");

    Bone *bone  = Bone::create("p1");
    bone->addDisplay(p1, 0);
    bone->changeDisplayWithIndex(0, true);
    bone->setIgnoreMovementBoneData(true);
    bone->setLocalZOrder(100);
    bone->setScale(1.2f);
    armature->addBone(bone, "bady-a3");

    bone  = Bone::create("p2");
    bone->addDisplay(p2, 0);
    bone->changeDisplayWithIndex(0, true);
    bone->setIgnoreMovementBoneData(true);
    bone->setLocalZOrder(100);
    bone->setScale(1.2f);
    armature->addBone(bone, "bady-a30");
}

void TestParticleDisplay::onExit()
{
    ArmatureTestLayer::onExit();
}

std::string TestParticleDisplay::title() const
{
    return "Test Particle Display";
}

std::string TestParticleDisplay::subtitle() const
{
    return "Touch to change animation";
}

void TestParticleDisplay::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    ++animationID;
    animationID = animationID % armature->getAnimation()->getMovementCount();
    armature->getAnimation()->playWithIndex(animationID);
}

void TestUseMutiplePicture::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestUseMutiplePicture::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    displayIndex = 0;

    armature = Armature::create("Knight_f/Knight");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::left().y));
    armature->setScale(1.2f);
    addChild(armature);

    std::string weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};

    for (int i = 0; i < 7; i++)
    {
        Skin *skin = Skin::createWithSpriteFrameName(weapon[i].c_str());
        armature->getBone("weapon")->addDisplay(skin, i);
    }

    // 	CCSpriteDisplayData displayData;
    // 	for (int i = 0; i < 7; i++)
    // 	{
    // 		displayData.setParam(weapon[i].c_str());
    // 		armature->getBone("weapon")->addDisplay(&displayData, i);
    // 	}

    auto l = Label::createWithTTF("This is a weapon!", "fonts/arial.ttf", 18);
    l->setAnchorPoint(Vec2(0.2f, 0.5f));
    armature->getBone("weapon")->addDisplay(l, 7);
}

void TestUseMutiplePicture::onExit()
{
    ArmatureTestLayer::onExit();
}

std::string TestUseMutiplePicture::title() const
{
    return "Test One Armature Use Different Picture";
}

std::string TestUseMutiplePicture::subtitle() const
{
    return "weapon and armature are in different picture";
}

void TestUseMutiplePicture::onTouchesEnded(const std::vector<Touch*>&  touches, Event* event)
{
    ++displayIndex;
    displayIndex = (displayIndex) % 8;
    armature->getBone("weapon")->changeDisplayWithIndex(displayIndex, true);
}

TestColliderDetector::~TestColliderDetector()
{
}
void TestColliderDetector::onEnter()
{
    ArmatureTestLayer::onEnter();

    scheduleUpdate();

    armature = Armature::create("Cowboy");
    armature->getAnimation()->play("FireWithoutBullet");
    armature->getAnimation()->setSpeedScale(0.2f);
    armature->setScaleX(-0.2f);
    armature->setScaleY(0.2f);
    armature->setPosition(Vec2(VisibleRect::left().x + 70, VisibleRect::left().y));

    /*
    * Set armature's frame event callback function
    * To disconnect this event, just setFrameEventCallFunc(nullptr);
    */
    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(TestColliderDetector::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    addChild(armature);

    armature2 = Armature::create("Cowboy");
    armature2->getAnimation()->play("Walk");
    armature2->setScaleX(-0.2f);
    armature2->setScaleY(0.2f);
    armature2->setPosition(Vec2(VisibleRect::right().x - 60, VisibleRect::left().y));
    addChild(armature2);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    bullet = cocos2d::extension::PhysicsSprite::createWithSpriteFrameName("25.png");
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    bullet = Sprite::createWithSpriteFrameName("25.png");
#endif
    addChild(bullet);

    initWorld();
}
std::string TestColliderDetector::title() const
{
    return "Test Collider Detector";
}
void TestColliderDetector::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);

    /*
    * originFrameIndex is the frame index editted in Action Editor
    * currentFrameIndex is the current index animation played to
    * frame event may be delay emit, so originFrameIndex may be different from currentFrameIndex.
    */

    Vec2 p = armature->getBone("Layer126")->getDisplayRenderNode()->convertToWorldSpaceAR(Vec2(0, 0));
    bullet->setPosition(Vec2(p.x + 60, p.y));

    bullet->stopAllActions();
    bullet->runAction(CCMoveBy::create(1.5f, Vec2(350, 0)));
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
void TestColliderDetector::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    world->DrawDebugData();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
void TestColliderDetector::update(float delta)
{
    armature2->setVisible(true);

    world->Step(delta, 0, 0);

    for (std::list<Contact>::iterator it = listener->contact_list.begin(); it != listener->contact_list.end(); ++it)
    {
        Contact &contact = *it;

        Bone *bb = static_cast<Bone *>(contact.fixtureB->GetUserData);

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
    bullet->setPosition( Vec2( -100, -100) );

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

    Bone *bone = (Bone *)a->data;
    bone->getArmature()->setVisible(false);

    return 0;
}

void TestColliderDetector::endHit(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);

    Bone *bone = (Bone *)a->data;
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

#if CC_ENABLE_CHIPMUNK_INTEGRATION
    // Physics debug layer
    cocos2d::extension::PhysicsDebugNode *debugLayer = cocos2d::extension::PhysicsDebugNode::create(space);
    this->addChild(debugLayer, INT_MAX);
#endif

    Size size = bullet->getContentSize();

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

    ColliderFilter filter = ColliderFilter(eEnemyTag);
    armature2->setColliderFilter(&filter);

    cpSpaceAddCollisionHandler(space, eEnemyTag, eBulletTag, beginHit, nullptr, nullptr, endHit, nullptr);
}
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
void TestColliderDetector::update(float delta)
{
    armature2->setVisible(true);

    Rect rect = bullet->getBoundingBox();

    // This code is just telling how to get the vertex.
    // For a more accurate collider detection, you need to implemente yourself.
    const Map<std::string, Bone*>& map = armature2->getBoneDic();
    for(const auto& element : map)
    {
        Bone *bone = element.second;
        ColliderDetector *detector = bone->getColliderDetector();

        if (!detector)
            continue;

        const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

        for (const auto& object : bodyList)
        {
            ColliderBody *body = static_cast<ColliderBody*>(object);
            const std::vector<Vec2> &vertexList = body->getCalculatedVertexList();

            float minx = 0, miny = 0, maxx = 0, maxy = 0;
            size_t length = vertexList.size();
            for (size_t i = 0; i<length; i++)
            {
                Vec2 vertex = vertexList.at(i);
                if (i == 0)
                {
                    minx = maxx = vertex.x;
                    miny = maxy = vertex.y;
                }
                else
                {
                    minx = vertex.x < minx ? vertex.x : minx;
                    miny = vertex.y < miny ? vertex.y : miny;
                    maxx = vertex.x > maxx ? vertex.x : maxx;
                    maxy = vertex.y > maxy ? vertex.y : maxy;
                }
            }
            Rect temp = Rect(minx, miny, maxx - minx, maxy - miny);

            if (temp.intersectsRect(rect))
            {
                armature2->setVisible(false);
            }
        }
    }
}
void TestColliderDetector::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TestColliderDetector::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void TestColliderDetector::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    armature2->drawContour();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
#endif





void TestBoundingBox::onEnter()
{
    ArmatureTestLayer::onEnter();

    armature = Armature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(VisibleRect::center());
    armature->setScale(0.2f);
    addChild(armature);

    Sprite *sprite = Sprite::create("Images/background3.png");
    armature->addChild(sprite);
}
std::string TestBoundingBox::title() const
{
    return "Test BoundingBox";
}
void TestBoundingBox::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TestBoundingBox::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);

}

void TestBoundingBox::onDraw(const Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);
    
    rect = armature->getBoundingBox();
    
    DrawPrimitives::setDrawColor4B(100, 100, 100, 255);
    DrawPrimitives::drawRect(rect.origin, Vec2(rect.getMaxX(), rect.getMaxY()));
}

void TestAnchorPoint::onEnter()
{
    ArmatureTestLayer::onEnter();

    for (int i = 0; i < 5; i++)
    {
        Armature *armature = Armature::create("Cowboy");
        armature->getAnimation()->playWithIndex(0);
        armature->setPosition(VisibleRect::center());
        armature->setScale(0.2f);
        addChild(armature, 0, i);
    }

    getChildByTag(0)->setAnchorPoint(Vec2(0, 0));
    getChildByTag(1)->setAnchorPoint(Vec2(0, 1));
    getChildByTag(2)->setAnchorPoint(Vec2(1, 0));
    getChildByTag(3)->setAnchorPoint(Vec2(1, 1));
    getChildByTag(4)->setAnchorPoint(Vec2(0.5, 0.5));

}
std::string TestAnchorPoint::title() const
{
    return "Test Set AnchorPoint";
}

void TestArmatureNesting::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestArmatureNesting::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    armature = Armature::create("cyborg");
    armature->getAnimation()->playWithIndex(1);
    armature->setPosition(VisibleRect::center());
    armature->setScale(1.2f);
    armature->getAnimation()->setSpeedScale(0.4f);
    addChild(armature);

    weaponIndex = 0;
}

void TestArmatureNesting::onExit()
{
    ArmatureTestLayer::onExit();
}

std::string TestArmatureNesting::title() const
{
    return "Test Armature Nesting";
}

void TestArmatureNesting::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    ++weaponIndex;
    weaponIndex = weaponIndex % 4;

    if(armature != nullptr)
    {
        armature->getBone("armInside")->getChildArmature()->getAnimation()->playWithIndex(weaponIndex);
        armature->getBone("armOutside")->getChildArmature()->getAnimation()->playWithIndex(weaponIndex);
    }
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
    return nullptr;
}

Hero::Hero()
    : m_pMount(nullptr)
    , m_pLayer(nullptr)
{
}

void Hero::changeMount(Armature *armature)
{
    if (armature == nullptr)
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
        Bone *bone = armature->getBone("hero");
        //Add hero as a display to this bone
        bone->addDisplay(this, 0);
        //Change this bone's display
        bone->changeDisplayWithIndex(0, true);
        bone->setIgnoreMovementBoneData(true);

        setPosition(Vec2(0,0));
        //Change animation
        playWithIndex(1);

        setScale(1);

        release();
    }

}

void Hero::playWithIndex(int index)
{
    _animation->playWithIndex(index);
    if (m_pMount)
    {
        m_pMount->getAnimation()->playWithIndex(index);
    }
}

void TestArmatureNesting2::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestArmatureNesting2::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    touchedMenu = false;

    auto label = Label::createWithTTF("Change Mount", "fonts/arial.ttf", 20);
    MenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, CC_CALLBACK_1(TestArmatureNesting2::changeMountCallback, this));

    Menu* pMenu =Menu::create(pMenuItem, nullptr);

    pMenu->setPosition( Vec2() );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 67, VisibleRect::bottom().y + 50) );

    addChild(pMenu, 2);

    //Create a hero
    hero = Hero::create("hero");
    hero->setLayer(this);
    hero->playWithIndex(0);
    hero->setPosition(Vec2(VisibleRect::left().x + 20, VisibleRect::left().y));
    addChild(hero);

    //Create 3 mount
    horse = createMount("horse", VisibleRect::center());

    horse2 = createMount("horse", Vec2(120, 200));
    horse2->setOpacity(200);

    bear = createMount("bear", Vec2(300,70));
}
void TestArmatureNesting2::onExit()
{
    ArmatureTestLayer::onExit();
}
std::string TestArmatureNesting2::title() const
{
    return "Test CCArmature Nesting 2";
}
std::string TestArmatureNesting2::subtitle() const
{
    return "Move to a mount and press the ChangeMount Button.";
}
void TestArmatureNesting2::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    Vec2 point = touches[0]->getLocation();

    Armature *armature = hero->getMount() == nullptr ? hero : hero->getMount();

    //Set armature direction
    if (point.x < armature->getPositionX())
    {
        armature->setScaleX(-1);
    }
    else
    {
        armature->setScaleX(1);
    }

    ActionInterval *move = CCMoveTo::create(2, point);
    armature->stopAllActions();
    armature->runAction(Sequence::create(move, nullptr));
}

void TestArmatureNesting2::changeMountCallback(Ref* pSender)
{
    hero->stopAllActions();

    if (hero->getMount())
    {
        hero->changeMount(nullptr);
    }
    else
    {
        if (hero->getPosition().getDistance(horse->getPosition()) < 20)
        {
            hero->changeMount(horse);
        }
        else if (hero->getPosition().getDistance(horse2->getPosition()) < 20)
        {
            hero->changeMount(horse2);
        }
        else if (hero->getPosition().getDistance(bear->getPosition()) < 30)
        {
            hero->changeMount(bear);
        }
    }
}

Armature * TestArmatureNesting2::createMount(const char *name, Vec2 position)
{
    Armature *armature = Armature::create(name);
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(position);
    addChild(armature);

    return armature;
}


void TestPlaySeveralMovement::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestPlaySeveralMovement::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    std::string name[] = {"Walk", "FireMax", "Fire"};
    std::vector<std::string> names(name, name+3);
//    int index[] = {0, 1, 2};
//    std::vector<int> indexes(index, index+3);

    Armature *armature = NULL;
    armature = Armature::create("Cowboy");
    armature->getAnimation()->playWithNames(names);
//    armature->getAnimation()->playWithIndexes(indexes);
    armature->setScale(0.2f);

    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
    addChild(armature);
}
std::string TestPlaySeveralMovement::title() const
{
    return "Test play several movement";
}

std::string TestPlaySeveralMovement::subtitle()const
{
    return "Movement is played one by one";
}


void TestEasing::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestPlaySeveralMovement::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    animationID = 0;

    armature = Armature::create("testEasing");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.8f);

    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);

    updateSubTitle();
}

std::string TestEasing::title() const
{
    return "Test easing effect";
}
std::string TestEasing::subtitle() const
{
    return "Current easing : ";
}
void TestEasing::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    animationID++;
    animationID = animationID % armature->getAnimation()->getMovementCount();
    armature->getAnimation()->playWithIndex(animationID);

    updateSubTitle();
}
void TestEasing::updateSubTitle()
{
    std::string str = subtitle() + armature->getAnimation()->getCurrentMovementID();
    auto label = (Label *)getChildByTag(10001);
    label->setString(str.c_str());
}

void TestChangeAnimationInternal::onEnter()
{
    ArmatureTestLayer::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestPlaySeveralMovement::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Armature *armature = NULL;
    armature = Armature::create("Cowboy");
    armature->getAnimation()->playWithIndex(0);
    armature->setScale(0.2f);

    armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
    addChild(armature);
}
void TestChangeAnimationInternal::onExit()
{
    Director::getInstance()->setAnimationInterval(1/60.0f);
    ArmatureTestLayer::onExit();
}
std::string TestChangeAnimationInternal::title() const
{
    return "Test change animation internal";
}
std::string TestChangeAnimationInternal::subtitle() const
{
    return "Touch to change animation internal";
}
void TestChangeAnimationInternal::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    if (Director::getInstance()->getAnimationInterval() == 1/30.0f)
    {
        Director::getInstance()->setAnimationInterval(1/60.0f);
    }
    else
    {
        Director::getInstance()->setAnimationInterval(1/30.0f);
    }
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
	
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(TestLoadFromBinary::onTouchesEnded, this);    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	m_armatureIndex = -1; // none
    
	// remove json created
	// remove sync resource
	ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/bear.ExportJson");
	ArmatureDataManager::getInstance()->removeArmatureFileInfo(m_binaryFilesNames[0]);
	// load from binary
	ArmatureDataManager::getInstance()->addArmatureFileInfo(m_binaryFilesNames[0]);
    
	m_armature = Armature::create(m_armatureNames[0]);
	m_armature->getAnimation()->playWithIndex(0);
	m_armature->setScale(1.0f);
    
	m_armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	addChild(m_armature);
    
}


std::string TestLoadFromBinary::title() const
{
	return "Test load from binary file";
}
std::string TestLoadFromBinary::subtitle() const
{
	return "direct load.Touch to change to Asynchronous load.";
}

void TestLoadFromBinary::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	// remove json created
	// remove sync resource
	if(-1 == m_armatureIndex )
	{
		ArmatureDataManager::getInstance()->removeArmatureFileInfo(m_binaryFilesNames[0]);
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/Cowboy.ExportJson");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/hero.ExportJson");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/horse.ExportJson");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/HeroAnimation.ExportJson");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("armature/testEasing.ExportJson");
        
		for( int i = 0; i < BINARYFILECOUNT; i++)
		{
			ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(m_binaryFilesNames[i], this, schedule_selector(TestLoadFromBinary::dataLoaded));
		}
        
		m_armatureIndex = -2;    // is loading
	}
	else if(m_armatureIndex>=0 && m_armature != NULL)
	{
		this->removeChild(m_armature);
		m_armatureIndex = m_armatureIndex==BINARYFILECOUNT-1 ? 0 : m_armatureIndex+1;
		m_armature = Armature::create(m_armatureNames[m_armatureIndex]);
		m_armature->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
		if(m_armatureIndex == 2 )  // cowboy is 0.2
			m_armature->setScale(0.2f);
		m_armature->getAnimation()->playWithIndex(0);
		addChild(m_armature);
	}
}


void TestLoadFromBinary::dataLoaded( float percent )
{
	Label *label = (Label *)getChildByTag(10001);
	if (label)
	{
		char pszPercent[255];
		sprintf(pszPercent, "%s %f", "Asynchronous loading: ", percent * 100);
		label->setString(pszPercent);
	}
    
	if (percent >= 1)
	{
		label->setString("Touch to change armature");
		m_armatureIndex = 0;
	}
}
