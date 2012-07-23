#ifndef _BOX2D_TEST_H_
#define _BOX2D_TEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../testBasic.h"

class Box2DTestLayer : public CCLayer
{
	b2World* world;
	//GLESDebugDraw *m_debugDraw;

public:
	Box2DTestLayer();
	~Box2DTestLayer();

	virtual void draw();

	void addNewSpriteWithCoords(CCPoint p);
	void update(ccTime dt);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);

	//CREATE_NODE(Box2DTestLayer);
} ;

class Box2DTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
