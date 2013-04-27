#include "MainSceneHelper.h"

CCMenuItemImage * CCBHelper::mBtnRun = NULL;
CCMenuItemImage * CCBHelper::mBtnPair = NULL;
CCMenuItemImage * CCBHelper::mBtnReset = NULL;

std::string CCBHelper::mLblStatus_prev = "";
std::string CCBHelper::mLblStatus_str = "";
std::string CCBHelper::mLblInstructions_prev= "";
std::string CCBHelper::mLblInstructions_str= "";
std::string CCBHelper::mLblPair_prev = "";
std::string CCBHelper::mLblPair_str = "";
bool CCBHelper::gameAvailable = false;

void CCBHelper::setStatusMessage(std::string str) {
    if(mLblStatus_prev.compare(str) != 0) {
        mLblStatus_prev = str;
        mLblStatus_str = str;
    }
}

void CCBHelper::setInstructionsMessage(std::string str) {
    if(mLblInstructions_prev.compare(str) != 0) {
        mLblInstructions_prev = str;
        mLblInstructions_str = str;
    }
}


void CCBHelper::setPairMessage(std::string str) {
    if(mLblPair_prev.compare(str) != 0) {
        mLblPair_prev = str;
        mLblPair_str = str;
    }
}

bool CCBHelper::checkIsMainJSPresent() {
    gameAvailable = CCFileUtils::sharedFileUtils()->isFileExist(CCFileUtils::sharedFileUtils()->fullPathForFilename("main.js"));
}

bool CCBHelper::isMainJSPresent() {
  return gameAvailable;
}

