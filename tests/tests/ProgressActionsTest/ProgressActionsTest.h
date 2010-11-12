#ifndef _PROGRESS_ACTIONS_TEST_H_
#define _PROGRESS_ACTIONS_TEST_H_

#include "../testBasic.h"

class SpriteDemo : public CCLayer
{
public:
	SpriteDemo(void);
	~SpriteDemo(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual void onEnter();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);
};

class SpriteProgressToRadial : public SpriteDemo
{
public:
	virtual void onEnter();
	virtual std::string subtitle();
};

class SpriteProgressToHorizontal : public SpriteDemo
{
public:
	virtual void onEnter();
	virtual std::string subtitle();
};

class SpriteProgressToVertical : public SpriteDemo
{
public:
	virtual void onEnter();
	virtual std::string subtitle();
};

class ProgressActionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
