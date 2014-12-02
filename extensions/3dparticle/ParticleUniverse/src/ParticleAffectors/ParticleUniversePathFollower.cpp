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

#include "ParticleAffectors/ParticleUniversePathFollower.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	void PathFollower::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);
		PathFollower* pathFollower = static_cast<PathFollower*>(affector);
		unsigned short numPoints = mSpline.getNumPoints();
		pathFollower->mSpline.clear();
		for (unsigned short i = 0; i < numPoints; ++i)
		{
			pathFollower->mSpline.addPoint(mSpline.getPoint(i));
		}
	}
	//-----------------------------------------------------------------------
	void PathFollower::addPoint(const Vector3& point)
	{
		mSpline.addPoint(point);
	}
	//-----------------------------------------------------------------------
	void PathFollower::clearPoints (void)
	{
		mSpline.clear();
	}
	//-----------------------------------------------------------------------
	void PathFollower::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (mSpline.getNumPoints() > 0)
		{
			// PU 1.4
			Real timeLeft = particle->totalTimeToLive - particle->timeToLive;
			Real timeFraction = timeLeft / particle->totalTimeToLive;
			Ogre::Real timeFractionPlusDelta = (timeLeft + timeElapsed ) / particle->totalTimeToLive;
			timeFractionPlusDelta = timeFractionPlusDelta < 1.0f ? timeFractionPlusDelta : 1.0f;
			particle->position += _mAffectorScale * (mSpline.interpolate(timeFractionPlusDelta) - mSpline.interpolate(timeFraction));
		}
	}
}
