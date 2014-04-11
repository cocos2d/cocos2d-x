
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
        layer = new LoadSceneEdtiorFileTest();
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

void SceneEditorTestScene::MainMenuCallback(Ref *pSender)
{
    removeAllChildren();
}


void SceneEditorTestLayer::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *pTitle = str.c_str();
    auto label = Label::createWithTTF(pTitle, "fonts/arial.ttf", 18);
    label->setTextColor(Color4B::WHITE);
    addChild(label, 1, 10000);
    label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        auto l = Label::createWithTTF(strSubtitle.c_str(), "fonts/arial.ttf", 18);
        l->setTextColor(Color4B::BLACK);
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

void SceneEditorTestLayer::restartCallback(Ref *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Restart());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::nextCallback(Ref *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Next());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::backCallback(Ref *pSender)
{
    Scene *s = new SceneEditorTestScene();
    s->addChild(Back());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SceneEditorTestLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    Layer::draw(renderer, transform, transformUpdated);
}


LoadSceneEdtiorFileTest::LoadSceneEdtiorFileTest()
{
	
}

LoadSceneEdtiorFileTest::~LoadSceneEdtiorFileTest()
{

}

std::string LoadSceneEdtiorFileTest::title()
{
    return "loadSceneEdtiorFile Test";
}

void LoadSceneEdtiorFileTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
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
	 SceneEditorTestLayer::onExit();
}


cocos2d::Node* LoadSceneEdtiorFileTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/LoadSceneEdtiorFileTest/FishJoy2.json");
	if (node == nullptr)
	{
		return nullptr;
	}
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

	ComRender *pSister1 = static_cast<ComRender*>(node->getChildByTag(10003)->getComponent("CCSprite"));
	pSister1->getNode()->runAction(action1);

	ComRender *pSister2 = static_cast<ComRender*>(node->getChildByTag(10004)->getComponent("CCSprite"));
	pSister2->getNode()->runAction(action2);

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
	 SceneEditorTestLayer::onExit();
}

cocos2d::Node* ArmatureComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/ArmatureComponentTest/ArmatureComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	ComRender *pBlowFish = static_cast<ComRender*>(node->getChildByTag(10007)->getComponent("CCArmature"));
	pBlowFish->getNode()->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

	ComRender *pButterflyfish = static_cast<ComRender*>(node->getChildByTag(10008)->getComponent("CCArmature"));
	pButterflyfish->getNode()->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

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
	
    ComRender *render = static_cast<ComRender*>(_node->getChildByTag(10025)->getComponent("GUIComponent"));
	Widget* widget = static_cast<cocos2d::ui::Widget*>(render->getNode());
	Button* button = static_cast<Button*>(widget->getChildByName("Button_156"));
	button->addTouchEventListener(this, toucheventselector(UIComponentTest::touchEvent));

    return node;
}

void UIComponentTest::touchEvent(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			ComRender *pBlowFish = static_cast<ComRender*>(_node->getChildByTag(10010)->getComponent("CCArmature"));
			pBlowFish->getNode()->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));

			ComRender *pButterflyfish = static_cast<ComRender*>(_node->getChildByTag(10011)->getComponent("CCArmature"));
			pButterflyfish->getNode()->runAction(CCMoveBy::create(10.0f, Point(-1000.0f, 0)));
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
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* TmxMapComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/TmxMapComponentTest/TmxMapComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}
	ComRender *tmxMap = static_cast<ComRender*>(node->getChildByTag(10015)->getComponent("CCTMXTiledMap"));
	ActionInterval *actionTo = SkewTo::create(2, 0.f, 2.f);
	ActionInterval *rotateTo = RotateTo::create(2, 61.0f);
	ActionInterval *actionScaleTo = ScaleTo::create(2, -0.44f, 0.47f);

	ActionInterval *actionScaleToBack = ScaleTo::create(2, 1.0f, 1.0f);
	ActionInterval *rotateToBack = RotateTo::create(2, 0);
	ActionInterval *actionToBack = SkewTo::create(2, 0, 0);

	tmxMap->getNode()->runAction(Sequence::create(actionTo, actionToBack, nullptr));
	tmxMap->getNode()->runAction(Sequence::create(rotateTo, rotateToBack, nullptr));
	tmxMap->getNode()->runAction(Sequence::create(actionScaleTo, actionScaleToBack, nullptr));
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
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* ParticleComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/ParticleComponentTest/ParticleComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}

	ComRender* Particle = static_cast<ComRender*>(node->getChildByTag(10020)->getComponent("CCParticleSystemQuad"));
	ActionInterval*  jump = JumpBy::create(5, Point(-500,0), 50, 4);
	FiniteTimeAction*  action = Sequence::create( jump, jump->reverse(), nullptr);
	Particle->getNode()->runAction(action);
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
    ComRender *render = static_cast<ComRender*>(_node->getChildByTag(10015)->getComponent("CCArmature"));
	Armature *pAr = static_cast<Armature*>(render->getNode());
	pAr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(EffectComponentTest::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
    SceneEditorTestLayer::onExit();
}

cocos2d::Node* BackgroundComponentTest::createGameScene()
{
    Node *node = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/BackgroundComponentTest/BackgroundComponentTest.json");
	if (node == nullptr)
	{
		return nullptr;
	}

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
	do 
	{
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
		initData();
        this->addChild(root, 0, 1);
	} while (0);
}

void AttributeComponentTest::onExit()
{
	ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
    SceneEditorTestLayer::onExit();
}

bool AttributeComponentTest::initData()
{
	bool bRet = false;
	rapidjson::Document doc;
	do {
		CC_BREAK_IF(_node == nullptr);
		ComAttribute *attribute = static_cast<ComAttribute*>(_node->getChildByTag(10015)->getComponent("CCComAttribute"));
		CC_BREAK_IF(attribute == nullptr);
		log("Name: %s, HP: %f, MP: %f", attribute->getString("name").c_str(), attribute->getFloat("maxHP"), attribute->getFloat("maxMP"));

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
	ArmatureDataManager::destroyInstance();
    SceneReader::destroyInstance();
    ActionManagerEx::destroyInstance();
    GUIReader::destroyInstance();
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
