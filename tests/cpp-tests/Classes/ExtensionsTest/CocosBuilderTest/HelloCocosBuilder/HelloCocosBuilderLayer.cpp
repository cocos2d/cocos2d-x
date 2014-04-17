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
using namespace cocosbuilder;

HelloCocosBuilderLayer::HelloCocosBuilderLayer()
: mBurstSprite(nullptr)
, mTestTitleLabelTTF(nullptr)
{}

HelloCocosBuilderLayer::~HelloCocosBuilderLayer()
{
    CC_SAFE_RELEASE(mBurstSprite);
    CC_SAFE_RELEASE(mTestTitleLabelTTF);
}

void HelloCocosBuilderLayer::openTest(const char * pCCBFileName, const char * nodeName, NodeLoader * nodeLoader) {
    /* Create an autorelease NodeLoaderLibrary. */
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    if(nodeName != NULL && nodeLoader != NULL) {
        ccNodeLoaderLibrary->registerNodeLoader(nodeName, nodeLoader);
    }

    /* Create an autorelease CCBReader. */
    cocosbuilder::CCBReader * ccbReader = new cocosbuilder::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    auto node = ccbReader->readNodeGraphFromFile(pCCBFileName, this);

    this->mTestTitleLabelTTF->setString(pCCBFileName);

    auto scene = Scene::create();
    if(node != NULL) {
        scene->addChild(node);
    }

    /* Push the new scene with a fancy transition. */
    Color3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene, transitionColor));
}


void HelloCocosBuilderLayer::onNodeLoaded(cocos2d::Node * node,  cocosbuilder::NodeLoader * nodeLoader) {
    auto ccRotateBy = RotateBy::create(20.0f, 360);
    auto ccRepeatForever = RepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);
}


SEL_MenuHandler HelloCocosBuilderLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    return NULL;    
}

Control::Handler HelloCocosBuilderLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMenuTestClicked", HelloCocosBuilderLayer::onMenuTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSpriteTestClicked", HelloCocosBuilderLayer::onSpriteTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonTestClicked", HelloCocosBuilderLayer::onButtonTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAnimationsTestClicked", HelloCocosBuilderLayer::onAnimationsTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onParticleSystemTestClicked", HelloCocosBuilderLayer::onParticleSystemTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onScrollViewTestClicked", HelloCocosBuilderLayer::onScrollViewTestClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTimelineCallbackSoundClicked", HelloCocosBuilderLayer::onTimelineCallbackSoundClicked);
    
    return NULL;
}

bool HelloCocosBuilderLayer::onAssignCCBMemberVariable(Ref * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", Sprite *, this->mBurstSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", Label *, this->mTestTitleLabelTTF);

    return false;
}

bool HelloCocosBuilderLayer::onAssignCCBCustomProperty(Ref* pTarget, const char* pMemberVariableName, const Value& pCCBValue)
{
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue.asInt();
            log("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue.asFloat();
            log("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue.asBool();
            log("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue.asString();
            log("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }

    return bRet;
}

void HelloCocosBuilderLayer::onMenuTestClicked(Ref * sender, Control::EventType pControlEvent) {
    this->openTest("ccb/ccb/TestMenus.ccbi", "TestMenusLayer", MenuTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onSpriteTestClicked(Ref * sender, Control::EventType pControlEvent) {
    this->openTest("ccb/ccb/TestSprites.ccbi", "TestSpritesLayer", SpriteTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onButtonTestClicked(Ref * sender, Control::EventType pControlEvent) {
    this->openTest("ccb/ccb/TestButtons.ccbi", "TestButtonsLayer", ButtonTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onAnimationsTestClicked(Ref * sender, Control::EventType pControlEvent) {

    /* Create an autorelease NodeLoaderLibrary. */
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
    ccNodeLoaderLibrary->registerNodeLoader("TestAnimationsLayer", AnimationsTestLayerLoader::loader());

    
    /* Create an autorelease CCBReader. */
    cocosbuilder::CCBReader * ccbReader = new cocosbuilder::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    auto animationsTest = ccbReader->readNodeGraphFromFile("ccb/ccb/TestAnimations.ccbi", this);
    // Load node graph (TestAnimations is a sub class of Layer) and retrieve the ccb action manager
    ((AnimationsTestLayer*)animationsTest)->setAnimationManager(ccbReader->getAnimationManager());
    
    this->mTestTitleLabelTTF->setString("TestAnimations.ccbi");
    
    auto scene = Scene::create();
    if(animationsTest != NULL) {
        scene->addChild(animationsTest);
    }
    
    /* Push the new scene with a fancy transition. */
    Color3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene, transitionColor));
    
    
    //this->openTest("TestAnimations.ccbi", "TestAnimationsLayer", AnimationsTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onParticleSystemTestClicked(Ref * sender, Control::EventType pControlEvent) {
    this->openTest("ccb/ccb/TestParticleSystems.ccbi", "TestParticleSystemsLayer", ParticleSystemTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onScrollViewTestClicked(Ref * sender, Control::EventType pControlEvent)
{
    this->openTest("ccb/ccb/TestScrollViews.ccbi", "TestScrollViewsLayer", ScrollViewTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onTimelineCallbackSoundClicked(Ref * sender, Control::EventType pControlEvent)
{
    this->openTest("ccb/ccb/TestTimelineCallback.ccbi", "TimelineCallbackTestLayer", TimelineCallbackTestLayerLoader::loader());
}
