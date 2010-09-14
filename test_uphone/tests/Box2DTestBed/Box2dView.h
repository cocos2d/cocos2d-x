#ifndef _BOX2D_VIEW_H_
#define _BOX2D_VIEW_H_

//#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayer : public CCLayer
{
	int		m_entryID;

public:
	MenuLayer(void);
	virtual ~MenuLayer(void);

	bool initWithEntryID(int entryId);

	void restartCallback(NSObject* sender);
	void nextCallback(NSObject* sender);
	void backCallback(NSObject* sender);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);

public:
	static MenuLayer* menuWithEntryID(int entryId);
};

struct TestEntry;
class Test;
class Box2DView : public CCLayer
{
	TestEntry*	m_entry;
	Test*		m_test;
	int			m_entryID;
public:
	Box2DView(void);
	virtual ~Box2DView(void);

	bool initWithEntryID(int entryId);
	std::string title();
	void tick(ccTime dt);
	void draw();

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, UIEvent* event);
	//virtual void accelerometer(UIAccelerometer* accelerometer, UIAcceleration* acceleration);

	static Box2DView* viewWithEntryID(int entryId);
};

class Box2dTestBedScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
