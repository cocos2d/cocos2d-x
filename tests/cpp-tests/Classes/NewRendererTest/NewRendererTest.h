#ifndef __NewRendererTest_H_
#define __NewRendererTest_H_

#include "cocos2d.h"
#include "../BaseTest.h"

#define kTagSpriteBatchNode 100
#define kTagClipperNode     101
#define kTagContentNode     102

DEFINE_TEST_SUITE(NewRendererTests);

class MultiSceneTest : public TestCase
{
public:
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:

};

class NewSpriteTest : public MultiSceneTest
{
public:
    CREATE_FUNC(NewSpriteTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void createSpriteTest();
    void createNewSpriteTest();
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

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

class NewClippingNodeTest : public MultiSceneTest
{
public:

    CREATE_FUNC(NewClippingNodeTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

protected:
    NewClippingNodeTest();
    virtual ~NewClippingNodeTest();

    bool _scrolling;
    cocos2d::Vec2 _lastPoint;
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
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    cocos2d::Vec2 _lastPos;
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

    void onCaptured(cocos2d::Ref*);
    void afterCaptured(bool succeed, const std::string& outputFile);

    std::string _filename;
};

class BugAutoCulling : public MultiSceneTest
{
public:
    CREATE_FUNC(BugAutoCulling);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
protected:
    BugAutoCulling();
};

class RendererBatchQuadTri : public MultiSceneTest
{
public:
    CREATE_FUNC(RendererBatchQuadTri);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
protected:
    RendererBatchQuadTri();
};

#endif //__NewRendererTest_H_
