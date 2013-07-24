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
#ifndef __CCPARTICLE_EXAMPLE_H__
#define __CCPARTICLE_EXAMPLE_H__

#include "CCParticleSystemQuad.h"

NS_CC_BEGIN

/**
 * @addtogroup particle_nodes
 * @{
 */

//! @brief A fire particle system
class CC_DLL ParticleFire : public ParticleSystemQuad
{
public:
    ParticleFire(){}
    virtual ~ParticleFire(){}
    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleFire* create();
    static ParticleFire* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A fireworks particle system
class CC_DLL ParticleFireworks : public ParticleSystemQuad
{
public:
    ParticleFireworks(){}
    virtual ~ParticleFireworks(){}
    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleFireworks* create();
    static ParticleFireworks* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A sun particle system
class CC_DLL ParticleSun : public ParticleSystemQuad
{
public:
    ParticleSun(){}
    virtual ~ParticleSun(){}
    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleSun* create();
    static ParticleSun* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A galaxy particle system
class CC_DLL ParticleGalaxy : public ParticleSystemQuad
{
public:
    ParticleGalaxy(){}
    virtual ~ParticleGalaxy(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleGalaxy* create();
    static ParticleGalaxy* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A flower particle system
class CC_DLL ParticleFlower : public ParticleSystemQuad
{
public:
    ParticleFlower(){}
    virtual ~ParticleFlower(){}
    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleFlower* create();
    static ParticleFlower* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A meteor particle system
class CC_DLL ParticleMeteor : public ParticleSystemQuad
{
public:
    ParticleMeteor(){}
    virtual ~ParticleMeteor(){}
    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);

    static ParticleMeteor * create();
    static ParticleMeteor* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An spiral particle system
class CC_DLL ParticleSpiral : public ParticleSystemQuad
{
public:
    ParticleSpiral(){}
    virtual ~ParticleSpiral(){}
    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleSpiral* create();
    static ParticleSpiral* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An explosion particle system
class CC_DLL ParticleExplosion : public ParticleSystemQuad
{
public:
    ParticleExplosion(){}
    virtual ~ParticleExplosion(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleExplosion* create();
    static ParticleExplosion* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An smoke particle system
class CC_DLL ParticleSmoke : public ParticleSystemQuad
{
public:
    ParticleSmoke(){}
    virtual ~ParticleSmoke(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleSmoke* create();
    static ParticleSmoke* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An snow particle system
class CC_DLL ParticleSnow : public ParticleSystemQuad
{
public:
    ParticleSnow(){}
    virtual ~ParticleSnow(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleSnow* create();
    static ParticleSnow* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A rain particle system
class CC_DLL ParticleRain : public ParticleSystemQuad
{
public:
    ParticleRain(){}
    virtual ~ParticleRain(){}
    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static ParticleRain* create();
    static ParticleRain* createWithTotalParticles(unsigned int numberOfParticles);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
