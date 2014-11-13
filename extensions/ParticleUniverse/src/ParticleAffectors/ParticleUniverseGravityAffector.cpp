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

#include "ParticleAffectors/ParticleUniverseGravityAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real GravityAffector::DEFAULT_GRAVITY = 1.0f;

	//-----------------------------------------------------------------------
	GravityAffector::GravityAffector(void) : 
		ParticleAffector(),
		mGravity(DEFAULT_GRAVITY)
	{
	}
	//-----------------------------------------------------------------------
	void GravityAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		GravityAffector* gravityAffector = static_cast<GravityAffector*>(affector);
		gravityAffector->mGravity = mGravity;
	}
	//-----------------------------------------------------------------------
	void GravityAffector::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Calculate the affectors' position so it is also safe to use mDerivedPosition.
		getDerivedPosition();
	}
	//-----------------------------------------------------------------------
	inline void GravityAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		 // Applied scaling in V1.3.1
		/** Applying Newton's law of universal gravitation.	*/
		Vector3 distance = mDerivedPosition - particle->position;
		Real length = distance.squaredLength();
		Real scaleVelocity = 1.0f;
		if (mParentTechnique)
		{
			scaleVelocity = mParentTechnique->getParticleSystemScaleVelocity();
		}
		if (length > 0 && mParentTechnique)
		{
			//Real force = (mGravity * particle->mass * mass) / length;
			Real force = (scaleVelocity * mGravity * particle->mass * mass) / length;
			particle->direction += force * distance * timeElapsed * _calculateAffectSpecialisationFactor(particle);
		}
	}
	//-----------------------------------------------------------------------
	Real GravityAffector::getGravity(void) const
	{
		return mGravity;
	}
	//-----------------------------------------------------------------------
	void GravityAffector::setGravity(Real gravity)
	{
		mGravity = gravity;
	}
}
