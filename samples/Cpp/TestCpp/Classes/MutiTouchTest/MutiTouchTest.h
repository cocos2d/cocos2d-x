#ifndef __MUTITOUCHTEST_H__
#define __MUTITOUCHTEST_H__

#include "../testBasic.h"

class MutiTouchTestLayer : public Layer
{
public:
    bool init();

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::Set  *touches, cocos2d::Event  *event);
    virtual void ccTouchesMoved(cocos2d::Set  *touches, cocos2d::Event  *event);
    virtual void ccTouchesEnded(cocos2d::Set  *touches, cocos2d::Event  *event);
    virtual void ccTouchesCancelled(cocos2d::Set  *touches, cocos2d::Event  *event);

    CREATE_FUNC(MutiTouchTestLayer)
};

class MutiTouchTestScene : public TestScene
{
 public:
  virtual void runThisTest();
};

#endif /* __MUTITOUCHTEST_H__ */
