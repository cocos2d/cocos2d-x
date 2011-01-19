#ifndef __COCOS_DENSHION_TEST__
#define __COCOS_DENSHION_TEST__

#include "../testBasic.h"

class CocosDenshionTest : public CCLayer
{
public:
	CocosDenshionTest(void);
	~CocosDenshionTest(void);

	void menuCallback(NSObject * pSender);
	virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent);
	virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent);
	virtual void onExit();

private:
	CCMenu* m_pItmeMenu;
	CGPoint m_tBeginPos;
	int m_nTestCount;
};

class CocosDenshionTestScene : public TestScene
{
public:
	virtual void runThisTest();
};

#endif //__COCOS_DENSHION_TEST__
