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

#include "ParticleAffectors/ParticleUniverseLineAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real LineAffector::DEFAULT_MAX_DEVIATION = 1.0f;
	const Real LineAffector::DEFAULT_TIME_STEP = 0.1f;
	const Vector3 LineAffector::DEFAULT_END(0, 0, 0);
	const Real LineAffector::DEFAULT_DRIFT = 0.0f;

	//-----------------------------------------------------------------------
	LineAffector::LineAffector(void) : 
		ParticleAffector(),
		mMaxDeviation(DEFAULT_MAX_DEVIATION),
		_mScaledMaxDeviation(1.0f),
		mEnd(DEFAULT_END),
		mTimeSinceLastUpdate(0.0f),
		mTimeStep(DEFAULT_TIME_STEP),
		mUpdate(true),
		mFirst(true),
		mDrift(DEFAULT_DRIFT),
		mOneMinusDrift(1.0f)
	{
	}
	//-----------------------------------------------------------------------
	Real LineAffector::getMaxDeviation(void) const
	{
		return mMaxDeviation;
	}
	//-----------------------------------------------------------------------
	void LineAffector::setMaxDeviation(Real maxDeviation)
	{
		mMaxDeviation = maxDeviation;
		_mScaledMaxDeviation = mMaxDeviation * _mAffectorScale.length();
	}
	//-----------------------------------------------------------------------
	const Vector3& LineAffector::getEnd(void) const
	{
		return mEnd;
	}
	//-----------------------------------------------------------------------
	void LineAffector::setEnd(const Vector3& end)
	{
		mEnd = end;
	}
	//-----------------------------------------------------------------------
	Real LineAffector::getTimeStep(void) const
	{
		return mTimeStep;
	}
	//-----------------------------------------------------------------------
	void LineAffector::setTimeStep(Real timeStep)
	{
		mTimeStep = timeStep;
	}
	//-----------------------------------------------------------------------
	Real LineAffector::getDrift(void) const
	{
		return mDrift;
	}
	//-----------------------------------------------------------------------
	void LineAffector::setDrift(Real drift)
	{
		mDrift = drift;
		mOneMinusDrift = 1.0f - drift;
	}
	//-----------------------------------------------------------------------
	void LineAffector::_notifyRescaled(const Vector3& scale)
	{
		ParticleAffector::_notifyRescaled(scale);
		_mScaledMaxDeviation = mMaxDeviation * scale.length();
	}
	//-----------------------------------------------------------------------
	void LineAffector::_firstParticle(ParticleTechnique* particleTechnique, 
		Particle* particle, 
		Real timeElapsed)
	{
		// The first particle should stay on its place
		mFirst = true;
	}
	//-----------------------------------------------------------------------
	void LineAffector::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		if (technique->getNumberOfEmittedParticles() > 0)
		{
			mTimeSinceLastUpdate += timeElapsed;
			while (mTimeSinceLastUpdate > mTimeStep)
			{
				mTimeSinceLastUpdate -= mTimeStep;
				mUpdate = true;
			}
		}
		mParentTechnique->getParentSystem()->rotationOffset(mEnd); // Always update
	}
	//-----------------------------------------------------------------------
	void LineAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		mParentTechnique->getParentSystem()->rotationOffset(particle->originalPosition); // Always update
		if (mUpdate && Math::UnitRandom() > 0.5 && !mFirst)
		{
			// Generate a random vector perpendicular on the line
			Vector3 perpendicular = mEnd.crossProduct(Vector3(Math::RangeRandom(-1, 1), 
				Math::RangeRandom(-1, 1), 
				Math::RangeRandom(-1, 1)));
			perpendicular.normalise();

			// Determine a random point near the line.
			Vector3 targetPosition = particle->originalPosition + _mScaledMaxDeviation * Math::UnitRandom() * perpendicular;

			/** Set the new position.
			@remarks
				This affector already takes rotational offset of the particle system into account. This means that there is no need
				to set the particle system to keep_local to 'true'. The reason is that this is a specialized affector that calculates
				a new particle position instead of a direction.
			*/
			particle->position = mDrift * targetPosition + mOneMinusDrift * particle->position;
			mParentTechnique->getParentSystem()->rotationOffset(particle->position);
		}
		mFirst = false;
	}
	//-----------------------------------------------------------------------
	void LineAffector::_postProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		mUpdate = false;
	}
	//-----------------------------------------------------------------------
	void LineAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		LineAffector* lineAffector = static_cast<LineAffector*>(affector);

		lineAffector->setMaxDeviation(mMaxDeviation);
		lineAffector->mEnd = mEnd;
		lineAffector->mTimeStep = mTimeStep;
		lineAffector->mDrift = mDrift;
		lineAffector->mOneMinusDrift = mOneMinusDrift;
	}
}
