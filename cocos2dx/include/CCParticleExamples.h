/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCPointParticleSystem.h"
#include "CCQuadParticleSystem.h"

namespace cocos2d {

	//! A fire particle system
	class CCX_DLL CCParticleFire : public CCQuadParticleSystem
	{
	public:
		CCParticleFire(){}
		virtual ~CCParticleFire(){}
		bool init(){ return initWithTotalParticles(250); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleFire * node()
		{
			CCParticleFire *pRet = new CCParticleFire();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A fireworks particle system
	class CCX_DLL CCParticleFireworks : public CCQuadParticleSystem
	{
	public:
		CCParticleFireworks(){}
		virtual ~CCParticleFireworks(){}
		bool init(){ return initWithTotalParticles(1500); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleFireworks * node()
		{
			CCParticleFireworks *pRet = new CCParticleFireworks();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A sun particle system
	class CCX_DLL CCParticleSun : public CCQuadParticleSystem
	{
	public:
		CCParticleSun(){}
		virtual ~CCParticleSun(){}
		bool init(){ return initWithTotalParticles(350); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleSun * node()
		{
			CCParticleSun *pRet = new CCParticleSun();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A galaxy particle system
	class CCX_DLL CCParticleGalaxy : public CCQuadParticleSystem
	{
	public:
		CCParticleGalaxy(){}
		virtual ~CCParticleGalaxy(){}
		bool init(){ return initWithTotalParticles(200); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleGalaxy * node()
		{
			CCParticleGalaxy *pRet = new CCParticleGalaxy();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A flower particle system
	class CCX_DLL CCParticleFlower : public CCQuadParticleSystem
	{
	public:
		CCParticleFlower(){}
		virtual ~CCParticleFlower(){}
		bool init(){ return initWithTotalParticles(250); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleFlower * node()
		{
			CCParticleFlower *pRet = new CCParticleFlower();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A meteor particle system
	class CCX_DLL CCParticleMeteor : public CCQuadParticleSystem
	{
	public:
		CCParticleMeteor(){}
		virtual ~CCParticleMeteor(){}
		bool init(){ return initWithTotalParticles(150); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleMeteor * node()
		{
			CCParticleMeteor *pRet = new CCParticleMeteor();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! An spiral particle system
	class CCX_DLL CCParticleSpiral : public CCQuadParticleSystem
	{
	public:
		CCParticleSpiral(){}
		virtual ~CCParticleSpiral(){}
		bool init(){ return initWithTotalParticles(500); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleSpiral * node()
		{
			CCParticleSpiral *pRet = new CCParticleSpiral();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! An explosion particle system
	class CCX_DLL CCParticleExplosion : public CCQuadParticleSystem
	{
	public:
		CCParticleExplosion(){}
		virtual ~CCParticleExplosion(){}
		bool init(){ return initWithTotalParticles(700); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleExplosion * node()
		{
			CCParticleExplosion *pRet = new CCParticleExplosion();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! An smoke particle system
	class CCX_DLL CCParticleSmoke : public CCQuadParticleSystem
	{
	public:
		CCParticleSmoke(){}
		virtual ~CCParticleSmoke(){}
		bool init(){ return initWithTotalParticles(200); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleSmoke * node()
		{
			CCParticleSmoke *pRet = new CCParticleSmoke();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! An snow particle system
	class CCX_DLL CCParticleSnow : public CCQuadParticleSystem
	{
	public:
		CCParticleSnow(){}
		virtual ~CCParticleSnow(){}
		bool init(){ return initWithTotalParticles(700); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleSnow * node()
		{
			CCParticleSnow *pRet = new CCParticleSnow();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

	//! A rain particle system
	class CCX_DLL CCParticleRain : public CCQuadParticleSystem
	{
	public:
		CCParticleRain(){}
		virtual ~CCParticleRain(){}
		bool init(){ return initWithTotalParticles(1000); }
		virtual bool initWithTotalParticles(int numberOfParticles);
		static CCParticleRain * node()
		{
			CCParticleRain *pRet = new CCParticleRain();
			if (pRet->init())
			{
				pRet->autorelease();
				return pRet;
			}
			CCX_SAFE_DELETE(pRet)
			return NULL;
		}
	};

}// namespace cocos2d
#endif //__CCPARTICLE_EXAMPLE_H__


