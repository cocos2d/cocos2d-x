#ifndef _PLAYERSTATUS_H_
#define _PLAYERSTATUS_H_

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.h"

/*
 * Note: for some pretty hard fucked up reason, the order of inheritance is important!
 * When CCLayer is the 'first' inherited object:
 * During runtime the method call to the (pure virtual) 'interfaces' fails jumping into a bogus method or just doing nothing: 
 *  #0    0x000cf840 in non-virtual thunk to HelloCocos....
 *  #1    ....
 *
 * This thread describes the problem:
 * http://www.cocoabuilder.com/archive/xcode/265549-crash-in-virtual-method-call.html
 */
void editBoxCallbackFunc(const char* pText, void* ctx);

class PairingDelegate: public cocos2d::extension::CCEditBoxDelegate {
private:
    void *m_Target;
public:
    
    void setTarget(void *target) {
        m_Target = target;
    }
    
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox) {
        editBoxCallbackFunc(editBox->getText(), m_Target);
        editBox->setVisible(false);
    }
};

class PlayerStatus
  : public cocos2d::CCLayer
  , public cocos2d::extension::CCBSelectorResolver
  , public cocos2d::extension::CCBMemberVariableAssigner
  , public cocos2d::extension::CCNodeLoaderListener
{
public:
  CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PlayerStatus, create);

  PlayerStatus();
  virtual ~PlayerStatus();

  virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
  virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
  virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
  virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

  void pressedPair(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
  void pressedReset(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
  void pressedRun(CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
  static cocos2d::CCScene* loadMainScene(const char *fileName);
  static void setDeviceResolution(std::string res);

  cocos2d::CCMenuItemImage* mBtnRun;
  cocos2d::CCMenuItemImage* mBtnReset;
  cocos2d::CCMenuItemImage* mBtnPair;
    
  cocos2d::CCLabelTTF* mLblStatus;
  cocos2d::CCLabelTTF* mLblInstructions;
  cocos2d::CCLabelTTF* mLblPair;
  virtual void update(float dt);
    static std::string pairingLabel;
private:
    cocos2d::extension::CCEditBox *editBox;

};


#endif
