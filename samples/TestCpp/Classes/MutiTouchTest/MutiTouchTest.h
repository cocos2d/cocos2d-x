#ifndef __MUTITOUCHTEST_H__
#define __MUTITOUCHTEST_H__

#include "../testBasic.h"

class MutiTouchTestLayer : public CCLayer
{
public:
    bool init();

    virtual void registerWithTouchDispatcher(void);
    virtual void onTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void onTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void onTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void onTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    LAYER_CREATE_FUNC(MutiTouchTestLayer)
};

class MutiTouchTestScene : public TestScene
{
 public:
  virtual void runThisTest();
};

#endif /* __MUTITOUCHTEST_H__ */
