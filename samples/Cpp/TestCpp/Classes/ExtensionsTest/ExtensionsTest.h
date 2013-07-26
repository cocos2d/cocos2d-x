#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testBasic.h"

class ExtensionsMainLayer : public Layer
{
public:
    virtual void onEnter();

	virtual void ccTouchesBegan(Set  *touches, Event  *event);
    virtual void ccTouchesMoved(Set  *touches, Event  *event);

	Point _beginPos;
    Menu* _itemMenu;

	int _testcount;
};

class ExtensionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __EXTENSIONS_TEST_H__ */
