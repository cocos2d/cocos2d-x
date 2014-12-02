/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_FLOCK_CENTER_AFFECTOR_H__
#define __PU_FLOCK_CENTER_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** A FlockCenteringAffector determines the center (position) of all particles and affects each particle to go towards that center.
    */
	class _ParticleUniverseExport FlockCenteringAffector : public ParticleAffector
	{
		protected:
			Vector3 mSum;
			Vector3 mAverage;
			Real mCount;

		public:
			FlockCenteringAffector(void) : 
				ParticleAffector(),
				mSum(Vector3::ZERO),
				mAverage(Vector3::ZERO),
				mCount(0.0f)
			{
			};
	        virtual ~FlockCenteringAffector(void) {};

			/** @copydoc ParticleAffector::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
	};

}
#endif
