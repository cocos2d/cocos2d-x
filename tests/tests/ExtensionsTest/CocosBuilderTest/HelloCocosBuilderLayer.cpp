#include "HelloCocosBuilderLayer.h"

#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#include "TestHeaderLayerLoader.h"
#include "ButtonTestLayerLoader.h"
#include "CCTransition.h"

USING_NS_CC;
USING_NS_CC_EXT;

HelloCocosBuilderLayer * HelloCocosBuilderLayer::node() { 
    HelloCocosBuilderLayer * ptr = new HelloCocosBuilderLayer();
    if(ptr && ptr->init()) { 
        ptr->autorelease();   
        return ptr;
    } 
    CC_SAFE_DELETE(ptr);
    return NULL;
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

    CCScene * scene = CCScene::node();
    if(node != NULL) {
        scene->addChild(node);
    }

    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::transitionWithDuration(0.5f, scene, transitionColor));
}


void HelloCocosBuilderLayer::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader) {
    CCRotateBy * ccRotateBy = CCRotateBy::actionWithDuration(0.5f, 10);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::actionWithAction(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);
}


SEL_MenuHandler HelloCocosBuilderLayer::onResolveCCBCCMenuSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler HelloCocosBuilderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    if(pTarget == this) {
        if(strcmp(pSelectorName, "onMenuTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onMenuTestClicked);
        } else if(strcmp(pSelectorName, "onSpriteTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onSpriteTestClicked);
        } else if(strcmp(pSelectorName, "onButtonTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onButtonTestClicked);
        } else if(strcmp(pSelectorName, "onLabelTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onLabelTestClicked);
        } else if(strcmp(pSelectorName, "onParticleSystemTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onParticleSystemTestClicked);
        } else if(strcmp(pSelectorName, "onScrollViewTestClicked") == 0) {
            return cccontrol_selector(HelloCocosBuilderLayer::onScrollViewTestClicked);
        }
    }
    return NULL;
}


bool HelloCocosBuilderLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    if(pTarget == this) {
        if(strcmp(pMemberVariableName, "mBurstSprite") == 0) {
            this->mBurstSprite = dynamic_cast<CCSprite *>(pNode);
            CC_ASSERT(this->mBurstSprite);
            this->mBurstSprite->retain();
            return true;
        } else if(strcmp(pMemberVariableName, "mTestTitleLabel") == 0) {
            this->mTestTitleLabelTTF = dynamic_cast<CCLabelTTF *>(pNode);
            CC_ASSERT(this->mTestTitleLabelTTF);
            this->mTestTitleLabelTTF->retain();
            return true;
        }
    }
    return false;
}


void HelloCocosBuilderLayer::onMenuTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onMenuTestClicked\n");
}

void HelloCocosBuilderLayer::onSpriteTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onSpriteTestClicked\n");
}

void HelloCocosBuilderLayer::onButtonTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onButtonTestClicked\n");
    this->openTest("ccb/ButtonTest.ccbi", "ButtonTestLayer", ButtonTestLayerLoader::loader());
}

void HelloCocosBuilderLayer::onLabelTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onLabelTestClicked\n");
}

void HelloCocosBuilderLayer::onParticleSystemTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onParticleSystemTestClicked\n");
}

void HelloCocosBuilderLayer::onScrollViewTestClicked(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    printf("onScrollViewTestClicked\n");
}