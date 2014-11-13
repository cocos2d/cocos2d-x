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

#include "ParticleAffectors/ParticleUniverseFlockCenteringAffector.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void FlockCenteringAffector::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		if (mCount != 0)
		{
			// Calculate the average of the previous update
			mAverage = mSum / mCount;
		}
		else
		{
			mAverage = getDerivedPosition(); // Set to position of the affector
		}
		mSum = Vector3::ZERO;
		mCount = 0;
	}
	//-----------------------------------------------------------------------
	void FlockCenteringAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		mSum += particle->position;
		mCount++;
		particle->direction += (mAverage - particle->position) * timeElapsed; // use average of the previous update
	}
	//-----------------------------------------------------------------------
	void FlockCenteringAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);
		FlockCenteringAffector* flockCenteringAffector = static_cast<FlockCenteringAffector*>(affector);
		(void)flockCenteringAffector;
	}
}
