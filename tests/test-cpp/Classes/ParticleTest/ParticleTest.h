#ifndef _PARTICLE_TEST_H_
#define _PARTICLE_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"
////----#include "cocos2d.h"
// #include "event_dispatcher/CCTouch.h"
// #include "CCParticleExample.h"

class ParticleTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ParticleDemo : public BaseTest
{
protected:
    ParticleSystemQuad*    _emitter;
    Sprite*            _background;
	LayerColor*		 _color;

public:
    ~ParticleDemo(void);

    virtual void onEnter(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
    void toggleCallback(Object* sender);

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);

    virtual void update(float dt);
    void setEmitterPosition();
};

class DemoFirework : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoFire : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoSun : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoGalaxy : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoBigFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoRotFlower : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoMeteor : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoSpiral : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoExplosion : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoSmoke : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoSnow : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoRain : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoModernArt : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class DemoRing : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class ParallaxParticle : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
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
    virtual std::string title() const override
    {
        return _title;
    }
};

class RadiusMode1 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class RadiusMode2 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
};

class Issue704 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue870 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void updateQuads(float dt);

private:
    int _index;
};

class Issue1201 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleBatchHybrid : public ParticleDemo
{
public:
    virtual void onEnter();
    void switchRender(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    Node* _parent1;
    Node* _parent2;
};

class ParticleBatchMultipleEmitters : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleReorder : public ParticleDemo
{
public:
    virtual void onEnter();
    void reorderParticles(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    unsigned int _order;
};

class MultipleParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt);
};

class MultipleParticleSystemsBatched : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual void update(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class AddAndDeleteParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual void update(float dt);
    void removeSystem(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class ReorderParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter();
    void reorderSystem(float time);
    virtual void update(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class PremultipliedAlphaTest : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PremultipliedAlphaTest2 : public ParticleDemo
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
