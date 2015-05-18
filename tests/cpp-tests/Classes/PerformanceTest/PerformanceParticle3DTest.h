#ifndef __PERFORMANCE_PARTICLE_3D_TEST_H__
#define __PERFORMANCE_PARTICLE_3D_TEST_H__

#include "PerformanceTest.h"

class Particle3DMenuLayer : public PerformBasicLayer
{
public:
    Particle3DMenuLayer(bool isControlMenuVisible, int maxCases = 0, int curCase = 0);
    virtual void showCurrentTest();
};

class Particle3DMainScene : public cocos2d::Scene
{
public:
    virtual void initWithSubTest(int subtest, int particles);
    virtual std::string title() const;

    void step(float dt);
    void createParticleSystem(int idx);
    void testNCallback(cocos2d::Ref* sender);
    void updateQuantityLabel();
    int getSubTestNum() { return _subtestNumber; }
    int getParticlesNum() { return _quantityParticles; }
    virtual void doTest() = 0;

protected:
    int             _lastRenderedCount;
    int             _quantityParticles;
    int             _subtestNumber;
    cocos2d::Label *_particleLab;
};

class Particle3DPerformTest : public Particle3DMainScene
{
public:
    virtual std::string title() const override;
    virtual void doTest();
};

void runParticle3DTest();

#endif
