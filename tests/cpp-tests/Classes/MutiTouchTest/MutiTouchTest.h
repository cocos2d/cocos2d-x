#ifndef __MUTITOUCHTEST_H__
#define __MUTITOUCHTEST_H__

#include "../testBasic.h"

class MutiTouchTestLayer : public Layer
{
public:
    bool init();

    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

    CREATE_FUNC(MutiTouchTestLayer)
};

class MutiTouchTestScene : public TestScene
{
 public:
  virtual void runThisTest();
};

#endif /* __MUTITOUCHTEST_H__ */
