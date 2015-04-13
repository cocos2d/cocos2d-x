#ifndef _EFFECTS_TEST_H_
#define _EFFECTS_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(EffectTests);

class EffectBaseTest : public TestCase
{
protected:
    //UxString    _title;
    cocos2d::NodeGrid* _gridNodeTarget;
public:
    static EffectBaseTest* create(int index)
    {
        auto ret = new (std::nothrow) EffectBaseTest(index);
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }

        return ret;
    }

    EffectBaseTest(int index);
    ~EffectBaseTest();

    void checkAnim(float dt);
};

#endif
