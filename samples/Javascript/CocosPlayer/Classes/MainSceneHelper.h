#include "cocos2d.h"
#include "string.h"

USING_NS_CC;

class CCBHelper {
 public:
  static CCMenuItemImage * mBtnRun;
  static CCMenuItemImage * mBtnReset;
  static CCMenuItemImage * mBtnPair;

  static CCLabelTTF *mLblStatus;
  static std::string mLblStatus_background;
  static CCLabelTTF *mLblPair;
  static std::string mLblPair_background;
  static CCLabelTTF *mLblInstructions;
  static bool mLblInstructions_visible;

  static void setPairObject(CCLabelTTF *pair);  
  static void setPairMessage(std::string str);  

  static void setInstructionsObject(CCLabelTTF *instr);  
  static void setInstructionsMessage(bool isVisible);  

  static void setStatusObject(CCLabelTTF *status);  
  static void setStatusMessage(std::string str);  

  static bool isMainJSPresent();
};
