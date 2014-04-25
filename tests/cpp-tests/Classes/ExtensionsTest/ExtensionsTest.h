#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testScene.h"

class ExtensionsMainLayer : public Layer
{
public:
    virtual void onEnter() override;

	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

	Point _beginPos;
    Menu* _itemMenu;

	int _testcount;
    
protected:
    void onMouseScroll(Event* event);
};

class ExtensionsTestScene : public TestScene
{
public:
	ExtensionsTestScene();
    virtual void runThisTest();
};

#endif /* __EXTENSIONS_TEST_H__ */
