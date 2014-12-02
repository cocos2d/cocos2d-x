/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleEmitters/ParticleUniverseBoxEmitter.h"

namespace ParticleUniverse
{
	// Constants
	const Real BoxEmitter::DEFAULT_WIDTH = 100.0f;
	const Real BoxEmitter::DEFAULT_HEIGHT = 100.0f;
	const Real BoxEmitter::DEFAULT_DEPTH = 100.0f;

	//-----------------------------------------------------------------------
	BoxEmitter::BoxEmitter(void) : 
		ParticleEmitter(),
		mWidth(DEFAULT_WIDTH),
		mHeight(DEFAULT_HEIGHT),
		mDepth(DEFAULT_DEPTH),
		mXRange(0.5f * DEFAULT_WIDTH),
		mYRange(0.5f * DEFAULT_HEIGHT),
		mZRange(0.5f * DEFAULT_DEPTH)
	{
	}
	//-----------------------------------------------------------------------
	const Real BoxEmitter::getHeight(void) const
	{
		return mHeight;
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::setHeight(const Real height)
	{
		mHeight = height;
		mYRange = 0.5f * height;
	}
	//-----------------------------------------------------------------------
	const Real BoxEmitter::getWidth(void) const
	{
		return mWidth;
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::setWidth(const Real width)
	{
		mWidth = width;
		mXRange = 0.5f * width;
	}
	//-----------------------------------------------------------------------
	const Real BoxEmitter::getDepth(void) const
	{
		return mDepth;
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::setDepth(const Real depth)
	{
		mDepth = depth;
		mZRange = 0.5f * depth;
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::_initParticlePosition(Particle* particle)
	{
		ParticleSystem* sys = mParentTechnique->getParentSystem();
		if (sys)
		{
			particle->position = getDerivedPosition() + 
				sys->getDerivedOrientation() *
				(_mEmitterScale *
				Vector3(Math::SymmetricRandom() * mXRange,
					Math::SymmetricRandom() * mYRange,
					Math::SymmetricRandom() * mZRange));
		}
		else
		{
			particle->position = getDerivedPosition() + 
				_mEmitterScale *
				Vector3(Math::SymmetricRandom() * mXRange,
					Math::SymmetricRandom() * mYRange,
					Math::SymmetricRandom() * mZRange);
		}

		particle->originalPosition = particle->position;
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);

		BoxEmitter* boxEmitter = static_cast<BoxEmitter*>(emitter);
		boxEmitter->mHeight = mHeight;
		boxEmitter->mWidth = mWidth;
		boxEmitter->mDepth = mDepth;
		boxEmitter->mXRange = mXRange;
		boxEmitter->mYRange = mYRange;
		boxEmitter->mZRange = mZRange;
	}
}
