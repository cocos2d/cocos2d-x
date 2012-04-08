#include "ParticleTest.h"
// #include "CCActionInterval.h"
// #include "CCMenu.h"
// #include "CCLabelTTF.h"
// #include "CCLabelAtlas.h"
// #include "touch_dispatcher/CCTouchDispatcher.h"
#include "../testResource.h"
/*#include "support/CCPointExtension.h"*/

enum {
	kTagParticleCount = 1,
};

CCLayer* nextParticleAction();
CCLayer* backParticleAction();
CCLayer* restartParticleAction();

//------------------------------------------------------------------
//
// DemoFirework
//
//------------------------------------------------------------------
void DemoFirework::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleFireworks::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	
	setEmitterPosition();
}

std::string DemoFirework::title()
{
	return "ParticleFireworks";
}


//------------------------------------------------------------------
//
// DemoFire
//
//------------------------------------------------------------------
void DemoFire::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleFire::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );//.pvr");
	CCPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CCPointMake(p.x, 100) );
	
	setEmitterPosition();
}

std::string DemoFire::title()
{
	return "ParticleFire";
}

//------------------------------------------------------------------
//
// DemoSun
//
//------------------------------------------------------------------
void DemoSun::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleSun::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoSun::title()
{
	return "ParticleSun";
}

//------------------------------------------------------------------
//
// DemoGalaxy
//
//------------------------------------------------------------------
void DemoGalaxy::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleGalaxy::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition(); 
}

std::string DemoGalaxy::title()
{
	return "ParticleGalaxy";
}

//------------------------------------------------------------------
//
// DemoFlower
//
//------------------------------------------------------------------
void DemoFlower::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleFlower::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	
	setEmitterPosition();
}

std::string DemoFlower::title()
{
	return "ParticleFlower";
}

//------------------------------------------------------------------
//
// DemoBigFlower
//
//------------------------------------------------------------------
void DemoBigFlower::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = new CCParticleSystemQuad();
	m_emitter->initWithTotalParticles(50);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	////m_emitter->release();	// win32 :  use this line or remove this line and use autorelease()
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );

	m_emitter->setDuration(-1);
	
	// gravity
	m_emitter->setGravity(CCPointZero);
	
	// angle
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	
	// speed of particles
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);
	
	// radial
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);
	
	// tagential
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	
	// emitter position
	m_emitter->setPosition( CCPointMake(160,240) );
	m_emitter->setPosVar(CCPointZero);
	
	// life of particles
	m_emitter->setLife(4);
	m_emitter->setLifeVar(1);
	
	// spin of particles
	m_emitter->setStartSpin(0);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);
	
	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
	m_emitter->setEndColorVar(endColorVar);
	
	// size, in pixels
	m_emitter->setStartSize(80.0f);
	m_emitter->setStartSizeVar(40.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);
	
	// emits per second
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	
	// additive
	m_emitter->setIsBlendAdditive(true);

	setEmitterPosition();
}

std::string DemoBigFlower::title()
{
	return "ParticleBigFlower";
}

//------------------------------------------------------------------
//
// DemoRotFlower
//
//------------------------------------------------------------------
void DemoRotFlower::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = new CCParticleSystemQuad();
	m_emitter->initWithTotalParticles(300);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	////m_emitter->release();	// win32 : Remove this line
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars2) );
	
	// duration
	m_emitter->setDuration(-1);
	
	// gravity
	m_emitter->setGravity(CCPointZero);
	
	// angle
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	
	// speed of particles
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);
	
	// radial
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);
	
	// tagential
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	
	// emitter position
	m_emitter->setPosition( CCPointMake(160,240) );
	m_emitter->setPosVar(CCPointZero);
	
	// life of particles
	m_emitter->setLife(3);
	m_emitter->setLifeVar(1);

	// spin of particles
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(2000);
	
	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
	m_emitter->setEndColorVar(endColorVar);

	// size, in pixels
	m_emitter->setStartSize(30.0f);
	m_emitter->setStartSizeVar(00.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);
	
	// emits per second
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());

	// additive
	m_emitter->setIsBlendAdditive(false);
	
	setEmitterPosition();
}

std::string DemoRotFlower::title()
{
	return "ParticleRotFlower";
}

//------------------------------------------------------------------
//
// DemoMeteor
//
//------------------------------------------------------------------
void DemoMeteor::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleMeteor::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoMeteor::title()
{
	return "ParticleMeteor";
}

//------------------------------------------------------------------
//
// DemoSpiral
//
//------------------------------------------------------------------
void DemoSpiral::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleSpiral::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoSpiral::title()
{
	return "ParticleSpiral";
}

//------------------------------------------------------------------
//
// DemoExplosion
//
//------------------------------------------------------------------
void DemoExplosion::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleExplosion::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	
	m_emitter->setIsAutoRemoveOnFinish(true);
	
	setEmitterPosition();
}

std::string DemoExplosion::title()
{
	return "ParticleExplosion";
}

//------------------------------------------------------------------
//
// DemoSmoke
//
//------------------------------------------------------------------
void DemoSmoke::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleSmoke::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	CCPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CCPointMake( p.x, 100) );
	
	setEmitterPosition();
}

std::string DemoSmoke::title()
{
	return "ParticleSmoke";
}

//------------------------------------------------------------------
//
// DemoSnow
//
//------------------------------------------------------------------
void DemoSnow::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleSnow::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	CCPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CCPointMake( p.x, p.y-110) );
	m_emitter->setLife(3);
	m_emitter->setLifeVar(1);
	
	// gravity
	m_emitter->setGravity(CCPointMake(0,-10));
		
	// speed of particles
	m_emitter->setSpeed(130);
	m_emitter->setSpeedVar(30);
	
	
	ccColor4F startColor = m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	m_emitter->setStartColorVar(startColorVar);
	
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_snow) );
	
	setEmitterPosition();
}

std::string DemoSnow::title()
{
	return "ParticleSnow";
}

//------------------------------------------------------------------
//
// DemoRain
//
//------------------------------------------------------------------
void DemoRain::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleRain::node();
    m_emitter->retain();
	m_background->addChild(m_emitter, 10);
	
	CCPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CCPointMake( p.x, p.y-100) );
	m_emitter->setLife(4);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoRain::title()
{
	return "ParticleRain";
}

//------------------------------------------------------------------
//
// DemoModernArt
//
//------------------------------------------------------------------
void DemoModernArt::onEnter()
{
	ParticleDemo::onEnter();

//FIXME: If use CCParticleSystemPoint, bada 1.0 device will crash. 
//  Crash place: CCParticleSystemPoint.cpp Line 149, function: glDrawArrays(GL_POINTS, 0, m_uParticleIdx);
//  m_emitter = new CCParticleSystemPoint();
    m_emitter = new CCParticleSystemQuad();
	m_emitter->initWithTotalParticles(1000);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	////m_emitter->release();
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	// duration
	m_emitter->setDuration(-1);
	
	// gravity
	m_emitter->setGravity(CCPointMake(0,0));
	
	// angle
	m_emitter->setAngle(0);
	m_emitter->setAngleVar(360);
	
	// radial
	m_emitter->setRadialAccel(70);
	m_emitter->setRadialAccelVar(10);
	
	// tagential
	m_emitter->setTangentialAccel(80);
	m_emitter->setTangentialAccelVar(0);
	
	// speed of particles
	m_emitter->setSpeed(50);
	m_emitter->setSpeedVar(10);
	
	// emitter position
	m_emitter->setPosition( CCPointMake( s.width/2, s.height/2) );
	m_emitter->setPosVar(CCPointZero);
	
	// life of particles
	m_emitter->setLife(2.0f);
	m_emitter->setLifeVar(0.3f);
	
	// emits per frame
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	
	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
	m_emitter->setEndColorVar(endColorVar);
	
	// size, in pixels
	m_emitter->setStartSize(1.0f);
	m_emitter->setStartSizeVar(1.0f);
	m_emitter->setEndSize(32.0f);
	m_emitter->setEndSizeVar(8.0f);
	
	// texture
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	// additive
	m_emitter->setIsBlendAdditive(false);
	
	setEmitterPosition();
}

std::string DemoModernArt::title()
{
	return "Varying size";
}

//------------------------------------------------------------------
//
// DemoRing 
//
//------------------------------------------------------------------
void DemoRing::onEnter()
{
	ParticleDemo::onEnter();

	m_emitter = CCParticleFlower::node();
    m_emitter->retain();

	m_background->addChild(m_emitter, 10);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	m_emitter->setLifeVar(0);
	m_emitter->setLife(10);
	m_emitter->setSpeed(100);
	m_emitter->setSpeedVar(0);
	m_emitter->setEmissionRate(10000);
	
	setEmitterPosition();
}

std::string DemoRing::title()
{
	return "Ring Demo";
}

//------------------------------------------------------------------
//
// ParallaxParticle
//
//------------------------------------------------------------------
void ParallaxParticle::onEnter()
{
	ParticleDemo::onEnter();
	
	m_background->getParent()->removeChild(m_background, true);
    m_background = NULL;

	CCParallaxNode* p = CCParallaxNode::node(); 
	addChild(p, 5);

	CCSprite *p1 = CCSprite::spriteWithFile(s_back3);
	CCSprite *p2 = CCSprite::spriteWithFile(s_back3);
	
	p->addChild( p1, 1, CCPointMake(0.5f,1), CCPointMake(0,250) );
	p->addChild(p2, 2, CCPointMake(1.5f,1), CCPointMake(0,50) );

	m_emitter = CCParticleFlower::node();
    m_emitter->retain();
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );

	p1->addChild(m_emitter, 10);
	m_emitter->setPosition( CCPointMake(250,200) );
	
	CCParticleSun* par = CCParticleSun::node();
	p2->addChild(par, 10);
    par->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	CCActionInterval* move = CCMoveBy::actionWithDuration(4, CCPointMake(300,0));
	CCActionInterval* move_back = move->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions( move, move_back, NULL);
	p->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)seq));	
}

std::string ParallaxParticle::title()
{
	return "Parallax + Particles";
}

//------------------------------------------------------------------
//
// RadiusMode1
//
//------------------------------------------------------------------
void RadiusMode1::onEnter()
{
    ParticleDemo::onEnter();

    setColor(ccBLACK);
    removeChild(m_background, true);
    m_background = NULL;

    m_emitter = new CCParticleSystemQuad();
    m_emitter->initWithTotalParticles(200);
    addChild(m_emitter, 10);
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/stars-grayscale.png"));

    // duration
    m_emitter->setDuration(kCCParticleDurationInfinity);

    // radius mode
    m_emitter->setEmitterMode(kCCParticleModeRadius);

    // radius mode: start and end radius in pixels
    m_emitter->setStartRadius(0);
    m_emitter->setStartRadiusVar(0);
    m_emitter->setEndRadius(160);
    m_emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    m_emitter->setRotatePerSecond(180);
    m_emitter->setRotatePerSecondVar(0);


    // angle
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(0);

    // emitter position
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_emitter->setPosition(ccp(size.width/2, size.height/2));
    m_emitter->setPosVar(CCPointZero);

    // life of particles
    m_emitter->setLife(5);
    m_emitter->setLifeVar(0);

    // spin of particles
    m_emitter->setStartSpin(0);
    m_emitter->setStartSpinVar(0);
    m_emitter->setEndSpin(0);
    m_emitter->setEndSpinVar(0);

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColorVar(startColorVar);

    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    m_emitter->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
    m_emitter->setEndColorVar(endColorVar);

    // size, in pixels
    m_emitter->setStartSize(32);
    m_emitter->setStartSizeVar(0);
    m_emitter->setEndSize(kCCParticleStartSizeEqualToEndSize);

    // emits per second
    m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());

    // additive
    m_emitter->setIsBlendAdditive(false);
}

std::string RadiusMode1::title()
{
    return "Radius Mode: Spiral";
}

//------------------------------------------------------------------
//
// RadiusMode2
//
//------------------------------------------------------------------
void RadiusMode2::onEnter()
{
    ParticleDemo::onEnter();

    setColor(ccBLACK);
    removeChild(m_background, true);
    m_background = NULL;

    m_emitter = new CCParticleSystemQuad();
    m_emitter->initWithTotalParticles(200);
    addChild(m_emitter, 10);
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/stars-grayscale.png"));

    // duration
    m_emitter->setDuration(kCCParticleDurationInfinity);

    // radius mode
    m_emitter->setEmitterMode(kCCParticleModeRadius);

    // radius mode: start and end radius in pixels
    m_emitter->setStartRadius(100);
    m_emitter->setStartRadiusVar(0);
    m_emitter->setEndRadius(kCCParticleStartRadiusEqualToEndRadius);
    m_emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    m_emitter->setRotatePerSecond(45);
    m_emitter->setRotatePerSecondVar(0);


    // angle
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(0);

    // emitter position
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_emitter->setPosition(ccp(size.width/2, size.height/2));
    m_emitter->setPosVar(CCPointZero);

    // life of particles
    m_emitter->setLife(4);
    m_emitter->setLifeVar(0);

    // spin of particles
    m_emitter->setStartSpin(0);
    m_emitter->setStartSpinVar(0);
    m_emitter->setEndSpin(0);
    m_emitter->setEndSpinVar(0);

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColorVar(startColorVar);

        ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    m_emitter->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
    m_emitter->setEndColorVar(endColorVar);

    // size, in pixels
    m_emitter->setStartSize(32);
    m_emitter->setStartSizeVar(0);
    m_emitter->setEndSize(kCCParticleStartSizeEqualToEndSize);

    // emits per second
    m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());

    // additive
    m_emitter->setIsBlendAdditive(false);
}

std::string RadiusMode2::title()
{
    return "Radius Mode: Semi Circle";
}

//------------------------------------------------------------------
//
// Issue704
//
//------------------------------------------------------------------
void Issue704::onEnter()
{
    ParticleDemo::onEnter();

    setColor(ccBLACK);
    removeChild(m_background, true);
    m_background = NULL;

    m_emitter = new CCParticleSystemQuad();
    m_emitter->initWithTotalParticles(100);
    addChild(m_emitter, 10);
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));

    // duration
    m_emitter->setDuration(kCCParticleDurationInfinity);

    // radius mode
    m_emitter->setEmitterMode(kCCParticleModeRadius);

    // radius mode: start and end radius in pixels
    m_emitter->setStartRadius(50);
    m_emitter->setStartRadiusVar(0);
    m_emitter->setEndRadius(kCCParticleStartRadiusEqualToEndRadius);
    m_emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    m_emitter->setRotatePerSecond(0);
    m_emitter->setRotatePerSecondVar(0);


    // angle
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(0);

    // emitter position
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_emitter->setPosition(ccp(size.width/2, size.height/2));
    m_emitter->setPosVar(CCPointZero);

    // life of particles
    m_emitter->setLife(5);
    m_emitter->setLifeVar(0);

    // spin of particles
    m_emitter->setStartSpin(0);
    m_emitter->setStartSpinVar(0);
    m_emitter->setEndSpin(0);
    m_emitter->setEndSpinVar(0);

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    m_emitter->setStartColorVar(startColorVar);

        ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    m_emitter->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
    m_emitter->setEndColorVar(endColorVar);

    // size, in pixels
    m_emitter->setStartSize(16);
    m_emitter->setStartSizeVar(0);
    m_emitter->setEndSize(kCCParticleStartSizeEqualToEndSize);

    // emits per second
    m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());

    // additive
    m_emitter->setIsBlendAdditive(false);

    CCRotateBy* rot = CCRotateBy::actionWithDuration(16, 360);
    m_emitter->runAction(CCRepeatForever::actionWithAction(rot));
}

std::string Issue704::title()
{
    return "Issue 704. Free + Rot";
}

std::string Issue704::subtitle()
{
    return "Emitted particles should not rotate";
}

//------------------------------------------------------------------
//
// Issue870
//
//------------------------------------------------------------------
void Issue870::onEnter()
{
    ParticleDemo::onEnter();

    setColor(ccBLACK);
    removeChild(m_background, true);
    m_background = NULL;

    CCParticleSystemQuad *system = new CCParticleSystemQuad();
    system->initWithFile("Images/SpinningPeas.plist");
    system->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("Images/particles.png"), CCRectMake(0,0,32,32));
    addChild(system, 10);
    m_emitter = system;

    m_nIndex = 0;
    schedule(schedule_selector(Issue870::updateQuads), 2.0f);
}

void Issue870::updateQuads(ccTime dt)
{
    m_nIndex = (m_nIndex + 1) % 4;
    CCRect rect = CCRectMake(m_nIndex * 32, 0, 32, 32);
    CCParticleSystemQuad* system = (CCParticleSystemQuad*)m_emitter;
    system->setTextureWithRect(m_emitter->getTexture(), rect);
}

std::string Issue870::title()
{
    return "Issue 870. SubRect";
}

std::string Issue870::subtitle()
{
    return "Every 2 seconds the particle should change";
}

//------------------------------------------------------------------
//
// DemoParticleFromFile
//
//------------------------------------------------------------------
void DemoParticleFromFile::onEnter()
{
    ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

    m_emitter = new CCParticleSystemQuad();
    std::string filename = "Images/" + m_title + ".plist";
    m_emitter->initWithFile(filename.c_str());
    addChild(m_emitter, 10);

    setEmitterPosition();
}

//------------------------------------------------------------------
//
// ParticleDemo
//
//------------------------------------------------------------------

enum
{
	IDC_NEXT = 100,
	IDC_BACK,
	IDC_RESTART,
	IDC_TOGGLE
};

static int sceneIdx = -1; 

#define MAX_LAYER	41

CCLayer* createParticleLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new ParticleReorder();
		case 1: return new ParticleBatchHybrid();
		case 2: return new ParticleBatchMultipleEmitters();
		case 3: return new DemoFlower();
		case 4: return new DemoGalaxy();
		case 5: return new DemoFirework();
		case 6: return new DemoSpiral();
		case 7: return new DemoSun();
		case 8: return new DemoMeteor();
		case 9: return new DemoFire();
		case 10: return new DemoSmoke();
		case 11: return new DemoExplosion();
		case 12: return new DemoSnow();
		case 13: return new DemoRain();
		case 14: return new DemoBigFlower();
		case 15: return new DemoRotFlower();
		case 16: return new DemoModernArt();
		case 17: return new DemoRing();
		case 18: return new ParallaxParticle();
        case 19: return new DemoParticleFromFile("BoilingFoam");
        case 20: return new DemoParticleFromFile("BurstPipe");
        case 21: return new DemoParticleFromFile("Comet");
        case 22: return new DemoParticleFromFile("debian");
        case 23: return new DemoParticleFromFile("ExplodingRing");
        case 24: return new DemoParticleFromFile("LavaFlow");
        case 25: return new DemoParticleFromFile("SpinningPeas");
        case 26: return new DemoParticleFromFile("SpookyPeas");
        case 27: return new DemoParticleFromFile("Upsidedown");
        case 28: return new DemoParticleFromFile("Flower");
        case 29: return new DemoParticleFromFile("Spiral");
        case 30: return new DemoParticleFromFile("Galaxy");
		case 31: return new DemoParticleFromFile("Phoenix");
        case 32: return new RadiusMode1();
        case 33: return new RadiusMode2();
        case 34: return new Issue704();
        case 35: return new Issue870();
		case 36: return new Issue1201();
		// v1.1 tests
		case 37: return new MultipleParticleSystems();
		case 38: return new MultipleParticleSystemsBatched();
		case 39: return new AddAndDeleteParticleSystems();
		case 40: return new ReorderParticleSystems();
		default:
			break;
	}

	return NULL;
}


CCLayer* nextParticleAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backParticleAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartParticleAction()
{
	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


ParticleDemo::ParticleDemo(void)
{
	initWithColor( ccc4(127,127,127,255) );

	m_emitter = NULL;

	setIsTouchEnabled( true );
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 100, 1000);
	label->setPosition( CCPointMake(s.width/2, s.height-50) );
	
	CCLabelTTF *tapScreen = CCLabelTTF::labelWithString("(Tap the Screen)", "Arial", 20);
	tapScreen->setPosition( CCPointMake(s.width/2, s.height-80) );
	addChild(tapScreen, 100);
	
	CCMenuItemImage* item1 = CCMenuItemImage::itemWithNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ParticleDemo::backCallback) );
	CCMenuItemImage* item2 = CCMenuItemImage::itemWithNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ParticleDemo::restartCallback) );
	CCMenuItemImage* item3 = CCMenuItemImage::itemWithNormalImage(s_pPathF1, s_pPathF2,  this, menu_selector(ParticleDemo::nextCallback) );
	
	CCMenuItemToggle* item4 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(ParticleDemo::toggleCallback), 
																CCMenuItemFont::itemWithString( "Free Movement" ),
                                                                CCMenuItemFont::itemWithString( "Relative Movement" ),
																CCMenuItemFont::itemWithString( "Grouped Movement" ),
																NULL );
	
	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, item4, NULL);
		
	menu->setPosition( CCPointZero );
	item1->setPosition( CCPointMake( s.width/2 - 100,30) );
	item2->setPosition( CCPointMake( s.width/2, 30) );
	item3->setPosition( CCPointMake( s.width/2 + 100,30) );
	item4->setPosition( CCPointMake( 0, 100) );
	item4->setAnchorPoint( CCPointMake(0,0) );

	addChild( menu, 100 );	
	
    CCLabelAtlas* labelAtlas = CCLabelAtlas::labelWithString("0000", "fonts/fps_images.png", 16, 24, '.');
    addChild(labelAtlas, 100, kTagParticleCount);
	labelAtlas->setPosition( CCPointMake(s.width-66,50) );
	
	// moving background
	m_background = CCSprite::spriteWithFile(s_back3);
	addChild(m_background, 5);
	m_background->setPosition( CCPointMake(s.width/2, s.height-180) );

	CCActionInterval* move = CCMoveBy::actionWithDuration(4, CCPointMake(300,0) );
	CCActionInterval* move_back = move->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions( move, move_back, NULL);
	m_background->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)seq) );
	
	
	scheduleUpdate();
}

ParticleDemo::~ParticleDemo(void)
{
	CC_SAFE_RELEASE(m_emitter);
}

void ParticleDemo::onEnter(void)
{
	CCLayer::onEnter();

	CCLabelTTF* pLabel = (CCLabelTTF*)(this->getChildByTag(1000));
	pLabel->setString(title().c_str());
}

std::string ParticleDemo::title()
{
	return "No title";
}

void ParticleDemo::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool ParticleDemo::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void ParticleDemo::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	return ccTouchEnded(touch, event);
}

void ParticleDemo::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint location = touch->locationInView();
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

    CCPoint pos = CCPointZero;
    if (m_background)
    {
	    pos = m_background->convertToWorldSpace(CCPointZero);
    }

	if (m_emitter != NULL)
	{
		m_emitter->setPosition( ccpSub(convertedLocation, pos) );	
	}
}

void ParticleDemo::update(ccTime dt)
{
    if (m_emitter)
    {
	    CCLabelAtlas* atlas = (CCLabelAtlas*)getChildByTag(kTagParticleCount);
        char str[5] = {0};
        sprintf(str, "%04d", m_emitter->getParticleCount());
	    atlas->setString(str);
    }
}

void ParticleDemo::toggleCallback(CCObject* pSender)
{
	if (m_emitter != NULL)
	{
		if( m_emitter->getPositionType() == kCCPositionTypeGrouped )
			m_emitter->setPositionType( kCCPositionTypeFree );
		else if (m_emitter->getPositionType() == kCCPositionTypeFree)
			m_emitter->setPositionType(kCCPositionTypeRelative);
		else if (m_emitter->getPositionType() == kCCPositionTypeRelative)
			m_emitter->setPositionType( kCCPositionTypeGrouped );
	}
}

void ParticleDemo::restartCallback(CCObject* pSender)
{
	if (m_emitter != NULL)
	{
		m_emitter->resetSystem(); 
	}
}

void ParticleDemo::nextCallback(CCObject* pSender)
{
	CCScene* s = new ParticleTestScene();
	s->addChild( nextParticleAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ParticleDemo::backCallback(CCObject* pSender)
{
	CCScene* s = new ParticleTestScene();
	s->addChild( backParticleAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void ParticleDemo::setEmitterPosition()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	if (m_emitter != NULL)
	{
		m_emitter->setPosition( CCPointMake(s.width / 2, s.height / 2) );
	}
}

// ParticleBatchHybrid

void ParticleBatchHybrid::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	m_emitter = CCParticleSystemQuad::particleWithFile("Images/LavaFlow.plist");
	m_emitter->retain();
	CCParticleBatchNode *batch = CCParticleBatchNode::batchNodeWithTexture(m_emitter->getTexture());

	batch->addChild(m_emitter);

	addChild(batch, 10);

	schedule(schedule_selector(ParticleBatchHybrid::switchRender), 2.0f);

	CCNode *node = CCNode::node();
	addChild(node);

	m_pParent1 = batch;
	m_pParent2 = node;
}

void ParticleBatchHybrid::switchRender(ccTime dt)
{
	bool usingBatch = ( m_emitter->getBatchNode() != NULL );
	m_emitter->removeFromParentAndCleanup(false);

	CCNode *newParent = (usingBatch ? m_pParent2  : m_pParent1 );
	newParent->addChild(m_emitter);

    CCLog("Particle: Using new parent: %s", usingBatch ? "CCNode" : "CCParticleBatchNode");
}

std::string ParticleBatchHybrid::title()
{
	return "Paticle Batch";
}

std::string ParticleBatchHybrid::subtitle()
{
	return "Hybrid: batched and non batched every 2 seconds";
}

// ParticleBatchMultipleEmitters

void ParticleBatchMultipleEmitters::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::particleWithFile("Images/LavaFlow.plist");
	emitter1->setStartColor(ccc4f(1,0,0,1));
	CCParticleSystemQuad *emitter2 = CCParticleSystemQuad::particleWithFile("Images/LavaFlow.plist");
	emitter2->setStartColor(ccc4f(0,1,0,1));
	CCParticleSystemQuad *emitter3 = CCParticleSystemQuad::particleWithFile("Images/LavaFlow.plist");
	emitter3->setStartColor(ccc4f(0,0,1,1));

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	emitter1->setPosition(ccp( s.width/1.25f, s.height/1.25f));
	emitter2->setPosition(ccp( s.width/2, s.height/2));
	emitter3->setPosition(ccp( s.width/4, s.height/4));

	CCParticleBatchNode *batch = CCParticleBatchNode::batchNodeWithTexture(emitter1->getTexture());

	batch->addChild(emitter1, 0);
	batch->addChild(emitter2, 0);
	batch->addChild(emitter3, 0);

	addChild(batch, 10);
}

std::string ParticleBatchMultipleEmitters::title()
{
	return "Paticle Batch";
}

std::string ParticleBatchMultipleEmitters::subtitle()
{
	return "Multiple emitters. One Batch";
}

// ParticleReorder

void ParticleReorder::onEnter()
{
	ParticleDemo::onEnter();

	m_nOrder = 0;
	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	CCParticleSystem *ignore = CCParticleSystemQuad::particleWithFile("Images/SmallSun.plist");
	CCNode *parent1 = CCNode::node();
	CCNode *parent2 = CCParticleBatchNode::batchNodeWithTexture(ignore->getTexture());

	for( unsigned int i=0; i<2;i++) {
		CCNode *parent = ( i==0 ? parent1 : parent2 );

		CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::particleWithFile("Images/SmallSun.plist");
		emitter1->setStartColor(ccc4f(1,0,0,1));
		emitter1->setIsBlendAdditive(false);
		CCParticleSystemQuad *emitter2 = CCParticleSystemQuad::particleWithFile("Images/SmallSun.plist");
		emitter2->setStartColor(ccc4f(0,1,0,1));
		emitter2->setIsBlendAdditive(false);
		CCParticleSystemQuad *emitter3 = CCParticleSystemQuad::particleWithFile("Images/SmallSun.plist");
		emitter3->setStartColor(ccc4f(0,0,1,1));
		emitter3->setIsBlendAdditive(false);

		CCSize s = CCDirector::sharedDirector()->getWinSize();

		int neg = (i==0 ? 1 : -1 );

		emitter1->setPosition(ccp( s.width/2-30,	s.height/2+60*neg));
		emitter2->setPosition(ccp( s.width/2,		s.height/2+60*neg));
		emitter3->setPosition(ccp( s.width/2+30,	s.height/2+60*neg));

		parent->addChild(emitter1, 0, 1);
		parent->addChild(emitter2, 0, 2);
		parent->addChild(emitter3, 0, 3);

		addChild(parent, 10, 1000+i);
	}

	schedule(schedule_selector(ParticleReorder::reorderParticles), 1.0f);
}

std::string ParticleReorder::title()
{
	return "Reordering particles";
}

std::string ParticleReorder::subtitle()
{
	return "Reordering particles with and without batches batches";
}

void ParticleReorder::reorderParticles(ccTime dt)
{
	for( int i=0; i<2;i++) {
		CCNode *parent = getChildByTag(1000+i);

		CCNode *child1 = parent->getChildByTag(1);
		CCNode *child2 = parent->getChildByTag(2);
		CCNode *child3 = parent->getChildByTag(3);

		if( m_nOrder % 3 == 0 ) {
			parent->reorderChild(child1, 1);
			parent->reorderChild(child2, 2);
			parent->reorderChild(child3, 3);

		} else if (m_nOrder % 3 == 1 ) {
			parent->reorderChild(child1, 3);
			parent->reorderChild(child2, 1);
			parent->reorderChild(child3, 2);

		} else if (m_nOrder % 3 == 2 ) {
			parent->reorderChild(child1, 2);
			parent->reorderChild(child2, 3);
			parent->reorderChild(child3, 1);
		}
	}

	m_nOrder++;
}

class RainbowEffect : public CCParticleSystemQuad
{
public:
	bool init();
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	virtual void update(ccTime dt);
};

bool RainbowEffect::init()
{
	return initWithTotalParticles(150);
}

bool RainbowEffect::initWithTotalParticles(unsigned int numberOfParticles)
{
	if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
	{
		// additive
		setIsBlendAdditive(false);

		// duration
		setDuration(kCCParticleDurationInfinity);

		// Gravity Mode
		setEmitterMode(kCCParticleModeGravity);

		// Gravity Mode: gravity
		setGravity(ccp(0,0));

		// Gravity mode: radial acceleration
		setRadialAccel(0);
		setRadialAccelVar(0);

		// Gravity mode: speed of particles
		setSpeed(120);
		setSpeedVar(0);


		// angle
		setAngle(180);
		setAngleVar(0);

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		setPosition(ccp(winSize.width/2, winSize.height/2));
		setPosVar(CCPointZero);

		// life of particles
		setLife(0.5f);
		setLifeVar(0);

		// size, in pixels
		setStartSize(25.0f);
		setStartSizeVar(0);
		setEndSize(kCCParticleStartSizeEqualToEndSize);

		// emits per seconds
		setEmissionRate(getTotalParticles()/getLife());

		// color of particles
		setStartColor(ccc4FFromccc4B(ccc4(50, 50, 50, 50)));
		setEndColor(ccc4FFromccc4B(ccc4(0, 0, 0, 0)));

		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/particles.png"));
		return true;
	}

	return false;
}

void RainbowEffect::update(ccTime dt)
{
	m_fEmitCounter = 0;
	CCParticleSystemQuad::update(dt);
}


void Issue1201::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	RainbowEffect *particle = new RainbowEffect();
	particle->initWithTotalParticles(50);

	addChild(particle);

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	particle->setPosition(ccp(s.width/2, s.height/2));

	m_emitter = particle;
}

std::string Issue1201::title()
{
	return "Issue 1201. Unfinished";
}

std::string Issue1201::subtitle()
{
	return "Unfinished test. Ignore it";
}

void MultipleParticleSystems::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	CCTextureCache::sharedTextureCache()->addImage("Images/particles.png"); 

	for (int i = 0; i<5; i++) {
		CCParticleSystemQuad *particleSystem = CCParticleSystemQuad::particleWithFile("Images/SpinningPeas.plist");

		particleSystem->setPosition(ccp(i*50 ,i*50));

		particleSystem->setPositionType(kCCPositionTypeGrouped);
		addChild(particleSystem);
	}

	m_emitter = NULL;

}

std::string MultipleParticleSystems::title()
{
	return "Multiple particle systems";
}

std::string MultipleParticleSystems::subtitle()
{
	return "v1.1 test: FPS should be lower than next test";
}

void MultipleParticleSystems::update(ccTime dt)
{
	CCLabelAtlas *atlas = (CCLabelAtlas*) getChildByTag(kTagParticleCount);

	unsigned int count = 0; 
	
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pChildren, pObj)
	{
		CCParticleSystem* item = dynamic_cast<CCParticleSystem*>(pObj);
		if (item != NULL)
		{
			count += item->getParticleCount();	
		}
	}
	char str[100] = {0};
	sprintf(str, "%4d", count);
	atlas->setString(str);
}

// MultipleParticleSystemsBatched

void MultipleParticleSystemsBatched::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	CCParticleBatchNode *batchNode = new CCParticleBatchNode();
	batchNode->initWithTexture(NULL, 3000);

	addChild(batchNode, 1, 2);

	for (int i = 0; i<5; i++) {

		CCParticleSystemQuad *particleSystem = CCParticleSystemQuad::particleWithFile("Images/SpinningPeas.plist");

		particleSystem->setPositionType(kCCPositionTypeGrouped);		 
		particleSystem->setPosition(ccp(i*50 ,i*50));

		batchNode->setTexture(particleSystem->getTexture());
		batchNode->addChild(particleSystem);
	}

	batchNode->release();

	m_emitter = NULL;
}

void MultipleParticleSystemsBatched::update(ccTime dt)
{
	CCLabelAtlas *atlas = (CCLabelAtlas*) getChildByTag(kTagParticleCount);

	unsigned count = 0; 
	
	CCNode* batchNode = getChildByTag(2);
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(batchNode->getChildren(), pObj)
	{
		CCParticleSystem* item = dynamic_cast<CCParticleSystem*>(pObj);
		if (item != NULL)
		{
			count += item->getParticleCount();	
		}
	}
	char str[50] = {0};
	sprintf(str, "%4d", count);
	atlas->setString(str);
}

std::string MultipleParticleSystemsBatched::title()
{
	return "Multiple particle systems batched";
}

std::string MultipleParticleSystemsBatched::subtitle()
{
	return "v1.1 test: should perform better than previous test";
}

// AddAndDeleteParticleSystems

void AddAndDeleteParticleSystems::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background, true);
	m_background = NULL;

	//adds the texture inside the plist to the texture cache
	m_pBatchNode = CCParticleBatchNode::batchNodeWithTexture(NULL, 16000);

	addChild(m_pBatchNode, 1, 2);

	for (int i = 0; i<6; i++) {

		CCParticleSystemQuad *particleSystem = CCParticleSystemQuad::particleWithFile("Images/Spiral.plist");
		m_pBatchNode->setTexture(particleSystem->getTexture());

		particleSystem->setPositionType(kCCPositionTypeGrouped);		 
		particleSystem->setTotalParticles(200);

		particleSystem->setPosition(ccp(i*15 +100,i*15+100));

		unsigned int randZ = rand() % 100; 
		m_pBatchNode->addChild(particleSystem, randZ, -1);

	}

	schedule(schedule_selector(AddAndDeleteParticleSystems::removeSystem), 0.5f);
	m_emitter = NULL;

}

void AddAndDeleteParticleSystems::removeSystem(ccTime dt)
{
	int nChildrenCount = m_pBatchNode->getChildren()->count();
	if (nChildrenCount > 0) 
	{
		CCLOG("remove random system");
		unsigned int uRand = rand() % (nChildrenCount - 1);
		m_pBatchNode->removeChild((CCNode*)m_pBatchNode->getChildren()->objectAtIndex(uRand), true);

		CCParticleSystemQuad *particleSystem = CCParticleSystemQuad::particleWithFile("Images/Spiral.plist");
		//add new

		particleSystem->setPositionType(kCCPositionTypeGrouped);		 
		particleSystem->setTotalParticles(200);

		particleSystem->setPosition(ccp(rand() % 300 ,rand() % 400));

		CCLOG("add a new system");
		unsigned int randZ = rand() % 100; 
		m_pBatchNode->addChild(particleSystem, randZ, -1);
	}
}

void AddAndDeleteParticleSystems::update(ccTime dt)
{
	CCLabelAtlas *atlas = (CCLabelAtlas*) getChildByTag(kTagParticleCount);

	unsigned int count = 0; 
	
	CCNode* batchNode = getChildByTag(2);
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(batchNode->getChildren(), pObj)
	{
		CCParticleSystem* item = dynamic_cast<CCParticleSystem*>(pObj);
		if (item != NULL)
		{
			count += item->getParticleCount();	
		}
	}
	char str[100] = {0};
	sprintf(str, "%4d", count);
	atlas->setString(str);
}

std::string AddAndDeleteParticleSystems::title()
{
	return "Add and remove Particle System";
}

std::string AddAndDeleteParticleSystems::subtitle()
{
	return "v1.1 test: every 2 sec 1 system disappear, 1 appears";
}

// ReorderParticleSystems

void ReorderParticleSystems::onEnter()
{
	ParticleDemo::onEnter();

	setColor(ccBLACK);
	removeChild(m_background ,true);
	m_background = NULL;

	m_pBatchNode = CCParticleBatchNode::batchNodeWithFile("Images/stars-grayscale.png" ,3000);

	addChild(m_pBatchNode, 1, 2);


	for (int i = 0; i<3; i++) {

		CCParticleSystemQuad* particleSystem = new CCParticleSystemQuad();
		particleSystem->initWithTotalParticles(200);
		particleSystem->setTexture(m_pBatchNode->getTexture());

		// duration
		particleSystem->setDuration(kCCParticleDurationInfinity);

		// radius mode
		particleSystem->setEmitterMode(kCCParticleModeRadius);

		// radius mode: 100 pixels from center
		particleSystem->setStartRadius(100);
		particleSystem->setStartRadiusVar(0);
		particleSystem->setEndRadius(kCCParticleStartRadiusEqualToEndRadius);
		particleSystem->setEndRadiusVar(0);	// not used when start == end

		// radius mode: degrees per second
		// 45 * 4 seconds of life = 180 degrees
		particleSystem->setRotatePerSecond(45);
		particleSystem->setRotatePerSecondVar(0);


		// angle
		particleSystem->setAngle(90);
		particleSystem->setAngleVar(0);

		// emitter position
		particleSystem->setPosVar(CCPointZero);

		// life of particles
		particleSystem->setLife(4);
		particleSystem->setLifeVar(0);

		// spin of particles
		particleSystem->setStartSpin(0);
		particleSystem->setStartSpinVar(0);
		particleSystem->setEndSpin(0);
		particleSystem->setEndSpinVar(0);

		// color of particles
		float color[3] = {0,0,0};
		color[i] = 1;
		ccColor4F startColor = {color[0], color[1], color[2], 1.0f};
		particleSystem->setStartColor(startColor);

		ccColor4F startColorVar = {0, 0, 0, 0};
		particleSystem->setStartColorVar(startColorVar);

		ccColor4F endColor = startColor;
		particleSystem->setEndColor(endColor);

		ccColor4F endColorVar = startColorVar;
		particleSystem->setEndColorVar(endColorVar);

		// size, in pixels
		particleSystem->setStartSize(32);
		particleSystem->setStartSizeVar(0);
		particleSystem->setEndSize(kCCParticleStartSizeEqualToEndSize);

		// emits per second
		particleSystem->setEmissionRate(particleSystem->getTotalParticles()/particleSystem->getLife());

		// additive

		particleSystem->setPosition(ccp(i*10+120 ,200));


		m_pBatchNode->addChild(particleSystem);
		particleSystem->setPositionType(kCCPositionTypeFree);

		particleSystem->release();

		//[pBNode addChild:particleSystem z:10 tag:0);

	}

	schedule(schedule_selector(ReorderParticleSystems::reorderSystem), 2.0f);
	m_emitter = NULL;

}

void ReorderParticleSystems::reorderSystem(ccTime time)
{
	CCParticleSystem* system = (CCParticleSystem*)m_pBatchNode->getChildren()->objectAtIndex(1);
	m_pBatchNode->reorderChild(system, system->getZOrder() - 1); 	
}


void ReorderParticleSystems::update(ccTime dt)
{
	CCLabelAtlas *atlas = (CCLabelAtlas*) getChildByTag(kTagParticleCount);

	unsigned int count = 0; 
	
	CCNode* batchNode = getChildByTag(2);
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(batchNode->getChildren(), pObj)
	{
		CCParticleSystem* item = dynamic_cast<CCParticleSystem*>(pObj);
		if (item != NULL)
		{
			count += item->getParticleCount();	
		}
	}
	char str[100] = {0};
	sprintf(str, "%4d", count);
	atlas->setString(str);
}

std::string ReorderParticleSystems::title()
{
	return "reorder systems";
}

std::string ReorderParticleSystems::subtitle()
{
	return "changes every 2 seconds";
}


void ParticleTestScene::runThisTest()
{
    addChild(nextParticleAction());

    CCDirector::sharedDirector()->replaceScene(this);
}
