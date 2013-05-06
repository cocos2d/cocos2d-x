
#include "PlayerStatus.h"
#include "PlayerStatusLoader.h"
#include "MainSceneHelper.h"
#include "AppDelegate.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "GUI/CCEditBox/CCEditBox.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

std::string PlayerStatus::pairingLabel = "";


PlayerStatus::PlayerStatus(): mBtnRun(NULL), mBtnReset(NULL), mBtnPair(NULL),
			      mLblStatus(NULL), mLblInstructions(NULL), mLblPair(NULL), editBox(NULL)
{
    this->scheduleUpdate();
}

PlayerStatus::~PlayerStatus()
{
  CC_SAFE_RELEASE(mBtnRun);
  CC_SAFE_RELEASE(mBtnReset);
  CC_SAFE_RELEASE(mBtnPair);

  CC_SAFE_RELEASE(mLblStatus);
  CC_SAFE_RELEASE(mLblPair);
  CC_SAFE_RELEASE(mLblInstructions);
}


void PlayerStatus::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {

}


SEL_CCControlHandler PlayerStatus::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
  return NULL;
}

SEL_MenuHandler PlayerStatus::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

  CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedPair:", PlayerStatus::pressedPair);
  CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedReset:", PlayerStatus::pressedReset);
  CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedRun:", PlayerStatus::pressedRun);

  return NULL;    
}


void PlayerStatus::setDeviceResolution(std::string res) {
  setDeviceResolutionJNI(res.c_str());
}

void updatePairing(const char *pairing);

void editBoxCallbackFunc(const char* pText, void* ctx)
{
  PlayerStatus *thiz = (PlayerStatus *)ctx;
  std::string text(pText);
  if(text == "" || text == " ") {
      PlayerStatus::pairingLabel = "";
    updatePairing("Auto");
  } else {
    PlayerStatus::pairingLabel = pText;
    updatePairing(pText);
  }
}

void PlayerStatus::pressedPair(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    showEditTextDialogJNI("Enter pairing code", "", kEditBoxInputModeNumeric, kEditBoxInputFlagInitialCapsWord,
                                        kKeyboardReturnTypeDone, 4, editBoxCallbackFunc, (void*)this);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    openEditBox();
#endif
}


void PlayerStatus::pressedReset(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cleanCacheDirJNI();
    CCBHelper::checkIsMainJSPresent();
}

void PlayerStatus::pressedRun(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    runJSApp();
}


bool PlayerStatus::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {


  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnRun", CCMenuItemImage *, this->mBtnRun);
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnReset", CCMenuItemImage *, this->mBtnReset);
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnPair", CCMenuItemImage *, this->mBtnPair);
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblStatus", CCLabelTTF *, this->mLblStatus);
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblPair", CCLabelTTF *, this->mLblPair);
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblInstructions", CCLabelTTF *, this->mLblInstructions);
  return false;
}

void PlayerStatus::update(float dt) {
    if(this->mLblInstructions != NULL && CCBHelper::mLblInstructions_str != "") {
        this->mLblInstructions->setString(CCBHelper::mLblInstructions_str.c_str());
    }
    if(this->mLblStatus != NULL && CCBHelper::mLblStatus_str != "") {
        this->mLblStatus->setString(CCBHelper::mLblStatus_str.c_str());
    }
    if(CCBHelper::isMainJSPresent() && this->mBtnRun != NULL && this->mBtnReset != NULL) {
        this->mBtnRun->setEnabled(true);
        this->mBtnReset->setEnabled(true);
    } else if(this->mBtnRun != NULL && this->mBtnReset != NULL) {
        this->mBtnRun->setEnabled(false);
        this->mBtnReset->setEnabled(false);
    }
    if(pairingLabel != "") {
        this->mLblPair->setString(pairingLabel.c_str());
    } else {
        this->mLblPair->setString("Auto");
    }
}

cocos2d::CCScene* PlayerStatus::loadMainScene(const char *pCCBFileName) {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerStatusLayer", PlayerStatusLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    CCNode * node = ccbReader->readNodeGraphFromFile(pCCBFileName, NULL);
    
    CCScene * scene = CCScene::create();
    if(node != NULL) {
      scene->addChild(node);
    }
    CCBHelper::checkIsMainJSPresent();
    return scene;

  }
