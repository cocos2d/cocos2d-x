/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCALE_AFFECTOR_H__
#define __PU_SCALE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Scales a particle. This can be a linear scale, but scaling that changes over time is possible.
    */
	class _ParticleUniverseExport ScaleAffector : public ParticleAffector
	{
		public:
			// Constants
			static const Real DEFAULT_X_SCALE;
			static const Real DEFAULT_Y_SCALE;
			static const Real DEFAULT_Z_SCALE;
			static const Real DEFAULT_XYZ_SCALE;

			ScaleAffector(void);
	        virtual ~ScaleAffector(void);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			DynamicAttribute* getDynScaleX(void) const {return mDynScaleX;};
			void setDynScaleX(DynamicAttribute* dynScaleX);
			void resetDynScaleX(bool resetToDefault = true);

			/** 
	        */
			DynamicAttribute* getDynScaleY(void) const {return mDynScaleY;};
			void setDynScaleY(DynamicAttribute* dynScaleY);
			void resetDynScaleY(bool resetToDefault = true);

			/** 
	        */
			DynamicAttribute* getDynScaleZ(void) const {return mDynScaleZ;};
			void setDynScaleZ(DynamicAttribute* dynScaleZ);
			void resetDynScaleZ(bool resetToDefault = true);

			/** 
	        */
			DynamicAttribute* getDynScaleXYZ(void) const {return mDynScaleXYZ;};
			void setDynScaleXYZ(DynamicAttribute* dynScaleXYZ);
			void resetDynScaleXYZ(bool resetToDefault = true);

			/** 
	        */
			bool isSinceStartSystem(void) const {return mSinceStartSystem;};
			void setSinceStartSystem(bool sinceStartSystem){mSinceStartSystem = sinceStartSystem;};

	protected:
			DynamicAttribute* mDynScaleX;
			DynamicAttribute* mDynScaleY;
			DynamicAttribute* mDynScaleZ;
			DynamicAttribute* mDynScaleXYZ;
			bool mDynScaleXSet;
			bool mDynScaleYSet;
			bool mDynScaleZSet;
			bool mDynScaleXYZSet;
			DynamicAttributeFactory mDynamicAttributeFactory;
			DynamicAttributeHelper mDynamicAttributeHelper;
			bool mSinceStartSystem;

			/** Returns the scale value for the dynamic Scale.
	        */
			Real _calculateScale(DynamicAttribute* dynScale, Particle* particle);

			Real mLatestTimeElapsed;
	};

}
#endif
