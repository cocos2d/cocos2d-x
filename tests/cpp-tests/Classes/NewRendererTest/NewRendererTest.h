//
// Created by NiTe Luo on 11/1/13.
//



#ifndef __NewRendererTest_H_
#define __NewRendererTest_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

#define kTagSpriteBatchNode 100
#define kTagClipperNode     101
#define kTagContentNode     102

class NewRendererTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class MultiSceneTest : public BaseTest
{
public:
    CREATE_FUNC(MultiSceneTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void restartCallback(Ref* sender) override;
    void nextCallback(Ref* sender) override;
    void backCallback(Ref* sender) override;

protected:
    MultiSceneTest();
    virtual ~MultiSceneTest();

};

class NewSpriteTest : public MultiSceneTest
{
public:
    CREATE_FUNC(NewSpriteTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void createSpriteTest();
    void createNewSpriteTest();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;

protected:
    NewSpriteTest();
    virtual ~NewSpriteTest();
};

class GroupCommandTest : public MultiSceneTest
{
public:
    CREATE_FUNC(GroupCommandTest);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    GroupCommandTest();
    virtual ~GroupCommandTest();
};

class NewSpriteBatchTest : public MultiSceneTest
{
public:

    CREATE_FUNC(NewSpriteBatchTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    void addNewSpriteWithCoords(Vec2 p);

protected:
    NewSpriteBatchTest();
    virtual ~NewSpriteBatchTest();
};

class NewClippingNodeTest : public MultiSceneTest
{
public:

    CREATE_FUNC(NewClippingNodeTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event) override;

protected:
    NewClippingNodeTest();
    virtual ~NewClippingNodeTest();

    bool _scrolling;
    Vec2 _lastPoint;
};

class NewDrawNodeTest : public MultiSceneTest
{
public:

    CREATE_FUNC(NewDrawNodeTest)
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    NewDrawNodeTest();
    virtual ~NewDrawNodeTest();
};

class NewCullingTest : public MultiSceneTest
{
public:
    
    CREATE_FUNC(NewCullingTest)
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    NewCullingTest();
    virtual ~NewCullingTest();
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    Vec2 _lastPos;
};

class VBOFullTest : public MultiSceneTest
{
public:
    CREATE_FUNC(VBOFullTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
protected:
    VBOFullTest();
    virtual ~VBOFullTest();
};

class CaptureScreenTest : public MultiSceneTest
{
    static const int childTag = 119;
public:
    CREATE_FUNC(CaptureScreenTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    CaptureScreenTest();
    ~CaptureScreenTest();

    void onCaptured(Ref*);
    void afterCaptured(bool succeed, const std::string& outputFile);

    std::string _filename;
};

#endif //__NewRendererTest_H_
