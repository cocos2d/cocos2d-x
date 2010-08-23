#ifndef _PARTICLE_TEST_H_
#define _PARTICLE_TEST_H_

#include "../testBasic.h"
#include "cocos2d.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCParticleExample.h"

class ParticleTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ParticleDemo : public CCColorLayer
{
protected:
	CCParticleSystem*	m_emitter;
	CCSprite*			m_background;

public:
	ParticleDemo(void);
	~ParticleDemo(void);

	virtual void onEnter(void);

	virtual std::string title();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);
	void toggleCallback(NSObject* pSender);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, UIEvent* event);

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

#endif
