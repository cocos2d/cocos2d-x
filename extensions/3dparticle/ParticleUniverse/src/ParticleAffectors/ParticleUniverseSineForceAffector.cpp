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

#include "ParticleAffectors/ParticleUniverseSineForceAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real SineForceAffector::DEFAULT_FREQ_MIN = 1.0f;
	const Real SineForceAffector::DEFAULT_FREQ_MAX = 1.0f;

	//-----------------------------------------------------------------------
	SineForceAffector::SineForceAffector(void) : 
		BaseForceAffector(),
		mAngle(361),
		mFrequencyMin(DEFAULT_FREQ_MIN),
		mFrequencyMax(DEFAULT_FREQ_MAX),
		mFrequency(1.0f)
	{
	}
	//-----------------------------------------------------------------------
	void SineForceAffector::copyAttributesTo (ParticleAffector* affector)
	{
		BaseForceAffector::copyAttributesTo(affector);

		SineForceAffector* sineForceAffector = static_cast<SineForceAffector*>(affector);
		sineForceAffector->mFrequencyMin = mFrequencyMin;
		sineForceAffector->mFrequencyMax = mFrequencyMax;
		sineForceAffector->mFrequency = mFrequency;
		sineForceAffector->mAngle = mAngle;
	}
	//-----------------------------------------------------------------------
	void SineForceAffector::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Scale by time
		mAngle += mFrequency * timeElapsed;
		Real sineValue = Math::Sin(Radian(mAngle));
		mScaledVector = mForceVector * timeElapsed * sineValue;

		if (mAngle > Math::TWO_PI)
		{
			mAngle = 0.0f;

			if (mFrequencyMin != mFrequencyMax)
			{
				mFrequency = Math::RangeRandom(mFrequencyMin, mFrequencyMax);
			}
		}
	}
	//-----------------------------------------------------------------------
	const Real SineForceAffector::getFrequencyMin(void) const
	{
		return mFrequencyMin;
	}
	//-----------------------------------------------------------------------
	void SineForceAffector::setFrequencyMin(const Real frequencyMin)
	{
		mFrequencyMin = frequencyMin;
		if (frequencyMin > mFrequencyMax)
		{
			mFrequency = frequencyMin;
		}
	}
	//-----------------------------------------------------------------------
	const Real SineForceAffector::getFrequencyMax(void) const
	{
		return mFrequencyMax;
	}
	//-----------------------------------------------------------------------
	void SineForceAffector::setFrequencyMax(const Real frequencyMax)
	{
		mFrequencyMax = frequencyMax;
		mFrequency = frequencyMax;
	}
	//-----------------------------------------------------------------------
	void SineForceAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// Affect the direction
		if (mForceApplication == FA_ADD)
		{
			particle->direction += mScaledVector;
		}
		else
		{
			particle->direction = (particle->direction + mForceVector) / 2;
		}
	}

}
