#ifndef __PERFORMANCE_PARTICLE_TEST_H__
#define __PERFORMANCE_PARTICLE_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceParticleTests);

class ParticleMainScene : public TestCase
{
public:
    virtual bool init() override;
    virtual void initWithSubTest(int subtest, int particles);

    void step(float dt);
    void createParticleSystem();
    void testNCallback(cocos2d::Ref* sender);
    void updateQuantityLabel();
    virtual void doTest() = 0;

protected:
    int            lastRenderedCount;
    static int quantityParticles;
    static int subtestNumber;
};

class ParticlePerformTest1 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest1);

    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest2 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest2);

    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest3 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest3);

    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest4 : public ParticleMainScene
{
public:
    CREATE_FUNC(ParticlePerformTest4);

    virtual std::string title() const override;
    virtual void doTest();
};

#endif
