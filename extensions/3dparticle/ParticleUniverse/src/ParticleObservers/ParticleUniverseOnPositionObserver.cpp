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

#include "ParticleObservers/ParticleUniverseOnPositionObserver.h"

namespace ParticleUniverse
{
	// Constants
	const Vector3 OnPositionObserver::DEFAULT_POSITION_THRESHOLD(0, 0, 0);

	//-----------------------------------------------------------------------
	OnPositionObserver::OnPositionObserver(void) : 
		ParticleObserver(),
		mPositionXThreshold(DEFAULT_POSITION_THRESHOLD.x),
		mPositionYThreshold(DEFAULT_POSITION_THRESHOLD.y),
		mPositionZThreshold(DEFAULT_POSITION_THRESHOLD.z),
		mComparePositionX(CO_LESS_THAN),
		mComparePositionY(CO_LESS_THAN),
		mComparePositionZ(CO_LESS_THAN),
		mPositionXThresholdSet(false),
		mPositionYThresholdSet(false),
		mPositionZThresholdSet(false)
	{
	}
	//-----------------------------------------------------------------------
	bool OnPositionObserver::_observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (!particle)
			return false;

		// Added scale in V1.3.1
		if (mPositionXThresholdSet && mComparePositionX == CO_LESS_THAN && particle->position.x < mPositionXThreshold * _mObserverScale.x)
			return true;
		if (mPositionXThresholdSet && mComparePositionX == CO_GREATER_THAN && particle->position.x > mPositionXThreshold * _mObserverScale.x)
			return true;
		if (mPositionXThresholdSet && mComparePositionX == CO_EQUALS && particle->position.x == mPositionXThreshold * _mObserverScale.x)
			return true;

		if (mPositionYThresholdSet && mComparePositionY == CO_LESS_THAN && particle->position.y < mPositionYThreshold * _mObserverScale.y)
			return true;
		if (mPositionYThresholdSet && mComparePositionY == CO_GREATER_THAN && particle->position.y > mPositionYThreshold * _mObserverScale.y)
			return true;
		if (mPositionYThresholdSet && mComparePositionY == CO_EQUALS && particle->position.y == mPositionYThreshold * _mObserverScale.y)
			return true;

		if (mPositionZThresholdSet && mComparePositionZ == CO_LESS_THAN && particle->position.z < mPositionZThreshold * _mObserverScale.z)
			return true;
		if (mPositionZThresholdSet && mComparePositionZ == CO_GREATER_THAN && particle->position.z > mPositionZThreshold * _mObserverScale.z)
			return true;
		if (mPositionZThresholdSet && mComparePositionZ == CO_EQUALS && particle->position.z == mPositionZThreshold * _mObserverScale.z)
			return true;

		return false;
	}
	//-----------------------------------------------------------------------
	void OnPositionObserver::copyAttributesTo(ParticleObserver* observer)
	{
		ParticleObserver::copyAttributesTo(observer);

		OnPositionObserver* onPositionObserver = static_cast<OnPositionObserver*>(observer);
		onPositionObserver->mPositionXThreshold = mPositionXThreshold;
		onPositionObserver->mPositionYThreshold = mPositionYThreshold;
		onPositionObserver->mPositionZThreshold = mPositionZThreshold;
		onPositionObserver->mComparePositionX = mComparePositionX;
		onPositionObserver->mComparePositionY = mComparePositionY;
		onPositionObserver->mComparePositionZ = mComparePositionZ;
		onPositionObserver->mPositionXThresholdSet = mPositionXThresholdSet;
		onPositionObserver->mPositionYThresholdSet = mPositionYThresholdSet;
		onPositionObserver->mPositionZThresholdSet = mPositionZThresholdSet;
	}

}
