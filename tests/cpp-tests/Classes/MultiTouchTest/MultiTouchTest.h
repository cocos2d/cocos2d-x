#ifndef __MULTITOUCHTEST_H__
#define __MULTITOUCHTEST_H__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(MultiTouchTests);

class MultiTouchTest : public TestCase
{
public:
    CREATE_FUNC(MultiTouchTest);

    virtual bool init() override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
};

#endif /* __MULTITOUCHTEST_H__ */
