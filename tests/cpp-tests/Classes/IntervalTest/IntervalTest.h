#ifndef _INTERVAL_TEST_H_
#define _INTERVAL_TEST_H_

#include "../testBasic.h"

class IntervalLayer : public Layer
{
public:
    IntervalLayer(void);
    virtual ~IntervalLayer();

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

class IntervalTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
