/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_INTERPARTICLE_COLLIDER_H__
#define __PU_INTERPARTICLE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseCollider.h"

namespace ParticleUniverse
{
	/** The InterParticleCollider is used to perform particle-particle collision.
    */
	class _ParticleUniverseExport InterParticleCollider : public BaseCollider
	{
		public:
			enum InterParticleCollisionResponse
			{
				IPCR_AVERAGE_VELOCITY,
				IPCR_ANGLE_BASED_VELOCITY
			};

			// Constants
			static const Real DEFAULT_ADJUSTMENT;
			static const InterParticleCollisionResponse DEFAULT_COLLISION_RESPONSE;

			InterParticleCollider(void);
	        virtual ~InterParticleCollider(void){};

			/** Todo
			*/
			Real getAdjustment(void) const;

			/** Todo
			*/
			void setAdjustment(Real adjustment);

			/** Todo
			*/
			InterParticleCollisionResponse getInterParticleCollisionResponse(void) const;

			/** Todo
			*/
			void setInterParticleCollisionResponse(InterParticleCollisionResponse interParticleCollisionResponse);

			/** @copydoc ParticleAffector::_prepare */
			virtual void _prepare(ParticleTechnique* particleTechnique);

			/** @copydoc ParticleAffector::_unprepare */
			virtual void _unprepare(ParticleTechnique* particleTechnique);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
		
		protected:
			Real mAdjustment;
			InterParticleCollisionResponse mInterParticleCollisionResponse;

			/** Todo
			*/
			bool _validateAndExecuteSphereCollision (Particle* particle1, Particle* particle2, Real timeElapsed);
	};

}
#endif
