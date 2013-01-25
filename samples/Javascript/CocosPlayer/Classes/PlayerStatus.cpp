
#include "PlayerStatus.h"
#include "PlayerStatusLoader.h"
#include "MainSceneHelper.h"
#include "AppDelegate.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"


USING_NS_CC;
USING_NS_CC_EXT;

PlayerStatus::PlayerStatus(): mBtnRun(NULL), mBtnReset(NULL), mBtnPair(NULL), 
			      mLblStatus(NULL), mLblInstructions(NULL), mLblPair(NULL)
{
  
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

void editBoxCallbackFunc(const char* pText, void* ctx)
{
  PlayerStatus *thiz = (PlayerStatus *)ctx;
  std::string text(pText);
  if(text == "" || text == " ") {
    thiz->mLblPair->setString("Auto");
    setPairingCodeJNI(-1);
  } else {
    thiz->mLblPair->setString(pText);
    setPairingCodeJNI(atoi(pText));
  }
}

void PlayerStatus::pressedPair(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    showEditTextDialogJNI("Enter pairing code", "", kEditBoxInputModeNumeric, kEditBoxInputFlagInitialCapsWord, 
			  kKeyboardReturnTypeDone, 4, editBoxCallbackFunc, (void*)this);
}

void PlayerStatus::pressedReset(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cleanCacheDirJNI();
    this->mBtnRun->setEnabled(false);
    this->mBtnReset->setEnabled(false);
}


void PlayerStatus::pressedRun(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    handle_ccb_run();
}


bool PlayerStatus::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {

  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnRun", CCMenuItemImage *, this->mBtnRun);
  if(strcmp(pMemberVariableName, "btnRun")) {
    if(this->mBtnRun  == NULL) {
      this->mBtnRun = CCMenuItemImage::create();
    }
    if(CCBHelper::isMainJSPresent()) {
      this->mBtnRun->setEnabled(true);
    } else {
      this->mBtnRun->setEnabled(false);
    }
  }
  

  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnReset", CCMenuItemImage *, this->mBtnReset);
  
  if(strcmp(pMemberVariableName, "btnReset")) {
    if(this->mBtnReset  == NULL) {
      this->mBtnReset = CCMenuItemImage::create();
    }
    if(CCBHelper::isMainJSPresent()) {
      this->mBtnReset->setEnabled(true);
    } else {
      this->mBtnReset->setEnabled(false);
    }
  }
  
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnPair", CCMenuItemImage *, this->mBtnPair);

  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblStatus", CCLabelTTF *, this->mLblStatus);
  if(strcmp(pMemberVariableName, "lblStatus") && this->mLblStatus != NULL) {
    CCBHelper::setStatusObject(this->mLblStatus);
  }

  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblPair", CCLabelTTF *, this->mLblPair);
  if(strcmp(pMemberVariableName, "lblPair") && this->mLblPair != NULL) {
    CCBHelper::setPairObject(this->mLblPair);
  }
    
  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblInstructions", CCLabelTTF *, this->mLblInstructions);
  if(strcmp(pMemberVariableName, "lblInstructions") && this->mLblInstructions != NULL) {
    CCBHelper::setInstructionsObject(this->mLblInstructions);
  }
 
  return false;
}


void PlayerStatus::loadMainScene(const char *pCCBFileName) {
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
    
    /* Push the new scene with a fancy transition. */
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    CCDirector::sharedDirector()->runWithScene(CCTransitionFade::create(0.5f, scene, transitionColor));
}
