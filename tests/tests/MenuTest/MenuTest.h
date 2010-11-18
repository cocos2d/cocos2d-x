#ifndef _MENU_TEST_H_
#define _MENU_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayer1 : public CCLayer
{
protected:
	CCMenuItem*	m_disabledItem;

public:
	MenuLayer1(void);
	~MenuLayer1();

public:
	void menuCallback(NSObject* pSender);
	void menuCallbackConfig(NSObject* pSender);
	void menuCallbackDisabled(NSObject* pSender);
	void menuCallbackEnable(NSObject* pSender);
	void menuCallback2(NSObject* pSender);
	void onQuit(NSObject* pSender);

	//CREATE_NODE(MenuLayer1);
};

class MenuLayer2 : public CCLayer
{
protected:
	CGPoint		m_centeredMenu;
	bool                m_alignedH; 

	void alignMenusH();
	void alignMenusV();

public:
	MenuLayer2(void);
	~MenuLayer2();

public:
	void menuCallback(NSObject* pSender);
	void menuCallbackOpacity(NSObject* pSender);
	void menuCallbackAlign(NSObject* pSender);

	//CREATE_NODE(MenuLayer2);
};

class MenuLayer3 : public CCLayer
{
protected:
	CCMenuItem*	m_disabledItem;

public:
	MenuLayer3(void);
	~MenuLayer3();

public:
	void menuCallback(NSObject* pSender);
	void menuCallback2(NSObject* pSender);
	void menuCallback3(NSObject* pSender);

	//CREATE_NODE(MenuLayer3);
};

class MenuLayer4 : public CCLayer
{
public:
	MenuLayer4(void);
	~MenuLayer4();

public:
	void menuCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);

	//CREATE_NODE(MenuLayer4);
};

class MenuTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
