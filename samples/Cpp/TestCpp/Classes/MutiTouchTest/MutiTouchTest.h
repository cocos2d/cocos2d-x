#ifndef __MUTITOUCHTEST_H__
#define __MUTITOUCHTEST_H__

#include "../testBasic.h"

class MutiTouchTestLayer : public Layer
{
public:
    bool init();

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cc::Set *pTouches, cc::Event *pEvent);
    virtual void ccTouchesMoved(cc::Set *pTouches, cc::Event *pEvent);
    virtual void ccTouchesEnded(cc::Set *pTouches, cc::Event *pEvent);
    virtual void ccTouchesCancelled(cc::Set *pTouches, cc::Event *pEvent);

    CREATE_FUNC(MutiTouchTestLayer)
};

class MutiTouchTestScene : public TestScene
{
 public:
  virtual void runThisTest();
};

#endif /* __MUTITOUCHTEST_H__ */
