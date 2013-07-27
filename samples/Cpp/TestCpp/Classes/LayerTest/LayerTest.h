#ifndef _LAYER_TEST_H_
#define _LAYER_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class LayerTest : public BaseTest
{
protected:
    std::string    _title;

public:
    LayerTest(void);
    ~LayerTest(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class LayerTestCascadingOpacityA : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class LayerTestCascadingOpacityB : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class LayerTestCascadingOpacityC : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class LayerTestCascadingColorA : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class LayerTestCascadingColorB : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class LayerTestCascadingColorC : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};


class LayerTest1 : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();

    void updateSize(Point &touchLocation);

    virtual void ccTouchesBegan(Set  *touches, Event  *event);
    virtual void ccTouchesMoved(Set  *touches, Event  *event);
    virtual void ccTouchesEnded(Set  *touches, Event  *event);
};

class LayerTest2 : public LayerTest
{
public:
    virtual void onEnter();
    virtual std::string title();
};


class LayerTestBlend : public LayerTest
{
public:
    LayerTestBlend();
    void newBlend(float dt);
    virtual std::string title();
};

class LayerGradientTest : public LayerTest
{
public:
    LayerGradientTest();
    virtual void ccTouchesMoved(Set * touches, Event *event);
    virtual std::string title();
    virtual std::string subtitle();
    void toggleItem(cocos2d::Object *sender);
};

class LayerGradientTest2 : public LayerTest
{
public:
    LayerGradientTest2();
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerGradientTest3 : public LayerTest
{
public:
    LayerGradientTest3();
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerIgnoreAnchorPointPos : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(Object* pObject);
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerIgnoreAnchorPointRot : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(Object* pObject);
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerIgnoreAnchorPointScale : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(Object* pObject);
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerExtendedBlendOpacityTest : public LayerTest
{
public:
    LayerExtendedBlendOpacityTest();
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
