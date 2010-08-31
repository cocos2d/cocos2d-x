#ifndef _LAYER_TEST_H_
#define _LAYER_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class LayerTest : public CCLayer
{
protected:
	std::string	m_strTitle;

public:
	LayerTest(void);
	~LayerTest(void);

	virtual std::string title();
	virtual void onEnter();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);
};

class LayerTest1 : public LayerTest
{
public:
	virtual void onEnter();
	virtual std::string title();

	void registerWithTouchDispatcher();
	void updateSize(CCTouch*touch);

	virtual bool ccTouchBegan(CCTouch* touche, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touche, UIEvent* event);
	virtual void ccTouchEnded(CCTouch* touche, UIEvent* event);
};

class LayerTest2 : public LayerTest
{
public:
	virtual void onEnter();
	virtual std::string title();
};


class LayerTestBlend : public LayerTest
{
public:
	LayerTestBlend();
	void newBlend(ccTime dt);
	virtual std::string title();
};

class LayerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
