/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_JET_AFFECTOR_H__
#define __PU_JET_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** Adds a non-linear boost to a particle.
    */
	class _ParticleUniverseExport JetAffector : public ParticleAffector
	{
		protected:
			Real mScaled;

			/** Dynamic attribute used to generate the velocity of a particle.
			*/
			DynamicAttribute* mDynAcceleration;

			/** Helper factory
			*/
			DynamicAttributeFactory mDynamicAttributeFactory;

		public:
			// Constants
			static const Real DEFAULT_ACCELERATION;

			JetAffector(void);
	        virtual ~JetAffector(void);

			/** 
	        */
			DynamicAttribute* getDynAcceleration(void) const {return mDynAcceleration;};
			void setDynAcceleration(DynamicAttribute* dynAcceleration);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
	};

}
#endif
