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

#include "ParticleEmitters/ParticleUniverseSphereSurfaceEmitter.h"

namespace ParticleUniverse
{
	// Constants
	const Real SphereSurfaceEmitter::DEFAULT_RADIUS = 10.0f;

	//-----------------------------------------------------------------------
	SphereSurfaceEmitter::SphereSurfaceEmitter(void) : 
		ParticleEmitter(),
		mRadius(DEFAULT_RADIUS),
		mRandomVector(Vector3::ZERO)
	{
	}
	//-----------------------------------------------------------------------
	const Real SphereSurfaceEmitter::getRadius(void) const
	{
		return mRadius;
	}
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::setRadius(const Real radius)
	{
		mRadius = radius;
	}
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::_initParticlePosition(Particle* particle)
	{
		// Generate a random unit vector to calculate a point on the sphere. This unit vector is
		// also used as direction vector if mAutoDirection has been set.
		mRandomVector = Vector3(Math::RangeRandom(-1, 1), 
			Math::RangeRandom(-1, 1),
			Math::RangeRandom(-1, 1));
		mRandomVector.normalise();
		ParticleSystem* sys = mParentTechnique->getParentSystem();
		if (sys)
		{
			particle->position = getDerivedPosition() + sys->getDerivedOrientation() * (_mEmitterScale * mRandomVector * mRadius);
		}
		else
		{
			particle->position = getDerivedPosition() + (_mEmitterScale * mRandomVector * mRadius);
		}
		particle->originalPosition = particle->position;
	}
	//-----------------------------------------------------------------------
    void SphereSurfaceEmitter::_initParticleDirection(Particle* particle)
    {
		if (mAutoDirection)
		{
			// The value of the direction vector that has been set does not have a meaning for
			// the sphere surface emitter.
			Radian angle;
			_generateAngle(angle);
			if (angle != Radian(0))
			{
				particle->direction = mRandomVector.randomDeviant(angle, mUpVector);
				particle->originalDirection = particle->direction;
			}
			else
			{
				particle->direction = mRandomVector;
				particle->originalDirection = particle->direction;
			}
		}
		else
		{
			// Use the standard way
			ParticleEmitter::_initParticleDirection(particle);
		}
    }
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);

		SphereSurfaceEmitter* sphereSurfaceEmitter = static_cast<SphereSurfaceEmitter*>(emitter);
		sphereSurfaceEmitter->mRadius = mRadius;
	}
}
