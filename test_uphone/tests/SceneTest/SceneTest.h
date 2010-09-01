#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class SceneTestLayer1 : public CCLayer
{
public:
	SceneTestLayer1();
	~SceneTestLayer1();

	void testDealloc(ccTime dt);
	void onPushScene(NSObject* pSender);
	void onPushSceneTran(NSObject* pSender);
	void onQuit(NSObject* pSender);

	//CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public CCLayer
{
	float	m_timeCounter;
public:
	SceneTestLayer2();

	void testDealloc(ccTime dt);
	void onGoBack(NSObject* pSender);
	void onReplaceScene(NSObject* pSender);
	void onReplaceSceneTran(NSObject* pSender);

	//CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public CCColorLayer
{
public:
	SceneTestLayer3();

	virtual void testDealloc(ccTime dt);

	virtual void ccTouchesEnded(NSSet* touches, UIEvent* event);

	//CREATE_NODE(SceneTestLayer3);
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
