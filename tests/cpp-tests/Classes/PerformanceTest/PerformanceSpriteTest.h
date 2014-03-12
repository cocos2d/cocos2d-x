/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __PERFORMANCE_SPRITE_TEST_H__
#define __PERFORMANCE_SPRITE_TEST_H__

#include "PerformanceTest.h"

class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    Sprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, Node* parent);

protected:
    int subtestNumber;
    Node *_parentNode;
};

class SpriteMenuLayer : public PerformBasicLayer
{
public:
    SpriteMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void restartCallback(Ref* sender);
    virtual void nextCallback(Ref* sender);
    virtual void backCallback(Ref* sender);
    virtual void showCurrentTest();
};

class SpriteMainScene : public Scene
{
public:
    virtual ~SpriteMainScene();
    virtual std::string title() const;
    virtual std::string subtitle() const;

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();

    void testNCallback(Ref* sender);
    void onIncrease(Ref* sender);
    void onDecrease(Ref* sender);

    virtual void doTest(Sprite* sprite) = 0;

    int getSubTestNum() { return subtestNumber; }
    int getNodesNum() { return quantityNodes; }
    
    virtual void onEnter() override;
    virtual void onExit() override;
    void  updateAutoTest(float dt);
    void  onAutoTest(Ref* sender);

    static bool _s_autoTest;
    static int  _s_nSpriteCurCase;

protected:
    void  dumpProfilerFPS();
    void  beginAutoTest();
    void  endAutoTest();
    void  nextAutoTest();
    void  finishAutoTest();
    void  autoShowSpriteTests(int curCase, int subTest,int nodes);

    int            lastRenderedCount;
    int            quantityNodes;
    SubTest        *_subTest;
    int            subtestNumber;
    std::vector<float> _vecFPS;
    int            _executeTimes;

    static const  int MAX_AUTO_TEST_TIMES  = 25;
    static const  int MAX_SPRITE_TEST_CASE = 7;
    static const  int MAX_SUB_TEST_NUMS    = 9;
    static const  int AUTO_TEST_NODE_NUM1  = 500;
    static const  int AUTO_TEST_NODE_NUM2  = 1500;
};

class SpritePerformTest1 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest2 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest3 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest4 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest5 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest6 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpritePerformTest7 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

void runSpriteTest();

#endif
