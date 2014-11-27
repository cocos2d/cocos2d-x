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

#include <vector>

#include "PerformanceTest.h"


class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    Sprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, Node* parent);

protected:
    int _subtestNumber;
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

    int getSubTestNum() { return _subtestNumber; }
    int getNodesNum() { return _quantityNodes; }
    
    virtual void onEnter() override;
    virtual void onExit() override;
    void updateAutoTest(float dt);
    void onAutoTest(Ref* sender);

    // auto tests
    static bool _s_autoTest;
    static int _s_nSpriteCurCase;
    static int _s_spritesQuatityIndex;
    static int _s_spritesQuanityArray[];
    static std::vector<float> _s_saved_fps;

protected:
    void dumpProfilerFPS();
    void saveFPS();
    void beginAutoTest();
    void endAutoTest();
    void nextAutoTest();
    void finishAutoTest();
    void autoShowSpriteTests(int curCase, int subTest,int nodes);

    int _lastRenderedCount;
    int _quantityNodes;
    SubTest* _subTest;
    int _subtestNumber;
};

class SpritePerformTestA : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestB : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestC : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestD : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestE : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestF : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

class SpritePerformTestG : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite) override;
    virtual std::string title() const override;
};

void runSpriteTest();

#endif
