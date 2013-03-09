#include "MainSceneHelper.h"

CCMenuItemImage * CCBHelper::mBtnRun = NULL;
CCMenuItemImage * CCBHelper::mBtnPair = NULL;
CCMenuItemImage * CCBHelper::mBtnReset = NULL;

CCLabelTTF * CCBHelper::mLblStatus = NULL;
CCLabelTTF * CCBHelper::mLblPair = NULL;
CCLabelTTF * CCBHelper::mLblInstructions = NULL;

std::string CCBHelper::mLblStatus_background = "";
std::string CCBHelper::mLblPair_background = "";
bool CCBHelper::mLblInstructions_visible = true;


void CCBHelper::setStatusObject(CCLabelTTF *status) {
  if(mLblStatus == NULL) {
    mLblStatus = CCLabelTTF::create();
  }

  status->retain();
  mLblStatus = status;

  if(mLblStatus_background != "") {    
    status->setString(mLblStatus_background.c_str());
  }
}


void CCBHelper::setStatusMessage(std::string str) {
  if(mLblStatus == NULL) {
    mLblStatus_background = str;
  } else {
    mLblStatus->setString(str.c_str());
  }
}

void CCBHelper::setInstructionsObject(CCLabelTTF *status) {
  if(mLblInstructions == NULL) {
    mLblInstructions = CCLabelTTF::create();
  }
  status->retain();
  mLblInstructions = status;
  if(!mLblInstructions_visible) {
    mLblInstructions->setVisible(false);
  }
}

void CCBHelper::setInstructionsMessage(bool isVisible) {
  if(mLblInstructions == NULL) {
    mLblInstructions_visible = isVisible;
  } else {
    mLblInstructions_visible = isVisible;
    mLblInstructions->setVisible(isVisible);
  }
}

void CCBHelper::setPairObject(CCLabelTTF *pair) {

  if(mLblPair == NULL) {
    mLblPair = CCLabelTTF::create();
  }
  pair->retain();
  mLblPair = pair;
  if(mLblPair_background != "") {
    mLblPair->setString(mLblPair_background.c_str());
  }
    
}

void CCBHelper::setPairMessage(std::string str) {
  if(mLblPair == NULL) {
    mLblPair_background = str;
  } else {
    mLblPair->setString(str.c_str());
  }
}

bool CCBHelper::isMainJSPresent() {
  std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("main.js");
  CCLOG("PATH RETURNED: %s", path.c_str());
  if(path == "") {
    return false;
  } 
  return true;
}

