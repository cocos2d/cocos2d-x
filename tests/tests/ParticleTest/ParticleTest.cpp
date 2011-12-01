#include "ParticleTest.h"
// #include "CCActionInterval.h"
// #include "CCMenu.h"
// #include "CCLabelTTF.h"
// #include "CCLabelAtlas.h"
// #include "touch_dispatcher/CCTouchDispatcher.h"
#include "../testResource.h"
/*#include "support/CCPointExtension.h"*/

enum 
{
	kTagLabelAtlas = 1,
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
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );//.pvr"];
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

#define MAX_LAYER	33

CCLayer* createParticleLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new DemoFlower();
		case 1: return new DemoGalaxy();
		case 2: return new DemoFirework();
		case 3: return new DemoSpiral();
		case 4: return new DemoSun();
		case 5: return new DemoMeteor();
		case 6: return new DemoFire();
		case 7: return new DemoSmoke();
		case 8: return new DemoExplosion();
		case 9: return new DemoSnow();
		case 10: return new DemoRain();
		case 11: return new DemoBigFlower();
		case 12: return new DemoRotFlower();
		case 13: return new DemoModernArt();
		case 14: return new DemoRing();
		case 15: return new ParallaxParticle();
        case 16: return new DemoParticleFromFile("BoilingFoam");
        case 17: return new DemoParticleFromFile("BurstPipe");
        case 18: return new DemoParticleFromFile("Comet");
        case 19: return new DemoParticleFromFile("debian");
        case 20: return new DemoParticleFromFile("ExplodingRing");
        case 21: return new DemoParticleFromFile("LavaFlow");
        case 22: return new DemoParticleFromFile("SpinningPeas");
        case 23: return new DemoParticleFromFile("SpookyPeas");
        case 24: return new DemoParticleFromFile("Upsidedown");
        case 25: return new DemoParticleFromFile("Flower");
        case 26: return new DemoParticleFromFile("Spiral");
        case 27: return new DemoParticleFromFile("Galaxy");
        case 28: return new RadiusMode1();
        case 29: return new RadiusMode2();
        case 30: return new Issue704();
        case 31: return new Issue870();
		case 32: return new DemoParticleFromFile("Phoenix");
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
	
	CCMenuItemImage* item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ParticleDemo::backCallback) );
	CCMenuItemImage* item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ParticleDemo::restartCallback) );
	CCMenuItemImage* item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2,  this, menu_selector(ParticleDemo::nextCallback) );
	
	CCMenuItemToggle* item4 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(ParticleDemo::toggleCallback), 
																CCMenuItemFont::itemFromString( "Free Movement" ),
                                                                CCMenuItemFont::itemFromString( "Relative Movement" ),
																CCMenuItemFont::itemFromString( "Grouped Movement" ),
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
    addChild(labelAtlas, 100, kTagLabelAtlas);
	labelAtlas->setPosition( CCPointMake(s.width-66,50) );
	
	// moving background
	m_background = CCSprite::spriteWithFile(s_back3);
	addChild(m_background, 5);
	m_background->setPosition( CCPointMake(s.width/2, s.height-180) );

	CCActionInterval* move = CCMoveBy::actionWithDuration(4, CCPointMake(300,0) );
	CCActionInterval* move_back = move->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions( move, move_back, NULL);
	m_background->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)seq) );
	
	
	schedule( schedule_selector(ParticleDemo::step) );
}

ParticleDemo::~ParticleDemo(void)
{
	m_emitter->release(); 
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
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
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
	CCPoint location = touch->locationInView( touch->view() );
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

    CCPoint pos = CCPointZero;
    if (m_background)
    {
	    pos = m_background->convertToWorldSpace(CCPointZero);
    }
	m_emitter->setPosition( ccpSub(convertedLocation, pos) );	
}

void ParticleDemo::step(ccTime dt)
{
    if (m_emitter)
    {
	    CCLabelAtlas* atlas = (CCLabelAtlas*)getChildByTag(kTagLabelAtlas);
        char str[5] = {0};
        sprintf(str, "%04d", m_emitter->getParticleCount());
	    atlas->setString(str);
    }
}

void ParticleDemo::toggleCallback(CCObject* pSender)
{
	if( m_emitter->getPositionType() == kCCPositionTypeGrouped )
		m_emitter->setPositionType( kCCPositionTypeFree );
    else if (m_emitter->getPositionType() == kCCPositionTypeFree)
        m_emitter->setPositionType(kCCPositionTypeRelative);
	else if (m_emitter->getPositionType() == kCCPositionTypeRelative)
		m_emitter->setPositionType( kCCPositionTypeGrouped );
}

void ParticleDemo::restartCallback(CCObject* pSender)
{
	m_emitter->resetSystem(); 
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

	m_emitter->setPosition( CCPointMake(s.width / 2, s.height / 2) );
}

void ParticleTestScene::runThisTest()
{
    addChild(nextParticleAction());

    CCDirector::sharedDirector()->replaceScene(this);
}
