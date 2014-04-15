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

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class LayerTestCascadingOpacityA : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityA);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingOpacityB : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityB);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingOpacityC : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityC);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorA : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorA);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorB : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorB);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorC : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorC);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


class LayerTest1 : public LayerTest
{
public:
    CREATE_FUNC(LayerTest1);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

    void updateSize(Vector2 &touchLocation);

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
};

class LayerTest2 : public LayerTest
{
public:
    CREATE_FUNC(LayerTest2);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


class LayerTestBlend : public LayerTest
{
public:
    CREATE_FUNC(LayerTestBlend);

    LayerTestBlend();
    void newBlend(float dt);
    virtual std::string subtitle() const override;
};

class LayerGradientTest : public LayerTest
{
public:
    CREATE_FUNC(LayerGradientTest);
    LayerGradientTest();
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void toggleItem(cocos2d::Ref *sender);
};

class LayerGradientTest2 : public LayerTest
{
public:
    CREATE_FUNC(LayerGradientTest2);
    LayerGradientTest2();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerGradientTest3 : public LayerTest
{
public:
    CREATE_FUNC(LayerGradientTest3);
    LayerGradientTest3();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointPos : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointPos);
    virtual void onEnter() override;
    void onToggle(Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointRot : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointRot);
    virtual void onEnter() override;
    void onToggle(Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointScale : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointScale);
    virtual void onEnter() override;
    void onToggle(Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerExtendedBlendOpacityTest : public LayerTest
{
public:
    CREATE_FUNC(LayerExtendedBlendOpacityTest);
    LayerExtendedBlendOpacityTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerBug3162A : public LayerTest
{
public:
    CREATE_FUNC(LayerBug3162A);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void step(float dt);
    
private:
    LayerColor* _layer[3];
};

class LayerBug3162B : public LayerTest
{
public:
    CREATE_FUNC(LayerBug3162B);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void step(float dt);
    
private:
    LayerColor* _layer[3];
};

class LayerColorOccludeBug : public LayerTest
{
public:
    CREATE_FUNC(LayerColorOccludeBug);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    LayerColor* _layer;
};

class LayerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
