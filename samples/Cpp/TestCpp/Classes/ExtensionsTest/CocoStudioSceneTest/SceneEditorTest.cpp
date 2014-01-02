
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"
#include "TriggerCode/EventDef.h"
#include "../../testResource.h"

using namespace cocos2d;
using namespace cocos2d::extension;

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
        pLayer = new loadSceneEdtiorFileTest();
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
    CCLabelTTF *label = CCLabelTTF::create(pTitle, "Arial", 10);
    label->setColor(ccc3(255, 255, 255));
    addChild(label, 1, 10000);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 10) );

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
    
    float fScale = 0.3f;
    
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

loadSceneEdtiorFileTest::loadSceneEdtiorFileTest()
{
	
}

loadSceneEdtiorFileTest::~loadSceneEdtiorFileTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void loadSceneEdtiorFileTest::onExit()
{

}


cocos2d::CCNode* loadSceneEdtiorFileTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
    return pNode;
}

SpriteComponentTest::SpriteComponentTest()
{
	
}

SpriteComponentTest::~SpriteComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void SpriteComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* SpriteComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}

ArmatureComponentTest::ArmatureComponentTest()
{
	
}

ArmatureComponentTest::~ArmatureComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void ArmatureComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* ArmatureComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}

UIComponentTest::UIComponentTest()
{
	
}

UIComponentTest::~UIComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void UIComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* UIComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}

TmxMapComponentTest::TmxMapComponentTest()
{
	
}

TmxMapComponentTest::~TmxMapComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void TmxMapComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* TmxMapComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}

ParticleComponentTest::ParticleComponentTest()
{
	
}

ParticleComponentTest::~ParticleComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void ParticleComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* ParticleComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
    return pNode;
}


EffectComponentTest::EffectComponentTest()
{
	
}

EffectComponentTest::~EffectComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void EffectComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* EffectComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}

BackgroundComponentTest::BackgroundComponentTest()
{
	
}

BackgroundComponentTest::~BackgroundComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void BackgroundComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* BackgroundComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}


AttributeComponentTest::AttributeComponentTest()
{
	
}

AttributeComponentTest::~AttributeComponentTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
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
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
		bRet = true;
	} while (0);
}

void AttributeComponentTest::onExit()
{
    SceneEditorTestLayer::onExit();
}

cocos2d::CCNode* AttributeComponentTest::createGameScene()
{
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}

    return pNode;
}


TriggerTest::TriggerTest()
{
	_pNode = NULL;
}

TriggerTest::~TriggerTest()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
}

std::string TriggerTest::title()
{
    return "TriggerTest Component Test";
}

bool TriggerTest::init()
{
	bool bRet = false;
	do 
	{
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);
        sendEvent(TRIGGEREVENT_INITSCENE);
	    this->schedule(schedule_selector(TriggerTest::gameLogic));
	    this->setTouchEnabled(true);
	    this->setTouchMode(kCCTouchesOneByOne);
		bRet = true;
	} while (0);

	return bRet;
}

void TriggerTest::onEnter()
{
	SceneEditorTestLayer::onEnter();
	sendEvent(TRIGGEREVENT_ENTERSCENE);
}

void TriggerTest::onExit()
{
	SceneEditorTestLayer::onExit();
	sendEvent(TRIGGEREVENT_LEAVESCENE);
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
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_pNode = pNode;
    
	//ui action
	actionObject = cocos2d::extension::ActionManager::shareManager()->playActionByName("startMenu_1.json","Animation1");

    return pNode;
}


