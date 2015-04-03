#ifndef _INTERVAL_TEST_H_
#define _INTERVAL_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(IntervalTests);

class IntervalTest : public TestCase
{
public:
    CREATE_FUNC(IntervalTest);
    IntervalTest();
    virtual ~IntervalTest();

    virtual void update(float dt) override;

    //CREATE_NODE(IntervalLayer);

protected:
    Label*    _label0;
    Label*    _label1;
    Label*    _label2;
    Label*    _label3;
    Label*    _label4;

    float        _time0, _time1, _time2, _time3, _time4;
};

#endif
