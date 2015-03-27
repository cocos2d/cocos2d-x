#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testBasic.h"

class ExtensionsMainLayer : public Layer
{
public:
    virtual void onEnter() override;

	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event) override;

	Vec2 _beginPos;
    Menu* _itemMenu;

	int _testcount;
    
protected:
    void onMouseScroll(Event* event);
};

class ExtensionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __EXTENSIONS_TEST_H__ */
