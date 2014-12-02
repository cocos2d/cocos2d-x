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

#include "ParticleObservers/ParticleUniverseOnCountObserver.h"

namespace ParticleUniverse
{
	// Constants
	const uint OnCountObserver::DEFAULT_THRESHOLD = 0;
	const ComparisionOperator OnCountObserver::DEFAULT_COMPARE = CO_LESS_THAN;

	//-----------------------------------------------------------------------
	OnCountObserver::OnCountObserver(void) : ParticleObserver(),
		mCount(1),
		mThreshold(DEFAULT_THRESHOLD),
		mCompare(DEFAULT_COMPARE)
	{
	}
	//-----------------------------------------------------------------------
	void OnCountObserver::_notifyStart (void)
	{
		ParticleObserver::_notifyStart();

		// At a restart the counter must be reset again.
		mCount = 1;
	}
	//-----------------------------------------------------------------------
	bool OnCountObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (!particle)
			return false;

		if (!particle->hasEventFlags(Particle::PEF_EMITTED))
			return false;
		
		if (mCompare == CO_GREATER_THAN)
		{
			if (mCount > mThreshold)
			{
				return true;
			}
			else
			{
				mCount++;
				return false;
			}
		}
		else if (mCompare == CO_LESS_THAN)
		{
			if (mCount < mThreshold)
			{
				mCount++;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (mCount == mThreshold)
			{
				mCount++;
				return true;
			}
			else
			{
				mCount++;
				return false;
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void OnCountObserver::copyAttributesTo(ParticleObserver* observer)
	{
		ParticleObserver::copyAttributesTo(observer);

		OnCountObserver* onCountObserver = static_cast<OnCountObserver*>(observer);
		onCountObserver->mCount = mCount;
		onCountObserver->mThreshold = mThreshold;
		onCountObserver->mCompare = mCompare;
	}
}
