/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PLANE_COLLIDER_H__
#define __PU_PLANE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseCollider.h"
#include "ParticleUniversePlane.h"

namespace ParticleUniverse
{
	/** The PlaneCollider is a plane shape that collides with the particles. The PlaneCollider can only collide 
		with particles that are created within the same ParticleTechnique as where the PlaneCollider is registered.
    */
	class _ParticleUniverseExport PlaneCollider : public BaseCollider
	{
		public:
			// Constants
			static const Vector3 DEFAULT_NORMAL;

			PlaneCollider(void);
	        virtual ~PlaneCollider(void){};

			/** Returns the normal of the plane
			*/
			const Vector3 getNormal(void) const;

			/** Sets the normal of the plane
			*/
			void setNormal(const Vector3& normal);

			/** Notify that the Affector is rescaled.
	        */
			virtual void _notifyRescaled(const Vector3& scale);

			/** 
			*/
			void calculateDirectionAfterCollision(Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Vector3 mNormal;
			Vector3 mPredictedPosition;
			Plane mPlane;
	};

}
#endif
