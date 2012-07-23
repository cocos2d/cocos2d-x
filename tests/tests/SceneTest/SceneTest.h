#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class SceneTestLayer1 : public CCLayer
{
public:
	SceneTestLayer1();
	~SceneTestLayer1();

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();

	void testDealloc(ccTime dt);
	void onPushScene(CCObject* pSender);
	void onPushSceneTran(CCObject* pSender);
	void onQuit(CCObject* pSender);

	//CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public CCLayer
{
	float	m_timeCounter;
public:
	SceneTestLayer2();

	void testDealloc(ccTime dt);
	void onGoBack(CCObject* pSender);
	void onReplaceScene(CCObject* pSender);
	void onReplaceSceneTran(CCObject* pSender);

	//CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public CCLayerColor
{
public:
	SceneTestLayer3();

	virtual void testDealloc(ccTime dt);

	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);

	//CREATE_NODE(SceneTestLayer3);
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
