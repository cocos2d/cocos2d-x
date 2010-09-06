#ifndef _INTERVAL_TEST_H_
#define _INTERVAL_TEST_H_

#include "../testBasic.h"

class IntervalLayer : public CCLayer
{
protected:
	CCBitmapFontAtlas*	m_label1;
	CCBitmapFontAtlas*	m_label2;
	CCBitmapFontAtlas*	m_label3;
	
	ccTime		m_time1, m_time2, m_time3;

public:
	IntervalLayer(void);

public:
	void onPause(NSObject* pSender);

	void step1(ccTime dt);
	void step2(ccTime dt);
	void step3(ccTime dt);

	//CREATE_NODE(IntervalLayer);
};

class IntervalTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
