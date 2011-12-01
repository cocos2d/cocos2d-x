#ifndef _INTERVAL_TEST_H_
#define _INTERVAL_TEST_H_

#include "../testBasic.h"

class IntervalLayer : public CCLayer
{
protected:
    CCLabelBMFont*	m_label0;
	CCLabelBMFont*	m_label1;
	CCLabelBMFont*	m_label2;
	CCLabelBMFont*	m_label3;
    CCLabelBMFont*	m_label4;
	
	ccTime		m_time0, m_time1, m_time2, m_time3, m_time4;

public:
	IntervalLayer(void);
    virtual ~IntervalLayer();
public:
	void onPause(CCObject* pSender);

	void step1(ccTime dt);
	void step2(ccTime dt);
	void step3(ccTime dt);
    void step4(ccTime dt);
    void update(ccTime dt);

	//CREATE_NODE(IntervalLayer);
};

class IntervalTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
