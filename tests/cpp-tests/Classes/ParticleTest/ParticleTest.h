#ifndef _PARTICLE_TEST_H_
#define _PARTICLE_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ParticleTests);

class ParticleDemo : public TestCase
{
protected:
    cocos2d::ParticleSystemQuad* _emitter;
    cocos2d::Sprite* _background;
    cocos2d::LayerColor* _color;

public:
    ~ParticleDemo();

    virtual void onEnter();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void toggleCallback(cocos2d::Ref* sender);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    virtual void update(float dt) override;
    void setEmitterPosition();
};

class DemoFirework : public ParticleDemo
{
public:
    CREATE_FUNC(DemoFirework);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoFire : public ParticleDemo
{
public:
    CREATE_FUNC(DemoFire);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSun : public ParticleDemo
{
public:
    CREATE_FUNC(DemoSun);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoGalaxy : public ParticleDemo
{
public:
    CREATE_FUNC(DemoGalaxy);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoFlower : public ParticleDemo
{
public:
    CREATE_FUNC(DemoFlower);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoBigFlower : public ParticleDemo
{
public:
    CREATE_FUNC(DemoBigFlower);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRotFlower : public ParticleDemo
{
public:
    CREATE_FUNC(DemoRotFlower);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoMeteor : public ParticleDemo
{
public:
    CREATE_FUNC(DemoMeteor);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSpiral : public ParticleDemo
{
public:
    CREATE_FUNC(DemoSpiral);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoExplosion : public ParticleDemo
{
public:
    CREATE_FUNC(DemoExplosion);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSmoke : public ParticleDemo
{
public:
    CREATE_FUNC(DemoSmoke);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoSnow : public ParticleDemo
{
public:
    CREATE_FUNC(DemoSnow);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRain : public ParticleDemo
{
public:
    CREATE_FUNC(DemoRain);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoModernArt : public ParticleDemo
{
public:
    CREATE_FUNC(DemoModernArt);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoRing : public ParticleDemo
{
public:
    CREATE_FUNC(DemoRing);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ParallaxParticle : public ParticleDemo
{
public:
    CREATE_FUNC(ParallaxParticle);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class DemoParticleFromFile : public ParticleDemo
{
public:
    static DemoParticleFromFile* create(const std::string& file)
    {
        auto ret = new (std::nothrow) DemoParticleFromFile;
        if (ret && ret->init())
        {
            ret->_title = file;
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }

        return ret;
    }

    std::string _title;
    
    virtual void onEnter() override;
    virtual std::string subtitle() const override
    {
        return _title;
    }
};

class RadiusMode1 : public ParticleDemo
{
public:
    CREATE_FUNC(RadiusMode1);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class RadiusMode2 : public ParticleDemo
{
public:
    CREATE_FUNC(RadiusMode2);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class Issue704 : public ParticleDemo
{
public:
    CREATE_FUNC(Issue704);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue870 : public ParticleDemo
{
public:
    CREATE_FUNC(Issue870);
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
    CREATE_FUNC(Issue1201);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleBatchHybrid : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleBatchHybrid);
    virtual void onEnter() override;
    void switchRender(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    cocos2d::Node* _parent1;
    cocos2d::Node* _parent2;
};

class ParticleBatchMultipleEmitters : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleBatchMultipleEmitters);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleReorder : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleReorder);
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
    CREATE_FUNC(MultipleParticleSystems);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void update(float dt) override;
};

class MultipleParticleSystemsBatched : public ParticleDemo
{
public:
    CREATE_FUNC(MultipleParticleSystemsBatched);
    virtual void onEnter() override;
    virtual void update(float dt) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class AddAndDeleteParticleSystems : public ParticleDemo
{
public:
    CREATE_FUNC(AddAndDeleteParticleSystems);
    virtual void onEnter() override;
    virtual void update(float dt) override;
    void removeSystem(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    cocos2d::ParticleBatchNode* _batchNode;
};

class ReorderParticleSystems : public ParticleDemo
{
public:
    CREATE_FUNC(ReorderParticleSystems);
    virtual void onEnter() override;
    void reorderSystem(float time);
    virtual void update(float dt) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    cocos2d::ParticleBatchNode* _batchNode;
};

class PremultipliedAlphaTest : public ParticleDemo
{
    bool _hasEmitter;
public:
    CREATE_FUNC(PremultipliedAlphaTest);
    virtual void onEnter() override;
    void readdPaticle(float delta);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PremultipliedAlphaTest2 : public ParticleDemo
{
public:
    CREATE_FUNC(PremultipliedAlphaTest2);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Issue3990 : public ParticleDemo
{
public:
    CREATE_FUNC(Issue3990);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleVisibleTest : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleVisibleTest);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void callback(float delta);
};

class ParticleAutoBatching : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleAutoBatching);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleResetTotalParticles : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleResetTotalParticles);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ParticleIssue12310 : public ParticleDemo
{
public:
    CREATE_FUNC(ParticleIssue12310);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

#endif
