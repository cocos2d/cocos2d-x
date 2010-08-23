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
	class CCParticleFire : public CCQuadParticleSystem
	{
		CCParticleFire(){}
		virtual ~CCParticleFire(){}
		bool init(){ initWithTotalParticles(250); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

	//! A fireworks particle system
	class CCParticleFireworks : public CCQuadParticleSystem
	{
		CCParticleFireworks(){}
		virtual ~CCParticleFireworks(){}
		bool init(){ initWithTotalParticles(1500); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! A sun particle system
	class CCParticleSun : public CCQuadParticleSystem
	{
		CCParticleSun(){}
		virtual ~CCParticleSun(){}
		bool init(){ initWithTotalParticles(350); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! A galaxy particle system
	class CCParticleGalaxy : public CCQuadParticleSystem
	{
		CCParticleGalaxy(){}
		virtual ~CCParticleGalaxy(){}
		bool init(){ initWithTotalParticles(200); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! A flower particle system
	class CCParticleFlower : public CCQuadParticleSystem
	{
		CCParticleFlower(){}
		virtual ~CCParticleFlower(){}
		bool init(){ initWithTotalParticles(250); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! A meteor particle system
	class CCParticleMeteor : public CCQuadParticleSystem
	{
		CCParticleMeteor(){}
		virtual ~CCParticleMeteor(){}
		bool init(){ initWithTotalParticles(150); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! An spiral particle system
	class CCParticleSpiral : public CCQuadParticleSystem
	{
		CCParticleSpiral(){}
		virtual ~CCParticleSpiral(){}
		bool init(){ initWithTotalParticles(500); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! An explosion particle system
	class CCParticleExplosion : public CCQuadParticleSystem
	{
		CCParticleExplosion(){}
		virtual ~CCParticleExplosion(){}
		bool init(){ initWithTotalParticles(700); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! An smoke particle system
	class CCParticleSmoke : public CCQuadParticleSystem
	{
		CCParticleSmoke(){}
		virtual ~CCParticleSmoke(){}
		bool init(){ initWithTotalParticles(200); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! An snow particle system
	class CCParticleSnow : public CCQuadParticleSystem
	{
		CCParticleSnow(){}
		virtual ~CCParticleSnow(){}
		bool init(){ initWithTotalParticles(700); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

		//! A rain particle system
	class CCParticleRain : public CCQuadParticleSystem
	{
		CCParticleRain(){}
		virtual ~CCParticleRain(){}
		bool init(){ initWithTotalParticles(1000); }
		virtual bool initWithTotalParticles(int numberOfParticles);
	};

}// namespace cocos2d
#endif //__CCPARTICLE_EXAMPLE_H__


