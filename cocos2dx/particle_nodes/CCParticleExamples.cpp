/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCParticleExamples.h"
#include "CCDirector.h"
#include "textures/CCTextureCache.h"
#include "firePngData.h"
#include "platform/CCImage.h"

NS_CC_BEGIN
//
// ParticleFire
//

static Texture2D* getDefaultTexture()
{
    Texture2D* texture = NULL;
    Image* pImage = NULL;
    do 
    {
        bool bRet = false;
        const char* key = "__firePngData";
        texture = TextureCache::getInstance()->textureForKey(key);
        CC_BREAK_IF(texture != NULL);

        pImage = new Image();
        CC_BREAK_IF(NULL == pImage);
        bRet = pImage->initWithImageData((void*)__firePngData, sizeof(__firePngData), Image::Format::PNG);
        CC_BREAK_IF(!bRet);

        texture = TextureCache::getInstance()->addUIImage(pImage, key);
    } while (0);

    CC_SAFE_RELEASE(pImage);

    return texture;
}

ParticleFire* ParticleFire::create()
{
    ParticleFire* pRet = new ParticleFire();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleFire* ParticleFire::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleFire* pRet = new ParticleFire();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleFire::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity = Point(0,0);

        // Gravity Mode: radial acceleration
        this->modeA.radialAccel = 0;
        this->modeA.radialAccelVar = 0;

        // Gravity Mode: speed of particles
        this->modeA.speed = 60;
        this->modeA.speedVar = 20;        

        // starting angle
        _angle = 90;
        _angleVar = 10;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, 60));
        this->_posVar = Point(40, 20);

        // life of particles
        _life = 3;
        _lifeVar = 0.25f;


        // size, in pixels
        _startSize = 54.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.76f;
        _startColor.g = 0.25f;
        _startColor.b = 0.12f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }
        
        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleFireworks
//

ParticleFireworks* ParticleFireworks::create()
{
    ParticleFireworks* pRet = new ParticleFireworks();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleFireworks* ParticleFireworks::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleFireworks* pRet = new ParticleFireworks();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleFireworks::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration= DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity = Point(0,-90);

        // Gravity Mode:  radial
        this->modeA.radialAccel = 0;
        this->modeA.radialAccelVar = 0;

        //  Gravity Mode: speed of particles
        this->modeA.speed = 180;
        this->modeA.speedVar = 50;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));

        // angle
        this->_angle= 90;
        this->_angleVar = 20;

        // life of particles
        this->_life = 3.5f;
        this->_lifeVar = 1;

        // emits per frame
        this->_emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.5f;
        _startColor.g = 0.5f;
        _startColor.b = 0.5f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.1f;
        _endColor.r = 0.1f;
        _endColor.g = 0.1f;
        _endColor.b = 0.1f;
        _endColor.a = 0.2f;
        _endColorVar.r = 0.1f;
        _endColorVar.g = 0.1f;
        _endColorVar.b = 0.1f;
        _endColorVar.a = 0.2f;

        // size, in pixels
        _startSize = 8.0f;
        _startSizeVar = 2.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }
        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleSun
//
ParticleSun* ParticleSun::create()
{
    ParticleSun* pRet = new ParticleSun();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleSun* ParticleSun::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleSun* pRet = new ParticleSun();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleSun::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // additive
        this->setBlendAdditive(true);

        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity mode: speed of particles
        setSpeed(20);
        setSpeedVar(5);


        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 1;
        _lifeVar = 0.5f;

        // size, in pixels
        _startSize = 30.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per seconds
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.76f;
        _startColor.g = 0.25f;
        _startColor.b = 0.12f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        return true;
    }
    return false;
}

//
// ParticleGalaxy
//

ParticleGalaxy* ParticleGalaxy::create()
{
    ParticleGalaxy* pRet = new ParticleGalaxy();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleGalaxy* ParticleGalaxy::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleGalaxy* pRet = new ParticleGalaxy();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleGalaxy::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity Mode: speed of particles
        setSpeed(60);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-80);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(80);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 37.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.12f;
        _startColor.g = 0.25f;
        _startColor.b = 0.76f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleFlower
//

ParticleFlower* ParticleFlower::create()
{
    ParticleFlower* pRet = new ParticleFlower();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleFlower* ParticleFlower::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleFlower* pRet = new ParticleFlower();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleFlower::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity Mode: speed of particles
        setSpeed(80);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-60);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(15);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 30.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.50f;
        _startColor.g = 0.50f;
        _startColor.b = 0.50f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.5f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleMeteor
//

ParticleMeteor * ParticleMeteor::create()
{
    ParticleMeteor *pRet = new ParticleMeteor();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleMeteor* ParticleMeteor::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleMeteor* pRet = new ParticleMeteor();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleMeteor::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(-200,200));

        // Gravity Mode: speed of particles
        setSpeed(15);
        setSpeedVar(5);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 2;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 60.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.2f;
        _startColor.g = 0.4f;
        _startColor.b = 0.7f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.2f;
        _startColorVar.a = 0.1f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleSpiral
//

ParticleSpiral* ParticleSpiral::create()
{
    ParticleSpiral* pRet = new ParticleSpiral();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleSpiral* ParticleSpiral::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleSpiral* pRet = new ParticleSpiral();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleSpiral::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity Mode: speed of particles
        setSpeed(150);
        setSpeedVar(0);

        // Gravity Mode: radial
        setRadialAccel(-380);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(45);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 0;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 12;
        _lifeVar = 0;

        // size, in pixels
        _startSize = 20.0f;
        _startSizeVar = 0.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.5f;
        _startColor.g = 0.5f;
        _startColor.b = 0.5f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.5f;
        _endColor.g = 0.5f;
        _endColor.b = 0.5f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.5f;
        _endColorVar.g = 0.5f;
        _endColorVar.b = 0.5f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleExplosion
//

ParticleExplosion* ParticleExplosion::create()
{
    ParticleExplosion* pRet = new ParticleExplosion();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleExplosion* ParticleExplosion::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleExplosion* pRet = new ParticleExplosion();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleExplosion::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = 0.1f;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity Mode: speed of particles
        setSpeed(70);
        setSpeedVar(40);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height/2));
        setPosVar(Point::ZERO);

        // life of particles
        _life = 5.0f;
        _lifeVar = 2;

        // size, in pixels
        _startSize = 15.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles/_duration;

        // color of particles
        _startColor.r = 0.7f;
        _startColor.g = 0.1f;
        _startColor.b = 0.2f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.5f;
        _endColor.g = 0.5f;
        _endColor.b = 0.5f;
        _endColor.a = 0.0f;
        _endColorVar.r = 0.5f;
        _endColorVar.g = 0.5f;
        _endColorVar.b = 0.5f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSmoke
//

ParticleSmoke* ParticleSmoke::create()
{
    ParticleSmoke* pRet = new ParticleSmoke();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleSmoke* ParticleSmoke::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleSmoke* pRet = new ParticleSmoke();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleSmoke::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        // Emitter mode: Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity Mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: speed of particles
        setSpeed(25);
        setSpeedVar(10);

        // angle
        _angle = 90;
        _angleVar = 5;

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, 0));
        setPosVar(Point(20, 0));

        // life of particles
        _life = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize = 60.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.8f;
        _startColor.g = 0.8f;
        _startColor.b = 0.8f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.02f;
        _startColorVar.g = 0.02f;
        _startColorVar.b = 0.02f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSnow
//

ParticleSnow* ParticleSnow::create()
{
    ParticleSnow* pRet = new ParticleSnow();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleSnow* ParticleSnow::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleSnow* pRet = new ParticleSnow();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleSnow::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        _duration = DURATION_INFINITY;

        // set gravity mode.
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,-1));

        // Gravity Mode: speed of particles
        setSpeed(5);
        setSpeedVar(1);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height + 10));
        setPosVar(Point(winSize.width/2, 0));

        // angle
        _angle = -90;
        _angleVar = 5;

        // life of particles
        _life = 45;
        _lifeVar = 15;

        // size, in pixels
        _startSize = 10.0f;
        _startSizeVar = 5.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 10;

        // color of particles
        _startColor.r = 1.0f;
        _startColor.g = 1.0f;
        _startColor.b = 1.0f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 1.0f;
        _endColor.g = 1.0f;
        _endColor.b = 1.0f;
        _endColor.a = 0.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleRain
//

ParticleRain* ParticleRain::create()
{
    ParticleRain* pRet = new ParticleRain();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ParticleRain* ParticleRain::createWithTotalParticles(unsigned int numberOfParticles)
{
    ParticleRain* pRet = new ParticleRain();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ParticleRain::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        _duration = DURATION_INFINITY;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(10,-10));

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // Gravity Mode: speed of particles
        setSpeed(130);
        setSpeedVar(30);

        // angle
        _angle = -90;
        _angleVar = 5;


        // emitter position
        Size winSize = Director::getInstance()->getWinSize();
        this->setPosition(Point(winSize.width/2, winSize.height));
        setPosVar(Point(winSize.width/2, 0));

        // life of particles
        _life = 4.5f;
        _lifeVar = 0;

        // size, in pixels
        _startSize = 4.0f;
        _startSizeVar = 2.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 20;

        // color of particles
        _startColor.r = 0.7f;
        _startColor.g = 0.8f;
        _startColor.b = 1.0f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.7f;
        _endColor.g = 0.8f;
        _endColor.b = 1.0f;
        _endColor.a = 0.5f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != NULL)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

NS_CC_END
