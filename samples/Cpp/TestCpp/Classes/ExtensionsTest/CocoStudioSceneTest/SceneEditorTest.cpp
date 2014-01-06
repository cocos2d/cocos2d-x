
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "TriggerCode/EventDef.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::gui;

CCLayer *Next();
CCLayer *Back();
CCLayer *Restart();

static int s_nIdx = -1;

CCLayer *createTests(int index)
{
    CCLayer *pLayer = NULL;
    switch(index)
    {
    case TEST_LOADSCENEEDITORFILE:
        pLayer = new LoadSceneEdtiorFileTest();
        break;
    case TEST_SPIRTECOMPONENT:
        pLayer = new SpriteComponentTest();
        break;
    case TEST_ARMATURECOMPONENT:
        pLayer = new ArmatureComponentTest();
        break;
    case TEST_UICOMPONENT:
        pLayer = new UIComponentTest();
        break;
    case TEST_TMXMAPCOMPONENT:
        pLayer = new TmxMapComponentTest();
        break;
    case TEST_PARTICLECOMPONENT:
        pLayer = new ParticleComponentTest();
        break;
    case TEST_EFEECTCOMPONENT:
        pLayer = new EffectComponentTest();
        break;
    case TEST_BACKGROUNDCOMPONENT:
        pLayer = new BackgroundComponentTest();
        break;
    case TEST_ATTRIBUTECOMPONENT:
        pLayer = new AttributeComponentTest();
        break;
    case TEST_TRIGGER:
        pLayer = new TriggerTest();
		pLayer->init();
        break;
    default:
        break;
    }
    return pLayer;
}

CCLayer *Next()
{
    ++s_nIdx;
    s_nIdx = s_nIdx % TEST_SCENEEDITOR_COUNT;

    CCLayer *pLayer = createTests(s_nIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *Back()
{
    --s_nIdx;
    if( s_nIdx < 0 )
        s_nIdx += TEST_SCENEEDITOR_COUNT;

    CCLayer *pLayer = createTests(s_nIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer *Restart()
{
    CCLayer *pLayer = createTests(s_nIdx);
    pLayer->autorelease();

    return pLayer;
}

SceneEditorTestScene::SceneEditorTestScene(bool bPortrait)
{
    TestScene::init();
}

void SceneEditorTestScene::runThisTest()
{
    s_nIdx = -1;
    addChild(Next());
    CCDirector::sharedDirector()->replaceScene(this);
}

void SceneEditorTestScene::MainMenuCallback(CCObject *pSender)
{
    TestScene::MainMenuCallback(pSender);
}


void SceneEditorTestLayer::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char *pTitle = str.c_str();
    CCLabelTTF *label = CCLabelTTF::create(pTitle, "Arial", 18);
    label->setColor(ccc3(255, 255, 255));
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
    backItem = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(SceneEditorTestLayer::backCallback) );
    restartItem = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(SceneEditorTestLayer::restartCallback) );
    nextItem = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(SceneEditorTestLayer::nextCallback) );
    
    CCMenu *menu = CCMenu::create(backItem, restartItem, nextItem, NULL);
    
    float fScale = 0.5f;
    
    menu->setPosition(ccp(0, 0));
    backItem->setPosition(ccp(VisibleRect::center().x - restartItem->getContentSize().width * 2 * fScale, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    backItem->setScale(fScale);
    
    restartItem->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    restartItem->setScale(fScale);
    
    nextItem->setPosition(ccp(VisibleRect::center().x + restartItem->getContentSize().width * 2 * fScale, VisibleRect::bottom().y + restartItem->getContentSize().height / 2));
    nextItem->setScale(fScale);
    
    addChild(menu, 100);
    
    
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

}
void SceneEditorTestLayer::onExit()
{
    removeAllChildren();

    backItem = restartItem = nextItem = NULL;
}

std::string SceneEditorTestLayer::title()
{
    return "SceneReader Test LoadSceneEditorFile";
}

std::string SceneEditorTestLayer::subtitle()
{
    return "";
}

void SceneEditorTestLayer::restartCallback(CCObject *pSender)
{
    CCScene *s = new SceneEditorTestScene();
    s->addChild(Restart());
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void SceneEditorTestLayer::nextCallback(CCObject *pSender)
{
    CCScene *s = new SceneEditorTestScene();
    s->addChild(Next());
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void SceneEditorTestLayer::backCallback(CCObject *pSender)
{
    CCScene *s = new SceneEditorTestScene();
    s->addChild(Back());
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
void SceneEditorTestLayer::draw()
{
    CCLayer::draw();
}

LoadSceneEdtiorFileTest::LoadSceneEdtiorFileTest()
{
	
}

LoadSceneEdtiorFileTest::~LoadSceneEdtiorFileTest()
{

}

std::string LoadSceneEdtiorFileTest::title()
{
    return "LoadSceneEdtiorFile Test";
}

void LoadSceneEdtiorFileTest::onEnter()
{
    SceneEditorTestLayer::onEnter();
	do 
	{
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void LoadSceneEdtiorFileTest::onExit()
{
	 CCArmatureDataManager::purge();
	 SceneReader::purge();
	 ActionManager::purge();
	 GUIReader::purge();
	 SceneEditorTestLayer::onExit();
}


cocos2d::CCNode* LoadSceneEdtiorFileTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/LoadSceneEdtiorFileTest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	cocos2d::extension::ActionManager::shareManager()->playActionByName("startMenu_1.json","Animation1");
    return pNode;
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void SpriteComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* SpriteComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/SpriteComponentTest/SpriteComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}

	CCActionInterval*  action1 = CCBlink::create(2, 10);
	CCActionInterval*  action2 = CCBlink::create(2, 5);

	CCComRender *pSister1 = static_cast<CCComRender*>(pNode->getChildByTag(10003)->getComponent("CCSprite"));
	pSister1->getNode()->runAction(action1);

	CCComRender *pSister2 = static_cast<CCComRender*>(pNode->getChildByTag(10004)->getComponent("CCSprite"));
	pSister2->getNode()->runAction(action2);

    return pNode;
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void ArmatureComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* ArmatureComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/ArmatureComponentTest/ArmatureComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	CCComRender *pBlowFish = static_cast<CCComRender*>(pNode->getChildByTag(10007)->getComponent("CCArmature"));
	pBlowFish->getNode()->runAction(CCMoveBy::create(10.0f, ccp(-1000.0f, 0)));

	CCComRender *pButterflyfish = static_cast<CCComRender*>(pNode->getChildByTag(10008)->getComponent("CCArmature"));
	pButterflyfish->getNode()->runAction(CCMoveBy::create(10.0f, ccp(-1000.0f, 0)));

    return pNode;
}

UIComponentTest::UIComponentTest()
: _node(NULL)
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void UIComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* UIComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/UIComponentTest/UIComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_node = pNode;
	
    
    CCComRender *render = static_cast<CCComRender*>(_node->getChildByTag(10025)->getComponent("GUIComponent"));
	cocos2d::gui::TouchGroup* touchGroup = static_cast<cocos2d::gui::TouchGroup*>(render->getNode());
	UIWidget* widget = static_cast<UIWidget*>(touchGroup->getWidgetByName("Panel_154"));
	UIButton* button = static_cast<UIButton*>(widget->getChildByName("Button_156"));
	button->addTouchEventListener(this, toucheventselector(UIComponentTest::touchEvent));

    return pNode;
}

void UIComponentTest::touchEvent(CCObject *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			CCComRender *pBlowFish = static_cast<CCComRender*>(_node->getChildByTag(10010)->getComponent("CCArmature"));
			pBlowFish->getNode()->runAction(CCMoveBy::create(10.0f, ccp(-1000.0f, 0)));

			CCComRender *pButterflyfish = static_cast<CCComRender*>(_node->getChildByTag(10011)->getComponent("CCArmature"));
			pButterflyfish->getNode()->runAction(CCMoveBy::create(10.0f, ccp(-1000.0f, 0)));
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void TmxMapComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* TmxMapComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/TmxMapComponentTest/TmxMapComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
    
	CCComRender *tmxMap = static_cast<CCComRender*>(pNode->getChildByTag(10015)->getComponent("CCTMXTiledMap"));
	CCActionInterval *actionTo = CCSkewTo::create(2, 0.f, 2.f);
	CCActionInterval *rotateTo = CCRotateTo::create(2, 61.0f);
	CCActionInterval *actionScaleTo = CCScaleTo::create(2, -0.44f, 0.47f);

	CCActionInterval *actionScaleToBack = CCScaleTo::create(2, 1.0f, 1.0f);
	CCActionInterval *rotateToBack = CCRotateTo::create(2, 0);
	CCActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);

	tmxMap->getNode()->runAction(CCSequence::create(actionTo, actionToBack, NULL));
	tmxMap->getNode()->runAction(CCSequence::create(rotateTo, rotateToBack, NULL));
	tmxMap->getNode()->runAction(CCSequence::create(actionScaleTo, actionScaleToBack, NULL));
    return pNode;
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void ParticleComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* ParticleComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/ParticleComponentTest/ParticleComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}

	CCComRender* Particle = static_cast<CCComRender*>(pNode->getChildByTag(10020)->getComponent("CCParticleSystemQuad"));
	CCActionInterval*  jump = CCJumpBy::create(5, ccp(-500,0), 50, 4);
	CCFiniteTimeAction*  action = CCSequence::create( jump, jump->reverse(), NULL);
	Particle->getNode()->runAction(action);
    return pNode;
}


EffectComponentTest::EffectComponentTest()
: _node(NULL)
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void EffectComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* EffectComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/EffectComponentTest/EffectComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_node = pNode;
    
	CCComRender *pRender = static_cast<CCComRender*>(_node->getChildByTag(10015)->getComponent("CCArmature"));
	CCArmature *pAr = static_cast<CCArmature*>(pRender->getNode());
	pAr->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(EffectComponentTest::animationEvent));
    return pNode;
}

void EffectComponentTest::animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID)
{
	 std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Fire") == 0)
		{
			CCComAudio *pAudio = static_cast<CCComAudio*>(_node->getChildByTag(10015)->getComponent("CCComAudio"));
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void BackgroundComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* BackgroundComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/BackgroundComponentTest/BackgroundComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	cocos2d::extension::ActionManager::shareManager()->playActionByName("startMenu_1.json","Animation1");

	CCComAudio *Audio = static_cast<CCComAudio*>(pNode->getComponent("CCBackgroundAudio"));
	Audio->playBackgroundMusic();
    return pNode;
}


AttributeComponentTest::AttributeComponentTest()
: _node(NULL)
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
        CCNode *root = createGameScene();
        initData();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
	} while (0);
}

void AttributeComponentTest::onExit()
{
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
    SceneEditorTestLayer::onExit();
}

bool AttributeComponentTest::initData()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(_node == NULL);
		CCComAttribute *pAttribute = static_cast<CCComAttribute*>(_node->getChildByTag(10015)->getComponent("CCComAttribute"));
		CCLog("Name: %s, HP: %f, MP: %f", pAttribute->getCString("name"), pAttribute->getFloat("maxHP"), pAttribute->getFloat("maxMP"));
		bRet = true;
	} while (0);
	return bRet;
}

cocos2d::CCNode* AttributeComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/AttributeComponentTest/AttributeComponentTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_node = pNode;
    return pNode;
}


TriggerTest::TriggerTest()
{
	_node = NULL;
}

TriggerTest::~TriggerTest()
{
}

std::string TriggerTest::title()
{
    return "Trigger Test";
}

bool TriggerTest::init()
{
   sendEvent(TRIGGEREVENT_INITSCENE);
   return true;
}

void TriggerTest::onEnter()
{
	SceneEditorTestLayer::onEnter();
	CCNode *root = createGameScene();
	this->addChild(root, 0, 1);
	this->schedule(schedule_selector(TriggerTest::gameLogic));
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
	sendEvent(TRIGGEREVENT_ENTERSCENE);
}

void TriggerTest::onExit()
{
	sendEvent(TRIGGEREVENT_LEAVESCENE);
    this->unschedule(schedule_selector(TriggerTest::gameLogic));
	this->setTouchEnabled(false);
	CCArmatureDataManager::purge();
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
	SceneEditorTestLayer::onExit();
}

bool TriggerTest::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHBEGAN);
	return true;
}

void TriggerTest::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHMOVED);
}

void TriggerTest::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHENDED); 
}

void TriggerTest::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	sendEvent(TRIGGEREVENT_TOUCHCANCELLED);
}

void TriggerTest::gameLogic(float dt)
{
    sendEvent(TRIGGEREVENT_UPDATESCENE);
}

static ActionObject* actionObject = NULL;

cocos2d::CCNode* TriggerTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/TriggerTest/TriggerTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_node = pNode;
    
	//ui action
	actionObject = cocos2d::extension::ActionManager::shareManager()->playActionByName("startMenu_1.json","Animation1");

    return pNode;
}


