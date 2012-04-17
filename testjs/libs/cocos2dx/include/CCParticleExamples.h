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

#include "platform/CCArchOptimalParticleSystem.h"

namespace cocos2d {

//! @brief A fire particle system
class CC_DLL CCParticleFire : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleFire(){}
	virtual ~CCParticleFire(){}
	bool init(){ return initWithTotalParticles(250); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFire * node()
	{
		CCParticleFire *pRet = new CCParticleFire();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A fireworks particle system
class CC_DLL CCParticleFireworks : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleFireworks(){}
	virtual ~CCParticleFireworks(){}
	bool init(){ return initWithTotalParticles(1500); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFireworks * node()
	{
		CCParticleFireworks *pRet = new CCParticleFireworks();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A sun particle system
class CC_DLL CCParticleSun : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleSun(){}
	virtual ~CCParticleSun(){}
	bool init(){ return initWithTotalParticles(350); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSun * node()
	{
		CCParticleSun *pRet = new CCParticleSun();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A galaxy particle system
class CC_DLL CCParticleGalaxy : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleGalaxy(){}
	virtual ~CCParticleGalaxy(){}
	bool init(){ return initWithTotalParticles(200); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleGalaxy * node()
	{
		CCParticleGalaxy *pRet = new CCParticleGalaxy();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A flower particle system
class CC_DLL CCParticleFlower : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleFlower(){}
	virtual ~CCParticleFlower(){}
	bool init(){ return initWithTotalParticles(250); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFlower * node()
	{
		CCParticleFlower *pRet = new CCParticleFlower();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A meteor particle system
class CC_DLL CCParticleMeteor : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleMeteor(){}
	virtual ~CCParticleMeteor(){}
	bool init(){ return initWithTotalParticles(150); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleMeteor * node()
	{
		CCParticleMeteor *pRet = new CCParticleMeteor();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief An spiral particle system
class CC_DLL CCParticleSpiral : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleSpiral(){}
	virtual ~CCParticleSpiral(){}
	bool init(){ return initWithTotalParticles(500); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSpiral * node()
	{
		CCParticleSpiral *pRet = new CCParticleSpiral();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief An explosion particle system
class CC_DLL CCParticleExplosion : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleExplosion(){}
	virtual ~CCParticleExplosion(){}
	bool init(){ return initWithTotalParticles(700); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleExplosion * node()
	{
		CCParticleExplosion *pRet = new CCParticleExplosion();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief An smoke particle system
class CC_DLL CCParticleSmoke : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleSmoke(){}
	virtual ~CCParticleSmoke(){}
	bool init(){ return initWithTotalParticles(200); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSmoke * node()
	{
		CCParticleSmoke *pRet = new CCParticleSmoke();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief An snow particle system
class CC_DLL CCParticleSnow : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleSnow(){}
	virtual ~CCParticleSnow(){}
	bool init(){ return initWithTotalParticles(700); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSnow * node()
	{
		CCParticleSnow *pRet = new CCParticleSnow();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

//! @brief A rain particle system
class CC_DLL CCParticleRain : public ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:
	CCParticleRain(){}
	virtual ~CCParticleRain(){}
	bool init(){ return initWithTotalParticles(1000); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleRain * node()
	{
		CCParticleRain *pRet = new CCParticleRain();
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}
};

}// namespace cocos2d

#endif //__CCPARTICLE_EXAMPLE_H__
