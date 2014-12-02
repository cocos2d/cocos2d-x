/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COLLISION_AVOIDANCE_AFFECTOR_H__
#define __PU_COLLISION_AVOIDANCE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** The CollisionAvoidanceAffector is used to prevent particles from colliding with each other.
	@remarks
		The current implementation doesn´t take avoidance of colliders (box, sphere, plane) into account (yet).
    */
	class _ParticleUniverseExport CollisionAvoidanceAffector : public ParticleAffector
	{
		public:
			// Constants
			static const Real DEFAULT_RADIUS;

			CollisionAvoidanceAffector(void);
	        virtual ~CollisionAvoidanceAffector(void){};

			/** Todo
			*/
			Real getRadius(void) const;

			/** Todo
			*/
			void setRadius(Real radius);

			/** @copydoc ParticleAffector::_prepare */
			virtual void _prepare(ParticleTechnique* particleTechnique);

			/** @copydoc ParticleAffector::_unprepare */
			virtual void _unprepare(ParticleTechnique* particleTechnique);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
		
		protected:
			Real mRadius;
	};

}
#endif
