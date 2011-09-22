#ifndef _PARTICLE_TEST_H_
#define _PARTICLE_TEST_H_

#include "../testBasic.h"
////----#include "cocos2d.h"
// #include "touch_dispatcher/CCTouch.h"
// #include "CCParticleExample.h"

class ParticleTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ParticleDemo : public CCLayerColor
{
protected:
	CCParticleSystem*	m_emitter;
	CCSprite*			m_background;

public:
	ParticleDemo(void);
	~ParticleDemo(void);

	virtual void onEnter(void);

	virtual std::string title();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);
	void toggleCallback(CCObject* pSender);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void step(ccTime dt);
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
    std::string m_title;
    DemoParticleFromFile(const char *file)
    {	
        m_title = file;
    }
    virtual void onEnter();
    virtual std::string title()
    {
        return m_title;
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
    void updateQuads(ccTime dt);

private:
    int m_nIndex;
};

#endif
