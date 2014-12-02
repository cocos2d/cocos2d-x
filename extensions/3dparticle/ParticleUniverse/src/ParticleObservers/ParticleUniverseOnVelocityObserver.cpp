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

#include "ParticleObservers/ParticleUniverseOnVelocityObserver.h"

namespace ParticleUniverse
{
	// Constants
	const Real OnVelocityObserver::DEFAULT_VELOCITY_THRESHOLD = 0.0f;

	//-----------------------------------------------------------------------
	OnVelocityObserver::OnVelocityObserver(void) : 
		ParticleObserver(),
		mThreshold(DEFAULT_VELOCITY_THRESHOLD),
		mCompare(CO_LESS_THAN)
	{
	};
	//-----------------------------------------------------------------------
	bool OnVelocityObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (!particle)
			return false;

		// Compensate for the scaled velocity
		Real scaleVelocity = particleTechnique->getParentSystem()->getScaleVelocity();
		if (mCompare == CO_GREATER_THAN)
		{
			// Changed in V 1.3.1
			return (particle->calculateVelocity()) > (scaleVelocity * mThreshold);
		}
		else if (mCompare == CO_LESS_THAN)
		{
			return (particle->calculateVelocity()) < (scaleVelocity * mThreshold);
		}
		else
		{
			// Equals
			return almostEquals(particle->calculateVelocity(), (scaleVelocity * mThreshold), 0.01f);
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void OnVelocityObserver::copyAttributesTo(ParticleObserver* observer)
	{
		ParticleObserver::copyAttributesTo(observer);

		OnVelocityObserver* onVelocityObserver = static_cast<OnVelocityObserver*>(observer);
		onVelocityObserver->mThreshold = mThreshold;
		onVelocityObserver->mCompare = mCompare;
	}
}
