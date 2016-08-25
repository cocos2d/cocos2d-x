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

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceSpriteTests);

class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    cocos2d::Sprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, cocos2d::Node* parent);
    cocos2d::Node* getTheParentNode() { return _parentNode; }

protected:
    int _subtestNumber;
    cocos2d::Node* _parentNode;
};

class SpriteMainScene : public TestCase
{
public:
    virtual ~SpriteMainScene();
    virtual bool init() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();
    void updateTitle();

    void testNCallback(cocos2d::Ref* sender);
    void onIncrease(cocos2d::Ref* sender);
    void onDecrease(cocos2d::Ref* sender);

    virtual void doTest(cocos2d::Sprite* sprite) = 0;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    virtual std::string getTestCaseName() = 0;
    
    void beginStat(float dt);
    void endStat(float dt);
    void doAutoTest();

protected:
    static int _quantityNodes;
    static int _subtestNumber;

    int _lastRenderedCount;
    SubTest* _subTest;

    bool       isStating;
    int        autoTestIndex;
    int        statCount;
    float      totalStatTime;
    float      minFrameRate;
    float      maxFrameRate;
};

class SpritePerformTestA : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestA);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "A"; }
};

class SpritePerformTestB : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestB);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
        virtual std::string getTestCaseName() override { return "B"; }
};

class SpritePerformTestC : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestC);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "C"; }
};

class SpritePerformTestD : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestD);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "D"; }
};

class SpritePerformTestE : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestE);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "E"; }
};

class SpritePerformTestF : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestF);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "F"; }
};

class SpritePerformTestG : public SpriteMainScene
{
public:
    CREATE_FUNC(SpritePerformTestG);

    virtual void doTest(cocos2d::Sprite* sprite) override;
    virtual std::string title() const override;
    virtual std::string getTestCaseName() override { return "G"; }
};

#endif
