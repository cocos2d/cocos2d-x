#ifndef _LAYER_TEST_H_
#define _LAYER_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class LayerTest : public CCLayer
{
protected:
	std::string	m_strTitle;

public:
	LayerTest(void);
	~LayerTest(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual void onEnter();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);
};

class LayerTest1 : public LayerTest
{
public:
	virtual void onEnter();
	virtual std::string title();

	void registerWithTouchDispatcher();
	void updateSize(CCTouch*touch);

	virtual bool ccTouchBegan(CCTouch* touche, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touche, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touche, CCEvent* event);
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

class LayerGradient : public LayerTest
{
public:
    LayerGradient();
    virtual void ccTouchesMoved(CCSet * touches, CCEvent *event);
    virtual std::string title();
	virtual std::string subtitle();
	void toggleItem(cocos2d::CCObject *sender);
};

class LayerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
