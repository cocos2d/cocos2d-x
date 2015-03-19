#ifndef __PERFORMANCE_PARTICLE_3D_TEST_H__
#define __PERFORMANCE_PARTICLE_3D_TEST_H__

#include "PerformanceTest.h"

class Particle3DMenuLayer : public PerformBasicLayer
{
public:
    Particle3DMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    virtual void showCurrentTest();
};

class Particle3DMainScene : public Scene
{
public:
    virtual void initWithSubTest(int subtest, int particles);
    virtual std::string title() const;

    void step(float dt);
    void createParticleSystem(int idx);
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

class Particle3DPerformTest : public Particle3DMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

void runParticle3DTest();

#endif
