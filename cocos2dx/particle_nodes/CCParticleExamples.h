/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
    static CCParticleFire * node()
    {
        return create();
    }

    static CCParticleFire * create()
    {
        CCParticleFire *pRet = new CCParticleFire();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A fireworks particle system
class CC_DLL CCParticleFireworks : public CCParticleSystemQuad
{
public:
    CCParticleFireworks(){}
    virtual ~CCParticleFireworks(){}
    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleFireworks * node()
    {
        return create();
    }

    static CCParticleFireworks * create()
    {
        CCParticleFireworks *pRet = new CCParticleFireworks();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A sun particle system
class CC_DLL CCParticleSun : public CCParticleSystemQuad
{
public:
    CCParticleSun(){}
    virtual ~CCParticleSun(){}
    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleSun * node()
    {
        return create();
    }
    static CCParticleSun * create()
    {
        CCParticleSun *pRet = new CCParticleSun();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A galaxy particle system
class CC_DLL CCParticleGalaxy : public CCParticleSystemQuad
{
public:
    CCParticleGalaxy(){}
    virtual ~CCParticleGalaxy(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleGalaxy * node()
    {
        return create();
    }

    static CCParticleGalaxy * create()
    {
        CCParticleGalaxy *pRet = new CCParticleGalaxy();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A flower particle system
class CC_DLL CCParticleFlower : public CCParticleSystemQuad
{
public:
    CCParticleFlower(){}
    virtual ~CCParticleFlower(){}
    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleFlower * node()
    {
        return create();
    }

    static CCParticleFlower * create()
    {
        CCParticleFlower *pRet = new CCParticleFlower();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A meteor particle system
class CC_DLL CCParticleMeteor : public CCParticleSystemQuad
{
public:
    CCParticleMeteor(){}
    virtual ~CCParticleMeteor(){}
    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleMeteor * node()
    {
        return create();
    }
    static CCParticleMeteor * create()
    {
        CCParticleMeteor *pRet = new CCParticleMeteor();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief An spiral particle system
class CC_DLL CCParticleSpiral : public CCParticleSystemQuad
{
public:
    CCParticleSpiral(){}
    virtual ~CCParticleSpiral(){}
    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleSpiral * node()
    {
        return create();
    }
    static CCParticleSpiral * create()
    {
        CCParticleSpiral *pRet = new CCParticleSpiral();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief An explosion particle system
class CC_DLL CCParticleExplosion : public CCParticleSystemQuad
{
public:
    CCParticleExplosion(){}
    virtual ~CCParticleExplosion(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleExplosion * node()
    {
        return create();
    }
    static CCParticleExplosion * create()
    {
        CCParticleExplosion *pRet = new CCParticleExplosion();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief An smoke particle system
class CC_DLL CCParticleSmoke : public CCParticleSystemQuad
{
public:
    CCParticleSmoke(){}
    virtual ~CCParticleSmoke(){}
    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleSmoke * node()
    {
        return create();
    }
    static CCParticleSmoke * create()
    {
        CCParticleSmoke *pRet = new CCParticleSmoke();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief An snow particle system
class CC_DLL CCParticleSnow : public CCParticleSystemQuad
{
public:
    CCParticleSnow(){}
    virtual ~CCParticleSnow(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleSnow * node()
    {
        return create();
    }

    static CCParticleSnow * create()
    {
        CCParticleSnow *pRet = new CCParticleSnow();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

//! @brief A rain particle system
class CC_DLL CCParticleRain : public CCParticleSystemQuad
{
public:
    CCParticleRain(){}
    virtual ~CCParticleRain(){}
    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleRain * node()
    {
        return create();
    }
    static CCParticleRain * create()
    {
        CCParticleRain *pRet = new CCParticleRain();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
