#ifndef __PERFORMANCE_PARTICLE_3D_TEST_H__
#define __PERFORMANCE_PARTICLE_3D_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceParticle3DTests);

class Particle3DMainScene : public TestCase
{
public:
    virtual void initScene();

    void step(float dt);
    void createParticleSystem(int idx);
    void updateQuantityLabel();
    int getParticlesNum() { return _quantityParticles; }
    virtual void doTest() = 0;

    // overrides
    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;
    void beginStat(float dt);
    void endStat(float dt);
    void doAutoTest();
    void removeAllParticles();
    
protected:
    int             _lastRenderedCount;
    int             _quantityParticles;
    cocos2d::Label *_particleLab;

    bool       isStating;
    int        autoTestIndex;
    int        statCount;
    float      totalStatTime;
    float      minFrameRate;
    float      maxFrameRate;
};

class Particle3DPerformTest : public Particle3DMainScene
{
public:
    CREATE_FUNC(Particle3DPerformTest);

    virtual bool init() override;
    virtual std::string title() const override;
    virtual void doTest()override{};
};

#endif
