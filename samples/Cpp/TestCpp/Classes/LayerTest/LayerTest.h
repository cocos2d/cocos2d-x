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

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);
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

    virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
    virtual void ccTouchesMoved(Set *pTouches, Event *pEvent);
    virtual void ccTouchesEnded(Set *pTouches, Event *pEvent);
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
