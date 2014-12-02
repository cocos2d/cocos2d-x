/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCALE_VELOCITY_AFFECTOR_H__
#define __PU_SCALE_VELOCITY_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Scales the velocity of a particle. This can be a linear scale, but scaling that changes over time alos is possible.
    */
	class _ParticleUniverseExport ScaleVelocityAffector : public ParticleAffector
	{
		public:
			// Constants
			static const Real DEFAULT_VELOCITY_SCALE;

			ScaleVelocityAffector(void);
	        virtual ~ScaleVelocityAffector(void);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			DynamicAttribute* getDynScaleVelocity(void) const {return mDynScaleVelocity;};
			void setDynScaleVelocity(DynamicAttribute* dynScaleVelocity);
			void resetDynScaleVelocity(bool resetToDefault = true);

			/** 
	        */
			bool isSinceStartSystem(void) const {return mSinceStartSystem;};
			void setSinceStartSystem(bool sinceStartSystem){mSinceStartSystem = sinceStartSystem;};

			/** 
	        */
			bool isStopAtFlip(void) const {return mStopAtFlip;};
			void setStopAtFlip(bool stopAtFlip){mStopAtFlip = stopAtFlip;};

	protected:
			DynamicAttribute* mDynScaleVelocity;
			DynamicAttributeFactory mDynamicAttributeFactory;
			DynamicAttributeHelper mDynamicAttributeHelper;
			bool mSinceStartSystem;
			bool mStopAtFlip;
	};

}
#endif
