#ifndef __PERFORMANCE_PARTICLE_3D_TEST_H__
#define __PERFORMANCE_PARTICLE_3D_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceParticle3DTests);

class Particle3DMainScene : public TestCase
{
public:
    virtual void initWithSubTest(int subtest, int particles);

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
    CREATE_FUNC(Particle3DPerformTest);

    virtual bool init() override;
    virtual std::string title() const override;
    virtual void doTest(){};
};

#endif
