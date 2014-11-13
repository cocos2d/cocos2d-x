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

#include "ParticleAffectors/ParticleUniverseRandomiser.h"

namespace ParticleUniverse
{
	// Constants
	const Vector3 Randomiser::DEFAULT_MAX_DEVIATION(0, 0, 0);
	const Real Randomiser::DEFAULT_TIME_STEP = 0.0f;
	const bool Randomiser::DEFAULT_RANDOM_DIRECTION = true;

	//-----------------------------------------------------------------------
	Randomiser::Randomiser(void) : 
		ParticleAffector(),
		mMaxDeviationX(DEFAULT_MAX_DEVIATION.x),
		mMaxDeviationY(DEFAULT_MAX_DEVIATION.y),
		mMaxDeviationZ(DEFAULT_MAX_DEVIATION.z),
		mTimeSinceLastUpdate(0.0f),
		mTimeStep(DEFAULT_TIME_STEP),
		mUpdate(true),
		mRandomDirection(DEFAULT_RANDOM_DIRECTION)
	{
	}
	//-----------------------------------------------------------------------
	Real Randomiser::getMaxDeviationX(void) const
	{
		return mMaxDeviationX;
	}
	//-----------------------------------------------------------------------
	void Randomiser::setMaxDeviationX(Real maxDeviationX)
	{
		mMaxDeviationX = maxDeviationX;
	}
	//-----------------------------------------------------------------------
	Real Randomiser::getMaxDeviationY(void) const
	{
		return mMaxDeviationY;
	}
	//-----------------------------------------------------------------------
	void Randomiser::setMaxDeviationY(Real maxDeviationY)
	{
		mMaxDeviationY = maxDeviationY;
	}
	//-----------------------------------------------------------------------
	Real Randomiser::getMaxDeviationZ(void) const
	{
		return mMaxDeviationZ;
	}
	//-----------------------------------------------------------------------
	void Randomiser::setMaxDeviationZ(Real maxDeviationZ)
	{
		mMaxDeviationZ = maxDeviationZ;
	}
	//-----------------------------------------------------------------------
	Real Randomiser::getTimeStep(void) const
	{
		return mTimeStep;
	}
	//-----------------------------------------------------------------------
	void Randomiser::setTimeStep(Real timeStep)
	{
		mTimeStep = timeStep;
		mTimeSinceLastUpdate = timeStep;
	}
	//-----------------------------------------------------------------------
	bool Randomiser::isRandomDirection(void) const
	{
		return mRandomDirection;
	}
	//-----------------------------------------------------------------------
	void Randomiser::setRandomDirection(bool randomDirection)
	{
		mRandomDirection = randomDirection;
	}
	//-----------------------------------------------------------------------
	void Randomiser::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		if (technique->getNumberOfEmittedParticles() > 0)
		{
			mTimeSinceLastUpdate += timeElapsed;
			if (mTimeSinceLastUpdate > mTimeStep)
			{
				mTimeSinceLastUpdate -= mTimeStep;
				mUpdate = true;
			}
		}
	}
	//-----------------------------------------------------------------------
	void Randomiser::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (mUpdate)
		{
			if (mRandomDirection)
			{
				// Random direction: Change the direction after each update
				particle->direction += Vector3(Math::RangeRandom(-mMaxDeviationX, mMaxDeviationX),
					Math::RangeRandom(-mMaxDeviationY, mMaxDeviationY),
					Math::RangeRandom(-mMaxDeviationZ, mMaxDeviationZ));
			}
			else
			{
				// Explicitly check on 'freezed', because it passes the techniques' validation.
				if (particle->isFreezed())
					return;

				// Random position: Add the position deviation after each update
				particle->position += _mAffectorScale * Vector3(Math::RangeRandom(-mMaxDeviationX, mMaxDeviationX),
					Math::RangeRandom(-mMaxDeviationY, mMaxDeviationY),
					Math::RangeRandom(-mMaxDeviationZ, mMaxDeviationZ));
			}
		}
	}
	//-----------------------------------------------------------------------
	void Randomiser::_postProcessParticles(ParticleTechnique* technique, Real timeElapsed)
	{
		mUpdate = false;
	}
	//-----------------------------------------------------------------------
	void Randomiser::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		Randomiser* randomiser = static_cast<Randomiser*>(affector);
		randomiser->mMaxDeviationX = mMaxDeviationX;
		randomiser->mMaxDeviationY = mMaxDeviationY;
		randomiser->mMaxDeviationZ = mMaxDeviationZ;
		randomiser->setTimeStep(mTimeStep); // Also sets time since last update to appropriate value
		randomiser->mRandomDirection = mRandomDirection;
	}

}
