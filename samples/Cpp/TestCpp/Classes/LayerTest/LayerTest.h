#ifndef _LAYER_TEST_H_
#define _LAYER_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class LayerTest : public CCLayer
{
protected:
    std::string    m_strTitle;

public:
    LayerTest(void);
    ~LayerTest(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
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

    void updateSize(CCPoint &touchLocation);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
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

class LayerGradient : public LayerTest
{
public:
    LayerGradient();
    virtual void ccTouchesMoved(CCSet * touches, CCEvent *event);
    virtual std::string title();
    virtual std::string subtitle();
    void toggleItem(cocos2d::CCObject *sender);
};

class LayerIgnoreAnchorPointPos : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(CCObject* pObject);
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerIgnoreAnchorPointRot : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(CCObject* pObject);
    virtual std::string title();
    virtual std::string subtitle();
};

class LayerIgnoreAnchorPointScale : public LayerTest
{
public:
    virtual void onEnter();
    void onToggle(CCObject* pObject);
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
