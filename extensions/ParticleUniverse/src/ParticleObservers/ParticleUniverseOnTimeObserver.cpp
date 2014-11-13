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

#include "ParticleObservers/ParticleUniverseOnTimeObserver.h"

namespace ParticleUniverse
{
	// Constants
	const Real OnTimeObserver::DEFAULT_THRESHOLD = 0.0f;
	const bool OnTimeObserver::DEFAULT_SINCE_START_SYSTEM = false;

	//-----------------------------------------------------------------------
	OnTimeObserver::OnTimeObserver(void) : ParticleObserver(),
		mThreshold(DEFAULT_THRESHOLD),
		mCompare(CO_GREATER_THAN),
		mSinceStartSystem(DEFAULT_SINCE_START_SYSTEM)
	{
	};
	//-----------------------------------------------------------------------
	void OnTimeObserver::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		// Call parent
		ParticleObserver::_preProcessParticles(technique, timeElapsed);

		// Also observe if there are no particles emitted, because some of the event handlers do not only
		// perform an action on a particle.
		if (technique->getNumberOfEmittedParticles() == 0)
		{
			_handleObserve(technique, 0, timeElapsed);
		}
	}
	//-----------------------------------------------------------------------
	bool OnTimeObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (mCompare == CO_GREATER_THAN)
		{
			if (mSinceStartSystem)
			{
				// Validate whether time since start of the particle system > threshold
				return (mParentTechnique->getParentSystem()->getTimeElapsedSinceStart() > mThreshold);
			}
			else
			{
				// Validate whether time since start of the particle emission > threshold
				return (particle && (particle->totalTimeToLive - particle->timeToLive) > mThreshold);
			}
		}
		else if (mCompare == CO_LESS_THAN)
		{
			if (mSinceStartSystem)
			{
				// Validate whether time since start of the particle system < threshold
				return (mParentTechnique->getParentSystem()->getTimeElapsedSinceStart() < mThreshold);
			}
			else
			{
				// Validate whether time since start of the particle emission < threshold
				return (particle && (particle->totalTimeToLive - particle->timeToLive) < mThreshold);
			}
		}
		else
		{
			// Equals
			if (mSinceStartSystem)
			{
				// Validate whether time since start of the particle system == threshold
				return almostEquals(mParentTechnique->getParentSystem()->getTimeElapsedSinceStart(), mThreshold, 0.01f);
			}
			else
			{
				// Validate whether time since start of the particle emission == threshold
				return particle && almostEquals((particle->totalTimeToLive - particle->timeToLive), mThreshold, 0.01f);
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void OnTimeObserver::copyAttributesTo(ParticleObserver* observer)
	{
		ParticleObserver::copyAttributesTo(observer);

		OnTimeObserver* onTimeObserver = static_cast<OnTimeObserver*>(observer);
		onTimeObserver->mThreshold = mThreshold;
		onTimeObserver->mCompare = mCompare;
		onTimeObserver->mSinceStartSystem = mSinceStartSystem;
	}
}
