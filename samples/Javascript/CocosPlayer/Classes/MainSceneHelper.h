#include "cocos2d.h"
#include "string.h"

USING_NS_CC;

class CCBHelper {
 public:
  static CCMenuItemImage * mBtnRun;
  static CCMenuItemImage * mBtnReset;
  static CCMenuItemImage * mBtnPair;
    static bool gameAvailable;
  static std::string mLblStatus_prev, mLblStatus_str;
  static std::string mLblPair_prev, mLblPair_str;
  static std::string mLblInstructions_str, mLblInstructions_prev;

  static void setPairMessage(std::string str);
    static void setInstructionsMessage(std::string msg);
  static void setStatusMessage(std::string str);
  static bool isMainJSPresent();
    static bool checkIsMainJSPresent();


};
