/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_FOLLOWER_H__
#define __PU_PARTICLE_FOLLOWER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector makes particles follow its predecessor.
    */
	class _ParticleUniverseExport ParticleFollower : public ParticleAffector
	{
		public:
			// Constants
			static const Real DEFAULT_MAX_DISTANCE;
			static const Real DEFAULT_MIN_DISTANCE;

			ParticleFollower(void);
	        virtual ~ParticleFollower(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** Validate if first particle.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			Real getMaxDistance(void) const;
			void setMaxDistance(Real maxDistance);

			/** 
	        */
			Real getMinDistance(void) const;
			void setMinDistance(Real minDistance);

		protected:
			Real mMinDistance;
			Real mMaxDistance;
			Vector3 mPositionPreviousParticle;
			bool mFirst;
	};

}
#endif
