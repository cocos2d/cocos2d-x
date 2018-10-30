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

#ifndef __PERFORMANCE_PARTICLE_TEST_H__
#define __PERFORMANCE_PARTICLE_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceParticleTests);

class ParticleMainScene : public TestCase
{
public:
    ParticleMainScene();
    virtual bool init() override;
    virtual void initWithSubTest(int subtest, int particles);

    void step(float dt);
    void createParticleSystem();
    void testNCallback(cocos2d::Ref* sender);
    void updateQuantityLabel();
    void updateTitle();
    virtual void doTest();

    // overrides
    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;
    void beginStat(float dt);
    void endStat(float dt);
    void doAutoTest();

protected:
    int        lastRenderedCount;
    static int quantityParticles;
    static int subtestNumber;
    int        particleSize;

    bool       isStating;
    int        autoTestIndex;
    int        statCount;
    float      totalStatTime;
    float      minFrameRate;
    float      maxFrameRate;
};

class ParticlePerformTest1 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest1);

    virtual std::string title() const override;
    virtual void initWithSubTest(int subtest, int particles) override;
};

class ParticlePerformTest2 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest2);

    virtual std::string title() const override;
    virtual void initWithSubTest(int subtest, int particles) override;
};

class ParticlePerformTest3 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest3);

    virtual std::string title() const override;
    virtual void initWithSubTest(int subtest, int particles) override;
};

class ParticlePerformTest4 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest4);

    virtual std::string title() const override;
    virtual void initWithSubTest(int subtest, int particles) override;
};

#endif
