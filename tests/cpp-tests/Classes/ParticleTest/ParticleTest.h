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

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    void toggleCallback(Ref* sender);

    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);

    virtual void update(float dt);
    void setEmitterPosition();
};

class DemoFirework : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoFire : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSun : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoGalaxy : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoFlower : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoBigFlower : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRotFlower : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoMeteor : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSpiral : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoExplosion : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSmoke : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSnow : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRain : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoModernArt : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRing : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ParallaxParticle : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoParticleFromFile : public ParticleDemo
{
public:
    std::string _title;
    DemoParticleFromFile(const char *file)
    {    
        _title = file;
    }
    virtual void onEnter() override;
    virtual std::string subtitle() const override
    {
        return _title;
    }
};

class RadiusMode1 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class RadiusMode2 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class Issue704 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue870 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void updateQuads(float dt);

private:
    int _index;
};

class Issue1201 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleBatchHybrid : public ParticleDemo
{
public:
    virtual void onEnter() override;
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
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleReorder : public ParticleDemo
{
public:
    virtual void onEnter() override;
    void reorderParticles(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    unsigned int _order;
};

class MultipleParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt);
};

class MultipleParticleSystemsBatched : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual void update(float dt) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class AddAndDeleteParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual void update(float dt) override;
    void removeSystem(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class ReorderParticleSystems : public ParticleDemo
{
public:
    virtual void onEnter() override;
    void reorderSystem(float time);
    virtual void update(float dt) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    ParticleBatchNode* _batchNode;
};

class PremultipliedAlphaTest : public ParticleDemo
{
public:
    virtual void onEnter() override;
    void readdPaticle(float delta);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PremultipliedAlphaTest2 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue3990 : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleVisibleTest : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void callback(float delta);
};

class ParticleAutoBatching : public ParticleDemo
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
