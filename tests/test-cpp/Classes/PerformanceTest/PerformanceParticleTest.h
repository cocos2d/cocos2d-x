#ifndef __PERFORMANCE_PARTICLE_TEST_H__
#define __PERFORMANCE_PARTICLE_TEST_H__

#include "PerformanceTest.h"

class ParticleMenuLayer : public PerformBasicLayer
{
public:
    ParticleMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    virtual void showCurrentTest();
};

class ParticleMainScene : public Scene
{
public:
    virtual void initWithSubTest(int subtest, int particles);
    virtual std::string title() const;

    void step(float dt);
    void createParticleSystem();
    void testNCallback(Ref* sender);
    void updateQuantityLabel();
    int getSubTestNum() { return subtestNumber; }
    int getParticlesNum() { return quantityParticles; }
    virtual void doTest() = 0;

protected:
    int            lastRenderedCount;
    int            quantityParticles;
    int            subtestNumber;
};

class ParticlePerformTest1 : public ParticleMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest2 : public ParticleMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest3 : public ParticleMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

class ParticlePerformTest4 : public ParticleMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

void runParticleTest();

#endif
