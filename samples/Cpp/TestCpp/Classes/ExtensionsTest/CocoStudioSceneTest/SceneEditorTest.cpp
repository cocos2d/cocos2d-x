
#include "extensions/cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "cocostudio/CocoStudio.h"
#include "gui/CocosGUI.h"
#include "TriggerCode/EventDef.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace gui;

Layer *Next();
Layer *Back();
Layer *Restart();

static int s_nIdx = -1;

Layer *createTests(int index)
{
    Layer *layer = nullptr;
    switch(index)
    {
    case TEST_LOADSCENEEDITORFILE:
        layer = new loadSceneEdtiorFileTest();
        break;
    case TEST_SPIRTECOMPONENT:
        layer = new SpriteComponentTest();
        break;
    case TEST_ARMATURECOMPONENT:
        layer = new ArmatureComponentTest();
        break;
    case TEST_UICOMPONENT:
        layer = new UIComponentTest();
        break;
    case TEST_TMXMAPCOMPONENT:
        layer = new TmxMapComponentTest();
        break;
    case TEST_PARTICLECOMPONENT:
        layer = new ParticleComponentTest();
        break;
    case TEST_EFEECTCOMPONENT:
        layer = new EffectComponentTest();
        break;
    case TEST_BACKGROUNDCOMPONENT:
        layer = new BackgroundComponentTest();
        break;
    case TEST_ATTRIBUTECOMPONENT:
        layer = new AttributeComponentTest();
        break;
    case TEST_TRIGGER:
        layer = new TriggerTest();
        break;
    default:
        break;
    }
    return layer;
}

Layer *Next()
{
    ++s_nIdx;
    s_nIdx = s_nIdx % TEST_SCENEEDITOR_COUNT;

    Layer *layer = createTests(s_nIdx);
    layer->autorelease();

    return layer;
}

Layer *Back()
{
    --s_nIdx;
    if( s_nIdx < 0 )
        s_nIdx += TEST_SCENEEDITOR_COUNT;

    Layer *layer = createTests(s_nIdx);
    layer->autorelease();

    return layer;
}

Layer *Restart()
{
    Layer *layer = createTests(s_nIdx);
    layer->autorelease();

    return layer;
}

SceneEditorTestScene::SceneEditorTestScene(bool bPortrait)
{
    TestScene::init();
}

void SceneEditorTestScene::runThisTest()
{
    s_nIdx = -1;
    addChild(Next());
    CCDirector::getInstance()->replaceScene(this);
}

void SceneEditorTestScene::MainMenuCallback(Object *pSender)
{
    removeAllChildren();
}


void SceneEditorTestLayer::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *pTitle = str.c_str();
    LabelTTF *label = LabelTTF::create(pTitle, "Arial", 18);
    label->setColor(Color3B(255, 255, 255));
    addChild(label, 1, 10000);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        LabelTTF *l = LabelTTF::create(strSubtitle.c_str(), "Arial", 18);
        l->setColor(Color3B(0, 0, 0));
        addChild(l, 1, 10001);
        l->setPosition(Point(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    // add menu
    backItem = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(SceneEditorTestLayer::backCallback, this) );
    restartItem = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(SceneEditorTestLayer::restartCallback, this) );
    nextItem = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(SceneEditorTestLayer::nextCallback, this) );

    
    Menu *menu = Menu::create(backItem, restartItem, nextItem, nullptr);
    
    float fScale = 0.5f;
    
    menu->setPosition(Point(0, 0));
    backItem->setPosition(Point(VisibleRect::center().x - restartItem->getContentSize().width * 2 * fScale, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    backItem->setScale(fScale);
    
    restartItem->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setScale(fScale);
    
    nextItem->setPosition(Point(VisibleRect::center().x + restartItem->getContentSize().width * 2 * fScale, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setScale(fScale);
    
    addChild(menu, 100);
    
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}

void SceneEditorTestLayer::onExit()
{
    removeAllChildren();
    backItem = restartItem = nextItem = nullptr;
    Layer::onExit();
}

std::string SceneEditorTestLayer::title()
{
    return "SceneReader Test LoadSceneEditorFile";
}

std::string SceneEditorTestLayer::subtitle()
{
    return "";
}

void SceneEditorTestLayer::restartCallback(Object *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Restart());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::nextCallback(Object *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Next());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::backCallback(Object *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Back());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::draw()
{
    Layer::draw();
}


loadSceneEdtiorFileTest::loadSceneEdtiorFileTest()
{
	
}

loadSceneEdtiorFileTest::~loadSceneEdtiorFileTest()
{

}

std::string loadSceneEdtiorFileTest::title()
{
    return "loadSceneEdtiorFile Test";
}

void loadSceneEdtiorFileTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void loadSceneEdtiorFileTest::onExit()
{
	 ArmatureDataManager::getInstance()->destroyInstance();
	 SceneReader::getInstance()->destroyInstance();
	 ActionManagerEx::getInstance()->destroyInstance();
	 GUIReader::shareReader()->purgeGUIReader();
	 SceneEditorTestLayer::onExit();
}


cocos2d::Node* loadSceneEdtiorFileTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/loadSceneEdtiorFileTest/FishJoy2.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	ActionManagerEx::getInstance()->playActionByName("startMenu_1.json","Animation1");
    return node;
}

SpriteComponentTest::SpriteComponentTest()
{
	
}

SpriteComponentTest::~SpriteComponentTest()
{

}

std::string SpriteComponentTest::title()
{
    return "Sprite Component Test";
}

void SpriteComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void SpriteComponentTest::onExit()
{
	 ArmatureDataManager::getInstance()->destroyInstance();
	 SceneReader::getInstance()->destroyInstance();
	 ActionManagerEx::getInstance()->destroyInstance();
	 GUIReader::shareReader()->purgeGUIReader();
	 SceneEditorTestLayer::onExit();
}

cocos2d::Node* SpriteComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/SpriteComponentTest/SpriteComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}

	ActionInterval*  action1 = CCBlink::create(2, 10);
	ActionInterval*  action2 = CCBlink::create(2, 5);

	Sprite *pSister1 = static_cast<Sprite*>(node->getChildByTag(10003)->getComponent("CCSprite")->getNode());
	pSister1->runAction(action1);

	Sprite *pSister2 = static_cast<Sprite*>(node->getChildByTag(10004)->getComponent("CCSprite")->getNode());
	pSister2->runAction(action2);

    return node;
}

ArmatureComponentTest::ArmatureComponentTest()
{
	
}

ArmatureComponentTest::~ArmatureComponentTest()
{
	
}

std::string ArmatureComponentTest::title()
{
    return "Armature Component Test";
}

void ArmatureComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void ArmatureComponentTest::onExit()
{
	 ArmatureDataManager::getInstance()->destroyInstance();
	 SceneReader::getInstance()->destroyInstance();
	 ActionManagerEx::getInstance()->destroyInstance();
	 GUIReader::shareReader()->purgeGUIReader();
	 SceneEditorTestLayer::onExit();
}

cocos2d::Node* ArmatureComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/ArmatureComponentTest/ArmatureComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	Armature *pBlowFish = static_cast<Armature*>(node->getChildByTag(10007)->getComponent("CCArmature")->getNode());
	pBlowFish->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

	Armature *pButterflyfish = static_cast<Armature*>(node->getChildByTag(10008)->getComponent("CCArmature")->getNode());
	pButterflyfish->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

    return node;
}

UIComponentTest::UIComponentTest()
: _node(nullptr)
{
	
}

UIComponentTest::~UIComponentTest()
{
}

std::string UIComponentTest::title()
{
    return "UI Component Test";
}

void UIComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void UIComponentTest::onExit()
{
	 ArmatureDataManager::getInstance()->destroyInstance();
	 SceneReader::getInstance()->destroyInstance();
	 ActionManagerEx::getInstance()->destroyInstance();
	 GUIReader::shareReader()->purgeGUIReader();
	 SceneEditorTestLayer::onExit();
}

cocos2d::Node* UIComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/UIComponentTest/UIComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	_node = node;
	
	Widget* widget = static_cast<cocos2d::gui::Widget*>(_node->getChildByTag(10025)->getComponent("GUIComponent")->getNode());
	Button* button = static_cast<Button*>(widget->getChildByName("Button_156"));
	button->addTouchEventListener(this, toucheventselector(UIComponentTest::touchEvent));

    return node;
}

void UIComponentTest::touchEvent(Object *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			Armature *pBlowFish = static_cast<Armature*>(_node->getChildByTag(10010)->getComponent("Armature")->getNode());
			pBlowFish->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

			Armature *pButterflyfish = static_cast<Armature*>(_node->getChildByTag(10011)->getComponent("Armature")->getNode());
			pButterflyfish->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));
		}
		break;
	default:
		break;
	}
}

TmxMapComponentTest::TmxMapComponentTest()
{
	
}

TmxMapComponentTest::~TmxMapComponentTest()
{

}

std::string TmxMapComponentTest::title()
{
    return "TmxMap Component Test";
}

void TmxMapComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void TmxMapComponentTest::onExit()
{
    ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* TmxMapComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/TmxMapComponentTest/TmxMapComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	TMXTiledMap *tmxMap = static_cast<TMXTiledMap*>(node->getChildByTag(10015)->getComponent("TMXTiledMap")->getNode());
	ActionInterval *actionTo = SkewTo::create(2, 0.f, 2.f);
	ActionInterval *rotateTo = RotateTo::create(2, 61.0f);
	ActionInterval *actionScaleTo = ScaleTo::create(2, -0.44f, 0.47f);

	ActionInterval *actionScaleToBack = ScaleTo::create(2, 1.0f, 1.0f);
	ActionInterval *rotateToBack = RotateTo::create(2, 0);
	ActionInterval *actionToBack = SkewTo::create(2, 0, 0);

	tmxMap->runAction(Sequence::create(actionTo, actionToBack, nullptr));
	tmxMap->runAction(Sequence::create(rotateTo, rotateToBack, nullptr));
	tmxMap->runAction(Sequence::create(actionScaleTo, actionScaleToBack, nullptr));
    return node;
}

ParticleComponentTest::ParticleComponentTest()
{
	
}

ParticleComponentTest::~ParticleComponentTest()
{
}

std::string ParticleComponentTest::title()
{
    return "Particle Component Test";
}

void ParticleComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void ParticleComponentTest::onExit()
{
	ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* ParticleComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/ParticleComponentTest/ParticleComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}

	ParticleSystemQuad* Particle = static_cast<ParticleSystemQuad*>(node->getChildByTag(10020)->getComponent("CCParticleSystemQuad")->getNode());
	ActionInterval*  jump = JumpBy::create(5, Point(-500,0), 50, 4);
	FiniteTimeAction*  action = Sequence::create( jump, jump->reverse(), nullptr);
	Particle->runAction(action);
    return node;
}


EffectComponentTest::EffectComponentTest()
: _node(nullptr)
{
	
}

EffectComponentTest::~EffectComponentTest()
{
}

std::string EffectComponentTest::title()
{
    return "Effect Component Test";
}

void EffectComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void EffectComponentTest::onExit()
{
	ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* EffectComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/EffectComponentTest/EffectComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	_node = node;
	Armature *pAr = static_cast<Armature*>(_node->getChildByTag(10015)->getComponent("Armature")->getNode());
	pAr->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(EffectComponentTest::animationEvent));
    return node;
}

void EffectComponentTest::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	 std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Fire") == 0)
		{
			ComAudio *pAudio = static_cast<ComAudio*>(_node->getChildByTag(10015)->getComponent("CCComAudio"));
			pAudio->playEffect();
		}
	}
}

BackgroundComponentTest::BackgroundComponentTest()
{
	
}

BackgroundComponentTest::~BackgroundComponentTest()
{
}

std::string BackgroundComponentTest::title()
{
    return "Background Component Test";
}

void BackgroundComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void BackgroundComponentTest::onExit()
{
	ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* BackgroundComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/BackgroundComponentTest/BackgroundComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	ActionManagerEx::getInstance()->playActionByName("startMenu_1.json","Animation1");

	ComAudio *Audio = static_cast<ComAudio*>(node->getComponent("CCBackgroundAudio"));
	Audio->playBackgroundMusic();
    return node;
}


AttributeComponentTest::AttributeComponentTest()
: _node(nullptr)
{
	
}

AttributeComponentTest::~AttributeComponentTest()
{
}

std::string AttributeComponentTest::title()
{
    return "Attribute Component Test";
}

void AttributeComponentTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	bool bRet = false;
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
		initData();
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void AttributeComponentTest::onExit()
{
	ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
}

bool AttributeComponentTest::initData()
{
	bool bRet = false;
	unsigned long size = 0;
	unsigned char *pBytes = nullptr;
	rapidjson::Document doc;
	do {
		CC_BREAK_IF(_node == nullptr);
		ComAttribute *attribute = static_cast<ComAttribute*>(_node->getChildByTag(10015)->getComponent("CCComAttribute"));
		CC_BREAK_IF(attribute == nullptr);
		std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(attribute->getJsonName());
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
        doc.Parse<0>(contentStr.c_str());
        CC_BREAK_IF(doc.HasParseError());

		std::string playerName = DICTOOL->getStringValue_json(doc, "name");
		float maxHP = DICTOOL->getFloatValue_json(doc, "maxHP");
		float maxMP = DICTOOL->getFloatValue_json(doc, "maxMP");
		
		attribute->setString("Name", playerName);
		attribute->setFloat("MaxHP", maxHP);
		attribute->setFloat("MaxMP", maxMP);

		log("Name: %s, HP: %f, MP: %f", attribute->getString("Name").c_str(), attribute->getFloat("MaxHP"), attribute->getFloat("MaxMP"));

		bRet = true;
	} while (0);
	return bRet;
}

cocos2d::Node* AttributeComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/AttributeComponentTest/AttributeComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	_node = node;
    return node;
}





TriggerTest::TriggerTest()
: _node(nullptr)
, _touchListener(nullptr)
{
	
}

TriggerTest::~TriggerTest()
{
}

std::string TriggerTest::title()
{
    return "Trigger Test";
}


// on "init" you need to initialize your instance
void TriggerTest::onEnter()
{
	SceneEditorTestLayer::onEnter();
    Node *root = createGameScene();
    this->addChild(root, 0, 1);
    this->schedule(schedule_selector(TriggerTest::gameLogic));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SceneEditorTestLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SceneEditorTestLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SceneEditorTestLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SceneEditorTestLayer::onTouchCancelled, this);
    dispatcher->addEventListenerWithFixedPriority(listener, 1);
    _touchListener = listener;
    sendEvent(TRIGGEREVENT_ENTERSCENE);
}


void TriggerTest::onExit()
{
	sendEvent(TRIGGEREVENT_LEAVESCENE);
    this->unschedule(schedule_selector(TriggerTest::gameLogic));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(_touchListener);
    Device::setAccelerometerEnabled(false);
	ArmatureDataManager::getInstance()->destroyInstance();
    SceneReader::getInstance()->destroyInstance();
    ActionManagerEx::getInstance()->destroyInstance();
    GUIReader::shareReader()->purgeGUIReader();
    SceneEditorTestLayer::onExit();
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
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/TriggerTest/TriggerTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	_node = node;
   
    return node;
}
