#include "ParticleTest.h"
#include "../testResource.h"

enum {
    kTagParticleCount = 1,
};

Layer* nextParticleAction();
Layer* backParticleAction();
Layer* restartParticleAction();

//------------------------------------------------------------------
//
// DemoFirework
//
//------------------------------------------------------------------
void DemoFirework::onEnter()
{
    ParticleDemo::onEnter();

    _emitter = ParticleFireworks::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars1) );
    
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

    _emitter = ParticleFire::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );//.pvr");
    Point p = _emitter->getPosition();
    _emitter->setPosition( Point(p.x, 100) );
    
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

    _emitter = ParticleSun::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);

    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
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

    _emitter = ParticleGalaxy::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
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

    _emitter = ParticleFlower::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars1) );
    
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

    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(50);
    //_emitter->autorelease();

    _background->addChild(_emitter, 10);
    ////_emitter->release();    // win32 :  use this line or remove this line and use autorelease()
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars1) );

    _emitter->setDuration(-1);
    
    // gravity
    _emitter->setGravity(Point::ZERO);
    
    // angle
    _emitter->setAngle(90);
    _emitter->setAngleVar(360);
    
    // speed of particles
    _emitter->setSpeed(160);
    _emitter->setSpeedVar(20);
    
    // radial
    _emitter->setRadialAccel(-120);
    _emitter->setRadialAccelVar(0);
    
    // tagential
    _emitter->setTangentialAccel(30);
    _emitter->setTangentialAccelVar(0);
    
    // emitter position
    _emitter->setPosition( Point(160,240) );
    _emitter->setPosVar(Point::ZERO);
    
    // life of particles
    _emitter->setLife(4);
    _emitter->setLifeVar(1);
    
    // spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSizeVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(0);
    
    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);
    
    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);
    
    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);
    
    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);
    
    // size, in pixels
    _emitter->setStartSize(80.0f);
    _emitter->setStartSizeVar(40.0f);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
    
    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());
    
    // additive
    _emitter->setBlendAdditive(true);

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

    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(300);
    //_emitter->autorelease();

    _background->addChild(_emitter, 10);
    ////_emitter->release();    // win32 : Remove this line
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars2) );
    
    // duration
    _emitter->setDuration(-1);
    
    // gravity
    _emitter->setGravity(Point::ZERO);
    
    // angle
    _emitter->setAngle(90);
    _emitter->setAngleVar(360);
    
    // speed of particles
    _emitter->setSpeed(160);
    _emitter->setSpeedVar(20);
    
    // radial
    _emitter->setRadialAccel(-120);
    _emitter->setRadialAccelVar(0);
    
    // tagential
    _emitter->setTangentialAccel(30);
    _emitter->setTangentialAccelVar(0);
    
    // emitter position
    _emitter->setPosition( Point(160,240) );
    _emitter->setPosVar(Point::ZERO);
    
    // life of particles
    _emitter->setLife(3);
    _emitter->setLifeVar(1);

    // spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(2000);
    
    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);
    
    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);
    
    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);
    
    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);

    // size, in pixels
    _emitter->setStartSize(30.0f);
    _emitter->setStartSizeVar(00.0f);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
    
    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());

    // additive
    _emitter->setBlendAdditive(false);
    
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

    _emitter = ParticleMeteor::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
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

    _emitter = ParticleSpiral::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
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

    _emitter = ParticleExplosion::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars1) );
    
    _emitter->setAutoRemoveOnFinish(true);
    
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

    _emitter = ParticleSmoke::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
    Point p = _emitter->getPosition();
    _emitter->setPosition( Point( p.x, 100) );
    
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

    _emitter = ParticleSnow::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    Point p = _emitter->getPosition();
    _emitter->setPosition( Point( p.x, p.y-110) );
    _emitter->setLife(3);
    _emitter->setLifeVar(1);
    
    // gravity
    _emitter->setGravity(Point(0,-10));
        
    // speed of particles
    _emitter->setSpeed(130);
    _emitter->setSpeedVar(30);
    
    
    Color4F startColor = _emitter->getStartColor();
    startColor.r = 0.9f;
    startColor.g = 0.9f;
    startColor.b = 0.9f;
    _emitter->setStartColor(startColor);
    
    Color4F startColorVar = _emitter->getStartColorVar();
    startColorVar.b = 0.1f;
    _emitter->setStartColorVar(startColorVar);
    
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_snow) );
    
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

    _emitter = ParticleRain::create();
    _emitter->retain();
    _background->addChild(_emitter, 10);
    
    Point p = _emitter->getPosition();
    _emitter->setPosition( Point( p.x, p.y-100) );
    _emitter->setLife(4);
    
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
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

//FIXME: If use ParticleSystemPoint, bada 1.0 device will crash. 
//  Crash place: ParticleSystemPoint.cpp Line 149, function: glDrawArrays(GL_POINTS, 0, _particleIdx);
//  _emitter = new ParticleSystemPoint();
    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(1000);
    //_emitter->autorelease();

    _background->addChild(_emitter, 10);
    ////_emitter->release();
    
    Size s = Director::getInstance()->getWinSize();
    
    // duration
    _emitter->setDuration(-1);
    
    // gravity
    _emitter->setGravity(Point(0,0));
    
    // angle
    _emitter->setAngle(0);
    _emitter->setAngleVar(360);
    
    // radial
    _emitter->setRadialAccel(70);
    _emitter->setRadialAccelVar(10);
    
    // tagential
    _emitter->setTangentialAccel(80);
    _emitter->setTangentialAccelVar(0);
    
    // speed of particles
    _emitter->setSpeed(50);
    _emitter->setSpeedVar(10);
    
    // emitter position
    _emitter->setPosition( Point( s.width/2, s.height/2) );
    _emitter->setPosVar(Point::ZERO);
    
    // life of particles
    _emitter->setLife(2.0f);
    _emitter->setLifeVar(0.3f);
    
    // emits per frame
    _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());
    
    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);
    
    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);
    
    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);
    
    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);
    
    // size, in pixels
    _emitter->setStartSize(1.0f);
    _emitter->setStartSizeVar(1.0f);
    _emitter->setEndSize(32.0f);
    _emitter->setEndSizeVar(8.0f);
    
    // texture
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
    // additive
    _emitter->setBlendAdditive(false);
    
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

    _emitter = ParticleFlower::create();
    _emitter->retain();

    _background->addChild(_emitter, 10);

    _emitter->setTexture( TextureCache::getInstance()->addImage(s_stars1) );
    _emitter->setLifeVar(0);
    _emitter->setLife(10);
    _emitter->setSpeed(100);
    _emitter->setSpeedVar(0);
    _emitter->setEmissionRate(10000);
    
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
    
    _background->getParent()->removeChild(_background, true);
    _background = NULL;

    ParallaxNode* p = ParallaxNode::create(); 
    addChild(p, 5);

    Sprite *p1 = Sprite::create(s_back3);
    Sprite *p2 = Sprite::create(s_back3);
    
    p->addChild( p1, 1, Point(0.5f,1), Point(0,250) );
    p->addChild(p2, 2, Point(1.5f,1), Point(0,50) );

    _emitter = ParticleFlower::create();
    _emitter->retain();
    _emitter->setTexture( TextureCache::getInstance()->addImage(s_fire) );

    p1->addChild(_emitter, 10);
    _emitter->setPosition( Point(250,200) );
    
    ParticleSun* par = ParticleSun::create();
    p2->addChild(par, 10);
    par->setTexture( TextureCache::getInstance()->addImage(s_fire) );
    
    ActionInterval* move = MoveBy::create(4, Point(300,0));
    ActionInterval* move_back = move->reverse();
    Sequence* seq = Sequence::create( move, move_back, NULL);
    p->runAction(RepeatForever::create(seq));    
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

	_color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(200);
    addChild(_emitter, 10);
    _emitter->setTexture(TextureCache::getInstance()->addImage("Images/stars-grayscale.png"));

    // duration
    _emitter->setDuration(ParticleSystem::DURATION_INFINITY);

    // radius mode
    _emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

    // radius mode: start and end radius in pixels
    _emitter->setStartRadius(0);
    _emitter->setStartRadiusVar(0);
    _emitter->setEndRadius(160);
    _emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    _emitter->setRotatePerSecond(180);
    _emitter->setRotatePerSecondVar(0);


    // angle
    _emitter->setAngle(90);
    _emitter->setAngleVar(0);

    // emitter position
    Size size = Director::getInstance()->getWinSize();
    _emitter->setPosition(Point(size.width/2, size.height/2));
    _emitter->setPosVar(Point::ZERO);

    // life of particles
    _emitter->setLife(5);
    _emitter->setLifeVar(0);

    // spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(0);

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);

    // size, in pixels
    _emitter->setStartSize(32);
    _emitter->setStartSizeVar(0);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

    // additive
    _emitter->setBlendAdditive(false);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(200);
    addChild(_emitter, 10);
    _emitter->setTexture(TextureCache::getInstance()->addImage("Images/stars-grayscale.png"));

    // duration
    _emitter->setDuration(ParticleSystem::DURATION_INFINITY);

    // radius mode
    _emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

    // radius mode: start and end radius in pixels
    _emitter->setStartRadius(100);
    _emitter->setStartRadiusVar(0);
    _emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
    _emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    _emitter->setRotatePerSecond(45);
    _emitter->setRotatePerSecondVar(0);


    // angle
    _emitter->setAngle(90);
    _emitter->setAngleVar(0);

    // emitter position
    Size size = Director::getInstance()->getWinSize();
    _emitter->setPosition(Point(size.width/2, size.height/2));
    _emitter->setPosVar(Point::ZERO);

    // life of particles
    _emitter->setLife(4);
    _emitter->setLifeVar(0);

    // spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(0);

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);

    // size, in pixels
    _emitter->setStartSize(32);
    _emitter->setStartSizeVar(0);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

    // additive
    _emitter->setBlendAdditive(false);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    _emitter = new ParticleSystemQuad();
    _emitter->initWithTotalParticles(100);
    addChild(_emitter, 10);
    _emitter->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));

    // duration
    _emitter->setDuration(ParticleSystem::DURATION_INFINITY);

    // radius mode
    _emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

    // radius mode: start and end radius in pixels
    _emitter->setStartRadius(50);
    _emitter->setStartRadiusVar(0);
    _emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
    _emitter->setEndRadiusVar(0);

    // radius mode: degrees per second
    _emitter->setRotatePerSecond(0);
    _emitter->setRotatePerSecondVar(0);


    // angle
    _emitter->setAngle(90);
    _emitter->setAngleVar(0);

    // emitter position
    Size size = Director::getInstance()->getWinSize();
    _emitter->setPosition(Point(size.width/2, size.height/2));
    _emitter->setPosVar(Point::ZERO);

    // life of particles
    _emitter->setLife(5);
    _emitter->setLifeVar(0);

    // spin of particles
    _emitter->setStartSpin(0);
    _emitter->setStartSpinVar(0);
    _emitter->setEndSpin(0);
    _emitter->setEndSpinVar(0);

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _emitter->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _emitter->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
    _emitter->setEndColorVar(endColorVar);

    // size, in pixels
    _emitter->setStartSize(16);
    _emitter->setStartSizeVar(0);
    _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

    // emits per second
    _emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

    // additive
    _emitter->setBlendAdditive(false);

    RotateBy* rot = RotateBy::create(16, 360);
    _emitter->runAction(RepeatForever::create(rot));
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    ParticleSystemQuad *system = new ParticleSystemQuad();
    system->initWithFile("Particles/SpinningPeas.plist");
    system->setTextureWithRect(TextureCache::getInstance()->addImage("Images/particles.png"), Rect(0,0,32,32));
    addChild(system, 10);
    _emitter = system;

    _index = 0;
    schedule(schedule_selector(Issue870::updateQuads), 2.0f);
}

void Issue870::updateQuads(float dt)
{
    _index = (_index + 1) % 4;
    Rect rect = Rect(_index * 32, 0, 32, 32);
    ParticleSystemQuad* system = (ParticleSystemQuad*)_emitter;
    system->setTextureWithRect(_emitter->getTexture(), rect);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    _emitter = new ParticleSystemQuad();
    std::string filename = "Particles/" + _title + ".plist";
    _emitter->initWithFile(filename.c_str());
    addChild(_emitter, 10);

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

#define MAX_LAYER    44

Layer* createParticleLayer(int nIndex)
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
        case 32: return new DemoParticleFromFile("lines");
        case 33: return new RadiusMode1();
        case 34: return new RadiusMode2();
        case 35: return new Issue704();
        case 36: return new Issue870();
        case 37: return new Issue1201();
        // v1.1 tests
        case 38: return new MultipleParticleSystems();
        case 39: return new MultipleParticleSystemsBatched();
        case 40: return new AddAndDeleteParticleSystems();
        case 41: return new ReorderParticleSystems();
        case 42: return new PremultipliedAlphaTest();
        case 43: return new PremultipliedAlphaTest2();
        default:
            break;
    }

    return NULL;
}


Layer* nextParticleAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* layer = createParticleLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backParticleAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* layer = createParticleLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartParticleAction()
{
    Layer* layer = createParticleLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 

ParticleDemo::~ParticleDemo(void)
{
    CC_SAFE_RELEASE(_emitter);
}

void ParticleDemo::onEnter(void)
{
    BaseTest::onEnter();

	_color = LayerColor::create( Color4B(127,127,127,255) );
	this->addChild(_color);
    
    _emitter = NULL;
    
    setTouchEnabled( true );
    
    Size s = Director::getInstance()->getWinSize();
    
    MenuItemToggle* item4 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(ParticleDemo::toggleCallback, this),
                                                               MenuItemFont::create( "Free Movement" ),
                                                               MenuItemFont::create( "Relative Movement" ),
                                                               MenuItemFont::create( "Grouped Movement" ),
                                                               NULL );
    
    Menu *menu = Menu::create(item4, NULL);
    
    menu->setPosition( Point::ZERO );
    item4->setPosition( Point( VisibleRect::left().x, VisibleRect::bottom().y+ 100) );
    item4->setAnchorPoint( Point(0,0) );
    
    addChild( menu, 100 );
    
    LabelAtlas* labelAtlas = LabelAtlas::create("0000", "fps_images.png", 12, 32, '.');
    addChild(labelAtlas, 100, kTagParticleCount);
    labelAtlas->setPosition(Point(s.width-66,50));
    
    // moving background
    _background = Sprite::create(s_back3);
    addChild(_background, 5);
    _background->setPosition( Point(s.width/2, s.height-180) );
    
    ActionInterval* move = MoveBy::create(4, Point(300,0) );
    ActionInterval* move_back = move->reverse();
    Sequence* seq = Sequence::create( move, move_back, NULL);
    _background->runAction( RepeatForever::create(seq) );
    
    
    scheduleUpdate();
}

std::string ParticleDemo::title()
{
    return "No title";
}

std::string ParticleDemo::subtitle()
{
    return "No titile";
}

void ParticleDemo::ccTouchesBegan(Set  *touches, Event  *event)
{
    ccTouchesEnded(touches, event);
}

void ParticleDemo::ccTouchesMoved(Set  *touches, Event  *event)
{
    return ccTouchesEnded(touches, event);
}

void ParticleDemo::ccTouchesEnded(Set  *touches, Event  *event)
{
    Touch *touch = static_cast<Touch*>(touches->anyObject());
    
    Point location = touch->getLocation();

    Point pos = Point::ZERO;
    if (_background)
    {
        pos = _background->convertToWorldSpace(Point::ZERO);
    }

    if (_emitter != NULL)
    {
        _emitter->setPosition(location -pos);
    }
}

void ParticleDemo::update(float dt)
{
    if (_emitter)
    {
        LabelAtlas* atlas = (LabelAtlas*)getChildByTag(kTagParticleCount);
        char str[5] = {0};
        sprintf(str, "%04d", _emitter->getParticleCount());
        atlas->setString(str);
    }
}

void ParticleDemo::toggleCallback(Object* sender)
{
    if (_emitter != NULL)
    {
        if (_emitter->getPositionType() == ParticleSystem::PositionType::GROUPED)
            _emitter->setPositionType(ParticleSystem::PositionType::FREE);
        else if (_emitter->getPositionType() == ParticleSystem::PositionType::FREE)
            _emitter->setPositionType(ParticleSystem::PositionType::RELATIVE);
        else if (_emitter->getPositionType() == ParticleSystem::PositionType::RELATIVE)
            _emitter->setPositionType(ParticleSystem::PositionType::GROUPED );
    }
}

void ParticleDemo::restartCallback(Object* sender)
{
    if (_emitter != NULL)
    {
        _emitter->resetSystem(); 
    }
}

void ParticleDemo::nextCallback(Object* sender)
{
    Scene* s = new ParticleTestScene();
    s->addChild( nextParticleAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ParticleDemo::backCallback(Object* sender)
{
    Scene* s = new ParticleTestScene();
    s->addChild( backParticleAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void ParticleDemo::setEmitterPosition()
{
    Size s = Director::getInstance()->getWinSize();
    if (_emitter != NULL)
    {
        _emitter->setPosition( Point(s.width / 2, s.height / 2) );
    }
}

// ParticleBatchHybrid

void ParticleBatchHybrid::onEnter()
{
    ParticleDemo::onEnter();

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    _emitter = ParticleSystemQuad::create("Particles/LavaFlow.plist");
    _emitter->retain();
    ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(_emitter->getTexture());

    batch->addChild(_emitter);

    addChild(batch, 10);

     schedule(schedule_selector(ParticleBatchHybrid::switchRender), 2.0f);
 
     Node *node = Node::create();
     addChild(node);
 
     _parent1 = batch;
     _parent2 = node;
}

void ParticleBatchHybrid::switchRender(float dt)
{
     bool usingBatch = ( _emitter->getBatchNode() != NULL );
     _emitter->removeFromParentAndCleanup(false);
 
     Node *newParent = (usingBatch ? _parent2  : _parent1 );
     newParent->addChild(_emitter);
 
     log("Particle: Using new parent: %s", usingBatch ? "CCNode" : "CCParticleBatchNode");
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    ParticleSystemQuad *emitter1 = ParticleSystemQuad::create("Particles/LavaFlow.plist");
    emitter1->setStartColor(Color4F(1,0,0,1));
    ParticleSystemQuad *emitter2 = ParticleSystemQuad::create("Particles/LavaFlow.plist");
    emitter2->setStartColor(Color4F(0,1,0,1));
    ParticleSystemQuad *emitter3 = ParticleSystemQuad::create("Particles/LavaFlow.plist");
    emitter3->setStartColor(Color4F(0,0,1,1));

    Size s = Director::getInstance()->getWinSize();

    emitter1->setPosition(Point( s.width/1.25f, s.height/1.25f));
    emitter2->setPosition(Point( s.width/2, s.height/2));
    emitter3->setPosition(Point( s.width/4, s.height/4));

    ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(emitter1->getTexture());

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

    _order = 0;
    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    ParticleSystem* ignore = ParticleSystemQuad::create("Particles/SmallSun.plist");
    Node *parent1 = Node::create();
    Node *parent2 = ParticleBatchNode::createWithTexture(ignore->getTexture());
    ignore->unscheduleUpdate();

    for( unsigned int i=0; i<2;i++) 
    {
        Node *parent = ( i==0 ? parent1 : parent2 );

        ParticleSystemQuad *emitter1 = ParticleSystemQuad::create("Particles/SmallSun.plist");
        emitter1->setStartColor(Color4F(1,0,0,1));
        emitter1->setBlendAdditive(false);
        ParticleSystemQuad *emitter2 = ParticleSystemQuad::create("Particles/SmallSun.plist");
        emitter2->setStartColor(Color4F(0,1,0,1));
        emitter2->setBlendAdditive(false);
        ParticleSystemQuad *emitter3 = ParticleSystemQuad::create("Particles/SmallSun.plist");
        emitter3->setStartColor(Color4F(0,0,1,1));
        emitter3->setBlendAdditive(false);

        Size s = Director::getInstance()->getWinSize();

        int neg = (i==0 ? 1 : -1 );

        emitter1->setPosition(Point( s.width/2-30,    s.height/2+60*neg));
        emitter2->setPosition(Point( s.width/2,        s.height/2+60*neg));
        emitter3->setPosition(Point( s.width/2+30,    s.height/2+60*neg));

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

void ParticleReorder::reorderParticles(float dt)
{
    for( int i=0; i<2;i++) {
        Node *parent = getChildByTag(1000+i);

        Node *child1 = parent->getChildByTag(1);
        Node *child2 = parent->getChildByTag(2);
        Node *child3 = parent->getChildByTag(3);

        if( _order % 3 == 0 ) {
            parent->reorderChild(child1, 1);
            parent->reorderChild(child2, 2);
            parent->reorderChild(child3, 3);

        } else if (_order % 3 == 1 ) {
            parent->reorderChild(child1, 3);
            parent->reorderChild(child2, 1);
            parent->reorderChild(child3, 2);

        } else if (_order % 3 == 2 ) {
            parent->reorderChild(child1, 2);
            parent->reorderChild(child2, 3);
            parent->reorderChild(child3, 1);
        }
    }

    _order++;
}

class RainbowEffect : public ParticleSystemQuad
{
public:
    bool init();
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    virtual void update(float dt);
};

bool RainbowEffect::init()
{
    return initWithTotalParticles(150);
}

bool RainbowEffect::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // additive
        setBlendAdditive(false);

        // duration
        setDuration(ParticleSystem::DURATION_INFINITY);

        // Gravity Mode
        setEmitterMode(ParticleSystem::Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

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
        Size winSize = Director::getInstance()->getWinSize();
        setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        setLife(0.5f);
        setLifeVar(0);

        // size, in pixels
        setStartSize(25.0f);
        setStartSizeVar(0);
        setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

        // emits per seconds
        setEmissionRate(getTotalParticles()/getLife());

        // color of particles
        setStartColor(Color4F(Color4B(50, 50, 50, 50)));
        setEndColor(Color4F(Color4B(0, 0, 0, 0)));

        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        setTexture(TextureCache::getInstance()->addImage("Images/particles.png"));
        return true;
    }

    return false;
}

void RainbowEffect::update(float dt)
{
    _emitCounter = 0;
    ParticleSystemQuad::update(dt);
}


void Issue1201::onEnter()
{
    ParticleDemo::onEnter();

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    RainbowEffect *particle = new RainbowEffect();
    particle->initWithTotalParticles(50);

    addChild(particle);

    Size s = Director::getInstance()->getWinSize();

    particle->setPosition(Point(s.width/2, s.height/2));

    _emitter = particle;
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    TextureCache::getInstance()->addImage("Images/particles.png"); 

    for (int i = 0; i<5; i++) {
        ParticleSystemQuad *particleSystem = ParticleSystemQuad::create("Particles/SpinningPeas.plist");

        particleSystem->setPosition(Point(i*50 ,i*50));

        particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
        addChild(particleSystem);
    }

    _emitter = NULL;

}

std::string MultipleParticleSystems::title()
{
    return "Multiple particle systems";
}

std::string MultipleParticleSystems::subtitle()
{
    return "v1.1 test: FPS should be lower than next test";
}

void MultipleParticleSystems::update(float dt)
{
    LabelAtlas *atlas = (LabelAtlas*) getChildByTag(kTagParticleCount);

    unsigned int count = 0; 
    
    Object* pObj = NULL;
    CCARRAY_FOREACH(getChildren(), pObj)
    {
        ParticleSystem* item = dynamic_cast<ParticleSystem*>(pObj);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    ParticleBatchNode *batchNode = new ParticleBatchNode();
    batchNode->initWithTexture(NULL, 3000);

    addChild(batchNode, 1, 2);

    for (int i = 0; i<5; i++) {

        ParticleSystemQuad *particleSystem = ParticleSystemQuad::create("Particles/SpinningPeas.plist");

        particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
        particleSystem->setPosition(Point(i*50 ,i*50));

        batchNode->setTexture(particleSystem->getTexture());
        batchNode->addChild(particleSystem);
    }

    batchNode->release();

    _emitter = NULL;
}

void MultipleParticleSystemsBatched::update(float dt)
{
    LabelAtlas *atlas = (LabelAtlas*) getChildByTag(kTagParticleCount);

    unsigned count = 0; 
    
    Node* batchNode = getChildByTag(2);
    Object* pObj = NULL;
    CCARRAY_FOREACH(batchNode->getChildren(), pObj)
    {
        ParticleSystem* item = dynamic_cast<ParticleSystem*>(pObj);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background, true);
    _background = NULL;

    //adds the texture inside the plist to the texture cache
    _batchNode = ParticleBatchNode::createWithTexture((Texture2D*)NULL, 16000);

    addChild(_batchNode, 1, 2);

    for (int i = 0; i<6; i++) {

        ParticleSystemQuad *particleSystem = ParticleSystemQuad::create("Particles/Spiral.plist");
        _batchNode->setTexture(particleSystem->getTexture());

        particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
        particleSystem->setTotalParticles(200);

        particleSystem->setPosition(Point(i*15 +100,i*15+100));

        unsigned int randZ = rand() % 100; 
        _batchNode->addChild(particleSystem, randZ, -1);

    }

    schedule(schedule_selector(AddAndDeleteParticleSystems::removeSystem), 0.5f);
    _emitter = NULL;

}

void AddAndDeleteParticleSystems::removeSystem(float dt)
{
    int nChildrenCount = _batchNode->getChildren()->count();
    if (nChildrenCount > 0) 
    {
        CCLOG("remove random system");
        unsigned int uRand = rand() % (nChildrenCount - 1);
        _batchNode->removeChild((Node*)_batchNode->getChildren()->objectAtIndex(uRand), true);

        ParticleSystemQuad *particleSystem = ParticleSystemQuad::create("Particles/Spiral.plist");
        //add new

        particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
        particleSystem->setTotalParticles(200);

        particleSystem->setPosition(Point(rand() % 300 ,rand() % 400));

        CCLOG("add a new system");
        unsigned int randZ = rand() % 100; 
        _batchNode->addChild(particleSystem, randZ, -1);
    }
}

void AddAndDeleteParticleSystems::update(float dt)
{
    LabelAtlas *atlas = (LabelAtlas*) getChildByTag(kTagParticleCount);

    unsigned int count = 0; 
    
    Node* batchNode = getChildByTag(2);
    Object* pObj = NULL;
    CCARRAY_FOREACH(batchNode->getChildren(), pObj)
    {
        ParticleSystem* item = dynamic_cast<ParticleSystem*>(pObj);
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

    _color->setColor(Color3B::BLACK);
    removeChild(_background ,true);
    _background = NULL;

    _batchNode = ParticleBatchNode::create("Images/stars-grayscale.png" ,3000);

    addChild(_batchNode, 1, 2);


    for (int i = 0; i<3; i++) {

        ParticleSystemQuad* particleSystem = new ParticleSystemQuad();
        particleSystem->initWithTotalParticles(200);
        particleSystem->setTexture(_batchNode->getTexture());

        // duration
        particleSystem->setDuration(ParticleSystem::DURATION_INFINITY);

        // radius mode
        particleSystem->setEmitterMode(ParticleSystem::Mode::RADIUS);

        // radius mode: 100 pixels from center
        particleSystem->setStartRadius(100);
        particleSystem->setStartRadiusVar(0);
        particleSystem->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
        particleSystem->setEndRadiusVar(0);    // not used when start == end

        // radius mode: degrees per second
        // 45 * 4 seconds of life = 180 degrees
        particleSystem->setRotatePerSecond(45);
        particleSystem->setRotatePerSecondVar(0);


        // angle
        particleSystem->setAngle(90);
        particleSystem->setAngleVar(0);

        // emitter position
        particleSystem->setPosVar(Point::ZERO);

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
        Color4F startColor(color[0], color[1], color[2], 1.0f);
        particleSystem->setStartColor(startColor);

        Color4F startColorVar(0, 0, 0, 0);
        particleSystem->setStartColorVar(startColorVar);

        Color4F endColor = startColor;
        particleSystem->setEndColor(endColor);

        Color4F endColorVar = startColorVar;
        particleSystem->setEndColorVar(endColorVar);

        // size, in pixels
        particleSystem->setStartSize(32);
        particleSystem->setStartSizeVar(0);
        particleSystem->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

        // emits per second
        particleSystem->setEmissionRate(particleSystem->getTotalParticles()/particleSystem->getLife());

        // additive

        particleSystem->setPosition(Point(i*10+120 ,200));


        _batchNode->addChild(particleSystem);
        particleSystem->setPositionType(ParticleSystem::PositionType::FREE);

        particleSystem->release();

        //[pBNode addChild:particleSystem z:10 tag:0);

    }

    schedule(schedule_selector(ReorderParticleSystems::reorderSystem), 2.0f);
    _emitter = NULL;

}

void ReorderParticleSystems::reorderSystem(float time)
{
    ParticleSystem* system = (ParticleSystem*)_batchNode->getChildren()->objectAtIndex(1);
    _batchNode->reorderChild(system, system->getZOrder() - 1);     
}


void ReorderParticleSystems::update(float dt)
{
    LabelAtlas *atlas = (LabelAtlas*) getChildByTag(kTagParticleCount);

    unsigned int count = 0; 
    
    Node* batchNode = getChildByTag(2);
    Object* pObj = NULL;
    CCARRAY_FOREACH(batchNode->getChildren(), pObj)
    {
        ParticleSystem* item = dynamic_cast<ParticleSystem*>(pObj);
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

// PremultipliedAlphaTest

std::string PremultipliedAlphaTest::title()
{
    return "premultiplied alpha";
}

std::string PremultipliedAlphaTest::subtitle()
{
    return "no black halo, particles should fade out";
}

void PremultipliedAlphaTest::onEnter()
{
    ParticleDemo::onEnter();

	_color->setColor(Color3B::BLUE);
    this->removeChild(_background, true);
    _background = NULL;

    _emitter = ParticleSystemQuad::create("Particles/BoilingFoam.plist");
    _emitter->retain();
    // Particle Designer "normal" blend func causes black halo on premul textures (ignores multiplication)
    //this->emitter.blendFunc = (BlendFunc){ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

    // Cocos2d "normal" blend func for premul causes alpha to be ignored (oversaturates colors)
    _emitter->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );

    CCASSERT(_emitter->isOpacityModifyRGB(), "Particle texture does not have premultiplied alpha, test is useless");

    // Toggle next line to see old behavior
    //	this->emitter.opacityModifyRGB = NO;

    _emitter->setStartColor(Color4F(1, 1, 1, 1));
    _emitter->setEndColor(Color4F(1, 1, 1, 0));
    _emitter->setStartColorVar(Color4F(0, 0, 0, 0));
    _emitter->setEndColorVar(Color4F(0, 0, 0, 0));

    this->addChild(_emitter, 10);
}

// PremultipliedAlphaTest2

void PremultipliedAlphaTest2::onEnter()
{
    ParticleDemo::onEnter();

	_color->setColor(Color3B::BLACK);
    this->removeChild(_background, true);
    _background = NULL;

    _emitter = ParticleSystemQuad::create("Particles/TestPremultipliedAlpha.plist");
    _emitter->retain();
    this->addChild(_emitter ,10);
}

std::string PremultipliedAlphaTest2::title()
{
    return "premultiplied alpha 2";
}

std::string PremultipliedAlphaTest2::subtitle()
{
    return "Arrows should be faded";
}

void ParticleTestScene::runThisTest()
{
    addChild(nextParticleAction());

    Director::getInstance()->replaceScene(this);
}
