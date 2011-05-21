#ifndef __PERFORMANCE_PARTICLE_TEST_H__
#define __PERFORMANCE_PARTICLE_TEST_H__

#include "cocos2d.h"

enum {
    kMaxParticles = 14000,
    kNodesIncrease = 100,
};

class ParticleMainScene : public cocos2d::CCScene
{
public:
    virtual void initWithSubTest(int subtest, int particles);
    virtual std::string title();

    void step(cocos2d::ccTime dt);
    void createParticleSystem();
    void onDecrease(cocos2d::CCObject* pSender);
    void onIncrease(cocos2d::CCObject* pSender);
    void testNCallback(cocos2d::CCObject* pSender);
    void updateQuantityLabel();

    void restartCallback(cocos2d::CCObject* pSender);
    void nextCallback(cocos2d::CCObject* pSender);
    void backCallback(cocos2d::CCObject* pSender);
    void showCurrentTest();

    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

    virtual void doTest() = 0;

protected:
    int			lastRenderedCount;
    int			quantityParticles;
    int			subtestNumber;
};

class ParticlePerformTest1 : public ParticleMainScene
{
public:
    virtual std::string title();
    virtual void doTest();
};

class ParticlePerformTest2 : public ParticleMainScene
{
public:
    virtual std::string title();
    virtual void doTest();
};

class ParticlePerformTest3 : public ParticleMainScene
{
public:
    virtual std::string title();
    virtual void doTest();
};

class ParticlePerformTest4 : public ParticleMainScene
{
public:
    virtual std::string title();
    virtual void doTest();
};

#endif
