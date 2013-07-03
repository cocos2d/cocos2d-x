#include "HelloCocosBuilderLayer.h"

#include "../TestHeader/TestHeaderLayerLoader.h"
#include "../LabelTest/LabelTestLayerLoader.h"
#include "../ButtonTest/ButtonTestLayerLoader.h"
#include "../SpriteTest/SpriteTestLayerLoader.h"
#include "../MenuTest/MenuTestLayerLoader.h"
#include "../ParticleSystemTest/ParticleSystemTestLayerLoader.h"
#include "../ScrollViewTest/ScrollViewTestLayerLoader.h"
#include "../AnimationsTest/AnimationsLayerLoader.h"
#include "../TimelineCallbackTest/TimelineCallbackLayerLoader.h"

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

void HelloCocosBuilderLayer::openTest(const char * pCCBFileName, const char * pNodeName, NodeLoader * pNodeLoader) {
    /* Create an autorelease NodeLoaderLibrary. */
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    if(pNodeName != NULL && pNodeLoader != NULL) {
        ccNodeLoaderLibrary->registerNodeLoader(pNodeName, pNodeLoader);
    }

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    Node * node = ccbReader->readNodeGraphFromFile(pCCBFileName, this);

    this->mTestTitleLabelTTF->setString(pCCBFileName);

    Scene * scene = Scene::create();
    if(node != NULL) {
        scene->addChild(node);
    }

    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, scene, transitionColor));
}


void HelloCocosBuilderLayer::onNodeLoaded(cocos2d::Node * pNode,  cocos2d::extension::NodeLoader * pNodeLoader) {
    RotateBy * ccRotateBy = RotateBy::create(20.0f, 360);
    RepeatForever * ccRepeatForever = RepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);
}


SEL_MenuHandler HelloCocosBuilderLayer::onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler HelloCocosBuilderLayer::onResolveCCBControlSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMenuTestClicked", HelloCocosBuilderLayer::onMenuTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSpriteTestClicked", HelloCocosBuilderLayer::onSpriteTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonTestClicked", HelloCocosBuilderLayer::onButtonTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAnimationsTestClicked", HelloCocosBuilderLayer::onAnimationsTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onParticleSystemTestClicked", HelloCocosBuilderLayer::onParticleSystemTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onScrollViewTestClicked", HelloCocosBuilderLayer::onScrollViewTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTimelineCallbackSoundClicked", HelloCocosBuilderLayer::onTimelineCallbackSoundClicked);
    
    return NULL;
}

bool HelloCocosBuilderLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", Sprite *, this->mBurstSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", LabelTTF *, this->mTestTitleLabelTTF);

    return false;
}

bool HelloCocosBuilderLayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }

    return bRet;
}

void HelloCocosBuilderLayer::onMenuTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent) {
    this->openTest("ccb/ccb/TestMenus.ccbi", "TestMenusLayer", MenuTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onSpriteTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent) {
    this->openTest("ccb/ccb/TestSprites.ccbi", "TestSpritesLayer", SpriteTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onButtonTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent) {
    this->openTest("ccb/ccb/TestButtons.ccbi", "TestButtonsLayer", ButtonTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onAnimationsTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent) {

    /* Create an autorelease NodeLoaderLibrary. */
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    ccNodeLoaderLibrary->registerNodeLoader("TestAnimationsLayer", AnimationsTestLayerLoader::loader());

    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    Node *animationsTest = ccbReader->readNodeGraphFromFile("ccb/ccb/TestAnimations.ccbi", this);
    // Load node graph (TestAnimations is a sub class of Layer) and retrieve the ccb action manager
    ((AnimationsTestLayer*)animationsTest)->setAnimationManager(ccbReader->getAnimationManager());
    
    this->mTestTitleLabelTTF->setString("TestAnimations.ccbi");
    
    Scene * scene = Scene::create();
    if(animationsTest != NULL) {
        scene->addChild(animationsTest);
    }
    
    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, scene, transitionColor));
    
    
    //this->openTest("TestAnimations.ccbi", "TestAnimationsLayer", AnimationsTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onParticleSystemTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent) {
    this->openTest("ccb/ccb/TestParticleSystems.ccbi", "TestParticleSystemsLayer", ParticleSystemTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onScrollViewTestClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent)
{
    this->openTest("ccb/ccb/TestScrollViews.ccbi", "TestScrollViewsLayer", ScrollViewTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onTimelineCallbackSoundClicked(Object * pSender, cocos2d::extension::ControlEvent pControlEvent)
{
    this->openTest("ccb/ccb/TestTimelineCallback.ccbi", "TimelineCallbackTestLayer", TimelineCallbackTestLayerLoader::loader());
}
