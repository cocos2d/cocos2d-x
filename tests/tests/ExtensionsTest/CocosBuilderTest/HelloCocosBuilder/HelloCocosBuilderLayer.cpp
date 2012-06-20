#include "HelloCocosBuilderLayer.h"

#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#include "../TestHeader/TestHeaderLayerLoader.h"
#include "../LabelTest/LabelTestLayerLoader.h"
#include "../ButtonTest/ButtonTestLayerLoader.h"
#include "../SpriteTest/SpriteTestLayerLoader.h"
#include "../MenuTest/MenuTestLayerLoader.h"
#include "../ParticleSystemTest/ParticleSystemTestLayerLoader.h"
#include "../ScrollViewTest/ScrollViewTestLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

HelloCocosBuilderLayer::HelloCocosBuilderLayer()
: mBurstSprite(NULL)
, mTestTitleLabelTTF(NULL)
{}

HelloCocosBuilderLayer::~HelloCocosBuilderLayer()
{
    CC_SAFE_RELEASE(mBurstSprite);
    CC_SAFE_RELEASE(mTestTitleLabelTTF);
}

void HelloCocosBuilderLayer::openTest(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader) {
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
        ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    }

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    CCNode * node = ccbReader->readNodeGraphFromFile("ccb/official/pub/", pCCBFileName, this);

    this->mTestTitleLabelTTF->setString(pCCBFileName);

    CCScene * scene = CCScene::create();
    if(node != NULL) {
        scene->addChild(node);
    }

    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene, transitionColor));
}


void HelloCocosBuilderLayer::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader) {
    CCRotateBy * ccRotateBy = CCRotateBy::create(0.5f, 10);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);
}


SEL_MenuHandler HelloCocosBuilderLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler HelloCocosBuilderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMenuTestClicked", HelloCocosBuilderLayer::onMenuTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSpriteTestClicked", HelloCocosBuilderLayer::onSpriteTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonTestClicked", HelloCocosBuilderLayer::onButtonTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLabelTestClicked", HelloCocosBuilderLayer::onLabelTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onParticleSystemTestClicked", HelloCocosBuilderLayer::onParticleSystemTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onScrollViewTestClicked", HelloCocosBuilderLayer::onScrollViewTestClicked);

    return NULL;
}

bool HelloCocosBuilderLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", CCSprite *, this->mBurstSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", CCLabelTTF *, this->mTestTitleLabelTTF);

    return false;
}


void HelloCocosBuilderLayer::onMenuTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/MenuTest.ccbi", "MenuTestLayer", MenuTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onSpriteTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/SpriteTest.ccbi", "SpriteTestLayer", SpriteTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onButtonTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/ButtonTest.ccbi", "ButtonTestLayer", ButtonTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onLabelTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/LabelTest.ccbi", "LabelTestLayer", LabelTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onParticleSystemTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/ParticleSystemTest.ccbi", "ParticleSystemTestLayer", ParticleSystemTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onScrollViewTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    this->openTest("ccb/ScrollViewTest.ccbi", "ScrollViewTestLayer", ScrollViewTestLayerLoader::loader());
}