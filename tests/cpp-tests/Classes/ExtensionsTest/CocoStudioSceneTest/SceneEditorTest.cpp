#include "extensions/cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TriggerCode/EventDef.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

CocoStudioSceneEditTests::CocoStudioSceneEditTests()
{
    ADD_TEST_CASE(LoadSceneEdtiorFileTest);
    ADD_TEST_CASE(SpriteComponentTest);
    ADD_TEST_CASE(ArmatureComponentTest);
    ADD_TEST_CASE(UIComponentTest);
    ADD_TEST_CASE(TmxMapComponentTest);
    ADD_TEST_CASE(ParticleComponentTest);
    ADD_TEST_CASE(EffectComponentTest);
    ADD_TEST_CASE(BackgroundComponentTest);
    ADD_TEST_CASE(AttributeComponentTest);
    ADD_TEST_CASE(TriggerTest);
}

const char* SceneEditorTestBase::_loadtypeStr[2] = {"change to load \nwith binary file","change to load \nwith json file"};
bool SceneEditorTestBase::init()
{
    if (TestCase::init())
    {
        _isCsbLoad = false;
        _loadtypelb = cocos2d::Label::createWithSystemFont(_loadtypeStr[0], "Arial", 12);
        // #endif        
        MenuItemLabel* itemlb = CCMenuItemLabel::create(_loadtypelb, CC_CALLBACK_1(SceneEditorTestBase::changeLoadTypeCallback, this));
        Menu* loadtypemenu = CCMenu::create(itemlb, nullptr);
        loadtypemenu->setPosition(Point(VisibleRect::rightTop().x - 50, VisibleRect::rightTop().y - 20));
        addChild(loadtypemenu, 100);

        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

        return true;
    }
	
    return false;
}

std::string SceneEditorTestBase::title() const
{
    return "SceneReader Test LoadSceneEditorFile";
}

void SceneEditorTestBase::changeLoadTypeCallback(cocos2d::Ref *pSender)
{
	_isCsbLoad = !_isCsbLoad;
	_loadtypelb->setString(_loadtypeStr[(int)_isCsbLoad]);
	loadFileChangeHelper(_filePath);
	
	if(_rootNode != nullptr)
	{
        ActionManagerEx::getInstance()->releaseActions();
		this->removeChild(_rootNode);
		_rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
		if (_rootNode == nullptr)
		{
			return ;
		}
		defaultPlay();
		this->addChild(_rootNode);
	}
}

void SceneEditorTestBase::loadFileChangeHelper(std::string& filePathName)
{
    std::string::size_type n = filePathName.find_last_of(".");
	if(n == std::string::npos)
		return;
	filePathName = filePathName.substr(0,n);
	if(_isCsbLoad)
		filePathName.append(".csb");
	else
		filePathName.append(".json");
}

LoadSceneEdtiorFileTest::LoadSceneEdtiorFileTest()
{
	
}

LoadSceneEdtiorFileTest::~LoadSceneEdtiorFileTest()
{

}

std::string LoadSceneEdtiorFileTest::title() const
{
    return "loadSceneEdtiorFile Test";
}

void LoadSceneEdtiorFileTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void LoadSceneEdtiorFileTest::onExit()
{
	 ArmatureDataManager::destroyInstance();
	 SceneReader::destroyInstance();
	 ActionManagerEx::destroyInstance();
	 GUIReader::destroyInstance();
	 SceneEditorTestBase::onExit();
}


cocos2d::Node* LoadSceneEdtiorFileTest::createGameScene()
{
    _filePath = "scenetest/LoadSceneEdtiorFileTest/FishJoy2.json";  //default is json
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
    ActionManagerEx::getInstance()->playActionByName("startMenu_1.json", "Animation1");
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
	defaultPlay();
    return _rootNode;
}

void LoadSceneEdtiorFileTest::defaultPlay()
{
	
}

SpriteComponentTest::SpriteComponentTest()
{
	
}

SpriteComponentTest::~SpriteComponentTest()
{

}

std::string SpriteComponentTest::title() const
{
    return "Sprite Component Test";
}

void SpriteComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void SpriteComponentTest::onExit()
{
	 ArmatureDataManager::destroyInstance();
	 SceneReader::destroyInstance();
	 ActionManagerEx::destroyInstance();
	 GUIReader::destroyInstance();
	 SceneEditorTestBase::onExit();
}

cocos2d::Node* SpriteComponentTest::createGameScene()
{
	_filePath = "scenetest/SpriteComponentTest/SpriteComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}

	defaultPlay();

    return _rootNode;
}


void SpriteComponentTest::defaultPlay()
{
	ActionInterval*  action1 = CCBlink::create(2, 10);
	ActionInterval*  action2 = CCBlink::create(2, 5);

	ComRender *pSister1 = static_cast<ComRender*>(_rootNode->getChildByTag(10003)->getComponent("CCSprite"));
	pSister1->getNode()->runAction(action1);

	ComRender *pSister2 = static_cast<ComRender*>(_rootNode->getChildByTag(10004)->getComponent("CCSprite"));
	pSister2->getNode()->runAction(action2);
}

ArmatureComponentTest::ArmatureComponentTest()
{
	
}

ArmatureComponentTest::~ArmatureComponentTest()
{
	
}

std::string ArmatureComponentTest::title() const
{
    return "Armature Component Test";
}

void ArmatureComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void ArmatureComponentTest::onExit()
{
	 ArmatureDataManager::destroyInstance();
	 SceneReader::destroyInstance();
	 ActionManagerEx::destroyInstance();
	 GUIReader::destroyInstance();
	 SceneEditorTestBase::onExit();
}

cocos2d::Node* ArmatureComponentTest::createGameScene()
{
	_filePath = "scenetest/ArmatureComponentTest/ArmatureComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
	defaultPlay();
    return _rootNode;
}

void ArmatureComponentTest::defaultPlay()
{
	ComRender *pBlowFish = static_cast<ComRender*>(_rootNode->getChildByTag(10007)->getComponent("CCArmature"));
	pBlowFish->getNode()->runAction(MoveBy::create(10.0f, Point(-1000.0f, 0)));

	ComRender *pButterflyfish = static_cast<ComRender*>(_rootNode->getChildByTag(10008)->getComponent("CCArmature"));
	pButterflyfish->getNode()->runAction(MoveBy::create(10.0f, Point(-1000.0f, 0)));

}

UIComponentTest::UIComponentTest()
{
	
}

UIComponentTest::~UIComponentTest()
{
}

std::string UIComponentTest::title() const
{
    return "UI Component Test";
}

void UIComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void UIComponentTest::onExit()
{
	 ArmatureDataManager::destroyInstance();
	 SceneReader::destroyInstance();
	 ActionManagerEx::destroyInstance();
	 GUIReader::destroyInstance();
	 SceneEditorTestBase::onExit();
}

cocos2d::Node* UIComponentTest::createGameScene()
{
	_filePath = "scenetest/UIComponentTest/UIComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
	defaultPlay();
    
    return _rootNode;
}

void UIComponentTest::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
        case ui::Widget::TouchEventType::BEGAN:
		{
			ComRender *pBlowFish = static_cast<ComRender*>(_rootNode->getChildByTag(10010)->getComponent("CCArmature"));
			pBlowFish->getNode()->runAction(CCMoveBy::create(10.0f, Vec2(-1000.0f, 0)));

			ComRender *pButterflyfish = static_cast<ComRender*>(_rootNode->getChildByTag(10011)->getComponent("CCArmature"));
			pButterflyfish->getNode()->runAction(CCMoveBy::create(10.0f, Vec2(-1000.0f, 0)));
		}
		break;
	default:
		break;
	}
}

void UIComponentTest::defaultPlay()
{

    ComRender *render = static_cast<ComRender*>(_rootNode->getChildByTag(10025)->getComponent("GUIComponent"));
	Widget* widget = static_cast<cocos2d::ui::Widget*>(render->getNode());
	Button* button = static_cast<Button*>(widget->getChildByName("Button_156"));
    button->addTouchEventListener(CC_CALLBACK_2(UIComponentTest::touchEvent, this));
}

TmxMapComponentTest::TmxMapComponentTest()
{
	
}

TmxMapComponentTest::~TmxMapComponentTest()
{

}

std::string TmxMapComponentTest::title() const
{
    return "TmxMap Component Test";
}

void TmxMapComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void TmxMapComponentTest::onExit()
{
    ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

cocos2d::Node* TmxMapComponentTest::createGameScene()
{
	_filePath = "scenetest/TmxMapComponentTest/TmxMapComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
    defaultPlay();
    return _rootNode;
}

void TmxMapComponentTest::defaultPlay()
{
	ComRender *tmxMap = static_cast<ComRender*>(_rootNode->getChildByTag(10015)->getComponent("CCTMXTiledMap"));
	ActionInterval *actionTo = CCSkewTo::create(2, 0.f, 2.f);
	ActionInterval *rotateTo = CCRotateTo::create(2, 61.0f);
	ActionInterval *actionScaleTo = CCScaleTo::create(2, -0.44f, 0.47f);

	ActionInterval *actionScaleToBack = CCScaleTo::create(2, 1.0f, 1.0f);
	ActionInterval *rotateToBack = CCRotateTo::create(2, 0);
	ActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);

	tmxMap->getNode()->runAction(CCSequence::create(actionTo, actionToBack, nullptr));
	tmxMap->getNode()->runAction(CCSequence::create(rotateTo, rotateToBack, nullptr));
	tmxMap->getNode()->runAction(CCSequence::create(actionScaleTo, actionScaleToBack, nullptr));
}

ParticleComponentTest::ParticleComponentTest()
{
	
}

ParticleComponentTest::~ParticleComponentTest()
{
}

std::string ParticleComponentTest::title() const
{
    return "Particle Component Test";
}

void ParticleComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void ParticleComponentTest::onExit()
{
	ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

cocos2d::Node* ParticleComponentTest::createGameScene()
{
	_filePath = "scenetest/ParticleComponentTest/ParticleComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
	defaultPlay();
    return _rootNode;
}

void ParticleComponentTest::defaultPlay()
{
	ComRender* Particle = static_cast<ComRender*>(_rootNode->getChildByTag(10020)->getComponent("CCParticleSystemQuad"));
	ActionInterval*  jump = CCJumpBy::create(5, Point(-500,0), 50, 4);
	FiniteTimeAction*  action = CCSequence::create( jump, jump->reverse(), nullptr);
	Particle->getNode()->runAction(action);
}


EffectComponentTest::EffectComponentTest()
{
	
}

EffectComponentTest::~EffectComponentTest()
{
}

std::string EffectComponentTest::title() const
{
    return "Effect Component Test";
}

void EffectComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void EffectComponentTest::onExit()
{
	ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

cocos2d::Node* EffectComponentTest::createGameScene()
{
	_filePath = "scenetest/EffectComponentTest/EffectComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
	if (_rootNode == nullptr)
	{
		return nullptr;
	}
    defaultPlay();  
	return _rootNode;
}

void EffectComponentTest::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	 std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Fire") == 0)
		{
			ComAudio *pAudio = static_cast<ComAudio*>(_rootNode->getChildByTag(10015)->getComponent("CCComAudio"));
			pAudio->playEffect();
		}
	}
}

void EffectComponentTest::defaultPlay()
{
    ComRender *render = static_cast<ComRender*>(_rootNode->getChildByTag(10015)->getComponent("CCArmature"));
	Armature *pAr = static_cast<Armature*>(render->getNode());
	pAr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(EffectComponentTest::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

BackgroundComponentTest::BackgroundComponentTest()
{
	
}

BackgroundComponentTest::~BackgroundComponentTest()
{
}

std::string BackgroundComponentTest::title() const
{
    return "Background Component Test";
}

void BackgroundComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
    do
    {
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
    } while (0);
}

void BackgroundComponentTest::onExit()
{
    ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

cocos2d::Node* BackgroundComponentTest::createGameScene()
{
    _filePath = "scenetest/BackgroundComponentTest/BackgroundComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
    if (_rootNode == nullptr)
    {
        return nullptr;
    }
    defaultPlay();
    return _rootNode;
}

void BackgroundComponentTest::defaultPlay()
{
    ComAudio *Audio = static_cast<ComAudio*>(_rootNode->getComponent("CCBackgroundAudio"));
    Audio->playBackgroundMusic();
}


AttributeComponentTest::AttributeComponentTest()
{
	
}

AttributeComponentTest::~AttributeComponentTest()
{
}

std::string AttributeComponentTest::title() const
{
    return "Attribute Component Test";
}

void AttributeComponentTest::onEnter()
{
    SceneEditorTestBase::onEnter();
    do
    {
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        defaultPlay();
        this->addChild(root, 0, 1);
    } while (0);
}

void AttributeComponentTest::onExit()
{
	ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

bool AttributeComponentTest::initData()
{
    bool bRet = false;
    rapidjson::Document doc;
    do {
        CC_BREAK_IF(_rootNode == nullptr);
        ComAttribute *attribute = static_cast<ComAttribute*>(_rootNode->getChildByTag(10015)->getComponent("CCComAttribute"));
        CC_BREAK_IF(attribute == nullptr);
        log("Name: %s, HP: %f, MP: %f", attribute->getString("name").c_str(), attribute->getFloat("maxHP"), attribute->getFloat("maxMP"));

        bRet = true;
    } while (0);
    return bRet;
}

cocos2d::Node* AttributeComponentTest::createGameScene()
{
    _filePath = "scenetest/AttributeComponentTest/AttributeComponentTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
    if (_rootNode == nullptr)
    {
        return nullptr;
    }
    return _rootNode;
}

void AttributeComponentTest::defaultPlay()
{
    initData();
}

TriggerTest::TriggerTest()
: _touchListener(nullptr)
{
	
}

TriggerTest::~TriggerTest()
{
}

std::string TriggerTest::title() const
{
    return "Trigger Test";
}


// on "init" you need to initialize your instance
void TriggerTest::onEnter()
{
    SceneEditorTestBase::onEnter();
    Node *root = createGameScene();
    this->addChild(root, 0, 1);
    this->schedule(CC_SCHEDULE_SELECTOR(TriggerTest::gameLogic));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TriggerTest::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TriggerTest::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TriggerTest::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TriggerTest::onTouchCancelled, this);
    dispatcher->addEventListenerWithFixedPriority(listener, 1);
    _touchListener = listener;
}


void TriggerTest::onExit()
{
    sendEvent(TRIGGEREVENT_LEAVESCENE);
    this->unschedule(CC_SCHEDULE_SELECTOR(TriggerTest::gameLogic));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(_touchListener);
    Device::setAccelerometerEnabled(false);
    ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestBase::onExit();
}

bool TriggerTest::onTouchBegan(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHBEGAN);
    return true;
}

void TriggerTest::onTouchMoved(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHMOVED);
}

void TriggerTest::onTouchEnded(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHENDED);
}

void TriggerTest::onTouchCancelled(Touch *touch, Event *unused_event)
{
    sendEvent(TRIGGEREVENT_TOUCHCANCELLED);
}

void TriggerTest::gameLogic(float dt)
{
    sendEvent(TRIGGEREVENT_UPDATESCENE);
}


cocos2d::Node* TriggerTest::createGameScene()
{
    _filePath = "scenetest/TriggerTest/TriggerTest.json";
    _rootNode = SceneReader::getInstance()->createNodeWithSceneFile(_filePath.c_str());
    if (_rootNode == nullptr)
    {
        return nullptr;
    }
    
    defaultPlay();
    return _rootNode;
}
void TriggerTest::defaultPlay()
{
    sendEvent(TRIGGEREVENT_ENTERSCENE);
}
