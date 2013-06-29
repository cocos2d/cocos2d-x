#ifndef _PARTICLE_TEST_H_
#define _PARTICLE_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"
////----#include "cocos2d.h"
// #include "touch_dispatcher/CCTouch.h"
// #include "CCParticleExample.h"

class ParticleTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ParticleDemo : public BaseTest
{
protected:
    CCParticleSystem*    _emitter;
    CCSprite*            _background;
	CCLayerColor*		 _color;

public:
    ~ParticleDemo(void);

    virtual void onEnter(void);

    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
    void toggleCallback(CCObject* pSender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    virtual void update(float dt);
    void setEmitterPosition();
};

class DemoFirework : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoFire : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoSun : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoGalaxy : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoBigFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoRotFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoMeteor : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoSpiral : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoExplosion : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoSmoke : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoSnow : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoRain : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoModernArt : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoRing : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class ParallaxParticle : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class DemoParticleFromFile : public ParticleDemo
{
public:
    std::string _title;
    DemoParticleFromFile(const char *file)
    {    
        _title = file;
    }
    virtual void onEnter();
    virtual std::string title()
    {
        return _title;
    }
};

class RadiusMode1 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class RadiusMode2 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
};

class Issue704 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class Issue870 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void updateQuads(float dt);

private:
    int _index;
};

class Issue1201 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ParticleBatchHybrid : public ParticleDemo
{
public:
    virtual void onEnter();
    void switchRender(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    CCNode* _parent1;
    CCNode* _parent2;
};

class ParticleBatchMultipleEmitters : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class ParticleReorder : public ParticleDemo
{
public:
    virtual void onEnter();
    void reorderParticles(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    unsigned int _order;
};

class MultipleParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void update(float dt);
};

class MultipleParticleSystemsBatched : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual void update(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    CCParticleBatchNode* _batchNode;
};

class AddAndDeleteParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual void update(float dt);
    void removeSystem(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    CCParticleBatchNode* _batchNode;
};

class ReorderParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    void reorderSystem(float time);
    virtual void update(float dt);
    virtual std::string title();
    virtual std::string subtitle();
private:
    CCParticleBatchNode* _batchNode;
};

class PremultipliedAlphaTest : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

class PremultipliedAlphaTest2 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};

#endif
