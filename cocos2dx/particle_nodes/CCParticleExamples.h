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
class CC_DLL CCParticleFire : public CCParticleSystemQuad
{
public:
    CCParticleFire(){}
    virtual ~CCParticleFire(){}
    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleFire* node();
    
    static CCParticleFire* create();
    static CCParticleFire* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A fireworks particle system
class CC_DLL CCParticleFireworks : public CCParticleSystemQuad
{
public:
    CCParticleFireworks(){}
    virtual ~CCParticleFireworks(){}
    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleFireworks* node();
    
    static CCParticleFireworks* create();
    static CCParticleFireworks* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A sun particle system
class CC_DLL CCParticleSun : public CCParticleSystemQuad
{
public:
    CCParticleSun(){}
    virtual ~CCParticleSun(){}
    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleSun* node();
    
    static CCParticleSun* create();
    static CCParticleSun* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A galaxy particle system
class CC_DLL CCParticleGalaxy : public CCParticleSystemQuad
{
public:
    CCParticleGalaxy(){}
    virtual ~CCParticleGalaxy(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleGalaxy* node();
    
    static CCParticleGalaxy* create();
    static CCParticleGalaxy* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A flower particle system
class CC_DLL CCParticleFlower : public CCParticleSystemQuad
{
public:
    CCParticleFlower(){}
    virtual ~CCParticleFlower(){}
    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleFlower* node();
    
    static CCParticleFlower* create();
    static CCParticleFlower* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A meteor particle system
class CC_DLL CCParticleMeteor : public CCParticleSystemQuad
{
public:
    CCParticleMeteor(){}
    virtual ~CCParticleMeteor(){}
    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    CC_DEPRECATED_ATTRIBUTE static CCParticleMeteor * node();
    static CCParticleMeteor * create();
    static CCParticleMeteor* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An spiral particle system
class CC_DLL CCParticleSpiral : public CCParticleSystemQuad
{
public:
    CCParticleSpiral(){}
    virtual ~CCParticleSpiral(){}
    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleSpiral* node();
    
    static CCParticleSpiral* create();
    static CCParticleSpiral* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An explosion particle system
class CC_DLL CCParticleExplosion : public CCParticleSystemQuad
{
public:
    CCParticleExplosion(){}
    virtual ~CCParticleExplosion(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleExplosion* node();
    
    static CCParticleExplosion* create();
    static CCParticleExplosion* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An smoke particle system
class CC_DLL CCParticleSmoke : public CCParticleSystemQuad
{
public:
    CCParticleSmoke(){}
    virtual ~CCParticleSmoke(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleSmoke* node();
    
    static CCParticleSmoke* create();
    static CCParticleSmoke* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief An snow particle system
class CC_DLL CCParticleSnow : public CCParticleSystemQuad
{
public:
    CCParticleSnow(){}
    virtual ~CCParticleSnow(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleSnow* node();
    
    static CCParticleSnow* create();
    static CCParticleSnow* createWithTotalParticles(unsigned int numberOfParticles);
};

//! @brief A rain particle system
class CC_DLL CCParticleRain : public CCParticleSystemQuad
{
public:
    CCParticleRain(){}
    virtual ~CCParticleRain(){}
    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCParticleRain* node();
    
    static CCParticleRain* create();
    static CCParticleRain* createWithTotalParticles(unsigned int numberOfParticles);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
