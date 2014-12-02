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

#include "ParticleObservers/ParticleUniverseOnRandomObserver.h"

namespace ParticleUniverse
{
	// Constants
	const Real OnRandomObserver::DEFAULT_THRESHOLD = 0.5f;

	//-----------------------------------------------------------------------
	OnRandomObserver::OnRandomObserver(void) : 
		ParticleObserver(),
		mThreshold(DEFAULT_THRESHOLD)
	{
	}
	//-----------------------------------------------------------------------
	void OnRandomObserver::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		// Call parent
		ParticleObserver::_preProcessParticles(technique, timeElapsed);

		// Handle the _observe here
		_handleObserve(technique, 0, timeElapsed);
	}
	//-----------------------------------------------------------------------
	void OnRandomObserver::_processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// No need to determine per particle
	}
	//-----------------------------------------------------------------------
	bool OnRandomObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		return (Math::UnitRandom() > mThreshold);
	}
	//-----------------------------------------------------------------------
	void OnRandomObserver::copyAttributesTo(ParticleObserver* observer)
	{
		ParticleObserver::copyAttributesTo(observer);
		OnRandomObserver* onRandomObserver = static_cast<OnRandomObserver*>(observer);
		onRandomObserver->mThreshold = mThreshold;
	}
}
