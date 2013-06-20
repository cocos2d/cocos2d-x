#ifndef _INTERVAL_TEST_H_
#define _INTERVAL_TEST_H_

#include "../testBasic.h"

class IntervalLayer : public Layer
{
protected:
    LabelBMFont*    _label0;
    LabelBMFont*    _label1;
    LabelBMFont*    _label2;
    LabelBMFont*    _label3;
    LabelBMFont*    _label4;
    
    float        _time0, _time1, _time2, _time3, _time4;

public:
    IntervalLayer(void);
    virtual ~IntervalLayer();
public:

    void step1(float dt);
    void step2(float dt);
    void step3(float dt);
    void step4(float dt);
    void update(float dt);

    //CREATE_NODE(IntervalLayer);
};

class IntervalTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
