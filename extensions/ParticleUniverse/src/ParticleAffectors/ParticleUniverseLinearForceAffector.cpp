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

#include "ParticleAffectors/ParticleUniverseLinearForceAffector.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void LinearForceAffector::copyAttributesTo (ParticleAffector* affector)
	{
		BaseForceAffector::copyAttributesTo(affector);
	}
	//-----------------------------------------------------------------------
	void LinearForceAffector::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Scale force
		mScaledVector = mForceVector * timeElapsed;
	}
	//-----------------------------------------------------------------------
	void LinearForceAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// Affect the direction and take the specialisation into account
		if (mForceApplication == FA_ADD)
		{
			particle->direction += mScaledVector * _calculateAffectSpecialisationFactor(particle);
		}
		else
		{
			particle->direction = (particle->direction + mForceVector) / 2;
		}
	}

}
