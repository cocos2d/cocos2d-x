/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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

class SpriteCreation : public MultiSceneTest
{
public:
    CREATE_FUNC(SpriteCreation);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void addSpritesCallback(Ref *);
    void delSpritesCallback(Ref *);

    void updateSpriteCountLabel(int x);

    void doTest();

protected:
    int totalSprites = 1000;
    int suggestDelta = 100;
    cocos2d::Label*   _labelSpriteNum = nullptr;
    cocos2d::Label*   labelCreate = nullptr;
    cocos2d::Label*   labelDestory = nullptr;
    SpriteCreation();
    virtual ~SpriteCreation();
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

class CaptureNodeTest : public MultiSceneTest
{
    static const int childTag = 120;
public:
    CREATE_FUNC(CaptureNodeTest);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    CaptureNodeTest();
    ~CaptureNodeTest();

    void onCaptured(cocos2d::Ref*);

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


class RendererUniformBatch : public MultiSceneTest
{
public:
    CREATE_FUNC(RendererUniformBatch);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
protected:
    RendererUniformBatch();

    cocos2d::backend::ProgramState* createBlurProgramState();
    cocos2d::backend::ProgramState* createSepiaProgramState();
};

class RendererUniformBatch2 : public MultiSceneTest
{
public:
    CREATE_FUNC(RendererUniformBatch2);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
protected:
    RendererUniformBatch2();

    cocos2d::backend::ProgramState* createBlurProgramState();
    cocos2d::backend::ProgramState* createSepiaProgramState();
};

class NonBatchSprites : public MultiSceneTest
{
public:
    CREATE_FUNC(NonBatchSprites);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual void update(float dt) override;
protected:
    NonBatchSprites();

    void createSprite();

    virtual ~NonBatchSprites();
    class Ticker {
    public:
        Ticker(int m):_max(m) {}
        void hit() {_cnt += 1;}
        void cancel() {_cnt = 0;}
        bool ok() {return _cnt >= _max;}
    private:
        int _cnt = 0;
        int _max = 0;
    };
    Node *_spritesAnchor = nullptr;
    int _spriteIndex = 0;
    float _maDt = 1.0f / 60.0f;
    float _rmaDt =  1.0f/ 60.0f;
    const float DEST_DT_30FPS = 1.0f / 30.0f;
    cocos2d::Label * _totalSprites = nullptr;
    Ticker _contSlow = Ticker(20);
    Ticker _contFast = Ticker(2);
    Ticker _around30fps = Ticker(60 * 3);
};
#endif //__NewRendererTest_H_
