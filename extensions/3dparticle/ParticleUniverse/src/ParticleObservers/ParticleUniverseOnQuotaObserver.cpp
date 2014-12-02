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

#include "ParticleObservers/ParticleUniverseOnQuotaObserver.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool OnQuotaObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		return mResult;
	}
	//-----------------------------------------------------------------------
	void OnQuotaObserver::_postProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		mResult = false;
		size_t quota = 0;
		if (mParticleTypeToObserveSet)
		{
			// Type to observe is set, so validate only that one
			switch (mParticleTypeToObserve)
			{
				case Particle::PT_VISUAL:
					quota = particleTechnique->getVisualParticleQuota();
				break;
				case Particle::PT_EMITTER:
					quota = particleTechnique->getEmittedEmitterQuota();
				break;
				case Particle::PT_AFFECTOR:
					quota = particleTechnique->getEmittedAffectorQuota();
				break;
				case Particle::PT_TECHNIQUE:
					quota = particleTechnique->getEmittedTechniqueQuota();
				break;
				case Particle::PT_SYSTEM:
					quota = particleTechnique->getEmittedAffectorQuota();
				break;
			}

			mResult = particleTechnique->getNumberOfEmittedParticles(mParticleTypeToObserve) >= quota;
		}
		else
		{
			// Type to observe is not set, so check them all
			quota = particleTechnique->getVisualParticleQuota() + 
				particleTechnique->getEmittedEmitterQuota() + 
				particleTechnique->getEmittedTechniqueQuota() + 
				particleTechnique->getEmittedAffectorQuota() +
				particleTechnique->getEmittedSystemQuota();
			mResult = particleTechnique->getNumberOfEmittedParticles() >= quota;
		}
	}
}
