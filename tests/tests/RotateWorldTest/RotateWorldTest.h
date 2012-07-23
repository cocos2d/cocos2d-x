#ifndef _ROTATE_WORLD_TEST_H_
#define _ROTATE_WORLD_TEST_H_

#include "../testBasic.h"

class RotateWorldTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class SpriteLayer : public CCLayer
{
public:
	virtual void onEnter();
	static SpriteLayer* node()
	{
		SpriteLayer* pNode = new SpriteLayer();
		pNode->autorelease();

		return pNode;
	}
};

class TestLayer : public CCLayer
{
public:
	virtual void onEnter();

	static TestLayer* node()
	{
		TestLayer* pNode = new TestLayer();
		pNode->autorelease();

		return pNode;
	}
};

class RotateWorldMainLayer : public CCLayer
{
public:
	virtual void onEnter();

	static RotateWorldMainLayer* node()
	{
		RotateWorldMainLayer* pNode = new RotateWorldMainLayer();
		pNode->autorelease();

		return pNode;
	}
};

#endif
