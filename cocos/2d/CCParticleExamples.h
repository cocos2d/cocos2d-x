/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "2d/CCParticleSystemQuad.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/** @class ParticleFire
 * @brief A fire particle system.
 */
class CC_DLL ParticleFire : public ParticleSystemQuad
{
public:
    /** Create a fire particle system.
     *
     * @return An autoreleased ParticleFire object.
     */
    static ParticleFire* create();
    /** Create a fire particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFire object.
     * @js NA
     */
    static ParticleFire* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleFire(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFire(){}

    bool init() override { return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles) override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFire);
};

/** @class ParticleFireworks
 * @brief A fireworks particle system.
 */
class CC_DLL ParticleFireworks : public ParticleSystemQuad
{
public:
    /** Create a fireworks particle system.
     *
     * @return An autoreleased ParticleFireworks object.
     */
    static ParticleFireworks* create();
    /** Create a fireworks particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFireworks object.
     * @js NA
     */
    static ParticleFireworks* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleFireworks(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFireworks(){}

    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFireworks);

};

/** @class ParticleSun
 * @brief A sun particle system.
 */
class CC_DLL ParticleSun : public ParticleSystemQuad
{
public:
    /** Create a sun particle system.
     *
     * @return An autoreleased ParticleSun object.
     */
    static ParticleSun* create();
    /** Create a sun particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSun object.
     * @js NA
     */
    static ParticleSun* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSun(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSun(){}

    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSun);

};

/** @class ParticleGalaxy
 * @brief A galaxy particle system.
 */
class CC_DLL ParticleGalaxy : public ParticleSystemQuad
{
public:
    /** Create a galaxy particle system.
     *
     * @return An autoreleased ParticleGalaxy object.
     */
    static ParticleGalaxy* create();
    /** Create a galaxy particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleGalaxy object.
     * @js NA
     */
    static ParticleGalaxy* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleGalaxy(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleGalaxy(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleGalaxy);

};

/** @class ParticleFlower
 * @brief A flower particle system.
 */
class CC_DLL ParticleFlower : public ParticleSystemQuad
{
public:
    /** Create a flower particle system.
     *
     * @return An autoreleased ParticleFlower object.
     */
    static ParticleFlower* create();
    /** Create a flower particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFlower object.
     * @js NA
     */
    static ParticleFlower* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleFlower(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFlower(){}

    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleFlower);
};

/** @class ParticleMeteor
 * @brief A meteor particle system.
 */
class CC_DLL ParticleMeteor : public ParticleSystemQuad
{
public:
    /** Create a meteor particle system.
     *
     * @return An autoreleased ParticleMeteor object.
     */
    static ParticleMeteor * create();
    /** Create a meteor particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleMeteor object.
     * @js NA
     */
    static ParticleMeteor* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleMeteor(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleMeteor(){}

    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleMeteor);
};

/** @class ParticleSpiral
 * @brief An spiral particle system.
 */
class CC_DLL ParticleSpiral : public ParticleSystemQuad
{
public:
    /** Create a spiral particle system.
     *
     * @return An autoreleased ParticleSpiral object.
     */
    static ParticleSpiral* create();
    /** Create a spiral particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSpiral object.
     * @js NA
     */
    static ParticleSpiral* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSpiral(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSpiral(){}

    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSpiral);

};

/** @class ParticleExplosion
 * @brief An explosion particle system.
 */
class CC_DLL ParticleExplosion : public ParticleSystemQuad
{
public:
    /** Create a explosion particle system.
     *
     * @return An autoreleased ParticleExplosion object.
     */
    static ParticleExplosion* create();
    /** Create a explosion particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleExplosion object.
     * @js NA
     */
    static ParticleExplosion* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleExplosion(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleExplosion(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleExplosion);
};

/** @class ParticleSmoke
 * @brief An smoke particle system.
 */
class CC_DLL ParticleSmoke : public ParticleSystemQuad
{
public:
    /** Create a smoke particle system.
     *
     * @return An autoreleased ParticleSmoke object.
     */
    static ParticleSmoke* create();
    /** Create a smoke particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSmoke object.
     * @js NA
     */
    static ParticleSmoke* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSmoke(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSmoke(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSmoke);
};

/** @class ParticleSnow
 * @brief An snow particle system.
 */
class CC_DLL ParticleSnow : public ParticleSystemQuad
{
public:
    /** Create a snow particle system.
     *
     * @return An autoreleased ParticleSnow object.
     */
    static ParticleSnow* create();
    /** Create a snow particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSnow object.
     * @js NA
     */
    static ParticleSnow* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSnow(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSnow(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSnow);
};

/** @class ParticleRain
 * @brief A rain particle system.
 */
class CC_DLL ParticleRain : public ParticleSystemQuad
{
public:
    /** Create a rain particle system.
     *
     * @return An autoreleased ParticleRain object.
     */
    static ParticleRain* create();
    /** Create a rain particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleRain object.
     * @js NA
     */
    static ParticleRain* createWithTotalParticles(int numberOfParticles);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleRain(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleRain(){}

    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleRain);
};

// end of _2d group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
