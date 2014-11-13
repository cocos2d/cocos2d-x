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

#include "ParticleAffectors/ParticleUniverseAlignAffector.h"

namespace ParticleUniverse
{
	// Constants
	const bool AlignAffector::DEFAULT_RESIZE = false;
	
	//-----------------------------------------------------------------------
	AlignAffector::AlignAffector(void) : 
		ParticleAffector(),
		mPreviousParticle(0),
		mResize(DEFAULT_RESIZE)
	{
	}
	//-----------------------------------------------------------------------
	void AlignAffector::_firstParticle(ParticleTechnique* particleTechnique, 
		Particle* particle, 
		Real timeElapsed)
	{
		mPreviousParticle = particle;
	}
	//-----------------------------------------------------------------------
	bool AlignAffector::isResize(void) const
	{
		return mResize;
	}
	//-----------------------------------------------------------------------
	void AlignAffector::setResize(bool resize)
	{
		mResize = resize;
	}
	//-----------------------------------------------------------------------
	void AlignAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (particle->particleType == Particle::PT_VISUAL)
		{
			// Set the orientation towards the previous particle, but rotation is undetermined.
			VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);

			// Get difference
			Vector3 diff = (mPreviousParticle->position - particle->position);
			if (mResize)
			{
				visualParticle->setOwnDimensions (visualParticle->width, diff.length(), visualParticle->depth);
			}
			diff.normalise();
			visualParticle->orientation.x = diff.x;
			visualParticle->orientation.y = diff.y;
			visualParticle->orientation.z = diff.z;
		}

		mPreviousParticle = particle;
	}
	//-----------------------------------------------------------------------
	void AlignAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		AlignAffector* alignAffector = static_cast<AlignAffector*>(affector);
		alignAffector->mResize = mResize;
	}
}
